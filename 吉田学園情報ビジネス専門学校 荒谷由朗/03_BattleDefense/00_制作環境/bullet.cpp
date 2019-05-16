//=============================================================================
//
// �r���{�[�h���� [Bullet.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "bullet.h"
//#include "shadow.h"
#include "player.h"
#include "explosion.h"
#include "obstacle.h"
#include "enemy.h"
#include "PlayerLife.h"
#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BULLET				(128)								// �ǂ̍ő吔
#define BULLET_TEXTURENAME		"data/TEXTURE/bullet000.png"		// �e�N�X�`���̖��O

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME, &g_pTextureBullet);

	// ���_���̍쐬
	MakeVertexBullet(pDevice);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// �e�N�X�`���̊J��;
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��;
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_3D*pVtx;			//���_���ւ̃|�C���^
	OBSTACLE *g_aObstacle;
	g_aObstacle = GetObstaclel();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//�e���g�p����Ă���

			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//SetPositionShadow(g_aBullet[nCntBullet].nIdyShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));

				pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�̈ʒu���ړ�
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

				//���_�ݒ�
				//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
				//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//SetPositionShadow(g_aBullet[nCntBullet].nIdyShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));

				pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�̈ʒu���ړ�
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

				//���_�ݒ�
				//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 0.0f, g_aBullet[nCntBullet].pos.z - 10);
				//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 0.0f, g_aBullet[nCntBullet].pos.z - 10);
				//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 0.0f, g_aBullet[nCntBullet].pos.z + 10);
				//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 0.0f, g_aBullet[nCntBullet].pos.z + 10);

			}
			//if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT
			//	|| g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH
			//	|| g_aBullet[nCntBullet].pos.z < 0 || g_aBullet[nCntBullet].pos.z > SCREEN_WIDTH)
			//{
			//	g_aBullet[nCntBullet].bUse = false;			//�g�p����ĂȂ���Ԃɂ���
			//}


			//SetPositionShadow(g_aBullet[nCntBullet].nIdyShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));
			////SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 10);

			//// �������v�Z����
			//g_aBullet[nCntBullet].posAngle = g_aBullet[nCntBullet].posDest - g_aBullet[nCntBullet].pos * 2.0f;		// ���� = �ړI - ����

			//if (g_aBullet[nCntBullet].posAngle.x > D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.x -= D3DX_PI * 2;
			//}
			//if (g_aBullet[nCntBullet].posAngle.x < -D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.x += D3DX_PI * 2;
			//}

			//if (g_aBullet[nCntBullet].posAngle.y > D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.y -= D3DX_PI * 2;
			//}
			//if (g_aBullet[nCntBullet].posAngle.y < -D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.y += D3DX_PI * 2;
			//}

			//if (g_aBullet[nCntBullet].posAngle.z > D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.z -= D3DX_PI * 2;
			//}
			//if (g_aBullet[nCntBullet].posAngle.z < -D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.z += D3DX_PI * 2;
			//}

			//g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posAngle * 0.002f;

			//// �X�V
			//if (g_aBullet[nCntBullet].pos >= g_aBullet[nCntBullet].posAngle)
			//{
			//	g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posAngle * 0.002f;
			//}
			//if (g_aBullet[nCntBullet].pos <= g_aBullet[nCntBullet].posAngle)
			//{
			//	g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posAngle * 0.002f;
			//}
			if (g_aBullet[nCntBullet].nLife < 0)
			{
				//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		// ���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffBullet->Unlock();

		g_aBullet[nCntBullet].nLife--;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

		// �r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &g_aBullet[nCntBullet].mtxView);

		// �J�����̋t�s���ݒ�
		g_aBullet[nCntBullet].mtxWorld._11 = g_aBullet[nCntBullet].mtxView._11;
		g_aBullet[nCntBullet].mtxWorld._12 = g_aBullet[nCntBullet].mtxView._21;
		g_aBullet[nCntBullet].mtxWorld._13 = g_aBullet[nCntBullet].mtxView._31;
		g_aBullet[nCntBullet].mtxWorld._21 = g_aBullet[nCntBullet].mtxView._12;
		g_aBullet[nCntBullet].mtxWorld._22 = g_aBullet[nCntBullet].mtxView._22;
		g_aBullet[nCntBullet].mtxWorld._23 = g_aBullet[nCntBullet].mtxView._32;
		g_aBullet[nCntBullet].mtxWorld._31 = g_aBullet[nCntBullet].mtxView._13;
		g_aBullet[nCntBullet].mtxWorld._32 = g_aBullet[nCntBullet].mtxView._23;
		g_aBullet[nCntBullet].mtxWorld._33 = g_aBullet[nCntBullet].mtxView._33;

		// ��]�𔽉f
		//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBullet[nCntBullet].rot.y, g_aBullet[nCntBullet].rot.x, g_aBullet[nCntBullet].rot.z);
		//D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 10.0f, 0.0f);		// ���_���W(X���W,Y���W)
		pVtx[1].pos = D3DXVECTOR3(5.0f, 10.0f, 0.0f);		// ���_���W(X���W,Y���W)
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);		// ���_���W(X���W,Y���W)
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);		// ���_���W(X���W,Y���W)

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j

		pVtx += 4;									// ���W��4���i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nLife, BULLETTYPE type)
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;
			//g_aBullet[nCntBullet].nIdyShadow = SetShadow(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// �e�̓����蔻��
//=============================================================================
bool CollisionPlayerBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy)
{
	bool bCollision = false;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
		{
			if (g_aBullet[nCntBullet].bUse == true)
			{
				if (pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x
					&& pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y
					&& pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
				{
					if (pPosOld->x + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x)
					{// �E���炫���Ƃ�
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					else if (pPosOld->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x)
					{// �����炫���Ƃ�
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					if (pPosOld->z + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z)
					{// �����炫���Ƃ�
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					else if (pPosOld->z - pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
					{// ��O���炫���Ƃ�
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					if (pPosOld->y + (pVtxMin->y) >= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y)
					{// �ォ�炫���Ƃ�
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					else if (pPosOld->y + (pVtxMax->y) <= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y)
					{// �����炫���Ƃ�
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
					}
					PlaySound(SOUND_LABEL_SE_PLEYERDAMEZ);
					g_aBullet[nCntBullet].bUse = false;
					HitEnemy(nNumEnemy, 1,0);
				}
			}
		}
	}
	return bCollision;
}
bool CollisionEnemyBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	bool bCollision = false;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
		{
			if (g_aBullet[nCntBullet].bUse == true)
			{
				if (pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x
					&& pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y
					&& pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
				{
					if (pPosOld->x + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x)
					{// �E���炫���Ƃ�
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					else if (pPosOld->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x)
					{// �����炫���Ƃ�
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					if (pPosOld->z + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z)
					{// �����炫���Ƃ�
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					else if (pPosOld->z - pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
					{// ��O���炫���Ƃ�
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					if (pPosOld->y + (pVtxMin->y) >= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y)
					{// �ォ�炫���Ƃ�
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "�G���[", NULL, MB_YESNO);
					}
					else if (pPosOld->y + (pVtxMax->y) <= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y)
					{// �����炫���Ƃ�
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
		}
	}
	return bCollision;
}