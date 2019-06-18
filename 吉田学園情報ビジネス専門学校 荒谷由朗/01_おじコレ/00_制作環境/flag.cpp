//=============================================================================
//
// �t���b�O���� [flag.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "flag.h"
#include "player.h"
#include "main.h"
#include "fade.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_FLAG				(256)							// �t���b�O�̍ő吔
#define FLAG_TEXTURENAME000		"data/TEXTURE/hata_GALL.png"	// �ǂݍ��ރe�N�X�`��
#define FLAG_TEXTURE_UV_U		(1.0f)							// �t���b�O�̃A�j���[�V����U�͈�
#define FLAG_TEXTURE_UV_V		(1.0f)							// �t���b�O�̃A�j���[�V����V�͈�

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_paTextureFlag = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlag	= NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Flag					g_aFlag[MAX_FLAG];			// �t���b�O�̏��

//=============================================================================
// �t���b�O�̏���������
//=============================================================================
void InitFlag(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFlag;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		g_aFlag[nCntFlag].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFlag[nCntFlag].fWidth	= 0;
		g_aFlag[nCntFlag].fHeight	= 0;
		g_aFlag[nCntFlag].bUse		= false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FLAG_TEXTURENAME000, &g_paTextureFlag);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLAG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFlag,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlag->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(FLAG_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, FLAG_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(FLAG_TEXTURE_UV_U, FLAG_TEXTURE_UV_V);

		pVtx += 4;				// ���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFlag->Unlock();
}

//=============================================================================
// �t���b�O�̏I������
//=============================================================================
void UninitFlag(void)
{
	// �e�N�X�`���̊J��
	if (g_paTextureFlag != NULL)
	{
		g_paTextureFlag->Release();
		g_paTextureFlag = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFlag != NULL)
	{
		g_pVtxBuffFlag->Release();
		g_pVtxBuffFlag = NULL;
	}
}

//=============================================================================
// �t���b�O�̍X�V����
//=============================================================================
void UpdateFlag(void)
{
}

//=============================================================================
// �t���b�O�̕`�揈��
//=============================================================================
void DrawFlag(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFlag;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffFlag, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_paTextureFlag);

	// �|���S���̕`��
	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		if (g_aFlag[nCntFlag].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFlag * 4, 2);
		}
	}
}

//=============================================================================
// �t���b�O�̐ݒ菈��
//=============================================================================
void SetFlag(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntFlag;

	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlag->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		if (g_aFlag[nCntFlag].bUse == false)
		{
			g_aFlag[nCntFlag].pos		= pos;
			g_aFlag[nCntFlag].fWidth	= fWidth;
			g_aFlag[nCntFlag].fHeight	= fHeight;
			g_aFlag[nCntFlag].bUse		= true;

			// ���_�ݒ�
			pVtx[nCntFlag * 4].pos		= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x, g_aFlag[nCntFlag].pos.y, 0.0f);
			pVtx[nCntFlag * 4 + 1].pos	= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth, g_aFlag[nCntFlag].pos.y, 0.0f);
			pVtx[nCntFlag * 4 + 2].pos	= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x, g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight, 0.0f);
			pVtx[nCntFlag * 4 + 3].pos	= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth, g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight, 0.0f);
			break;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFlag->Unlock();
}

//=============================================================================
// �t���b�O�̓����蔻��
//=============================================================================
bool CollisionFlag(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int		nCntFlag;
	bool	bLand = false;		// ���n�������ǂ���

	VERTEX_2D	*pVtx;							// ���_���ւ̃|�C���^
	FADE		fade		= GetFade();		// �t�F�[�h�̎擾
	Player		*pPlayer	= GetPlayer();		// �v���C���[�̎擾

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlag->Lock(0, 0, (void**)&pVtx, 0);

	// �����蔻��
	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		if (g_aFlag[nCntFlag].bUse == true)
		{// �g�p���Ă��邩�ǂ���
			if (g_aFlag[nCntFlag].pos.x - 14.9 <= pPos->x
				&& g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth + 14.9 >= pPos->x)
			{// �v���C���[���㉺�͈͓̔��ɂ��邩�ǂ���
				if (g_aFlag[nCntFlag].pos.y <= pPos->y
					&& g_aFlag[nCntFlag].pos.y >= pPosOld->y)
				{// ��
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// ���[�h�ݒ�
						SetFade(MODE_RESULT);
					}
				}
				else if (g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight > pPos->y - 50
					&& g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight < pPosOld->y - 50)
				{// ��
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// ���[�h�ݒ�
						SetFade(MODE_RESULT);
					}
				}
			}
			if (g_aFlag[nCntFlag].pos.y < pPos->y
				&& g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight + 50 > pPos->y)
			{// �v���C���[�����E�͈͓̔��ɂ��邩�ǂ���
				if (g_aFlag[nCntFlag].pos.x - 15 >= pPosOld->x
					&& g_aFlag[nCntFlag].pos.x - 15 <= pPos->x)
				{// ��
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// ���[�h�ݒ�
						SetFade(MODE_RESULT);
					}
				}
				if (g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth + 15 <= pPosOld->x
					&& g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth + 15 >= pPos->x)
				{// �E
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// ���[�h�ݒ�
						SetFade(MODE_RESULT);
					}
				}
			}
		}
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffFlag->Unlock();
	return bLand;	//�l��Ԃ�
}