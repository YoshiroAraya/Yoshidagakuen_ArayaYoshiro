//=============================================================================
//
// �I�u�W�F�N�g�̃��C�t�Q�[�W���� [ObjectLife.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "ObjectLife.h"
#include "game.h"
#include "player.h"
#include "obstacle.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_OBLife001		"data/TEXTURE/gauge.png"			// �ǂݍ��ރe�N�X�`���t�F�C����
#define TEXTURE_OBLife000		"data/TEXTURE/Metre000.png"			// �ǂݍ��ރe�N�X�`���t�F�C����
#define MAX_OBLife				(2)									// �Q�[�W�̍ő吔
#define REDUCE_OBLife			(0.3f)								// �Q�[�W�̌����(���t���[��)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexOBLife(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureOBLife[MAX_OBLife] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOBLife = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
float					g_fOBLife;							// �Q�[�W�̒l
float					g_fOBLifeColR;						// �Q�[�W�̐F(��)
float					g_fOBLifeColG;						// �Q�[�W�̐F(��)
float					g_fOBLifeColB;						// �Q�[�W�̐F(��)

//=============================================================================
// ����������
//=============================================================================
void InitOBLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �Q�[�W�̏�����
	g_fOBLife		= 400.0f;
	g_fOBLifeColR	= 1.0f;
	g_fOBLifeColG	= 0.0f;
	g_fOBLifeColB	= 0.0f;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OBLife000, &g_pTextureOBLife[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OBLife001, &g_pTextureOBLife[1]);

	// ���_���̍쐬
	MakeVertexOBLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitOBLife(void)
{
	for (int nCntOBLife = 0; nCntOBLife < MAX_OBLife; nCntOBLife++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureOBLife[nCntOBLife] != NULL)
		{
			g_pTextureOBLife[nCntOBLife]->Release();
			g_pTextureOBLife[nCntOBLife] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffOBLife != NULL)
	{
		g_pVtxBuffOBLife->Release();
		g_pVtxBuffOBLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateOBLife(void)
{
	OBSTACLE *g_aObstacle;
	g_aObstacle = GetObstaclel();

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOBLife->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aObstacle->ObjectState == OBJECTSTATE_DAMAGE)
	{
		g_fOBLife -= ((400.0f - 17.0f) / g_aObstacle->nLifeMAX);
	}

	if (g_aObstacle->nLife == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
	}
	else
	{
		pVtx[0].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fOBLife, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fOBLife, 65.0f, 0.0f);
	}

	// �F�̕ω�(�Q�[�W)
	if (g_fOBLife >= 17.0f && g_fOBLife <= 100.0f)
	{
		g_fOBLifeColG -= 0.002f;

		if (g_fOBLifeColG <= 0.0f)
		{
			g_fOBLifeColG = 0.0f;
		}

		pVtx[0].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffOBLife->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawOBLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOBLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntOBLife = 0; nCntOBLife < MAX_OBLife; nCntOBLife++)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureOBLife[nCntOBLife]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntOBLife * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexOBLife(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBLife,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOBLife,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffOBLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntOBLife = 0; nCntOBLife < MAX_OBLife; nCntOBLife++)
	{
		if (nCntOBLife == 0)
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(400.0f, 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(400.0f, 65.0f, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(415.0f, 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(415.0f, 80.0f, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffOBLife->Unlock();
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
float GetOBLife(void)
{
	return g_fOBLife;
}