//===========================================================================
//
// �I�v�V�������� [option.cpp]
// Author : TEAM_Fascinator
//
//===========================================================================
#include "main.h"
#include "input.h"
#include "inputx.h"
#include "option.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//===========================================================================
// �}�N����`(Option)
//===========================================================================
#define OPTION_TEXTURE_NAME		"data/TEXTURE/credit.png"	// �e�N�X�`��
#define OPTION_POS_X			(0.0f)						// ����X���W
#define OPTION_POS_Y			(0.0f)						// ����Y���W
#define OPTION_WIDTH			(SCREEN_WIDTH)				// ��
#define OPTION_HEIGHT			(SCREEN_HEIGHT)				// ����
#define OPTION_MAX				(2)							// ����
#define OPTION_TEXTURE_UV_U		(1.0f)						// �A�j���[�V����U�͈�
#define OPTION_TEXTURE_UV_V		(1.0f)						// �A�j���[�V����V�͈�
#define OPTION_SPEED			(0.003f)					// �X�s�[�h

//===========================================================================
// �O���[�o���ϐ�(Option)
//===========================================================================
LPDIRECT3DTEXTURE9			g_pTextureOption = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffOption = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3					g_posOption;					// �ʒu
D3DXVECTOR3					g_moveOption;					// �ړ�
JoyState					g_JoyStateOption;				// �W���C�p�b�h�̏��

//===========================================================================
// ����������(Option)
//===========================================================================
void InitOption(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posOption = D3DXVECTOR3((OPTION_POS_X + OPTION_WIDTH) / 2, (OPTION_POS_Y + OPTION_HEIGHT) / 2, 0.0f);	// ���S�l
	g_moveOption = D3DXVECTOR3(0.0f, OPTION_SPEED, 0.0f);													// �ړ��l
	g_JoyStateOption.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, OPTION_TEXTURE_NAME, &g_pTextureOption);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * OPTION_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOption,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffOption->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(OPTION_POS_X, OPTION_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(OPTION_WIDTH, OPTION_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(OPTION_POS_X, OPTION_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(OPTION_WIDTH, OPTION_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(OPTION_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, OPTION_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(OPTION_TEXTURE_UV_U, OPTION_TEXTURE_UV_V);

	pVtx += 4;	// �|�C���^�i�s(4)

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffOption->Unlock();
}

//===========================================================================
// �I������(Option)
//===========================================================================
void UninitOption(void)
{
	// �e�N�X�`���j��
	if (g_pTextureOption != NULL)
	{ 
		g_pTextureOption->Release(); g_pTextureOption = NULL;
	}

	// ���_�o�b�t�@�j��
	if (g_pVtxBuffOption != NULL)
	{ 
		g_pVtxBuffOption->Release(); g_pVtxBuffOption = NULL;
	}
}

//===========================================================================
// �X�V����(Option)
//===========================================================================
void UpdateOption(void)
{
	FADE fade = GetFade();
	JoyState pJoystate = GetJoystate();		//�W���C�p�b�h�̐ڑ����m�F

	//�W���C�p�b�h�̓��͏��擾
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateOption.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//�W���C�p�b�h�̘A�Ŗh�~

			if (fade != FADE_OUT)
			{
				// ���[�h�ݒ�
				SetFade(MODE_TITLE);
				// ���艹
				PlaySound(SOUND_LABEL_SE_DECISION);
			}
		}
		g_JoyStateOption.nJoypadState = INPUT_JOYSTATE_PUSH;  //�W���C�p�b�h��������Ԃɂ���
	}

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateOption.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateOption.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateOption.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateOption.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//===========================================================================
// �`�揈��(Option)
//===========================================================================
void DrawOption(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffOption, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureOption);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}