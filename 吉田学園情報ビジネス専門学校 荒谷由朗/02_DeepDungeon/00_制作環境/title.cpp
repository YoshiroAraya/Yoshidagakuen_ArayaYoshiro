//***************************************************************************//
//
// Title Processing [Title.cpp]
// Author : TEAM_Fascinator
//
//***************************************************************************//
#include "main.h"
#include "input.h"
#include "inputx.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//***************************************************************************//
// �}�N����`(Title)
//***************************************************************************//
#define TITLE_TEXTURE		"data/TEXTURE/title000.jpg"		// TitleBack
#define TITLE_TEXTURE2		"data/TEXTURE/New Game.png"		// New Game
#define TITLE_TEXTURE3		"data/TEXTURE/Gallery.png"		// Gallery
#define TITLE_TEXTURE4		"data/TEXTURE/Option.png"		// Option
#define TITLE_TEXTURE5		"data/TEXTURE/Title.png"	// TitleLogo
#define MAX_TEXTURE			(5)								// �e�N�X�`����
#define MAX_SELECT_NUM		(3)								// �I�����̐�
#define TITLE_POS_X			(0.0f)							// ����X���W
#define TITLE_POS_Y			(0.0f)							// ����Y���W
#define TITLE_WIDTH			(SCREEN_WIDTH)					// ��
#define TITLE_HEIGHT		(SCREEN_HEIGHT)					// ����
#define TITLELOGO_WIDTH			(500)					// ��
#define TITLELOGO_HEIGHT		(200)					// ����
#define TITLE_TEXTURE_UV_U	(1.0f)							// �A�j���[�V����U�͈�
#define TITLE_TEXTURE_UV_V	(1.0f)							// �A�j���[�V����V�͈�
#define TITLE_SPEED			(0.003f)						// �X�s�[�h

//***************************************************************************//
// �O���[�o���ϐ�(Title)
//***************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureTitle[MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
JoyState				g_JoyStateTitle;					// �W���C�p�b�h�̏��
D3DXVECTOR3				g_posTitle;							// �ʒu
D3DXVECTOR3				g_moveTitle;						// �ړ�
int						g_SelectNum_Title;					// �I��ԍ�
float					g_SelectColor_Title;				// �I��F
int						g_nSelectCount = 0;					// �I�����_�ŗp
D3DXVECTOR3				g_LogoPos;
//===========================================================================//
// ����������(Title)
//===========================================================================//
void InitTitle(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posTitle = D3DXVECTOR3((TITLE_POS_X + TITLE_WIDTH) / 2, (TITLE_POS_Y + TITLE_HEIGHT) / 2, 0.0f);	// ���S�l
	g_LogoPos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -100.0f, 0.0f);
	g_moveTitle = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);													// �ړ��l
	g_SelectNum_Title = CHOICE_ONE;																		// �I��ԍ�
	g_SelectColor_Title = 1.0f;																			// �I���J���[
	g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE,  &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE2, &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE3, &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE4, &g_pTextureTitle[3]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE5, &g_pTextureTitle[4]);

	float PosTitle = (SCREEN_HEIGHT / 2) + 50;

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE, 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++, pVtx += 4)
	{
		if (nCnt == 0)	// �w�i
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		}
		else if (nCnt == 1 || nCnt == 2 || nCnt == 3)	// ���j���[
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(TITLE_WIDTH / 2 - 200.0f, PosTitle, 0.0f);			// ����
			pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH / 2 + 200.0f, PosTitle, 0.0f);			// �E��
			pVtx[2].pos = D3DXVECTOR3(TITLE_WIDTH / 2 - 200.0f, PosTitle + 100.0f, 0.0f);	// ����
			pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH / 2 + 200.0f, PosTitle + 100.0f, 0.0f);	// �E��

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ��
			PosTitle += 100;
		}
		else // �^�C�g�����S
		{
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(-TITLELOGO_WIDTH, -TITLELOGO_HEIGHT, 0.0f) + g_LogoPos;
			pVtx[1].pos = D3DXVECTOR3(TITLELOGO_WIDTH, -TITLELOGO_HEIGHT, 0.0f) + g_LogoPos;
			pVtx[2].pos = D3DXVECTOR3(-TITLELOGO_WIDTH, TITLELOGO_HEIGHT, 0.0f) + g_LogoPos;
			pVtx[3].pos = D3DXVECTOR3(TITLELOGO_WIDTH, TITLELOGO_HEIGHT , 0.0f) + g_LogoPos;

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//===========================================================================//
// �I������(Title)
//===========================================================================//
void UninitTitle(void)
{
	// �e�N�X�`���j��
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_pTextureTitle[nCntTex] != NULL)
		{ 
			g_pTextureTitle[nCntTex]->Release(); g_pTextureTitle[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�j��
	if (g_pVtxBuffTitle != NULL) 
	{ 
		g_pVtxBuffTitle->Release(); g_pVtxBuffTitle = NULL;
	}
}

//===========================================================================//
// �X�V����(Title)
//===========================================================================//
void UpdateTitle(void)
{
	FADE fade = GetFade();
	JoyState pJoystate = GetJoystate();

	XINPUT_STATE state;
	XInputGetState(0, &state);

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);

			// ���_�J���[
			for (int nCntCol = 0; nCntCol < 4; nCntCol++)
			{
				pVtx[g_SelectNum_Title * 4 + nCntCol + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}
			g_SelectNum_Title = (g_SelectNum_Title + 2) % 3;
			g_SelectColor_Title = 1.0f;
		}
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);

			// ���_�J���[
			for (int nCntCol = 0; nCntCol < 4; nCntCol++)
			{
				pVtx[g_SelectNum_Title * 4 + nCntCol + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}
			g_SelectNum_Title = (g_SelectNum_Title + 1) % 3;
			g_SelectColor_Title = 1.0f;
		}
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (g_nSelectCount == 0)
	{//�I�����̓����x�������Ă���
		g_SelectColor_Title -= 0.012f;
		if (g_SelectColor_Title <= 0.1f)
		{
			g_SelectColor_Title = 0.1f;
			g_nSelectCount = 1;
		}
	}
	else if (g_nSelectCount == 1)
	{//�I�����̓����x���グ�Ă���
		g_SelectColor_Title += 0.012f;
		if (g_SelectColor_Title >= 1.0f)
		{
			g_SelectColor_Title = 1.0f;
			g_nSelectCount = 0;
		}
	}

	// ���_�J���[
	for (int nCntCol = 0; nCntCol < 4; nCntCol++)
	{
		pVtx[g_SelectNum_Title * 4 + nCntCol + 4].col = D3DXCOLOR(g_SelectColor_Title, g_SelectColor_Title, g_SelectColor_Title, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			if (fade != FADE_OUT)
			{

				if (g_SelectNum_Title == 0)
				{// �j���[�Q�[��
					StopSound();
					PlaySound(SOUND_LABEL_SE_DECISION);

					SetFade(MODE_SELECT);
				}
				else if (g_SelectNum_Title == 1)
				{// �M�������[
					StopSound();
					PlaySound(SOUND_LABEL_SE_DECISION);
					SetFade(MODE_PROLOGUE);
				}
				else if (g_SelectNum_Title == 2)
				{// �I�v�V����
					StopSound();
					PlaySound(SOUND_LABEL_SE_DECISION);
					SetFade(MODE_OPTION);
				}
			}
		}
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//===========================================================================//
// �`�揈��(Title)
//===========================================================================//
void DrawTitle(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	
	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		// �e�N�X�`��
		pDevice->SetTexture(0, g_pTextureTitle[nCntTex]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}
}