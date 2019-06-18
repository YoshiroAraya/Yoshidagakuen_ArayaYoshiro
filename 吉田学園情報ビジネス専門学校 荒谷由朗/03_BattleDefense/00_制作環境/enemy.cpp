//=============================================================================
//
// ���f������ [player.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "enemy.h"
#include "txt.h"
#include "obstacle.h"
#include "bullet.h"
#include "input.h"
#include "game.h"
#include "score.h"
#include "life.h"
#include "player.h"
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMY_NAME			"data/MODEL/monkey_head.x"				// ���f���̖��O
#define ENEMY_UV_NAME		"data/TEXTURE/UV/kuroto_head_UV.png"	// ���f��UV�̖��O

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
ENEMYSTATE	g_EnemyState = ENEMEYSTATE_NEUTRAL;		// �v���C���[�̏��
ENEMYSTATE	g_EnemyStateNow = ENEMEYSTATE_NEUTRAL;
DWORD		g_nNumMatModel_Enemy = 0;				// �}�e���A�����̐�
Enemy		g_aEnemy[MAX_ENEMY];					// �G�̏��
int			g_nNumEnemy;							// �G�̑���
int			g_MAX_ENEMY;							// �G�̑���

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_MAX_ENEMY = 0;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// �ʒu�E�����̏����ݒ�
		g_aEnemy[nCntEnemy].Pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].Rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].RotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].fAngle		= 0.0f;
		g_aEnemy[nCntEnemy].nLife		= 1;
		g_aEnemy[nCntEnemy].bUse		= false;
		g_aEnemy[nCntEnemy].vtxMin		= D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);			// �ŏ��l�̏ꍇ�͑��߂ɐ��l�������i��r�̂���)
		g_aEnemy[nCntEnemy].vtxMax		= D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		// �ő�l�̏ꍇ�͏��Ȃ߂ɐ��l�������i��r�̂���)
		g_aEnemy[nCntEnemy].MAX_PARTS	= 1;

		// �t�@�C���̓ǂݍ���
		for (int nCntFile = 0; nCntFile < g_aEnemy[nCntEnemy].MAX_PARTS; nCntFile++)
		{
			D3DXLoadMeshFromX(ENEMY_NAME, D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aEnemy[nCntEnemy].aModel[nCntFile].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[nCntFile].nNumMat, &g_aEnemy[nCntEnemy].aModel[nCntFile].pMash);
			D3DXCreateTextureFromFile(pDevice, ENEMY_UV_NAME, &g_aEnemy[nCntEnemy].aModel[nCntFile].pTexture);
		}

		int nNumVtx;		// ���_��
		DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

		// ���_���̎擾
		nNumVtx = g_aEnemy[nCntEnemy].aModel[0].pMash->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy[nCntEnemy].aModel[0].pMash->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_aEnemy[nCntEnemy].aModel[0].pMash->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			// ���_���W�̑��

			if (vtx.x < g_aEnemy[nCntEnemy].vtxMin.x)
			{
				g_aEnemy[nCntEnemy].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_aEnemy[nCntEnemy].vtxMin.y)
			{
				g_aEnemy[nCntEnemy].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_aEnemy[nCntEnemy].vtxMin.z)
			{
				g_aEnemy[nCntEnemy].vtxMin.z = vtx.z;
			}
			if (vtx.x > g_aEnemy[nCntEnemy].vtxMax.x)
			{
				g_aEnemy[nCntEnemy].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_aEnemy[nCntEnemy].vtxMax.y)
			{
				g_aEnemy[nCntEnemy].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_aEnemy[nCntEnemy].vtxMax.z)
			{
				g_aEnemy[nCntEnemy].vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;			// �T�C�Y���̃|�C���^��i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		g_aEnemy[nCntEnemy].aModel[0].pMash->UnlockVertexBuffer();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// ���b�V���̔j��
		if (g_aEnemy[nCntEnemy].aModel[0].pMash != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pMash->Release();
			g_aEnemy[nCntEnemy].aModel[0].pMash = NULL;
		}
		// ���_�o�b�t�@�̔j��
		if (g_aEnemy[nCntEnemy].aModel[0].pBuffMat != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat->Release();
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	OBSTACLE *g_aObstacle;
	g_aObstacle = GetObstaclel();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			float fAngle;

			g_aEnemy[nCntEnemy].PosOld = g_aEnemy[nCntEnemy].Pos;
			fAngle = atan2f(g_aObstacle->pos.x - g_aEnemy[nCntEnemy].Pos.x, g_aObstacle->pos.z - g_aEnemy[nCntEnemy].Pos.z) + D3DX_PI;

			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}
			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI* 2;
			}

			g_aEnemy[nCntEnemy].Rot.y = fAngle;

			// �e�L�X�g�f�[�^������W�����擾����
			g_aEnemy[nCntEnemy].PosDest = g_aObstacle->pos;

			// �������v�Z����
			g_aEnemy[nCntEnemy].fPosAngle.x = g_aEnemy[nCntEnemy].PosDest.x - g_aEnemy[nCntEnemy].Pos.x;			// ���� = �ړI - ����
			g_aEnemy[nCntEnemy].fPosAngle.y = g_aEnemy[nCntEnemy].PosDest.y - g_aEnemy[nCntEnemy].Pos.y + 20.0f;	// ���� = �ړI - ����
			g_aEnemy[nCntEnemy].fPosAngle.z = g_aEnemy[nCntEnemy].PosDest.z - g_aEnemy[nCntEnemy].Pos.z;			// ���� = �ړI - ����

			g_aEnemy[nCntEnemy].Pos.x += g_aEnemy[nCntEnemy].fPosAngle.x * 0.00125f;
			g_aEnemy[nCntEnemy].Pos.y += g_aEnemy[nCntEnemy].fPosAngle.y * 0.00125f;
			g_aEnemy[nCntEnemy].Pos.z += g_aEnemy[nCntEnemy].fPosAngle.z * 0.00125f;

			CollisionPlayerBULLET(&g_aEnemy[nCntEnemy].Pos, &g_aEnemy[nCntEnemy].PosOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].vtxMin, &g_aEnemy[nCntEnemy].vtxMax, nCntEnemy);
			CollisionObstaclel_Enemy(&g_aEnemy[nCntEnemy].Pos, &g_aEnemy[nCntEnemy].PosOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].vtxMin, &g_aEnemy[nCntEnemy].vtxMax, nCntEnemy);

			if (rand() % 400 == 0)
			{
				// �e�̐ݒ�
				D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);

				// �v���C���[�̎擾
				Player *g_aPlayer;
				g_aPlayer = GetPlayer();

				float fAngleXY, fAngleZ;

				fAngleXY = atan2f(g_aPlayer->pos.x - g_aEnemy[nCntEnemy].Pos.x, g_aPlayer->pos.y - g_aEnemy[nCntEnemy].Pos.y);
				fAngleZ = atan2f(g_aPlayer->pos.x - g_aEnemy[nCntEnemy].Pos.x, g_aPlayer->pos.z - g_aEnemy[nCntEnemy].Pos.z);

				BulletMove.x = sinf(fAngleXY) * 5.0f;
				BulletMove.y = cosf(fAngleXY) * 5.0f;
				BulletMove.z = cosf(fAngleZ) * 5.0f;

				SetBullet(g_aEnemy[nCntEnemy].Pos, BulletMove, g_aEnemy[nCntEnemy].Rot, 100, BULLETTYPE_ENEMY);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			LPDIRECT3DDEVICE9	pDevice = GetDevice();	// �f�o�C�X�̎擾
			D3DXMATRIX			mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
			D3DMATERIAL9		matDef;					// ���݂̃}�e���A��
			D3DXMATERIAL		*pMat;					// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATRIX			mtxParent;				// �e�q�֌W�}�g���b�N�X

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEnemy[nCntEnemy].Rot.y, g_aEnemy[nCntEnemy].Rot.x, g_aEnemy[nCntEnemy].Rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aEnemy[nCntEnemy].Pos.x, g_aEnemy[nCntEnemy].Pos.y, g_aEnemy[nCntEnemy].Pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			for (int nCntParts = 0; nCntParts < g_aEnemy[nCntEnemy].MAX_PARTS; nCntParts++)
			{
				if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == -1)
				{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 0)
				{// ��(�E)�̎��A�r(�E)�̃}�g���b�N�X�ɓ����
					mtxParent = g_aEnemy[nCntEnemy].aModel[0].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 1)
				{// ��(�E)�̎��A�r(�E)�̃}�g���b�N�X�ɓ����
					mtxParent = g_aEnemy[nCntEnemy].aModel[1].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 8)
				{// ��(�E)�̎��A�r(�E)�̃}�g���b�N�X�ɓ����
					mtxParent = g_aEnemy[nCntEnemy].aModel[8].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 5)
				{// ��(�E)�̎��A�r(�E)�̃}�g���b�N�X�ɓ����
					mtxParent = g_aEnemy[nCntEnemy].aModel[5].mtxWorld;
				}

				else
				{// ���A�r(���E)�A�r(���E)�̎��A�̂̃}�g���b�N�X�ɓ����
					mtxParent = g_aEnemy[nCntEnemy].aModel[nCntParts - 1].mtxWorld;
				}
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aEnemy[nCntEnemy].aModel[nCntParts].rot.y, g_aEnemy[nCntEnemy].aModel[nCntParts].rot.x, g_aEnemy[nCntEnemy].aModel[nCntParts].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans,
					g_aEnemy[nCntEnemy].aModel[nCntParts].pos.x, g_aEnemy[nCntEnemy].aModel[nCntParts].pos.y, g_aEnemy[nCntEnemy].aModel[nCntParts].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &mtxTrans);

				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld);

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntParts].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntParts].nNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice->SetTexture(0, g_aEnemy[nCntEnemy].aModel[nCntParts].pTexture);
					//���f��(�p�[�c)�̕`��
					g_aEnemy[nCntEnemy].aModel[nCntParts].pMash->DrawSubset(nCntMat);
				}
				//�}�e���A����Ԃ�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].Pos		= pos;
			g_aEnemy[nCntEnemy].bUse	= true;
			g_MAX_ENEMY++;	// �G�̑��������Z
			break;
		}
	}
}

//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nNumEnemy, int nDamage ,int typ)
{
	g_aEnemy[nNumEnemy].nLife -= nDamage;

	if (g_aEnemy[nNumEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nNumEnemy].Pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aEnemy[nNumEnemy].bUse = false;
		g_aEnemy[nNumEnemy].EnemyState = ENEMEYSTATE_DEATH;
		g_MAX_ENEMY--;
		if (typ == 0)
		{
			AddScore(200);
		}
	}
	else
	{
		g_aEnemy[nNumEnemy].EnemyState = ENEMEYSTATE_DAMAGE;
	}
}

//=============================================================================
// �G�̏�Ԃ̐ݒ�
//=============================================================================
void SetEnemyState(ENEMYSTATE state)
{
	g_EnemyState = state;
}

//=============================================================================
// �G�̏�Ԃ̎擾
//=============================================================================
ENEMYSTATE GetEnemyState(void)
{
	return g_EnemyState;
}

//=============================================================================
// �G�̏�Ԃ̎擾(����)
//=============================================================================
ENEMYSTATE GetEnemyStateNow(void)
{
	return g_EnemyStateNow;
}
//=============================================================================
// �G�̏��̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}