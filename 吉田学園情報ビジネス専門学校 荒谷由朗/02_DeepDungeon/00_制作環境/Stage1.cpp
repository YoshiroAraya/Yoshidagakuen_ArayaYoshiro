//=============================================================================
//
// �X�e�[�W1���� [Stage1.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "Stage1.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTUER "data/TEXTURE/Field000.jpg"
#define STAGE_SPLIT (16)	//�X�e�[�W1���\������t�B�[���h�̕�����
#define STAGE1VTX_X (100.0f)
#define STAGE1VTX_Z (100.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexStage1(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage1[STAGE_SPLIT] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStage1 = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffStage1[STAGE_SPLIT] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Stage1 g_Stage1[STAGE_SPLIT];
StageVtx1 g_StageVtx[STAGE_SPLIT];

//=============================================================================
// ����������
//=============================================================================
void InitStage1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		g_Stage1[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage1[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Stage1[nCnt].bUse = false;
		g_Stage1[nCnt].Heidth = 0;
		g_Stage1[nCnt].Width = 0;
		g_StageVtx[nCnt].VertexStage = 0;
		g_StageVtx[nCnt].IndexStage = 0;
		g_StageVtx[nCnt].PolygonStage = 0;
	}
	SetStageMap1(8, 4, D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//1-a
	SetStageMap1(3, 8, D3DXVECTOR3(0.0f, 0.0f, 800.0f));	//1-b
	SetStageMap1(3, 3, D3DXVECTOR3(300.0f, 0.0f, 600.0f));	//1-c
	SetStageMap1(3, 5, D3DXVECTOR3(600.0f, 0.0f, 600.0f));	//1-d
	SetStageMap1(8, 8, D3DXVECTOR3(-100.0f, 0.0f, 1600.0f));//1-e
	SetStageMap1(3, 5, D3DXVECTOR3(900.0f, 0.0f, 1200.0f));	//1-f
	SetStageMap1(6, 3, D3DXVECTOR3(700.0f, 0.0f, 1500.0f));	//1-g
	SetStageMap1(3, 3, D3DXVECTOR3(1000.0f, 0.0f, 1700.0f));//1-h
	SetStageMap1(5, 5, D3DXVECTOR3(600.0f, 0.0f, 2300.0f));	//1-i
	SetStageMap1(8, 3, D3DXVECTOR3(-200.0f, 0.0f, 2200.0f));//1-j
	SetStageMap1(3, 3, D3DXVECTOR3(100.0f, 0.0f, 1900.0f));	//1-k
	SetStageMap1(6, 1, D3DXVECTOR3(-600.0f, 0.0f, 1000.0f));//1-l
	SetStageMap1(4, 2, D3DXVECTOR3(-400.0f, 0.0f, 1200.0f));//1-n
	SetStageMap1(3, 4, D3DXVECTOR3(-600.0f, 0.0f, 900.0f));	//1-m
	SetStageMap1(2, 2, D3DXVECTOR3(-600.0f, 0.0f, 1200.0f));//1-o
	SetStageMap1(3, 3, D3DXVECTOR3(-700.0f, 0.0f, 1500.0f));//1-p

	MakeVertexStage1(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage1(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStage1 != NULL)
	{
		g_pTextureStage1->Release();
		g_pTextureStage1 = NULL;
	}
	// ���_�o�b�t�@�̊J��
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_pVtxBuffStage1[nCnt] != NULL)
		{
			g_pVtxBuffStage1[nCnt]->Release();
			g_pVtxBuffStage1[nCnt] = NULL;
		}
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_pIdxBuffStage1[nCnt] != NULL)
		{
			g_pIdxBuffStage1[nCnt]->Release();
			g_pIdxBuffStage1[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage1(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage1(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Stage1[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Stage1[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Stage1[nCnt].rot.y, g_Stage1[nCnt].rot.x, g_Stage1[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Stage1[nCnt].mtxWorld, &g_Stage1[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Stage1[nCnt].pos.x, g_Stage1[nCnt].pos.y, g_Stage1[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Stage1[nCnt].mtxWorld, &g_Stage1[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Stage1[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffStage1[nCnt], 0,
				sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffStage1[nCnt]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureStage1);
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
void MakeVertexStage1(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	WORD*pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx;	//�C���f�b�N�X�̃J�E���^�[

					//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTUER, &g_pTextureStage1);
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_StageVtx[nCnt].VertexStage * STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffStage1[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_StageVtx[nCnt].IndexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit�m�ۂ���
			D3DPOOL_MANAGED,
			&g_pIdxBuffStage1[nCnt],
			NULL);


		// ���_���̐ݒ�----------------------------------------
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffStage1[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_Stage1[nCnt].Heidth; nCntz++)
		{//�c
			for (int nCntx = 0; nCntx <= g_Stage1[nCnt].Width; nCntx++)
			{//��
			 //���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-STAGE1VTX_X + (STAGE1VTX_X * nCntx), 0.0f, STAGE1VTX_Z - (STAGE1VTX_Z * nCntz));

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
		g_pVtxBuffStage1[nCnt]->Unlock();

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
		g_pIdxBuffStage1[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//�C���f�b�N�X�J�E���^�[�̏�����

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_Stage1[nCnt].Heidth; nCntIdx_Z++)
		{//Z��
			for (int nCntIdx_X = 0; nCntIdx_X <= g_Stage1[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X���iIdx���ꏏ�ɐ�����j
				pIdx[0] = (g_Stage1[nCnt].Width + 1) + nCntIdx;		//(����+1)+Idx�J�E���g
				pIdx[1] = nCntIdx;									//Idx�J�E���g�̐�
				pIdx += 2;											//�j�R�C�`�Ői�߂�

																	//�����̒[�܂œ��B�����@&&�@�c���̃J�E���g���c��-1��菬����
				if (nCntIdx_X == g_Stage1[nCnt].Width && nCntIdx_Z < g_Stage1[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;									//Idx�J�E���g�̐�
					pIdx[1] = (g_Stage1[nCnt].Width + 1) + nCntIdx + 1;	//(����+1)+Idx�J�E���g+1
					pIdx += 2;											//�j�R�C�`�Ői�߂�
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffStage1[nCnt]->Unlock();


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
Stage1*GetStage1(void)
{
	return &g_Stage1[0];
}

//=============================================================================
// �X�e�[�W1�̔z�u
//=============================================================================
void SetStageMap1(int Width, int Heidth, D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_Stage1[nCnt].bUse == false)
		{
			g_Stage1[nCnt].Heidth = Heidth;
			g_Stage1[nCnt].Width = Width;
			g_Stage1[nCnt].pos = pos;
			g_Stage1[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//Vtx,Index,Polygon�̌v�Z
			g_StageVtx[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_StageVtx[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_StageVtx[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_Stage1[nCnt].bUse = true;
			break;
		}
	}

}