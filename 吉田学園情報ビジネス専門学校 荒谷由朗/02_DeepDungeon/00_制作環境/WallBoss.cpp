//=============================================================================
//
// �X�e�[�W1���� [WallBoss.cpp]
// Author : ��Ո�
//
//=============================================================================
#include "WallBoss.h"
#include "player.h"
#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTUER "data\\TEXTURE\\Wall000.jpg"
#define STAGE_SPLIT (4)		//�X�e�[�W1���\������t�B�[���h�̕�����
#define STAGEVTX_X (100.0f)		//���_��u�����Ԋu
#define STAGEVTX_Y (100.0f)		//���_��u�������Ԋu
#define STAGEPOS_Y (200.0f)		//�ǂ̈ʒu�i�����j

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWallBoss(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWallBoss[STAGE_SPLIT] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWallBoss = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffWallBoss[STAGE_SPLIT] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
WallBoss g_WallBoss[STAGE_SPLIT];

//=============================================================================
// ����������
//=============================================================================
void InitWallBoss(void)
{
	/*�t���A�ړ�����͂����Ă郂�f���̈ʒu��
	D3DXVECTOR3(200.0f, 0.0f, 1300.0f);�@
	�ɕύX���肢���܂�*/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		g_WallBoss[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_WallBoss[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_WallBoss[nCnt].bUse = false;
		g_WallBoss[nCnt].Heidth = 0;
		g_WallBoss[nCnt].Width = 0;
		g_WallBoss[nCnt].VertexStage = 0;
		g_WallBoss[nCnt].IndexStage = 0;
		g_WallBoss[nCnt].PolygonStage = 0;
	}

	SetWallBoss(7, 3, D3DXVECTOR3(0.0f, STAGEPOS_Y, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWallBoss(7, 3, D3DXVECTOR3(500.0f, STAGEPOS_Y, -1100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	SetWallBoss(12, 3, D3DXVECTOR3(600.0f, STAGEPOS_Y, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetWallBoss(12, 3, D3DXVECTOR3(-100.0f, STAGEPOS_Y, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));

	MakeVertexWallBoss(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitWallBoss(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWallBoss != NULL)
	{
		g_pTextureWallBoss->Release();
		g_pTextureWallBoss = NULL;
	}
	// ���_�o�b�t�@�̊J��
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_pVtxBuffWallBoss[nCnt] != NULL)
		{
			g_pVtxBuffWallBoss[nCnt]->Release();
			g_pVtxBuffWallBoss[nCnt] = NULL;
		}
		//�C���f�b�N�X�o�b�t�@�̔j��
		if (g_pIdxBuffWallBoss[nCnt] != NULL)
		{
			g_pIdxBuffWallBoss[nCnt]->Release();
			g_pIdxBuffWallBoss[nCnt] = NULL;
		}
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateWallBoss(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWallBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_WallBoss[nCnt].bUse == true)
		{
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O

																				// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_WallBoss[nCnt].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_WallBoss[nCnt].rot.y, g_WallBoss[nCnt].rot.x, g_WallBoss[nCnt].rot.z);
			D3DXMatrixMultiply(&g_WallBoss[nCnt].mtxWorld, &g_WallBoss[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_WallBoss[nCnt].pos.x, g_WallBoss[nCnt].pos.y, g_WallBoss[nCnt].pos.z);
			D3DXMatrixMultiply(&g_WallBoss[nCnt].mtxWorld, &g_WallBoss[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_WallBoss[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWallBoss[nCnt], 0,
				sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffWallBoss[nCnt]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWallBoss);
			// �X�e�[�W1�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_WallBoss[nCnt].VertexStage,	  //���_��
				0,
				g_WallBoss[nCnt].PolygonStage);//�|���S����

			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O���Ȃ�

		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWallBoss(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
	WORD*pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx;	//�C���f�b�N�X�̃J�E���^�[

					//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTUER, &g_pTextureWallBoss);
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{

		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_WallBoss[nCnt].VertexStage * STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffWallBoss[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_WallBoss[nCnt].IndexStage*STAGE_SPLIT,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,		//16bit�m�ۂ���
			D3DPOOL_MANAGED,
			&g_pIdxBuffWallBoss[nCnt],
			NULL);


		// ���_���̐ݒ�----------------------------------------
		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffWallBoss[nCnt]->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntz = 0; nCntz <= g_WallBoss[nCnt].Heidth; nCntz++)
		{//�c
			for (int nCntx = 0; nCntx <= g_WallBoss[nCnt].Width; nCntx++)
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
		g_pVtxBuffWallBoss[nCnt]->Unlock();

		// �C���f�b�N�X���̐ݒ�----------------------------------------
		//�C���f�b�N�X�o�b�t�@�����b�N���ăC���f�b�N�X�o�b�t�@�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffWallBoss[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		nCntIdx = 0;//�C���f�b�N�X�J�E���^�[�̏�����

		for (int nCntIdx_Z = 0; nCntIdx_Z < g_WallBoss[nCnt].Heidth; nCntIdx_Z++)
		{//Z��
			for (int nCntIdx_X = 0; nCntIdx_X <= g_WallBoss[nCnt].Width; nCntIdx_X++, nCntIdx++)
			{//X���iIdx���ꏏ�ɐ�����j
				pIdx[0] = (g_WallBoss[nCnt].Width + 1) + nCntIdx;		//(����+1)+Idx�J�E���g
				pIdx[1] = nCntIdx;									//Idx�J�E���g�̐�
				pIdx += 2;											//�j�R�C�`�Ői�߂�

																	//�����̒[�܂œ��B�����@&&�@�c���̃J�E���g���c��-1��菬����
				if (nCntIdx_X == g_WallBoss[nCnt].Width && nCntIdx_Z < g_WallBoss[nCnt].Heidth - 1)
				{
					pIdx[0] = nCntIdx;									//Idx�J�E���g�̐�
					pIdx[1] = (g_WallBoss[nCnt].Width + 1) + nCntIdx + 1;	//(����+1)+Idx�J�E���g+1
					pIdx += 2;											//�j�R�C�`�Ői�߂�
				}
			}
		}
		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		g_pIdxBuffWallBoss[nCnt]->Unlock();
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
WallBoss*GetWallBoss(void)
{
	return &g_WallBoss[0];
}

//=============================================================================
// �X�e�[�W1�̔z�u
//=============================================================================
void SetWallBoss(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{
		if (g_WallBoss[nCnt].bUse == false)
		{
			g_WallBoss[nCnt].Heidth = Heidth;
			g_WallBoss[nCnt].Width = Width;
			g_WallBoss[nCnt].pos = pos;
			g_WallBoss[nCnt].rot = rot;

			//Vtx,Index,Polygon�̌v�Z
			g_WallBoss[nCnt].VertexStage = (Width + 1) * (Heidth + 1);
			g_WallBoss[nCnt].IndexStage = (Width * Heidth) * 2 + (4 * (Heidth - 1)) + 2;
			g_WallBoss[nCnt].PolygonStage = (Width * Heidth * 2) + (4 * (Heidth - 1));
			g_WallBoss[nCnt].bUse = true;

			if (rot.y == 0)
			{// ��
				g_WallBoss[nCnt].aPos[0] = D3DXVECTOR3(-100.0f + pos.x, 0.0f, pos.z + 20.0f);
				g_WallBoss[nCnt].aPos[1] = D3DXVECTOR3(-100.0f + pos.x + (100.0f * Width), 0.0f, pos.z + 20.0f);
				g_WallBoss[nCnt].aPos[2] = D3DXVECTOR3(-100.0f + pos.x + (100.0f * Width), 0.0f, pos.z - 20.0f);
				g_WallBoss[nCnt].aPos[3] = D3DXVECTOR3(-100.0f + pos.x, 0.0f, pos.z - 20.0f);
			}
			else if (rot.y == D3DX_PI * 0.5)
			{// �E
				g_WallBoss[nCnt].aPos[0] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z + 100.0f);
				g_WallBoss[nCnt].aPos[1] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z + 100.0f);
				g_WallBoss[nCnt].aPos[2] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z + (-100.0f * Width) + 100.0f);
				g_WallBoss[nCnt].aPos[3] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z + (-100.0f * Width) + 100.0f);
			}
			else if (rot.y == D3DX_PI * -0.5)
			{// ��
				g_WallBoss[nCnt].aPos[0] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z - 100.0f);
				g_WallBoss[nCnt].aPos[1] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z - 100.0f);
				g_WallBoss[nCnt].aPos[2] = D3DXVECTOR3(pos.x + 20.0f, 0.0f, pos.z + (100.0f * Width) - 100.0f);
				g_WallBoss[nCnt].aPos[3] = D3DXVECTOR3(pos.x - 20.0f, 0.0f, pos.z + (100.0f * Width) - 100.0f);
			}
			else if (rot.y == D3DX_PI)
			{// ��O
				g_WallBoss[nCnt].aPos[0] = D3DXVECTOR3(100.0f + pos.x, 0.0f, pos.z + 20.0f);
				g_WallBoss[nCnt].aPos[1] = D3DXVECTOR3(100.0f + pos.x + (-100.0f * Width), 0.0f, pos.z + 20.0f);
				g_WallBoss[nCnt].aPos[2] = D3DXVECTOR3(100.0f + pos.x + (-100.0f * Width), 0.0f, pos.z - 20.0f);
				g_WallBoss[nCnt].aPos[3] = D3DXVECTOR3(100.0f + pos.x, 0.0f, pos.z - 20.0f);
			}


			break;
		}
	}

}
//=============================================================================
// ���ʂ̕ǂ����蔻��(�G)
//=============================================================================
void CollisionWallBoss_WIDTHBack_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_WallBoss[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_WallBoss[nCnt].rot.y == 0.0f)
			{//����
				if (g_WallBoss[nCnt].aPos[0].x < pPlayer->pos.x &&
					g_WallBoss[nCnt].aPos[1].x > pPlayer->pos.x)
				{//�ǂ͈̔�
					if (g_WallBoss[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[2] - g_WallBoss[nCnt].aPos[3];
						g_WallBoss[nCnt].VecC = pPlayer->pos - g_WallBoss[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pPlayer->pos.z = g_WallBoss[nCnt].aPos[2].z - ((pPlayer->vtxMaxModel.z + pPlayer->vtxMinModel.z) / 2);
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
void CollisionWallBoss_WIDTHThisSide_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_WallBoss[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_WallBoss[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_WallBoss[nCnt].aPos[1].x < pPlayer->pos.x &&
					g_WallBoss[nCnt].aPos[0].x > pPlayer->pos.x)
				{//�ǂ͈̔�
					if (g_WallBoss[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[0] - g_WallBoss[nCnt].aPos[1];
						g_WallBoss[nCnt].VecC = pPlayer->pos - g_WallBoss[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pPlayer->pos.z = g_WallBoss[nCnt].aPos[0].z - ((pPlayer->vtxMaxModel.z + pPlayer->vtxMinModel.z) / 2);
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
void CollisionWallBoss_RIGHT_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_WallBoss[nCnt].bUse == true)
		{// �E��
			if (g_WallBoss[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_WallBoss[nCnt].aPos[1].z > pPlayer->pos.z &&
					g_WallBoss[nCnt].aPos[2].z < pPlayer->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_WallBoss[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[1] - g_WallBoss[nCnt].aPos[2];
						g_WallBoss[nCnt].VecC = pPlayer->pos - g_WallBoss[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pPlayer->pos.x = g_WallBoss[nCnt].aPos[1].x - ((pPlayer->vtxMaxModel.x + pPlayer->vtxMinModel.x) / 2);
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
void CollisionWallBoss_LEFT_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	PLAYER*pPlayer = GetPlayer();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_WallBoss[nCnt].bUse == true)
		{// �E��
			if (g_WallBoss[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_WallBoss[nCnt].aPos[2].z > pPlayer->pos.z &&
					g_WallBoss[nCnt].aPos[1].z < pPlayer->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_WallBoss[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[1] - g_WallBoss[nCnt].aPos[2];
						g_WallBoss[nCnt].VecC = pPlayer->pos - g_WallBoss[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pPlayer->pos.x = g_WallBoss[nCnt].aPos[1].x + ((pPlayer->vtxMaxModel.x + pPlayer->vtxMinModel.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}
//=============================================================================
// ���ʂ̕ǂ����蔻��i�G�j
//=============================================================================
void CollisionWallBoss_WIDTHBack_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_WallBoss[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_WallBoss[nCnt].rot.y == 0.0f)
			{//����
				if (g_WallBoss[nCnt].aPos[0].x < pEnemy->pos.x &&
					g_WallBoss[nCnt].aPos[1].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_WallBoss[nCnt].pos.z > posOld->z)
					{//�O���瓖������
					 //�x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[2] - g_WallBoss[nCnt].aPos[3];
						g_WallBoss[nCnt].VecC = pEnemy->pos - g_WallBoss[nCnt].aPos[2];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] <= 0)
						{
							pEnemy->pos.z = g_WallBoss[nCnt].aPos[2].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
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
void CollisionWallBoss_WIDTHThisSide_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		//�����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{//�ǂ̖���
		if (g_WallBoss[nCnt].bUse == true)
		{//�ǂ��o�Ă���
			if (g_WallBoss[nCnt].rot.y == D3DX_PI)
			{//��O��
				if (g_WallBoss[nCnt].aPos[1].x < pEnemy->pos.x &&
					g_WallBoss[nCnt].aPos[0].x > pEnemy->pos.x)
				{//�ǂ͈̔�
					if (g_WallBoss[nCnt].pos.z < posOld->z)
					{//��납�瓖������
					 //�x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[0] - g_WallBoss[nCnt].aPos[1];
						g_WallBoss[nCnt].VecC = pEnemy->pos - g_WallBoss[nCnt].aPos[0];

						//�����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{
							pEnemy->pos.z = g_WallBoss[nCnt].aPos[0].z - ((pEnemy->VtxMaxEnemy.z + pEnemy->VtxMinEnemy.z) / 2);
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
void CollisionWallBoss_RIGHT_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_WallBoss[nCnt].bUse == true)
		{// �E��
			if (g_WallBoss[nCnt].rot.y == D3DX_PI * 0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_WallBoss[nCnt].aPos[1].z > pEnemy->pos.z &&
					g_WallBoss[nCnt].aPos[2].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_WallBoss[nCnt].pos.x > posOld->x)
					{// �x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[1] - g_WallBoss[nCnt].aPos[2];
						g_WallBoss[nCnt].VecC = pEnemy->pos - g_WallBoss[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_WallBoss[nCnt].aPos[1].x - ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
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
void CollisionWallBoss_LEFT_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	float VecLine[STAGE_SPLIT];		// �����蔻��̌v�Z����
	ENEMY*pEnemy = GetEnemy();

	// �ǂ̖���
	for (int nCnt = 0; nCnt < STAGE_SPLIT; nCnt++)
	{// �ǂ��o�Ă���
		if (g_WallBoss[nCnt].bUse == true)
		{// �E��
			if (g_WallBoss[nCnt].rot.y == D3DX_PI * -0.5)
			{// �ǂ͈̔͂��������蔻��
				if (g_WallBoss[nCnt].aPos[2].z > pEnemy->pos.z &&
					g_WallBoss[nCnt].aPos[1].z < pEnemy->pos.z)
				{// �O��̈ʒu���ǂ�����O��������
					if (g_WallBoss[nCnt].pos.x < posOld->x)
					{// �x�N�g���v�Z
						g_WallBoss[nCnt].VecA = g_WallBoss[nCnt].aPos[1] - g_WallBoss[nCnt].aPos[2];
						g_WallBoss[nCnt].VecC = pEnemy->pos - g_WallBoss[nCnt].aPos[1];

						// �����蔻��v�Z
						VecLine[nCnt] = (g_WallBoss[nCnt].VecA.z*g_WallBoss[nCnt].VecC.x) - (g_WallBoss[nCnt].VecA.x*g_WallBoss[nCnt].VecC.z);

						if (VecLine[nCnt] >= 0)
						{// ������������
							pEnemy->pos.x = g_WallBoss[nCnt].aPos[1].x + ((pEnemy->VtxMaxEnemy.x + pEnemy->VtxMinEnemy.x) / 2);
							break;
						}
					}
				}
			}
		}
	}
}