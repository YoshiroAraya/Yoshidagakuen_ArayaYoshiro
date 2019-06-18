//=============================================================================
//
// �X�e�[�W1���� [Stage1.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "StageBoss.h"
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTUER "data\\TEXTURE\\Field000.jpg"
#define STAGE_SPLIT (1)	//�X�e�[�W1���\������t�B�[���h�̕�����
#define STAGEBOSSVTX_X (100.0f)
#define STAGEBOSSVTX_Y (100.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexStageBoss(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageBoss[STAGE_SPLIT] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureStageBoss = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffStageBoss[STAGE_SPLIT] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
StageBoss g_StageBoss[STAGE_SPLIT];

//=============================================================================
// ����������
//=============================================================================
void InitStageBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	PLAYER *pPlayer = GetPlayer();

	/*�]�ڃ��f���͂ǂ����ɂǂ����Ă������o���Ȃ��悤�ɂ��Ă�������*/

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		g_StageBoss[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_StageBoss[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_StageBoss[nCnt].bUse = false;
		g_StageBoss[nCnt].Heidth = 0;
		g_StageBoss[nCnt].Width = 0;
		g_StageBoss[nCnt].VertexStage = 0;
		g_StageBoss[nCnt].IndexStage = 0;
		g_StageBoss[nCnt].PolygonStage = 0;
	}

	SetStageMapBoss(7, 12, D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//2-a

	pPlayer->pos = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
	MakeVertexStageBoss(pDevice);

}
//=============================================================================
// �I������
//=============================================================================
void UninitStageBoss(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStageBoss != NULL)
	{
		g_pTextureStageBoss->Release();
		g_pTextureStageBoss = NULL;
	}
	// ���_�o�b�t�@�̊J��
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_pVtxBuffStageBoss[nCnt] != NULL)
		{
			g_pVtxBuffStageBoss[nCnt]->Release();
			g_pVtxBuffStageBoss[nCnt] = NULL;
		}
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_pIdxBuffStageBoss[nCnt] != NULL)
		{
			g_pIdxBuffStageBoss[nCnt]->Release();
			g_pIdxBuffStageBoss[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateStageBoss(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStageBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_StageBoss[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_StageBoss[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_StageBoss[nCnt].rot.y, g_StageBoss[nCnt].rot.x, g_StageBoss[nCnt].rot.z);
			D3DXMatrixMultiply(&g_StageBoss[nCnt].mtxWorld, &g_StageBoss[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_StageBoss[nCnt].pos.x, g_StageBoss[nCnt].pos.y, g_StageBoss[nCnt].pos.z);
			D3DXMatrixMultiply(&g_StageBoss[nCnt].mtxWorld, &g_StageBoss[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_StageBoss[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffStageBoss[nCnt], 0,
				sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffStageBoss[nCnt]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureStageBoss);

			// �X�e�[�W1�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_StageBoss[nCnt].VertexStage,	  //���_��
				0,
				g_StageBoss[nCnt].PolygonStage);//�|���S����
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexStageBoss(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	WORD*pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx;	//�C���f�b�N�X�̃J�E���^�[

		//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTUER, &g_pTextureStageBoss);
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_StageBoss[nCnt].VertexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffStageBoss[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_StageBoss[nCnt].IndexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit�m�ۂ���
			D3DPOOL_MANAGED,
			&g_pIdxBuffStageBoss[nCnt],
			NULL);


		// ���_���̐ݒ�----------------------------------------
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffStageBoss[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_StageBoss[nCnt].Heidth; nCntz++)
		{//�c
			for (int nCntx = 0; nCntx <= g_StageBoss[nCnt].Width; nCntx++)
			{//��
				//���_���W��ݒ�
				pVtx[0].pos = D3DXVECTOR3(-STAGEBOSSVTX_X + (STAGEBOSSVTX_X * nCntx), 0.0f, STAGEBOSSVTX_X - (STAGEBOSSVTX_X * nCntz));

				//�@���̐ݒ�i���̐�����S��������1.0(-1.0)�ɂȂ�j
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[��ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f , 1.0f, 1.0f, 1.0f);

				//�e�N�X�`���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntx), 0.0f + (1.0f * nCntz));

				pVtx += 1;
			}
		}
		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffStageBoss[nCnt]->Unlock();

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
		g_pIdxBuffStageBoss[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//�C���f�b�N�X�J�E���^�[�̏�����

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_StageBoss[nCnt].Heidth; nCntIdx_Z++)
		{//Z��
			for (int nCntIdx_X = 0; nCntIdx_X <= g_StageBoss[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X���iIdx���ꏏ�ɐ�����j
				pIdx[0] = (g_StageBoss[nCnt].Width + 1) + nCntIdx;		//(����+1)+Idx�J�E���g
				pIdx[1] = nCntIdx;						//Idx�J�E���g�̐�
				pIdx += 2;								//�j�R�C�`�Ői�߂�

			//�����̒[�܂œ��B�����@&&�@�c���̃J�E���g���c��-1��菬����
				if (nCntIdx_X == g_StageBoss[nCnt].Width && nCntIdx_Z < g_StageBoss[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;						//Idx�J�E���g�̐�
					pIdx[1] = (g_StageBoss[nCnt].Width + 1) + nCntIdx + 1;	//(����+1)+Idx�J�E���g+1
					pIdx += 2;								//�j�R�C�`�Ői�߂�
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffStageBoss[nCnt]->Unlock();


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
StageBoss*GetStageBoss(void)
{
	return &g_StageBoss[0];
}

//=============================================================================
// �X�e�[�W1�̔z�u
//=============================================================================
void SetStageMapBoss(int Width, int Heidth, D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_StageBoss[nCnt].bUse == false)
		{
			g_StageBoss[nCnt].Heidth = Heidth;
			g_StageBoss[nCnt].Width = Width;
			g_StageBoss[nCnt].pos = pos;
			g_StageBoss[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//Vtx,Index,Polygon�̌v�Z
			g_StageBoss[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_StageBoss[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_StageBoss[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_StageBoss[nCnt].bUse = true;
			break;
		}
	}

}