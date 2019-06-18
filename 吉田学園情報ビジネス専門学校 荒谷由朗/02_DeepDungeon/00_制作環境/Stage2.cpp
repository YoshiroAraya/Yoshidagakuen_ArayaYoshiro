//=============================================================================
//
// �X�e�[�W1���� [Stage1.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "Stage2.h"
#include "Wall2.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTUER "data/TEXTURE/Field000.jpg"
#define STAGE_SPLIT (19)	//�X�e�[�W1���\������t�B�[���h�̕�����
#define STAGE2VTX_X (100.0f)
#define STAGE2VTX_Y (100.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexStage2(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage2[STAGE_SPLIT] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStage2 = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffStage2[STAGE_SPLIT] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Stage2 g_Stage2[STAGE_SPLIT];
StageVtx2 g_StageVtx[STAGE_SPLIT];

//=============================================================================
// ����������
//=============================================================================
void InitStage2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	PLAYER *pPlayer = GetPlayer();

	/*�]�����@�w�̈ʒu�́@D3DXVECTOR3(1500.0f, 0.0f, 700.0f)�@������ł�*/

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		g_Stage2[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage2[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage2[nCnt].bUse = false;
		g_Stage2[nCnt].Heidth = 0;
		g_Stage2[nCnt].Width = 0;
		g_StageVtx[nCnt].VertexStage = 0;
		g_StageVtx[nCnt].IndexStage = 0;
		g_StageVtx[nCnt].PolygonStage = 0;
	}

	SetStageMap2(4, 5, D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//2-a
	SetStageMap2(3, 3, D3DXVECTOR3(400.0f, 0.0f, -100.0f));	//2-b
	SetStageMap2(6, 4, D3DXVECTOR3(700.0f, 0.0f, -100.0f));	//2-c
	SetStageMap2(4, 4, D3DXVECTOR3(900.0f, 0.0f, 300.0f));	//2-b
	SetStageMap2(3, 3, D3DXVECTOR3(600.0f, 0.0f, 300.0f));	//2-e
	SetStageMap2(7, 3, D3DXVECTOR3(200.0f, 0.0f, 600.0f));	//2-f
	SetStageMap2(4, 7, D3DXVECTOR3(-200.0f, 0.0f, 800.0f));	//2-g
	SetStageMap2(7, 3, D3DXVECTOR3(-200.0f, 0.0f, 1100.0f));//2-h
	SetStageMap2(4, 5, D3DXVECTOR3(500.0f, 0.0f, 1200.0f));	//2-i
	SetStageMap2(3, 4, D3DXVECTOR3(-200.0f, 0.0f, 1400.0f));//2-j
	SetStageMap2(8, 4, D3DXVECTOR3(-800.0f, 0.0f, 1800.0f));//2-k
	SetStageMap2(9, 6, D3DXVECTOR3(-800.0f, 0.0f, 2400.0f));//2-l
	SetStageMap2(5, 3, D3DXVECTOR3(100.0f, 0.0f, 2200.0f));	//2-n
	SetStageMap2(5, 7, D3DXVECTOR3(600.0f, 0.0f, 2500.0f));	//2-m
	SetStageMap2(3, 4, D3DXVECTOR3(700.0f, 0.0f, 1800.0f));	//2-o
	SetStageMap2(7, 3, D3DXVECTOR3(0.0f, 0.0f, 1700.0f));	//2-p
	SetStageMap2(6, 3, D3DXVECTOR3(1100.0f, 0.0f, 2400.0f));//2-q
	SetStageMap2(3, 10, D3DXVECTOR3(1400.0f, 0.0f, 2200.0f));//2-r
	SetStageMap2(9, 7, D3DXVECTOR3(1100.0f, 0.0f, 1200.0f));//2-s






	pPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertexStage2(pDevice);

}
//=============================================================================
// �I������
//=============================================================================
void UninitStage2(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStage2 != NULL)
	{
		g_pTextureStage2->Release();
		g_pTextureStage2 = NULL;
	}
	// ���_�o�b�t�@�̊J��
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_pVtxBuffStage2[nCnt] != NULL)
		{
			g_pVtxBuffStage2[nCnt]->Release();
			g_pVtxBuffStage2[nCnt] = NULL;
		}
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_pIdxBuffStage2[nCnt] != NULL)
		{
			g_pIdxBuffStage2[nCnt]->Release();
			g_pIdxBuffStage2[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage2(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Stage2[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Stage2[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Stage2[nCnt].rot.y, g_Stage2[nCnt].rot.x, g_Stage2[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Stage2[nCnt].mtxWorld, &g_Stage2[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Stage2[nCnt].pos.x, g_Stage2[nCnt].pos.y, g_Stage2[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Stage2[nCnt].mtxWorld, &g_Stage2[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Stage2[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffStage2[nCnt], 0,
				sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffStage2[nCnt]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureStage2);

			// �X�e�[�W1�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_StageVtx[nCnt].VertexStage,	  //���_��
				0,
				g_StageVtx[nCnt].PolygonStage);//�|���S����
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexStage2(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	WORD*pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx;	//�C���f�b�N�X�̃J�E���^�[

					//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTUER, &g_pTextureStage2);
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_StageVtx[nCnt].VertexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffStage2[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_StageVtx[nCnt].IndexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit�m�ۂ���
			D3DPOOL_MANAGED,
			&g_pIdxBuffStage2[nCnt],
			NULL);


		// ���_���̐ݒ�----------------------------------------
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffStage2[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_Stage2[nCnt].Heidth; nCntz++)
		{//�c
			for (int nCntx = 0; nCntx <= g_Stage2[nCnt].Width; nCntx++)
			{//��
			 //���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-STAGE2VTX_X + (STAGE2VTX_X * nCntx), 0.0f, STAGE2VTX_X - (STAGE2VTX_X * nCntz));

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
		g_pVtxBuffStage2[nCnt]->Unlock();

		////���_���W��ݒ�
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

		// �C���f�b�N�X���̐ݒ�----------------------------------------
		//�C���f�b�N�X�o�b�t�@�����b�N���ăC���f�b�N�X�o�b�t�@�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffStage2[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//�C���f�b�N�X�J�E���^�[�̏�����

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_Stage2[nCnt].Heidth; nCntIdx_Z++)
		{//Z��
			for (int nCntIdx_X = 0; nCntIdx_X <= g_Stage2[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X���iIdx���ꏏ�ɐ�����j
				pIdx[0] = (g_Stage2[nCnt].Width + 1) + nCntIdx;		//(����+1)+Idx�J�E���g
				pIdx[1] = nCntIdx;						//Idx�J�E���g�̐�
				pIdx += 2;								//�j�R�C�`�Ői�߂�

														//�����̒[�܂œ��B�����@&&�@�c���̃J�E���g���c��-1��菬����
				if (nCntIdx_X == g_Stage2[nCnt].Width && nCntIdx_Z < g_Stage2[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;						//Idx�J�E���g�̐�
					pIdx[1] = (g_Stage2[nCnt].Width + 1) + nCntIdx + 1;	//(����+1)+Idx�J�E���g+1
					pIdx += 2;								//�j�R�C�`�Ői�߂�
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffStage2[nCnt]->Unlock();


		////�C���f�b�N�X�̐ݒ�
		//pIdx[0] = 3;
		//pIdx[1] = 0;

		//pIdx[2] = 4;
		//pIdx[3] = 1;
		//
		//pIdx[4] = 5;
		//pIdx[5] = 2;
		//
		//pIdx[6] = 2;
		//pIdx[7] = 6;
		//
		//pIdx[8] = 6;
		//pIdx[9] = 3;
		//
		//pIdx[10] = 7;
		//pIdx[11] = 4;
		//
		//pIdx[12] = 8;
		//pIdx[13] = 5;

	}

}
//=============================================================================
// �X�e�[�W1�̎擾
//=============================================================================
Stage2*GetStage2(void)
{
	return &g_Stage2[0];
}

//=============================================================================
// �X�e�[�W1�̔z�u
//=============================================================================
void SetStageMap2(int Width, int Heidth, D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Stage2[nCnt].bUse == false)
		{
			g_Stage2[nCnt].Heidth = Heidth;
			g_Stage2[nCnt].Width = Width;
			g_Stage2[nCnt].pos = pos;
			g_Stage2[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//Vtx,Index,Polygon�̌v�Z
			g_StageVtx[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_StageVtx[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_StageVtx[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_Stage2[nCnt].bUse = true;
			break;
		}
	}

}