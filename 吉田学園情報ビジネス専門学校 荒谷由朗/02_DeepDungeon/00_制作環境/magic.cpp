//=============================================================================
//
// ���@�U������ [magic.cpp]
// Author : komatsu keisuke
//
//=============================================================================
#include "magic.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "particle.h"
#include "enemy.h"
#include "SencerCol.h"
#include "enemy0.h"

#include "enemy1.h"
#include "enemy2.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAGIC_TEXTURENAME	"data/TEXTURE/bullet000.png"	//�\������t�@�C���̖��O
#define MAX_MAGIC			(256)							//���@�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureMagic = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagic = NULL;		//���_�o�b�t�@�ւ̃|�C���^
BULLET g_aMagic[MAX_MAGIC];							//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitMagic(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_3D *pVtx;

	for (int nCntMagic = 0; nCntMagic < MAX_MAGIC; nCntMagic++)
	{ // �e�̏�����
		g_aMagic[nCntMagic].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagic[nCntMagic].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagic[nCntMagic].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagic[nCntMagic].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagic[nCntMagic].nLife = 0;
		g_aMagic[nCntMagic].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MAGIC_TEXTURENAME, &g_pTextureMagic);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MAGIC,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMagic,
		NULL);

	g_pVtxBuffMagic->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�̃��b�N

	for (int nCntMagic = 0; nCntMagic < MAX_MAGIC; nCntMagic++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-8.0f, 8.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(8.0f, 8.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-8.0f, -8.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(8.0f, -8.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.6f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.6f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.6f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.6f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffMagic->Unlock();	//���_�o�b�t�@�̃A�����b�N
}

//=============================================================================
// �I������
//=============================================================================
void UninitMagic(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMagic != NULL)
	{
		g_pTextureMagic->Release();
		g_pTextureMagic = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMagic != NULL)
	{
		g_pVtxBuffMagic->Release();
		g_pVtxBuffMagic = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMagic(void)
{
	ENEMY *pEnemy;
	pEnemy = GetEnemy();


	ENEMY_0 *pEnemy0;
	pEnemy0 = GetEnemy_0();

	ENEMY_1 *pEnemy1;
	pEnemy1 = GetEnemy_1();


	ENEMY_2 *pEnemy2;
	pEnemy2 = GetEnemy_2();

	for (int nCntMagic = 0; nCntMagic < MAX_MAGIC; nCntMagic++)
	{//�e���ړ�������
		if (g_aMagic[nCntMagic].bUse == true)
		{
			g_aMagic[nCntMagic].posOld = g_aMagic[nCntMagic].pos;
			g_aMagic[nCntMagic].pos += g_aMagic[nCntMagic].move;
			g_aMagic[nCntMagic].nLife--;

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++, pEnemy0++, pEnemy1++, pEnemy2++)
			{
				if (CollisionSencer_Magic(&g_aMagic[nCntMagic].pos, nCntEnemy) == true)
				{
					g_aMagic[nCntMagic].bUse = false;
				}

				if (CollisionSencer_Magic_Boss(&g_aMagic[nCntMagic].pos) == true)
				{
					g_aMagic[nCntMagic].bUse = false;
				}

				if (CollisionSencer_L_Magic(&g_aMagic[nCntMagic].pos, nCntEnemy) == true)
				{
					g_aMagic[nCntMagic].bUse = false;
				}

				if (CollisionSencer_L_Magic_Boss(&g_aMagic[nCntMagic].pos) == true)
				{
					g_aMagic[nCntMagic].bUse = false;
				}
			}

			if (g_aMagic[nCntMagic].nType == 0)
			{
				SetParticle(g_aMagic[nCntMagic].pos, 20, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.6f), PARTICLETYPE_BULLET);
				SetParticle(g_aMagic[nCntMagic].pos, 20, D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.6f), PARTICLETYPE_BULLET);
			}

			if (g_aMagic[nCntMagic].nType == 1)
			{
				SetParticle(g_aMagic[nCntMagic].pos, 20, D3DXCOLOR(0.6f, 0.0f, 0.8f, 0.6f), PARTICLETYPE_BULLET);
				SetParticle(g_aMagic[nCntMagic].pos, 20, D3DXCOLOR(1.0f, 0.0f, 0.9f, 0.6f), PARTICLETYPE_BULLET);
			}
			if (g_aMagic[nCntMagic].nLife < 0)
			{
				g_aMagic[nCntMagic].bUse = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMagic(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntMagic = 0; nCntMagic < MAX_MAGIC; nCntMagic++)
	{
		if (g_aMagic[nCntMagic].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMagic[nCntMagic].mtxWorldMagic);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s���ݒ�
			g_aMagic[nCntMagic].mtxWorldMagic._11 = mtxView._11;
			g_aMagic[nCntMagic].mtxWorldMagic._12 = mtxView._21;
			g_aMagic[nCntMagic].mtxWorldMagic._13 = mtxView._31;
			g_aMagic[nCntMagic].mtxWorldMagic._21 = mtxView._12;
			g_aMagic[nCntMagic].mtxWorldMagic._22 = mtxView._22;
			g_aMagic[nCntMagic].mtxWorldMagic._23 = mtxView._32;
			g_aMagic[nCntMagic].mtxWorldMagic._31 = mtxView._13;
			g_aMagic[nCntMagic].mtxWorldMagic._32 = mtxView._23;
			g_aMagic[nCntMagic].mtxWorldMagic._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMagic[nCntMagic].pos.x, g_aMagic[nCntMagic].pos.y, g_aMagic[nCntMagic].pos.z);
			D3DXMatrixMultiply(&g_aMagic[nCntMagic].mtxWorldMagic, &g_aMagic[nCntMagic].mtxWorldMagic, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMagic[nCntMagic].mtxWorldMagic);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMagic, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			if (g_aMagic[nCntMagic].bUse == true)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureMagic);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMagic * 4, 2);
			}
		}
	}

	//�A���t�@�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���@�̐ݒ�
//=============================================================================
void SetMagic(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife, int nType)
{
	for (int nCntMagic = 0; nCntMagic < MAX_MAGIC; nCntMagic++)
	{
		if (g_aMagic[nCntMagic].bUse == false)
		{
			g_aMagic[nCntMagic].pos = pos;
			g_aMagic[nCntMagic].rot = rot;
			g_aMagic[nCntMagic].move = move;
			g_aMagic[nCntMagic].nLife = nLife;
			g_aMagic[nCntMagic].nType = nType;
			g_aMagic[nCntMagic].bUse = true;

			break;
		}
	}
}

void Set_L_Magic(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife, int nType)
{
	for (int nCntMagic = 0; nCntMagic < MAX_MAGIC; nCntMagic++)
	{
		if (g_aMagic[nCntMagic].bUse == false)
		{
			g_aMagic[nCntMagic].pos = pos;
			g_aMagic[nCntMagic].rot = rot;
			g_aMagic[nCntMagic].move = move;
			g_aMagic[nCntMagic].nLife = nLife;
			g_aMagic[nCntMagic].nType = nType;
			g_aMagic[nCntMagic].bUse = true;
			break;
		}
	}
}
