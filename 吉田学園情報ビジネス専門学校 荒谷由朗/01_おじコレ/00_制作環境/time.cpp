//=============================================================================
//
// �^�C������ [time.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "time.h"
#include "fade.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME			(3)								// ����
#define TIME_SPEED			(6)								// �^�C���̃X�s�[�h

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nTime;					// �^�C��
int						nCntTime;					// �J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X���擾

	g_nTime		= 900;	// �^�C���̏�����
	nCntTime	= 0;	// �J�E���^�[�̏�����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TIME,		// �t�@�C���̖��O
								&g_pTextureTime);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	nCntTime++;								// �J�E���^�[�̉��Z
	if ((nCntTime % TIME_SPEED) == 0)		// �A�j���[�V�����̑�����ς�����
	{
		AddTime(-1);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0, nTimePos = 100; nCntTime < MAX_TIME; nCntTime++, nTimePos -= 30)
	{
		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3((float)nTimePos, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)nTimePos + 30.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((float)nTimePos, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)nTimePos + 30.0f, 80.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.9f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.9f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;				// ���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �^�C���̉��Z
//=============================================================================
void AddTime(int nValue)
{
	FADE fade = GetFade();		// �t�F�[�h�̎擾

	g_nTime += nValue;			// �^�C������
	int nTexData = g_nTime;		// �^�C�����i�[

	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock
	(0, 0, (void**)&pVtx, 0);
	if (g_nTime >= 0)
	{
		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{// �^�C���J�E���g
			// �e�N�X�`���ݒ�
			pVtx[nCntTime * 4].tex		= D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 1].tex	= D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 2].tex	= D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
			pVtx[nCntTime * 4 + 3].tex	= D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
			nTexData /= 10;
		}
	}
	// �^�C�}�[��0�ȉ��ɂȂ����Ƃ�
	else if (g_nTime <= 0)
	{
		if (fade != FADE_OUT)
		{
			SetGameState(GAMESTATE_OVER);
			// ���[�h�ݒ�
			SetFade(MODE_RESULT);
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}