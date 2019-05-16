//=============================================================================
//
// ����ʏ��� [char_select.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "main.h"
#include "char_select.h"
#include "fade.h"
#include "input.h"
#include "inputx.h"
#include "bg.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SELECT_TEXTURENAME_1	"DATA/TEXTURE/select.png"		//�L�����I���̉摜
#define SELECT_TEXTURENAME_2	"DATA/TEXTURE/s.jpeg"			//�L�����I���̔w�i
#define SELECT_TEXTURENAME_3	"DATA/TEXTURE/player100.png"	//�L������(�\���W���[)
#define SELECT_TEXTURENAME_4	"DATA/TEXTURE/player101.png"	//�L������(�E�H���A�[)
#define SELECT_TEXTURENAME_5	"DATA/TEXTURE/player102.png"	//�L������(�\�[�T���[)
#define MAX_TYPE_SELECT			(5)								//�g���e�N�X�`���̐�
#define MAX_SELECT				(5)								//�\������e�N�X�`���̐�
#define WIDTH					(1000)							//��
#define HEIGHT					(670)							//����
#define CHARACTER_WIDTH			(130)							//�L�����̕�
#define CHARACTER_HEIGHT		(35)							//�L�����̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureCharSelect[MAX_TYPE_SELECT] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharSelect = NULL;				//���_�o�b�t�@�ւ̃|�C���^
CHARACTER_TYPE g_CharaType = CHARACTER_TYPE_SORCERER;				//�����L�����^�C�v
SELECT g_aCharSelect[MAX_SELECT];									//�Z���N�g�̏��
JoyState g_JoyStateCharSelect;										//�W���C�p�b�h�̏��
int g_nCharSelectPage;												//�I��ԍ�

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitCharSelect(void)
{
	InitBG();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int nCntCharSelect = 0; nCntCharSelect < MAX_SELECT; nCntCharSelect++)
	{
		g_aCharSelect[nCntCharSelect].state = SELECTSTATE_NONE;
		g_aCharSelect[nCntCharSelect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCharSelect[nCntCharSelect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	g_JoyStateCharSelect.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	g_aCharSelect[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 125, SCREEN_HEIGHT / 2, 0.0f);
	g_aCharSelect[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 510, 400, 0.0f);
	g_aCharSelect[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 520, 300, 0.0f);
	g_aCharSelect[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 520, 400, 0.0f);
	g_aCharSelect[4].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 520, 500, 0.0f);

	g_aCharSelect[0].bUse = true;
	g_aCharSelect[1].bUse = true;
	g_aCharSelect[2].bUse = true;
	g_aCharSelect[3].bUse = true;
	g_aCharSelect[4].bUse = true;

	g_nCharSelectPage = PAGE_ONE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SELECT_TEXTURENAME_1, &g_pTextureCharSelect[0]);
	D3DXCreateTextureFromFile(pDevice, SELECT_TEXTURENAME_2, &g_pTextureCharSelect[1]);
	D3DXCreateTextureFromFile(pDevice, SELECT_TEXTURENAME_3, &g_pTextureCharSelect[2]);
	D3DXCreateTextureFromFile(pDevice, SELECT_TEXTURENAME_4, &g_pTextureCharSelect[3]);
	D3DXCreateTextureFromFile(pDevice, SELECT_TEXTURENAME_5, &g_pTextureCharSelect[4]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharSelect,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCharSelect->Lock(0, 0, (void**)&pVtx, 0);

	//�L�����ڍ׉摜===================================================================================================
	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aCharSelect[0].pos.x - WIDTH / 2, g_aCharSelect[0].pos.y - HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharSelect[0].pos.x + WIDTH / 2, g_aCharSelect[0].pos.y - HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharSelect[0].pos.x - WIDTH / 2, g_aCharSelect[0].pos.y + HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharSelect[0].pos.x + WIDTH / 2, g_aCharSelect[0].pos.y + HEIGHT / 2, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.33f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.33f);

	pVtx += 4;

	//�w�i=============================================================================================================
	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aCharSelect[1].pos.x - 120, g_aCharSelect[1].pos.y - 180, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharSelect[1].pos.x + 120, g_aCharSelect[1].pos.y - 180, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharSelect[1].pos.x - 120, g_aCharSelect[1].pos.y + 180, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharSelect[1].pos.x + 120, g_aCharSelect[1].pos.y + 180, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�L�����P=========================================================================================================
	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aCharSelect[2].pos.x - CHARACTER_WIDTH, g_aCharSelect[2].pos.y - CHARACTER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharSelect[2].pos.x + CHARACTER_WIDTH, g_aCharSelect[2].pos.y - CHARACTER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharSelect[2].pos.x - CHARACTER_WIDTH, g_aCharSelect[2].pos.y + CHARACTER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharSelect[2].pos.x + CHARACTER_WIDTH, g_aCharSelect[2].pos.y + CHARACTER_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�L�����Q=========================================================================================================
	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aCharSelect[3].pos.x - CHARACTER_WIDTH, g_aCharSelect[3].pos.y - CHARACTER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharSelect[3].pos.x + CHARACTER_WIDTH, g_aCharSelect[3].pos.y - CHARACTER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharSelect[3].pos.x - CHARACTER_WIDTH, g_aCharSelect[3].pos.y + CHARACTER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharSelect[3].pos.x + CHARACTER_WIDTH, g_aCharSelect[3].pos.y + CHARACTER_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�L�����R=========================================================================================================
	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aCharSelect[4].pos.x - CHARACTER_WIDTH, g_aCharSelect[4].pos.y - CHARACTER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharSelect[4].pos.x + CHARACTER_WIDTH, g_aCharSelect[4].pos.y - CHARACTER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharSelect[4].pos.x - CHARACTER_WIDTH, g_aCharSelect[4].pos.y + CHARACTER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharSelect[4].pos.x + CHARACTER_WIDTH, g_aCharSelect[4].pos.y + CHARACTER_HEIGHT, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCharSelect->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitCharSelect(void)
{
	UninitBG();
	for (int nCntCharSelect = 0; nCntCharSelect < MAX_TYPE_SELECT; nCntCharSelect++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureCharSelect[nCntCharSelect] != NULL)
		{
			g_pTextureCharSelect[nCntCharSelect]->Release();
			g_pTextureCharSelect[nCntCharSelect] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCharSelect != NULL)
	{
		g_pVtxBuffCharSelect->Release();
		g_pVtxBuffCharSelect = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateCharSelect(void)
{
	UpdateBG();
	JoyState pJoystate = GetJoystate();
	FADE pFade = GetFade();
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateCharSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);

			g_nCharSelectPage = (g_nCharSelectPage + (PAGE_MAX - 1)) % PAGE_MAX;	//�I����Ԃ���グ��		
		}
		g_JoyStateCharSelect.nJoypadState = INPUT_JOYSTATE_PUSH;
	}


	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && pJoystate.bConnectionJoypad == true))
	{
		if (g_JoyStateCharSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			PlaySound(SOUND_LABEL_SE_SELECT);

			g_nCharSelectPage = (g_nCharSelectPage + 1) % PAGE_MAX;	//�I����Ԃ��������
		}
		g_JoyStateCharSelect.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
		{
			if (g_JoyStateCharSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
			{
				// ���艹
				PlaySound(SOUND_LABEL_SE_DECISION);

				if (g_nCharSelectPage == 0)
				{//�L�����^�C�v�F�\���W���[
					g_CharaType = CHARACTER_TYPE_SOLDIER;
				}
				else if (g_nCharSelectPage == 1)
				{//�L�����^�C�v�F�E�H���A�[
					g_CharaType = CHARACTER_TYPE_WARRIOR;
				}
				else if (g_nCharSelectPage == 2)
				{//�L�����^�C�v�F�\�[�T���[
					g_CharaType = CHARACTER_TYPE_SORCERER;
				}

				SetFade(MODE_TUTO);
				//SetStageMode(STAGEMODE_STAGE1);
			}
			g_JoyStateCharSelect.nJoypadState = INPUT_JOYSTATE_PUSH;
		}
	}

	switch (g_nCharSelectPage)
	{
	case PAGE_ONE:
		g_aCharSelect[2].select = true;
		g_aCharSelect[3].select = false;
		g_aCharSelect[4].select = false;

		switch (g_aCharSelect[2].state)
		{
		case SELECTSTATE_NONE:
			g_aCharSelect[2].col.a -= 0.02f;
			if (g_aCharSelect[2].col.a <= 0.0f)
			{//�g���ĂȂ��Ƃ�
				g_aCharSelect[2].col.a = 0.0f;
				g_aCharSelect[2].state = SELECTSTATE_USE;
			}
			break;
		case SELECTSTATE_USE:
			g_aCharSelect[2].col.a += 0.02f;
			if (g_aCharSelect[2].col.a >= 1.0f)
			{//�g���Ă�Ƃ�
				g_aCharSelect[2].col.a = 1.0f;
				g_aCharSelect[2].state = SELECTSTATE_NONE;
			}
			break;
		}
		break;
	case PAGE_TWO:
		g_aCharSelect[2].select = false;
		g_aCharSelect[3].select = true;
		g_aCharSelect[4].select = false;
		switch (g_aCharSelect[3].state)
		{
		case SELECTSTATE_NONE:
			g_aCharSelect[3].col.a -= 0.01f;
			if (g_aCharSelect[3].col.a <= 0.0f)
			{
				g_aCharSelect[3].col.a = 0.0f;
				g_aCharSelect[3].state = SELECTSTATE_USE;
			}
			break;
		case SELECTSTATE_USE:
			g_aCharSelect[3].col.a += 0.01f;
			if (g_aCharSelect[3].col.a >= 1.0f)
			{
				g_aCharSelect[3].col.a = 1.0f;
				g_aCharSelect[3].state = SELECTSTATE_NONE;
			}
			break;
		}
		break;
	case PAGE_THREE:
		g_aCharSelect[2].select = false;
		g_aCharSelect[3].select = false;
		g_aCharSelect[4].select = true;
		switch (g_aCharSelect[4].state)
		{
		case SELECTSTATE_NONE:
			g_aCharSelect[4].col.a -= 0.01f;
			if (g_aCharSelect[4].col.a <= 0.0f)
			{
				g_aCharSelect[4].col.a = 0.0f;
				g_aCharSelect[4].state = SELECTSTATE_USE;
			}
			break;
		case SELECTSTATE_USE:
			g_aCharSelect[4].col.a += 0.01f;
			if (g_aCharSelect[4].col.a >= 1.0f)
			{
				g_aCharSelect[4].col.a = 1.0f;
				g_aCharSelect[4].state = SELECTSTATE_NONE;
			}
			break;
		}
		break;
	}

	if (g_aCharSelect[2].select != true)
	{
		g_aCharSelect[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	if (g_aCharSelect[3].select != true)
	{
		g_aCharSelect[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	if (g_aCharSelect[4].select != true)
	{
		g_aCharSelect[4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCharSelect->Lock(0, 0, (void**)&pVtx, 0);

	if (g_nCharSelectPage == 0)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.33f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.33f);
	}
	if (g_nCharSelectPage == 1)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.34f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.34f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.66f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.66f);
	}
	if (g_nCharSelectPage == 2)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.68f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.68f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	pVtx += 4;
	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aCharSelect[2].col;
	pVtx[1].col = g_aCharSelect[2].col;
	pVtx[2].col = g_aCharSelect[2].col;
	pVtx[3].col = g_aCharSelect[2].col;
	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aCharSelect[3].col;
	pVtx[1].col = g_aCharSelect[3].col;
	pVtx[2].col = g_aCharSelect[3].col;
	pVtx[3].col = g_aCharSelect[3].col;
	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aCharSelect[4].col;
	pVtx[1].col = g_aCharSelect[4].col;
	pVtx[2].col = g_aCharSelect[4].col;
	pVtx[3].col = g_aCharSelect[4].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCharSelect->Unlock();

	if (g_JoyStateCharSelect.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateCharSelect.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateCharSelect.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateCharSelect.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawCharSelect(void)
{
	DrawBG();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharSelect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntCharSelect = 0; nCntCharSelect < MAX_TYPE_SELECT; nCntCharSelect++)
	{
		if (g_aCharSelect[nCntCharSelect].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCharSelect[nCntCharSelect]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCharSelect * 4, 2);
		}
	}
}

//=============================================================================
// �L�����I�����̎擾
//=============================================================================
CHARACTER_TYPE GetCharaType(void)
{
	return g_CharaType;
}