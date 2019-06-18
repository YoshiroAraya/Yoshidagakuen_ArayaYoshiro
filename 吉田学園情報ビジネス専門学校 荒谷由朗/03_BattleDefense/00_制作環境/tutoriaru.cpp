//=============================================================================
//
// �`���[�g���A������ [tutoriaru.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BG_TEXTURENAME		"data/TEXTURE/BattleDefense_TUTORIAL.png"		// �ǂݍ��ރe�N�X�`��
#define BG_POS_X			(0)												// ���_���W�iX���W�j
#define BG_POS_Y			(0)												// ���_���W�iY���W�j
#define BG_POS_WIDTH		(SCREEN_WIDTH)									// DirectX�̕�
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)									// DirectX�̍���

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTutoriaru = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutoriaru = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
JoyState				g_JoyStateTutoriau;

//=============================================================================
// ����������
//=============================================================================
void InitTutoriaru(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();

	// �R���g���[���[�̎擾
	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateTutoriau.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�N�X�`���̓ǂݍ���
	if (g_JoyState.bConnectionJoypad == true)
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureTutoriaru);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureTutoriaru);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutoriaru,
		NULL);

	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutoriaru->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);	 // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);	 // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);	 // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);	 // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTutoriaru->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutoriaru(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureTutoriaru != NULL)
	{
		g_pTextureTutoriaru->Release();
		g_pTextureTutoriaru = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutoriaru != NULL)
	{
		g_pVtxBuffTutoriaru->Release();
		g_pVtxBuffTutoriaru = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutoriaru(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// �t�F�[�h�̎擾
	FADE fade;
	fade = GetFade();

	// ����L�[�������ꂽ��
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && pJoyState.bConnectionJoypad == true))
	{
		if (fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_SELEKUTO);
			// ���[�h�ݒ�
			SetFade(MODE_GAME);
		}
	}
	if (g_JoyStateTutoriau.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateTutoriau.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateTutoriau.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateTutoriau.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutoriaru(void)
{
	// �f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutoriaru, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutoriaru);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}