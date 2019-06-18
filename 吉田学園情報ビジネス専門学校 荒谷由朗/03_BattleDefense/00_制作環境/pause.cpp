//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : �r�J�R�N
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "inputx.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PAUSE_POLYGON		(5)								// �|�[�Y�|���S���ő吔
#define MAX_PAUSE_TEXTURE		(4)								// �|�[�Y�e�N�X�`���ő吔
#define PAUSE_TEXTURE_NAME_1	"data\\TEXTURE\\pause100.png"	// �ǂݍ��ރe�N�X�`���t�@�C��1
#define PAUSE_TEXTURE_NAME_2	"data\\TEXTURE\\pause000.png"	// �ǂݍ��ރe�N�X�`���t�@�C��2
#define PAUSE_TEXTURE_NAME_3	"data\\TEXTURE\\pause001.png"	// �ǂݍ��ރe�N�X�`���t�@�C��3
#define PAUSE_TEXTURE_NAME_4	"data\\TEXTURE\\pause002.png"	// �ǂݍ��ރe�N�X�`���t�@�C��4
#define PAUSE_POS_X				(0)								// �|�[�Y�̍���X���W
#define PAUSE_POS_Y				(0)								// �|�[�Y�̍���Y���W
#define PAUSE_WIDTH				(SCREEN_WIDTH)					// �|�[�Y�̕�
#define PAUSE_HEIGHT			(SCREEN_HEIGHT)					// �|�[�Y�̍���
#define PAUSE_TEXTURE_SPEED		(5)								// �e�N�X�`���A�j���[�V�����X�s�[�h
#define PAUSE_TEXTURE_PATTERN	(10)							// �e�N�X�`���A�j���[�V�����p�^�[����
#define PAUSE_TEXTURE_UV_U		(1.0f)							// �e�N�X�`���A�j���[�V����U�͈�
#define PAUSE_TEXTURE_UV_V		(1.0f)							// �e�N�X�`���A�j���[�V����V�͈�
#define PAUSE_BACKTEXTURE_UV_U	(1.0f)							// �O�e�N�X�`���A�j���[�V����U�͈�
#define PAUSE_BACKTEXTURE_UV_V	(1.0f)							// �O�e�N�X�`���A�j���[�V����V�͈�
#define PAUSE_SPEED				(0.002f)						// �|�[�Y�X�s�[�h

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9				g_pTexturePause[MAX_PAUSE_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffPause = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3						g_posPause;									// �|�[�Y�̈ʒu
JoyState						g_JoyStatePause;
int								g_SelectNum;								// �I��ԍ�
float							g_SelectColor;								// �I��F

//=============================================================================
// �|�[�Y����������
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾
	g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	int nCntPause;								// �|�[�Y�J�E���^

	g_posPause		= D3DXVECTOR3((PAUSE_POS_X + PAUSE_WIDTH) / 2, (PAUSE_POS_Y + PAUSE_HEIGHT) / 2, 0.0f);		// �|�[�Y�̒��S�l
	g_SelectNum		= 0;						// �I��ԍ�
	g_SelectColor	= 1.0f;						// �I���J���[
	float fPosPause = -150;						// �|�[�Y�ʒu

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(// �|�[�Y
		pDevice,
		PAUSE_TEXTURE_NAME_1,
		&g_pTexturePause[0]
	);
	D3DXCreateTextureFromFile
	(// �R���e�j���[
		pDevice,
		PAUSE_TEXTURE_NAME_2,
		&g_pTexturePause[1]
	);
	D3DXCreateTextureFromFile
	(// ���g���C
		pDevice,
		PAUSE_TEXTURE_NAME_3,
		&g_pTexturePause[2]
	);
	D3DXCreateTextureFromFile
	(// �N�E�B�b�g
		pDevice,
		PAUSE_TEXTURE_NAME_4,
		&g_pTexturePause[3]
	);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_PAUSE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL
	);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntPause = 0; nCntPause < MAX_PAUSE_POLYGON; nCntPause++)
	{// �|�[�Y���J�E���g
		if (nCntPause == 0)
		{// BG
		 // ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
		}
		else if (nCntPause == 1)
		{// �|�[�Y
		 // ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) - 180, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) - 180, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + 180, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + 180, 0.0f);
			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
		}
		else
		{// �|�[�Y���j���[
		 // ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + fPosPause + 100, 0.0f);

			if (nCntPause == 2)
			{
				// ���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				// ���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			}

			fPosPause += 100;
		}
		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, PAUSE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, PAUSE_TEXTURE_UV_V);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// �|�[�Y�I������
//=============================================================================
void UninitPause(void)
{
	// �ϐ��錾
	int nCntTex;		// �e�N�X�`���J�E���^

	// �e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_PAUSE_TEXTURE; nCntTex++)
	{// �e�N�X�`�����J�E���g
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
// �|�[�Y�X�V����
//=============================================================================
void UpdatePause(void)
{
	JoyState		pJoyState = GetJoystate();
	XINPUT_STATE	state;
	XInputGetState(0, &state);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	if (GetKeyboardTrigger(DIK_W) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	�g���K�[
		 // ���_�J���[�ݒ�
			pVtx[g_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			g_SelectNum		= (g_SelectNum + 2) % 3;
			g_SelectColor	= 1.0f;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (GetKeyboardTrigger(DIK_S) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	�g���K�[
		 // ���_�J���[�ݒ�
			pVtx[g_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			g_SelectNum		= (g_SelectNum + 1) % 3;
			g_SelectColor	= 1.0f;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	g_SelectColor -= 0.004f;

	if (g_SelectColor < 0.65f)
	{
		g_SelectColor = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[g_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);
	pVtx[g_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);
	pVtx[g_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);
	pVtx[g_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	�g���K�[
		PlaySound(SOUND_LABEL_SE_SELEKUTO);
			if (g_SelectNum == 0)
			{
				SetPauseState(false);
			}
			else if (g_SelectNum == 1)
			{
				SetFade(MODE_GAME);
			}
			else if (g_SelectNum == 2)
			{
				SetFade(MODE_TITLE);
			}
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}

}

//=============================================================================
// �|�[�Y�`�揈��
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�|�C���^
	int nCntPause;					// �|�[�Y�J�E���^
	int nCntTex = 0;				// �e�N�X�`���J�E���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffPause,
		0,
		sizeof(VERTEX_2D)
	);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < MAX_PAUSE_POLYGON; nCntPause++)
	{// �|�[�Y���J�E���g
		if (nCntPause >= 1)
		{
			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTexturePause[nCntTex]);
			nCntTex++;
		}

		// �|�[�Y�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}