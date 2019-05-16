//=========================================================================================================================
// 
// �|�[�Y���� [pause.cpp]
// Author : TEAM_Fascinator
// 
//=========================================================================================================================
#include "pause.h"		
#include "fade.h"		
#include "input.h"
#include "inputx.h"
#include "game.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define PAUSE_TEXTURE_NAME_1	"data/TEXTURE/pausebg.png"		// �ǂݍ��ރe�N�X�`���t�@�C��1
#define PAUSE_TEXTURE_NAME_2	"data/TEXTURE/Continue.png"		// �ǂݍ��ރe�N�X�`���t�@�C��2
#define PAUSE_TEXTURE_NAME_3	"data/TEXTURE/Quit.png"			// �ǂݍ��ރe�N�X�`���t�@�C��4
#define MAX_PAUSE_TEXTURE		(3)								// �|�[�Y�e�N�X�`���ő吔
#define PAUSE_POS_X				(0)								// �|�[�Y�̍���X���W
#define PAUSE_POS_Y				(0)								// �|�[�Y�̍���Y���W
#define PAUSE_WIDTH				(SCREEN_WIDTH)					// �|�[�Y�̕�
#define PAUSE_HEIGHT			(SCREEN_HEIGHT)					// �|�[�Y�̍���
#define PAUSE_TEXTURE_UV_U		(1.0f)							// �e�N�X�`���A�j���[�V����U�͈�
#define PAUSE_TEXTURE_UV_V		(1.0f)							// �e�N�X�`���A�j���[�V����V�͈�

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3DTEXTURE9			g_pTexturePause[MAX_PAUSE_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPause = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3					g_posPause;						// �|�[�Y�̈ʒu
JoyState					g_JoyStatePause;				// �W���C�p�b�h�̏��
int							g_SelectNum;					// �I��ԍ�
float						g_SelectColor;					// �I��F
int							g_nPauseCount = 0;				// �I�����_�ŗp

//=========================================================================================================================
// �|�[�Y����������
//=========================================================================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾

	g_posPause = D3DXVECTOR3((PAUSE_POS_X + PAUSE_WIDTH) / 2, (PAUSE_POS_Y + PAUSE_HEIGHT) / 2, 0.0f);		// �|�[�Y�̒��S�l
	g_SelectColor = 1.0f;						// �I���J���[

	float fPosPause = -120.0f;						// �|�[�Y�ʒu

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,PAUSE_TEXTURE_NAME_1,&g_pTexturePause[0]);	//pause
	D3DXCreateTextureFromFile(pDevice,PAUSE_TEXTURE_NAME_2,&g_pTexturePause[1]);	//continue
	D3DXCreateTextureFromFile(pDevice,PAUSE_TEXTURE_NAME_3,&g_pTexturePause[2]);	//quit

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE_TEXTURE,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPause,
								NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	g_pVtxBuffPause->Lock(0,0,(void**)&pVtx,0);	// ���_�o�b�t�@�����b�N

	for (int nCount = 0; nCount < MAX_PAUSE_TEXTURE; nCount++)
	{
		if (nCount == 0)
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) - 180, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) - 180, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + 180, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + 180, 0.0f);

			// ���_�J���[
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + fPosPause + 100, 0.0f);

			if (nCount == 1)
			{	//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{	//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// ��
			fPosPause += 150.0f;
		}

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, PAUSE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, PAUSE_TEXTURE_UV_V);

		pVtx += 4;
	}

	g_pVtxBuffPause->Unlock();	// ���_�o�b�t�@���A�����b�N
}

//=========================================================================================================================
// �|�[�Y�I������
//=========================================================================================================================
void UninitPause(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_PAUSE_TEXTURE; nCntTex++)
	{
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

//=========================================================================================================================
// �|�[�Y�X�V����
//=========================================================================================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^
	FADE fade = GetFade();

	//�R���g���[���[�֌W
	JoyState pJoystate = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true ||
		(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && pJoystate.bConnectionJoypad == true) || 
		(state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true))
	{//��
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			// ���_�J���[�ݒ�
			pVtx[g_SelectNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[g_SelectNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[g_SelectNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[g_SelectNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_SelectNum = (g_SelectNum + 1) % 2;
			g_SelectColor = 1.0f;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true ||
		(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && pJoystate.bConnectionJoypad == true) ||
		(state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true))
	{//��
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			// ���_�J���[�ݒ�
			pVtx[g_SelectNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[g_SelectNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[g_SelectNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[g_SelectNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_SelectNum = (g_SelectNum + 1) % 2;
			g_SelectColor = 1.0f;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (g_nPauseCount == 0)
	{
		g_SelectColor -= 0.01f;	// �s�����x�������Ă���
		if (g_SelectColor <= 0.5f)
		{// �Â�����
			g_nPauseCount = 1;
			g_SelectColor = 0.5f;
		}
	}
	else if (g_nPauseCount == 1)
	{
		g_SelectColor += 0.01f;	// �s�����x���グ�Ă���
		if (g_SelectColor >= 1.0f)
		{// ���邭����
			g_nPauseCount = 0;
			g_SelectColor = 1.0f;
		}
	}

	// ���_�J���[
	pVtx[g_SelectNum * 4 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
	pVtx[g_SelectNum * 4 + 1 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
	pVtx[g_SelectNum * 4 + 2 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
	pVtx[g_SelectNum * 4 + 3 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);

	g_pVtxBuffPause->Unlock();	// ���_�o�b�t�@���A�����b�N

	if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
	{// ���[�h�I��
		if (fade != FADE_OUT && g_JoyStatePause.nJoypadState == 0)
		{
			if (g_SelectNum == 0)
			{// continue
				SetPauseState(false);
			}
			else if (g_SelectNum == 1)
			{// quit
				SetFade(MODE_TITLE);
			}
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	else if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoystate.bConnectionJoypad == true))
	{
		SetPauseState(false);
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

//=========================================================================================================================
// �|�[�Y�`�揈��
//=========================================================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,g_pVtxBuffPause,0,sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_PAUSE_TEXTURE; nCount++)
	{
		// �e�N�X�`��
		pDevice->SetTexture(0, g_pTexturePause[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}