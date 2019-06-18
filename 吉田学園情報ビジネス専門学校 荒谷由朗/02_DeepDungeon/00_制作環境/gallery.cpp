//===========================================================================
//
// �M�������[���� [Gallery.cpp]
// Author : TEAM_Fascinator
//
//===========================================================================
#include "main.h"
#include "gallery.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "sound.h"

//===========================================================================
// �}�N����`(Gallery)
//===========================================================================
#define TITLE_TEXTURE_NAME		"data/TEXTURE/Gallery.jpg"	// �e�N�X�`��
#define TITLE_POS_X				(0.0f)						// ����X���W
#define TITLE_POS_Y				(0.0f)						// ����Y���W
#define TITLE_WIDTH				(SCREEN_WIDTH)				// ��
#define TITLE_HEIGHT			(SCREEN_HEIGHT)				// ����
#define TITLE_TEXTURE_UV_U		(1.0f)						// �A�j���[�V����U�͈�
#define TITLE_TEXTURE_UV_V		(1.0f)						// �A�j���[�V����V�͈�
#define TITLE_SPEED				(0.003f)					// �X�s�[�h

//===========================================================================
// �O���[�o���ϐ�(Gallery)
//===========================================================================
LPDIRECT3DTEXTURE9 g_pTextureGallery = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGallery = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posGallery;								// �ʒu
D3DXVECTOR3 g_moveGallery;								// �ړ�
JoyState	g_JoyStateGallery;							// �W���C�p�b�h�̏��

//===========================================================================
// ����������(Gallery)
//===========================================================================
void InitGallery(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posGallery = D3DXVECTOR3((TITLE_POS_X + TITLE_WIDTH) / 2, (TITLE_POS_Y + TITLE_HEIGHT) / 2, 0.0f);	// ���S�l
	g_moveGallery = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);													// �ړ��l
	g_JoyStateGallery.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME, &g_pTextureGallery);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2, 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D, 
		D3DPOOL_MANAGED,
		&g_pVtxBuffGallery, 
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffGallery->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V);

	pVtx += 4;	// �|�C���^�i�s(4)

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffGallery->Unlock();
}

//===========================================================================
// �I������(Gallery)
//===========================================================================
void UninitGallery(void)
{
	// �e�N�X�`���j��
	if (g_pTextureGallery != NULL)
	{
		g_pTextureGallery->Release();
		g_pTextureGallery = NULL;
	}
	// ���_�o�b�t�@�j��
	if (g_pVtxBuffGallery != NULL)
	{ 
		g_pVtxBuffGallery->Release(); 
		g_pVtxBuffGallery = NULL;
	}
}

//===========================================================================
// �X�V����(Gallery)
//===========================================================================
void UpdateGallery(void)
{
	JoyState pJoystate = GetJoystate();		//�W���C�p�b�h�̐ڑ����m�F
	FADE fade = GetFade();

	//�W���C�p�b�h�̓��͏��擾
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateGallery.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//�W���C�p�b�h�̘A�Ŗh�~
			if (fade != FADE_OUT)
			{
				// ���[�h�ݒ�
				SetFade(MODE_TITLE);
				// ���艹
				StopSound();
				PlaySound(SOUND_LABEL_SE_DECISION);
				PlaySound(SOUND_LABEL_BGM000);
			}
		}
		g_JoyStateGallery.nJoypadState = INPUT_JOYSTATE_PUSH;  //�W���C�p�b�h��������Ԃɂ���
	}

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateGallery.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateGallery.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateGallery.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateGallery.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//===========================================================================
// �`�揈��(Gallery)
//===========================================================================
void DrawGallery(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGallery, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureGallery);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}