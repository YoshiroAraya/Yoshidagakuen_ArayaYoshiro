//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : �r�J�R�N
//
//=============================================================================
#include "main.h"
#include "bg.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BG_TEXTURENAME	"data/TEXTURE/RunBG.png"		//�w�i�Ƃ��ĕ\������t�@�C���̖��O
#define BG_POS_X		(0)								//�|���S���̊J�nX���W
#define BG_POS_Y		(0)								//�|���S���̊J�nY���W
#define BG_WIDTH		(SCREEN_WIDTH)					//����
#define BG_HEIGHT		(SCREEN_HEIGHT)					//�c��
#define TIME_SPEED		(2)								//�w�i�X�N���[���̃X�s�[�h

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;			//���_�o�b�t�@�ւ̃|�C���^
int g_nCntBG = 0;
int nCntBG;

//=============================================================================
// �|���S������������
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	nCntBG = 0;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);
	//���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//rwhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{
	//���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *pVtx;

	nCntBG++;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	if ((nCntBG % TIME_SPEED) == 0)		//�A�j���[�V�����̑�����ς�����
	{
	    g_nCntBG++;
		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.002f * g_nCntBG + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.002f * g_nCntBG + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.002f * g_nCntBG + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.002f * g_nCntBG + 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}