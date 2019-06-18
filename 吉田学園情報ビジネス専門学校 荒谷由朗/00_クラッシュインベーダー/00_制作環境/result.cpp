//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BG_TEXTURENAME_WIN		"data/TEXTURE/GAMECLEAR.png"		// �ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAME_LOSE		"data/TEXTURE/GAMEOVER.png"			// �ǂݍ��ރe�N�X�`��

#define BG_POS_X				(0)									// ���_���W�iX���W�j
#define BG_POS_Y				(0)									// ���_���W�iY���W�j
#define BG_POS_WIDTH			(SCREEN_WIDTH)						// DirectX�̕�
#define BG_POS_HEIGHT			(SCREEN_HEIGHT)						// DirectX�̍���

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureResult = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^

	GAMESTATE pGame;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	pGame = GetGameStateNow();

	if (pGame == GAMESTATE_CLEAR)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_WIN, &g_pTextureResult);
	}
	else
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_LOSE, &g_pTextureResult);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);			// ���_���W(X���W,Y���W)
	pVtx[1].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_Y, 0.0f);		// ���_���W(X���W,Y���W)
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_HEIGHT, 0.0f);		// ���_���W(X���W,Y���W)
	pVtx[3].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_HEIGHT, 0.0f);	// ���_���W(X���W,Y���W)

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);		// �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);		// �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);		// �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);		// �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffResult->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	FADE fade;

	fade = GetFade();
	// ����L�[�������ꂽ��
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			// ���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}