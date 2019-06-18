//=============================================================================
//
// �R�C������ [coin.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "coin.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_COIN				(128)								// �R�C���̍ő吔
#define POYGON_TEXTURENAME		"data/TEXTURE/coin000.png"			// �ǂݍ��ރe�N�X�`��
#define COIN_TEXTURE_SPEED		(10)								// �R�C���A�j���[�V�����X�s�[�h
#define COIN_TEXTURE_UV_U		(0.25f)								// �R�C���A�j���[�V����U�͈�
#define COIN_TEXTURE_UV_V		(1.0f)								// �R�C���A�j���[�V����V�͈�


//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureCoin = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCoin = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Coin					g_aCoin[MAX_COIN];		// �R�C���̏��

//=============================================================================
// �R�C���̏���������
//=============================================================================
void InitCoin(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntCoin;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �R�C���̏��̏�����
	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		g_aCoin[nCntCoin].pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCoin[nCntCoin].nCounterAnim	= 0;
		g_aCoin[nCntCoin].nPatternAnim	= 0;
		g_aCoin[nCntCoin].bUse			= false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureCoin);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCoin,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(COIN_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, COIN_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(COIN_TEXTURE_UV_U, COIN_TEXTURE_UV_V);

		pVtx += 4;				// ���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffCoin->Unlock();
}

//=============================================================================
// �R�C���̏I������
//=============================================================================
void UninitCoin(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureCoin != NULL)
	{
		g_pTextureCoin->Release();
		g_pTextureCoin = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCoin != NULL)
	{
		g_pVtxBuffCoin->Release();
		g_pVtxBuffCoin = NULL;
	}
}

//=============================================================================
// �R�C���̍X�V����
//=============================================================================
void UpdateCoin(void)
{
	int nCntCoin;
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == true)
		{	// �R�C�����g�p����Ă���
			g_aCoin[nCntCoin].nCounterAnim++;			// �J�E���^�[���Z

			if ((g_aCoin[nCntCoin].nCounterAnim % COIN_TEXTURE_SPEED) == 0)		// �A�j���[�V�����̑�����ς�����
			{
				g_aCoin[nCntCoin].nPatternAnim = (g_aCoin[nCntCoin].nPatternAnim + 1);

				// ���_�ݒ�
				pVtx[nCntCoin * 4].pos		= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x, g_aCoin[nCntCoin].pos.y, 0.0f);
				pVtx[nCntCoin * 4 + 1].pos	= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth, g_aCoin[nCntCoin].pos.y, 0.0f);
				pVtx[nCntCoin * 4 + 2].pos	= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x, g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight, 0.0f);
				pVtx[nCntCoin * 4 + 3].pos	= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth, g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight, 0.0f);

				// �e�N�X�`���ݒ�
				pVtx[nCntCoin * 4].tex		= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f), 0.0f);
				pVtx[nCntCoin * 4 + 1].tex	= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f) + 0.25f, 0.0f);
				pVtx[nCntCoin * 4 + 2].tex	= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f), COIN_TEXTURE_UV_V);
				pVtx[nCntCoin * 4 + 3].tex	= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f) + 0.25f, COIN_TEXTURE_UV_V);
			}
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffCoin->Unlock();
}

//=============================================================================
// �R�C���̕`�揈��
//=============================================================================
void DrawCoin(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntCoin;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffCoin, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCoin);

	// �|���S���̕`��
	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCoin * 4, 2);
		}
	}
}

//=============================================================================
// �R�C���̐ݒ菈��
//=============================================================================
void SetCoin(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntCoin;

	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == false)
		{
			g_aCoin[nCntCoin].pos		= pos;
			g_aCoin[nCntCoin].fWidth	= fWidth;
			g_aCoin[nCntCoin].fHeight	= fHeight;

			// ���_�ݒ�
			pVtx[nCntCoin * 4].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntCoin * 4 + 1].pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntCoin * 4 + 2].pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntCoin * 4 + 3].pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aCoin[nCntCoin].bUse = true;
			break;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffCoin->Unlock();
}

//=============================================================================
// �R�C���̐ݒ菈��
//=============================================================================
bool CollisionCoin(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int		nCntCoin;
	bool	bLand = false;		// ���n�������ǂ���

	VERTEX_2D *pVtx;					// ���_���ւ̃|�C���^
	FADE fade = GetFade();				// �t�F�[�h�̎擾
	Player *pPlayer = GetPlayer();		// �v���C���[�̎擾

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	// �����蔻��
	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == true)
		{
			if (g_aCoin[nCntCoin].pos.x - 30 <= pPos->x
				&& g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth + 30 >= pPos->x)
			{// �㉺�͈͓̔�
				if (g_aCoin[nCntCoin].pos.y <= pPos->y
					&& g_aCoin[nCntCoin].pos.y >= pPosOld->y)
				{// ��
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// �g�p���Ă��Ȃ����
				}
				else if (g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight > pPos->y
					&& g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight < pPosOld->y)
				{// ��
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// �g�p���Ă��Ȃ����
				}
			}
			if (g_aCoin[nCntCoin].pos.y < pPos->y
				&& g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight + 40 > pPos->y)
			{// ���E�͈͓̔�
				if (g_aCoin[nCntCoin].pos.x - 15 >= pPosOld->x
					&& g_aCoin[nCntCoin].pos.x - 15 <= pPos->x)
				{// ��
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// �g�p���Ă��Ȃ����
				}
				if (g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth + 15 <= pPosOld->x
					&& g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth + 15 >= pPos->x)
				{// �E
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// �g�p���Ă��Ȃ����
				}
			}
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffCoin->Unlock();

	return bLand;
}