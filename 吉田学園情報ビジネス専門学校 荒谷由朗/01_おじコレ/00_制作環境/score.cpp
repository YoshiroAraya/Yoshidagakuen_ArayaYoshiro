//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORE			(8)								// ����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore;					// �X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾

	// �X�R�A�̏�����
	g_nScore = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,							// �t�@�C���̖��O
		&g_pTextureScore);						// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾
	int nCntScore;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	int		nCntScore;		// �J�E���^�[
	float	nScorePos;		// �X�R�A�ʒu

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0, nScorePos = 1200; nCntScore < MAX_SCORE; nCntScore++, nScorePos -= 30)
	{
		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(nScorePos, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(nScorePos + 30.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(nScorePos, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(nScorePos + 30.0f, 80.0f, 0.0f);

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				// ���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	// �ϐ��錾
	int nCntScore;
	int nTexData;

	g_nScore += nValue;		// �X�R�A����
	nTexData = g_nScore;	// �X�R�A���i�[

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{// �X�R�A�J�E���g
		// �e�N�X�`���ݒ�
		pVtx[nCntScore * 4].tex		= D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
		pVtx[nCntScore * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
		pVtx[nCntScore * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
		pVtx[nCntScore * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
		nTexData /= 10;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}