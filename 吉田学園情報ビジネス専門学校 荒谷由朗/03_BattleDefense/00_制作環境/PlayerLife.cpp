//=============================================================================
//
// �v���C���[�̃��C�t�Q�[�W���� [PlayerLife.cpp]
// Author : �r�J�R�N
//
//=============================================================================
#include "PlayerLife.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_PlayerLife001		"data/TEXTURE/PlayerLife.png"			// �ǂݍ��ރe�N�X�`���t�F�C����
#define TEXTURE_PlayerLife000		"data/TEXTURE/Metre000.png"			// �ǂݍ��ރe�N�X�`���t�F�C����
#define MAX_PlayerLife				(1)									// �Q�[�W�̍ő吔	
#define REDUCE_PlayerLife			(0.3f)								// �Q�[�W�̌����(���t���[��)

#define LIFE_VERTEX ((g_PlayerLife_h + 1) * (g_PlayerLife_v + 1))
#define LIFE_INDEX ( (g_PlayerLife_h * g_PlayerLife_v )* 2 + (4 * (g_PlayerLife_v - 1)) + 2 )
#define LIFE_POLYGON ( (g_PlayerLife_h * g_PlayerLife_v) * 2 + (4 * (g_PlayerLife_v - 1)) )

#define LIFE_RADIUS (85.0f)
#define LIFE_RADIUS2 (50.0f)

#define LIFE_POS_X (95.0f)
#define LIFE_POS_Y (630.0f)

//#define LIFE_HEIGHT (5.0f)

#define LIFE_H (100) //���b�V���̕�����(H)
#define LIFE_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPlayerLife(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexPlayerLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePlayerLife[MAX_PlayerLife] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerLife = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffPlayerLife = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

float g_fPlayerLife;												// �Q�[�W�̒l
float g_fPlayerLifeColR;											// �Q�[�W�̐F(��)
float g_fPlayerLifeColG;											// �Q�[�W�̐F(��)
float g_fPlayerLifeColB;											// �Q�[�W�̐F(��)

int g_nPlayerLife;

int g_PlayerLife_h, g_PlayerLife_v;
float g_PosLife_x, g_PosLife_y;

//=============================================================================
// ����������
//=============================================================================
void InitPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_PlayerLife_h = LIFE_H;
	g_PlayerLife_v = LIFE_V;
	g_PosLife_x = LIFE_POS_X;
	g_PosLife_y = LIFE_POS_Y;
	int Polygon = (g_PlayerLife_h * g_PlayerLife_v) * 2 + (4 * (g_PlayerLife_v - 1));
	// �Q�[�W�̏�����
	g_fPlayerLife = 583.0f;
	g_fPlayerLifeColR = 1.0f;
	g_fPlayerLifeColG = 0.0f;
	g_fPlayerLifeColB = 0.0f;
	g_nPlayerLife = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PlayerLife000, &g_pTexturePlayerLife[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PlayerLife001, &g_pTexturePlayerLife[1]);

	// ���_���̍쐬
	MakeVertexPlayerLife(pDevice);
	MakeIndexPlayerLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerLife(void)
{
	for (int nCntPlayerLife = 0; nCntPlayerLife < MAX_PlayerLife; nCntPlayerLife++)
	{
		// �e�N�X�`���̊J��
		if (g_pTexturePlayerLife[nCntPlayerLife] != NULL)
		{
			g_pTexturePlayerLife[nCntPlayerLife]->Release();
			g_pTexturePlayerLife[nCntPlayerLife] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayerLife != NULL)
	{
		g_pVtxBuffPlayerLife->Release();
		g_pVtxBuffPlayerLife = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffPlayerLife != NULL)
	{
		g_pIdxBuffPlayerLife->Release();
		g_pIdxBuffPlayerLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerLife(void)
{
	if (g_nPlayerLife <= -LIFE_H *2)
	{
		g_nPlayerLife = 0;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerLife, 0, sizeof(VERTEX_2D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffPlayerLife);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, 0);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, LIFE_VERTEX, 0, LIFE_POLYGON + g_nPlayerLife);
	// �|���S���̕`��
	for (int nCntPlayerLife = 0; nCntPlayerLife < MAX_PlayerLife; nCntPlayerLife++)
	{// �e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayerLife * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPlayerLife(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * LIFE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerLife,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = D3DX_PI * 2 / g_PlayerLife_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_PlayerLife_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_PlayerLife_h + 1; nCntLife_H++)
		{
			if (nCntLife_V == 0)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.x = -sinf(fDestAngle) * LIFE_RADIUS + g_PosLife_x;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.y = cosf(fDestAngle) * LIFE_RADIUS + g_PosLife_y;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.z = 0.0f;

				//���_�J���[
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_PlayerLife_h / 2)), nCntLife_V * -1.0f);
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
			if (nCntLife_V == 1)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.x = -sinf(fDestAngle) * (LIFE_RADIUS - LIFE_RADIUS2) + g_PosLife_x;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.y = cosf(fDestAngle) * (LIFE_RADIUS - LIFE_RADIUS2) + g_PosLife_y;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.z = 0.0f;

				//���_�J���[
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].col = D3DXCOLOR(0.5f, 1.0f, 0.5f, 0.9f);

				//�e�N�X�`�����W
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_PlayerLife_h / 2)), nCntLife_V * -1.0f);
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
		}
	}
	//for (int nCntGauge = 0; nCntGauge < MAX_PlayerLife; nCntGauge++)
	//{
	//	if (nCntGauge == 0)
	//	{
	//		//���_�ݒ�
	//		pVtx[0].pos = D3DXVECTOR3(68.0f, 652.0f, 0.0f);
	//		pVtx[1].pos = D3DXVECTOR3(583.0f, 652.0f, 0.0f);
	//		pVtx[2].pos = D3DXVECTOR3(68.0f, 690.0f, 0.0f);
	//		pVtx[3].pos = D3DXVECTOR3(583.0f, 690.0f, 0.0f);

	//		//���_�J���[�ݒ�
	//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//	}
	//	else
	//	{
	//		// ������
	//		//���_�ݒ�
	//		pVtx[0].pos = D3DXVECTOR3(50.0f, 630.0f, 0.0f);
	//		pVtx[1].pos = D3DXVECTOR3(600.0f, 630.0f, 0.0f);
	//		pVtx[2].pos = D3DXVECTOR3(50.0f, 700.0f, 0.0f);
	//		pVtx[3].pos = D3DXVECTOR3(600.0f, 700.0f, 0.0f);

	//		//���_�J���[�ݒ�
	//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	}

	//	//1.0f�ŌŒ�
	//	pVtx[0].rhw = 1.0f;
	//	pVtx[1].rhw = 1.0f;
	//	pVtx[2].rhw = 1.0f;
	//	pVtx[3].rhw = 1.0f;

	//	//�e�N�X�`���ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	//}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayerLife->Unlock();
}
//=============================================================================
// �C���f�b�N�X���̍쐬
//=============================================================================
void MakeIndexPlayerLife(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * LIFE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffPlayerLife,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffPlayerLife->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_PlayerLife_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_PlayerLife_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_PlayerLife_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_PlayerLife_h && nCntIndex_V <= g_PlayerLife_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_PlayerLife_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffPlayerLife->Unlock();

}
void HitPlayerLife(int nDamage)
{
	g_nPlayerLife -= nDamage;
}

float GetPlayerLife(void)
{
	return g_fPlayerLife;
}