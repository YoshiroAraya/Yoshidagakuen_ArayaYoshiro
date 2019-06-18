//=============================================================================
//
// ��Q���̏��� [obstacle.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "obstacle.h"
#include "input.h"
#include "camera.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define OBSTACLE_NAME		"data/MODEL/TOWADA_Class.x"			// ���f���̖��O

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH		g_pMeshObstacle		= NULL;			//���b�V�����ւ̃|�C���^
LPD3DXBUFFER	g_pBuffMatObstacle	= NULL;			// �}�e���A�����ւ̃|�C���^
DWORD			g_nNumMatObstacle	= 0;			// �}�e���A���̏��
OBSTACLE		g_aObstacle;

//=============================================================================
// ����������
//=============================================================================
void InitObstaclel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E�����̏����ݒ�
	g_aObstacle.pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aObstacle.posOld		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aObstacle.rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aObstacle.bUse		= true;
	g_aObstacle.nLife		= 20;
	g_aObstacle.nLifeMAX	= 20;
	g_aObstacle.vtxMin		= D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);			// �ŏ��l�̏ꍇ�͑��߂ɐ��l�������i��r�̂���)
	g_aObstacle.vtxMax		= D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		// �ő�l�̏ꍇ�͏��Ȃ߂ɐ��l�������i��r�̂���)

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(OBSTACLE_NAME, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObstacle, NULL, &g_nNumMatObstacle, &g_pMeshObstacle);

	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// ���_���̎擾
	nNumVtx = g_pMeshObstacle->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle->GetFVF());

	// ���_�o�b�t�@�����b�N
	g_pMeshObstacle->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			// ���_���W�̑��

		if (vtx.x < g_aObstacle.vtxMin.x)
		{
			g_aObstacle.vtxMin.x = vtx.x;
		}
		if (vtx.y < g_aObstacle.vtxMin.y)
		{
			g_aObstacle.vtxMin.y = vtx.y;
		}
		if (vtx.z < g_aObstacle.vtxMin.z)
		{
			g_aObstacle.vtxMin.z = vtx.z;
		}
		if (vtx.x > g_aObstacle.vtxMax.x)
		{
			 g_aObstacle.vtxMax.x = vtx.x;
		}
		if (vtx.y > g_aObstacle.vtxMax.y)
		{
			g_aObstacle.vtxMax.y = vtx.y;
		}
		if (vtx.z > g_aObstacle.vtxMax.z)
		{
			g_aObstacle.vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;			// �T�C�Y���̃|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pMeshObstacle->UnlockVertexBuffer();
}

//=============================================================================
// �I������
//=============================================================================
void UninitObstaclel(void)
{
	// ���b�V���̊J��
	if (g_pMeshObstacle != NULL)
	{
		g_pMeshObstacle->Release();
		g_pMeshObstacle = NULL;
	}

	// �}�e���A���̊J��
	if (g_pBuffMatObstacle != NULL)
	{
		g_pBuffMatObstacle->Release();
		g_pBuffMatObstacle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObstaclel(void)
{
	FADE fade;
	fade = GetFade();

	if (g_aObstacle.bUse == true)
	{
		switch (g_aObstacle.ObjectState)
		{
		case OBJECTSTATE_NORMAL:
			break;
		case OBJECTSTATE_DAMAGE:
			g_aObstacle.nCunterState--;
			if (g_aObstacle.nCunterState <= 0)
			{
				g_aObstacle.ObjectState = OBJECTSTATE_NORMAL;
			}
			break;
		case OBJECTSTATE_DEATH:
			g_aObstacle.nCunterState--;
			return;
			break;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObstaclel(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;						// �}�e���A���f�[�^�ւ̃|�C���^

	if (g_aObstacle.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aObstacle.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle.rot.y, g_aObstacle.rot.x, g_aObstacle.rot.z);
		D3DXMatrixMultiply(&g_aObstacle.mtxWorld, &g_aObstacle.mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aObstacle.pos.x, g_aObstacle.pos.y, g_aObstacle.pos.z);
		D3DXMatrixMultiply(&g_aObstacle.mtxWorld, &g_aObstacle.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aObstacle.mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatObstacle->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatObstacle; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_pMeshObstacle->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// �v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CollisionObstaclel_Player(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	bool bCollision = false;

	if (g_aObstacle.bUse == true)
	{
		if (pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x
			&& pPos->y + (pVtxMax->y +15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y
			&& pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
		{
			if (pPosOld->x + pVtxMax->z <= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x)
			{// �E���炫���Ƃ�
				bCollision = true;
				pPos->x = pPosOld->x;
			}
			else if (pPosOld->x + pVtxMax->z >= g_aObstacle.vtxMax.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x)
			{// �����炫���Ƃ�
				bCollision = true;
				pPos->x = pPosOld->x;
			}
			if (pPosOld->z + pVtxMax->z <= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z)
			{// �����炫���Ƃ�
				bCollision = true;
				pPos->z = pPosOld->z;
			}
			else if (pPosOld->z - pVtxMax->z >= g_aObstacle.vtxMax.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
			{// ��O���炫���Ƃ�
				bCollision = true;
				pPos->z = pPosOld->z;
			}
			if (pPosOld->y + (pVtxMin->y + 10.0f) >= g_aObstacle.vtxMax.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y)
			{// �ォ�炫���Ƃ�
				bCollision = true;
				pPos->y = pPosOld->y;
			}
			else if (pPosOld->y + (pVtxMax->y + 15.0f) <= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMax->y + 15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y)
			{// �����炫���Ƃ�
				bCollision = true;
				pPos->y = pPosOld->y;
			}
		}
	}
	return bCollision;
}

//=============================================================================
// �G�l�~�[�Ƃ̓����蔻��
//=============================================================================
bool CollisionObstaclel_Enemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy)
{
	bool bCollision = false;

	Enemy *g_Enemy;
	g_Enemy	= GetEnemy();

	if (g_aObstacle.bUse == true)
	{
		if (pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x
			&& pPos->y + (pVtxMax->y + 15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y
			&& pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
		{
			if (pPosOld->x + pVtxMax->z <= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x)
			{// �E���炫���Ƃ�
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
			}
			else if (pPosOld->x + pVtxMax->z >= g_aObstacle.vtxMax.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x)
			{// �����炫���Ƃ�
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
			}
			if (pPosOld->z + pVtxMax->z <= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z)
			{// �����炫���Ƃ�
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
			}
			else if (pPosOld->z - pVtxMax->z >= g_aObstacle.vtxMax.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
			{// ��O���炫���Ƃ�
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
			}
			if (pPosOld->y + (pVtxMin->y + 10.0f) >= g_aObstacle.vtxMax.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y)
			{// �ォ�炫���Ƃ�
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
			}
			else if (pPosOld->y + (pVtxMax->y + 15.0f) <= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMax->y + 15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y)
			{// �����炫���Ƃ�
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
			}
			HitObstaclel(1);
		}
	}
	return bCollision;
}

//=============================================================================
// �_���[�W����
//=============================================================================
void HitObstaclel(int nDamage)
{
	g_aObstacle.nLife -= nDamage;
	if (g_aObstacle.nLife <= 0)
	{
		SetExplosion(g_aObstacle.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aObstacle.bUse = false;
		g_aObstacle.ObjectState = OBJECTSTATE_DEATH;
		SetGameState(GAMESTATE_OVER);
		g_aObstacle.nCunterState = 60.0f;
	}
	else
	{
		g_aObstacle.ObjectState = OBJECTSTATE_DAMAGE;
		g_aObstacle.nCunterState = 1.15f;
	}
}

//=============================================================================
// �I�u�W�F�N�g�̎擾
//=============================================================================
OBSTACLE *GetObstaclel(void)
{
	return &g_aObstacle;
}