//=============================================================================
//
// �X�e�[�W1���� [Wall1.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "Wall1.h"
#include "player.h"
#include "enemy.h"
#include "enemy0.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "enemy5.h"
#include "enemy6.h"
#include "enemy7.h"
#include "enemy8.h"

#include "arrow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTUER "data/TEXTURE/Wall000.jpg"
#define STAGE_SPLIT (55)		//�X�e�[�W1���\������t�B�[���h�̕�����(50)
#define STAGEVTX_X (100.0f)		//���_��u�����Ԋu
#define STAGEVTX_Y (100.0f)		//���_��u�������Ԋu
#define STAGEPOS_Y (200.0f)		//�ǂ̈ʒu�i�����j

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall1(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall1[STAGE_SPLIT] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall1 = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWall1[STAGE_SPLIT] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Wall1 g_Wall1[STAGE_SPLIT];

//=============================================================================
// ����������
//=============================================================================
void InitWall1(void)
{
	/*�t���A�ړ�����͂����Ă郂�f���̈ʒu��
	D3DXVECTOR3(200.0f, 0.0f, 1300.0f);�@
	�ɕύX���肢���܂�*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		g_Wall1[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall1[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall1[nCnt].bUse = false;
		g_Wall1[nCnt].Heidth = 0;
		g_Wall1[nCnt].Width = 0;
		g_Wall1[nCnt].VertexStage = 0;
		g_Wall1[nCnt].IndexStage = 0;
		g_Wall1[nCnt].PolygonStage = 0;
	}
	//1-a����---------------------------------
	SetWall1(5, 3, D3DXVECTOR3(300.0f, STAGEPOS_Y, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(4, 3, D3DXVECTOR3(600.0f, STAGEPOS_Y, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(4, 3, D3DXVECTOR3(700.0f, STAGEPOS_Y, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(4, 3, D3DXVECTOR3(-100.0f, STAGEPOS_Y, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-b����---------------------------------
	SetWall1(2, 3, D3DXVECTOR3(200.0f, STAGEPOS_Y, 800.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(200.0f, STAGEPOS_Y, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(8, 3, D3DXVECTOR3(-100.0f, STAGEPOS_Y, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-c����---------------------------------
	SetWall1(6, 3, D3DXVECTOR3(300.0f, STAGEPOS_Y, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(400.0f, STAGEPOS_Y, 400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//1-d����---------------------------------
	SetWall1(5, 3, D3DXVECTOR3(800.0f, STAGEPOS_Y, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(2, 3, D3DXVECTOR3(500.0f, STAGEPOS_Y, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(700.0f, STAGEPOS_Y, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//1-e����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(400.0f, STAGEPOS_Y, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(2, 3, D3DXVECTOR3(-100.0f, STAGEPOS_Y, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(4, 3, D3DXVECTOR3(500.0f, STAGEPOS_Y, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(-200.0f, STAGEPOS_Y, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(600.0f, STAGEPOS_Y, 1600.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(4, 3, D3DXVECTOR3(600.0f, STAGEPOS_Y, 1200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(-200.0f, STAGEPOS_Y, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	SetWall1(4, 3, D3DXVECTOR3(-200.0f, STAGEPOS_Y, 1400.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-e����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(350.0f, STAGEPOS_Y, 1350.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(50.0f, STAGEPOS_Y, 1350.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(350.0f, STAGEPOS_Y, 1250.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(50.0f, STAGEPOS_Y, 1250.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(150.0f, STAGEPOS_Y, 1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(250.0f, STAGEPOS_Y, 1150.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//1-f����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(1000.0f, STAGEPOS_Y, 800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(5, 3, D3DXVECTOR3(1100.0f, STAGEPOS_Y, 1200.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(5, 3, D3DXVECTOR3(800.0f, STAGEPOS_Y, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-g����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(700.0f, STAGEPOS_Y, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(2, 3, D3DXVECTOR3(700.0f, STAGEPOS_Y, 1300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(1100.0f, STAGEPOS_Y, 1300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//1-h����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(1000.0f, STAGEPOS_Y, 1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(5, 3, D3DXVECTOR3(1200.0f, STAGEPOS_Y, 1700.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(2, 3, D3DXVECTOR3(900.0f, STAGEPOS_Y, 1700.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-i����---------------------------------
	SetWall1(5, 3, D3DXVECTOR3(600.0f, STAGEPOS_Y, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(5, 3, D3DXVECTOR3(900.0f, STAGEPOS_Y, 1900.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(5, 3, D3DXVECTOR3(1000.0f, STAGEPOS_Y, 2300.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(500.0f, STAGEPOS_Y, 2400.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(500.0f, STAGEPOS_Y, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-j����---------------------------------
	SetWall1(8, 3, D3DXVECTOR3(-200.0f, STAGEPOS_Y, 2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(-100.0f, STAGEPOS_Y, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(2, 3, D3DXVECTOR3(400.0f, STAGEPOS_Y, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(-300.0f, STAGEPOS_Y, 2100.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-k����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(300.0f, STAGEPOS_Y, 1900.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(0.0f, STAGEPOS_Y, 1800.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-l����---------------------------------
	SetWall1(2, 3, D3DXVECTOR3(-300.0f, STAGEPOS_Y, 1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//1-m����---------------------------------
	SetWall1(4, 3, D3DXVECTOR3(-400.0f, STAGEPOS_Y, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(-500.0f, STAGEPOS_Y, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//1-n����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(-400.0f, STAGEPOS_Y, 1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//1-o����---------------------------------
	SetWall1(7, 3, D3DXVECTOR3(-700.0f, STAGEPOS_Y, 700.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	//1-p����---------------------------------
	SetWall1(3, 3, D3DXVECTOR3(-700.0f, STAGEPOS_Y, 1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall1(1, 3, D3DXVECTOR3(-800.0f, STAGEPOS_Y, 1300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(-500.0f, STAGEPOS_Y, 1500.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(-800.0f, STAGEPOS_Y, 1400.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	SetWall1(3, 3, D3DXVECTOR3(-800.0f, STAGEPOS_Y, 1400.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	MakeVertexWall1(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall1(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall1 != NULL)
	{
		g_pTextureWall1->Release();
		g_pTextureWall1 = NULL;
	}
	// ���_�o�b�t�@�̊J��
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_pVtxBuffWall1[nCnt] != NULL)
		{
			g_pVtxBuffWall1[nCnt]->Release();
			g_pVtxBuffWall1[nCnt] = NULL;
		}
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_pIdxBuffWall1[nCnt] != NULL)
		{
			g_pIdxBuffWall1[nCnt]->Release();
			g_pIdxBuffWall1[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall1(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Wall1[nCnt].bUse == true)
		{
			if (nCnt < 20 || nCnt > 26)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Wall1[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall1[nCnt].rot.y, g_Wall1[nCnt].rot.x, g_Wall1[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Wall1[nCnt].mtxWorld, &g_Wall1[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall1[nCnt].pos.x, g_Wall1[nCnt].pos.y, g_Wall1[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Wall1[nCnt].mtxWorld, &g_Wall1[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall1[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall1[nCnt], 0,
				sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffWall1[nCnt]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall1);
			// �X�e�[�W1�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_Wall1[nCnt].VertexStage,	  //���_��
				0,
				g_Wall1[nCnt].PolygonStage);//�|���S����

			if (nCnt > 20 && nCnt < 26)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O���Ȃ�
			}
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall1(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	WORD*pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx;	//�C���f�b�N�X�̃J�E���^�[

					//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTUER, &g_pTextureWall1);
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Wall1[nCnt].VertexStage * STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffWall1[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_Wall1[nCnt].IndexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit�m�ۂ���
			D3DPOOL_MANAGED,
			&g_pIdxBuffWall1[nCnt],
			NULL);


		// ���_���̐ݒ�----------------------------------------
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffWall1[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_Wall1[nCnt].Heidth; nCntz++)
		{//�c
			for (int nCntx = 0; nCntx <= g_Wall1[nCnt].Width; nCntx++)
			{//��
			 //���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-STAGEVTX_X + (STAGEVTX_X * nCntx), STAGEVTX_Y - (STAGEVTX_Y * nCntz), 0.0f);

				//�@���̐ݒ�i���̐�����S��������1.0(-1.0)�ɂȂ�j
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[��ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntx), 0.0f + (1.0f * nCntz));

				pVtx += 1;
			}
		}
		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffWall1[nCnt]->Unlock();

		// �C���f�b�N�X���̐ݒ�----------------------------------------
		//�C���f�b�N�X�o�b�t�@�����b�N���ăC���f�b�N�X�o�b�t�@�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffWall1[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//�C���f�b�N�X�J�E���^�[�̏�����

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_Wall1[nCnt].Heidth; nCntIdx_Z++)
		{//Z��
			for (int nCntIdx_X = 0; nCntIdx_X <= g_Wall1[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X���iIdx���ꏏ�ɐ�����j
				pIdx[0] = (g_Wall1[nCnt].Width + 1) + nCntIdx;		//(����+1)+Idx�J�E���g
				pIdx[1] = nCntIdx;									//Idx�J�E���g�̐�
				pIdx += 2;											//�j�R�C�`�Ői�߂�

																	//�����̒[�܂œ��B�����@&&�@�c���̃J�E���g���c��-1��菬����
				if (nCntIdx_X == g_Wall1[nCnt].Width && nCntIdx_Z < g_Wall1[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;									//Idx�J�E���g�̐�
					pIdx[1] = (g_Wall1[nCnt].Width + 1) + nCntIdx + 1;	//(����+1)+Idx�J�E���g+1
					pIdx += 2;											//�j�R�C�`�Ői�߂�
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffWall1[nCnt]->Unlock();
	}

	//���_���W��ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	////���_���W��ݒ�
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 1.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 2.0f);
	//pVtx[3].pos = D3DXVECTOR3(1.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(1.0f, 1.0f);
	//pVtx[5].pos = D3DXVECTOR3(1.0f, 2.0f);
	//pVtx[6].pos = D3DXVECTOR3(2.0f, 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(2.0f, 1.0);
	//pVtx[8].pos = D3DXVECTOR3(2.0f, 2.0f);

	//�C���f�b�N�X�̐ݒ�
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;


}
//=============================================================================
// �X�e�[�W1�̎擾
//=============================================================================
Wall1*GetWall1(void)
{
	return &g_Wall1[0];
}

//=============================================================================
// �X�e�[�W1�̔z�u
//=============================================================================
void SetWall1(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Wall1[nCnt].bUse == false)
		{
			g_Wall1[nCnt].Heidth = Heidth;
			g_Wall1[nCnt].Width = Width;
			g_Wall1[nCnt].pos = pos;
			g_Wall1[nCnt].rot = rot;

			//Vtx,Index,Polygon�̌v�Z
			g_Wall1[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_Wall1[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_Wall1[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_Wall1[nCnt].bUse = true;

			if (rot.y == 0)
			{// ��
				g_Wall1[nCnt].aPos[0] = D3DXVECTOR3(-100.0f + pos.x, 0.0f, pos.z + 20.0f);
				g_Wall1[nCnt].aPos[1] = D3DXVECTOR3(-100.0f + pos.x + (100.0f * Width), 0.0f, pos.z + 20.0f);
				g_Wall1[nCnt].aPos[2] = D3DXVECTOR3(-100.0f + pos.x + (100.0f * Width), 0.0f, pos.z - 20.0f);
				g_Wall1[nCnt].aPos[3] = D3DXVECTOR3(-100.0f + pos.x, 0.0f, pos.z - 20.0f);
			}
			else if (rot.y == D3DX_PI * 0.5)
			{// �E
				g_Wall1[nCnt].aPos[0] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z + 100.0f);
				g_Wall1[nCnt].aPos[1] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z + 100.0f);
				g_Wall1[nCnt].aPos[2] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z + (-100.0f * Width) + 100.0f);
				g_Wall1[nCnt].aPos[3] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z + (-100.0f * Width) + 100.0f);
			}
			else if (rot.y == D3DX_PI * -0.5)
			{// ��
				g_Wall1[nCnt].aPos[0] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z - 100.0f);
				g_Wall1[nCnt].aPos[1] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z - 100.0f);
				g_Wall1[nCnt].aPos[2] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z + (100.0f * Width) - 100.0f);
				g_Wall1[nCnt].aPos[3] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z + (100.0f * Width) - 100.0f);
			}
			else if (rot.y == D3DX_PI)
			{// ��O
				g_Wall1[nCnt].aPos[0] = D3DXVECTOR3(100.0f + pos.x, 0.0f, pos.z + 20.0f);
				g_Wall1[nCnt].aPos[1] = D3DXVECTOR3(100.0f + pos.x + (-100.0f * Width), 0.0f, pos.z + 20.0f);
				g_Wall1[nCnt].aPos[2] = D3DXVECTOR3(100.0f + pos.x + (-100.0f * Width), 0.0f, pos.z - 20.0f);
				g_Wall1[nCnt].aPos[3] = D3DXVECTOR3(100.0f + pos.x, 0.0f, pos.z - 20.0f);
			}

			break;
		}
	}
}
//=============================================================================
// ���ʂ̕ǂ����蔻��i�v���C���[�j
//=============================================================================
void CollisionWall1_WIDTHBack_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pPlayer->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pPlayer->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pPlayer->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pPlayer->pos.z = g_Wall1[nCnt].aPos[2].z - ((pPlayer->vtxMaxModel.z + pPlayer->vtxMinModel.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// ��O�ʂ̕ǂ����蔻��i�v���C���[�j
//=============================================================================
void CollisionWall1_WIDTHThisSide_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pPlayer->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pPlayer->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pPlayer->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pPlayer->pos.z = g_Wall1[nCnt].aPos[0].z - ((pPlayer->vtxMaxModel.z + pPlayer->vtxMinModel.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// �E�ǂ̓����蔻��i�v���C���[�j
//=============================================================================
void CollisionWall1_RIGHT_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pPlayer->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pPlayer->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pPlayer->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pPlayer->pos.x = g_Wall1[nCnt].aPos[1].x - ((pPlayer->vtxMaxModel.x + pPlayer->vtxMinModel.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// ���ǂ̓����蔻��i�v���C���[�j
//=============================================================================
void CollisionWall1_LEFT_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pPlayer->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pPlayer->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pPlayer->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pPlayer->pos.x = g_Wall1[nCnt].aPos[1].x + ((pPlayer->vtxMaxModel.x + pPlayer->vtxMinModel.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// ���ʂ̕ǂ����蔻��(�G)
//=============================================================================
void CollisionWall1_WIDTHBack_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// ��O�ʂ̕ǂ����蔻��(�G)
//=============================================================================
void CollisionWall1_WIDTHThisSide_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// �E�ǂ̓����蔻��(�G)
//=============================================================================
void CollisionWall1_RIGHT_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// ���ǂ̓����蔻��(�G)
//=============================================================================
void CollisionWall1_LEFT_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}










//     //////////////////				///////////////					////////    
//=============================================================================
// 000000000000000000000000000000000000000000000
//=============================================================================
void CollisionWall1_WIDTHBack_Ene0(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_0 *pEnemy = GetEnemy_0();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene0(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_0 *pEnemy = GetEnemy_0();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene0(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_0 *pEnemy = GetEnemy_0();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene0(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_0 *pEnemy = GetEnemy_0();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}





//     //////////////////				///////////////					////////    
//=============================================================================
// 11111111111111111111111111111111
//=============================================================================
void CollisionWall1_WIDTHBack_Ene1(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_1 *pEnemy = GetEnemy_1();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene1(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_1 *pEnemy = GetEnemy_1();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene1(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_1 *pEnemy = GetEnemy_1();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene1(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_1 *pEnemy = GetEnemy_1();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}





//     //////////////////				///////////////					////////    
//=============================================================================
// 22222222222222222222222
//=============================================================================
void CollisionWall1_WIDTHBack_Ene2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_2 *pEnemy = GetEnemy_2();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_2 *pEnemy = GetEnemy_2();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_2 *pEnemy = GetEnemy_2();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_2 *pEnemy = GetEnemy_2();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}



//     //////////////////				///////////////					////////    
//=============================================================================
// 333333333333333333333333333333333333333333333
//=============================================================================
void CollisionWall1_WIDTHBack_Ene3(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_3 *pEnemy = GetEnemy_3();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene3(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_3 *pEnemy = GetEnemy_3();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene3(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_3 *pEnemy = GetEnemy_3();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene3(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_3 *pEnemy = GetEnemy_3();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}





//     //////////////////				///////////////					////////    
//=============================================================================
// 4444444444444444444444444444444444444444444444444
//=============================================================================
void CollisionWall1_WIDTHBack_Ene4(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_4 *pEnemy = GetEnemy_4();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene4(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_4 *pEnemy = GetEnemy_4();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene4(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_4 *pEnemy = GetEnemy_4();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene4(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_4 *pEnemy = GetEnemy_4();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}



//     //////////////////				///////////////					////////    
//=============================================================================
// 5555555555555555555555555555555555555555555555555555
//=============================================================================
void CollisionWall1_WIDTHBack_Ene5(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_5 *pEnemy = GetEnemy_5();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene5(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_5 *pEnemy = GetEnemy_5();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene5(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_5 *pEnemy = GetEnemy_5();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene5(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_5 *pEnemy = GetEnemy_5();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}

//     //////////////////				///////////////					////////    
//=============================================================================
// 66666666666666666666666666666666666666666666666
//=============================================================================
void CollisionWall1_WIDTHBack_Ene6(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_6 *pEnemy = GetEnemy_6();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == 0.0f)
			{//����
				if (g_Wall1[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_WIDTHThisSide_Ene6(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY_6 *pEnemy = GetEnemy_6();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_Wall1[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_Wall1[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_Wall1[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_Wall1[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_Wall1[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_Wall1[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_RIGHT_Ene6(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_6 *pEnemy = GetEnemy_6();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
void CollisionWall1_LEFT_Ene6(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY_6 *pEnemy = GetEnemy_6();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_Wall1[nCnt].bUse == true)
		{// �E��
			if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_Wall1[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_Wall1[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_Wall1[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
						g_Wall1[nCnt].VecC = pEnemy->pos - g_Wall1[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_Wall1[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}







void CollisionWall1_WIDTHBack_Arrow(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ARROW *pArrow = GetArrow();

	for (int nCntArrow = 0; nCntArrow < STAGE_SPLIT; nCntArrow++, pArrow++)
	{
		for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
		{//�ǂ̖���
			if (g_Wall1[nCnt].bUse == true)
			{//�ǂ��o�Ă���
				if (g_Wall1[nCnt].rot.y == 0.0f)
				{//����
					if (g_Wall1[nCnt].aPos[0].x < pArrow->pos.x &&
						g_Wall1[nCnt].aPos[1].x > pArrow->pos.x)
					{//�ǂ͈̔�
						if (g_Wall1[nCnt].pos.z > posOld->z)
						{//�O���瓖������
						 //�x�N�g���v�Z
							g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[2] - g_Wall1[nCnt].aPos[3];
							g_Wall1[nCnt].VecC = pArrow->pos - g_Wall1[nCnt].aPos[2];

							//�����蔻��v�Z
							VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

							if (VecLine[nCnt] <= 0)
							{
								pArrow->bUse = false;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CollisionWall1_WIDTHThisSide_Arrow(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ARROW *pArrow = GetArrow();

	for (int nCntArrow = 0; nCntArrow < STAGE_SPLIT; nCntArrow++, pArrow++)
	{
		for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
		{//�ǂ̖���
			if (g_Wall1[nCnt].bUse == true)
			{//�ǂ��o�Ă���
				if (g_Wall1[nCnt].rot.y == D3DX_PI)
				{//��O��
					if (g_Wall1[nCnt].aPos[1].x < pArrow->pos.x &&
						g_Wall1[nCnt].aPos[0].x > pArrow->pos.x)
					{//�ǂ͈̔�
						if (g_Wall1[nCnt].pos.z < posOld->z)
						{//��납�瓖������
						 //�x�N�g���v�Z
							g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[0] - g_Wall1[nCnt].aPos[1];
							g_Wall1[nCnt].VecC = pArrow->pos - g_Wall1[nCnt].aPos[0];

							//�����蔻��v�Z
							VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

							if (VecLine[nCnt] >= 0)
							{
								pArrow->bUse = false;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CollisionWall1_RIGHT_Arrow(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ARROW *pArrow = GetArrow();

	for (int nCntArrow = 0; nCntArrow < STAGE_SPLIT; nCntArrow++, pArrow++)
	{
	// �ǂ̖���
		for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
		{// �ǂ��o�Ă���
			if (g_Wall1[nCnt].bUse == true)
			{// �E��
				if (g_Wall1[nCnt].rot.y == D3DX_PI * 0.5)
				{// �ǂ͈̔͂��������蔻��
					if (g_Wall1[nCnt].aPos[1].z > pArrow->pos.z &&
						g_Wall1[nCnt].aPos[2].z < pArrow->pos.z)
					{// �O��̈ʒu���ǂ�����O��������
						if (g_Wall1[nCnt].pos.x > posOld->x)
						{// �x�N�g���v�Z
							g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
							g_Wall1[nCnt].VecC = pArrow->pos - g_Wall1[nCnt].aPos[1];

							// �����蔻��v�Z
							VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

							if (VecLine[nCnt] >= 0)
							{// ������������
								pArrow->bUse = false;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CollisionWall1_LEFT_Arrow(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ARROW *pArrow = GetArrow();

	for (int nCntArrow = 0; nCntArrow < STAGE_SPLIT; nCntArrow++, pArrow++)
	{
		// �ǂ̖���
		for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
		{// �ǂ��o�Ă���
			if (g_Wall1[nCnt].bUse == true)
			{// �E��
				if (g_Wall1[nCnt].rot.y == D3DX_PI * -0.5)
				{// �ǂ͈̔͂��������蔻��
					if (g_Wall1[nCnt].aPos[2].z > pArrow->pos.z &&
						g_Wall1[nCnt].aPos[1].z < pArrow->pos.z)
					{// �O��̈ʒu���ǂ�����O��������
						if (g_Wall1[nCnt].pos.x < posOld->x)
						{// �x�N�g���v�Z
							g_Wall1[nCnt].VecA = g_Wall1[nCnt].aPos[1] - g_Wall1[nCnt].aPos[2];
							g_Wall1[nCnt].VecC = pArrow->pos - g_Wall1[nCnt].aPos[1];

							// �����蔻��v�Z
							VecLine[nCnt] = (g_Wall1[nCnt].VecA.z*g_Wall1[nCnt].VecC.x) - (g_Wall1[nCnt].VecA.x*g_Wall1[nCnt].VecC.z);

							if (VecLine[nCnt] >= 0)
							{// ������������
								pArrow->bUse = false;
								break;
							}
						}
					}
				}
			}
		}
	}
}
