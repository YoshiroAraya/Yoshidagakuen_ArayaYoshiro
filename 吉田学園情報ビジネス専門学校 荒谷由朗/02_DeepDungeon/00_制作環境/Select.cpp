//=============================================================================
//
// �X�e�[�W�ړ��Z���N�g���� [Pause.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "inputx.h"
#include "Stagefade.h"
#include "Select.h"
#include "Select_NO.h"
#include "Select_YES.h"
#include "SelectBG.h"
#include "player.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
STAGESERECTSTATE	g_SelectMode = STAGESERECTSATE_NONE;
int					g_nSelectManu;
JoyState			g_JoyStateSelect;		// �W���C�p�b�h�̏��

//=============================================================================
// �X�e�[�W�ړ��Z���N�g����������[InitPolygon]
//=============================================================================
void InitSelect(void)
{
	g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	//�Z���N�g��ʔw�i�̏���������
	InitSelectBG();

	//�Z���N�g���No�̏���������
	InitSelectNo();

	//�Z���N�g���Yes�̏���������
	InitSelectYes();
}

//=============================================================================
//�X�e�[�W�ړ��Z���N�g�I������ [UninitPolygon]
//=============================================================================
void UninitSelect(void)
{
	//�Z���N�g��ʔw�i�̏I������
	UninitSelectBG();

	//�Z���N�g���No�̏I������
	UninitSelectNo();

	//�Z���N�g���Yes�̏I������
	UninitSelectYes();
}

//=============================================================================
// �X�e�[�W�ړ��Z���N�g�X�V����[UpdataPolygon]
//=============================================================================
void UpdateSelect(void)
{
	FADE pFade = GetFade();					//�t�F�[�h��Ԃ̎擾
	PLAYER *pPlayer = GetPlayer();			//�v���C���[���̎擾
	STAGEFADE pStageFade = GetStageFade();		//�t�F�[�h�󋵂��擾
	STAGEMODE pStageMode = GetStageMode();	//�X�e�[�W���[�h�̎擾
	JoyState pJoystate = GetJoystate();		//�W���C�p�b�h�̐ڑ����m�F

	//�W���C�p�b�h�̓��͏��擾
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_A) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && pJoystate.bConnectionJoypad == true))
	{//A�L�[�J�[�\������ or PRESS GAMEPAD RIGHTPAD
		if (g_JoyStateSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//�W���C�p�b�h�̘A�Ŗh�~
			PlaySound(SOUND_LABEL_SE_SELECT);

			g_nSelectManu = (g_nSelectManu + 1) % 2;
		}
		g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_PUSH; //�W���C�p�b�h��������Ԃɂ���
	}

	if (GetKeyboardTrigger(DIK_D) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && pJoystate.bConnectionJoypad == true))
	{//D�L�[�J�[�\������ or PRESS GAMEPAD LEFTPAD
		if (g_JoyStateSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//�W���C�p�b�h�̘A�Ŗh�~
			PlaySound(SOUND_LABEL_SE_SELECT);

			g_nSelectManu = (g_nSelectManu + 1) % 2;
		}
		g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_PUSH; //�W���C�p�b�h��������Ԃɂ���
	}

	if (g_nSelectManu == 0)
	{//YES�ɃJ�[�\���������Ă���
		SetSelectYes(YESSTATE_SELECT);//Yes���I�΂�Ă�����
		SetSelectNo(NOSTATE_NOSELECT);//No�͑I�΂�ĂȂ����
		if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
		{//��ɐi�� or PRESS GAMEPAD BKEY
			if (g_JoyStateSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
			{//�W���C�p�b�h�̘A�Ŗh�~
				if (pStageFade != STAGEFADE_OUT)
				{//Enter�A�łɂ��_�Ŗh�~
					PlaySound(SOUND_LABEL_SE_DECISION);

					g_SelectMode = STAGESERECTSATE_YES;
				}
			}
			g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_PUSH;  //�W���C�p�b�h��������Ԃɂ���
		}
	}

	if (g_nSelectManu == 1)
	{//NO�ɃJ�[�\���������Ă���
		SetSelectYes(YESSTATE_NOSELECT);//Yes�͑I�΂�Ă��Ȃ�
		SetSelectNo(NOSTATE_SELECT);	//No���I�΂�Ă���
		if (GetKeyboardTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoystate.bConnectionJoypad == true))
		{//�i�܂Ȃ� or PRESS GAMEPAD BKEY
			if (g_JoyStateSelect.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
			{//�W���C�p�b�h�̘A�Ŗh�~
				if (pStageFade != STAGEFADE_OUT)
				{//Enter�A�łɂ��_�Ŗh�~
					PlaySound(SOUND_LABEL_SE_DECISION);

					g_SelectMode = STAGESERECTSATE_NO;
				}
			}
			g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_PUSH; //�W���C�p�b�h��������Ԃɂ���
		}
	}

	switch (g_SelectMode)
	{
	case STAGESERECTSATE_YES:
		if (pStageMode == STAGEMODE_STAGE1)
		{//�X�e�[�W1����2�ֈړ�
			SetStageFade(STAGEMODE_STAGE2);
			g_SelectMode = STAGESERECTSATE_NONE;
			SetSelect(false);
			pPlayer->pos = D3DXVECTOR3(350.0f, 0.0f, -350.0f);	//�v���C���[�̈ʒu���ړ�������		
			pPlayer->rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 00.0f);	//�v���C���[�̈ʒu���ړ�������		
			break;
		}
		else if (pStageMode == STAGEMODE_STAGE2)
		{//�X�e�[�W2����3�ֈړ�
			SetStageFade(STAGEMODE_STAGE3);
			g_SelectMode = STAGESERECTSATE_NONE;
			SetSelect(false);
			pPlayer->pos = D3DXVECTOR3(350.0f, 0.0f, -350.0f);	//�v���C���[�̈ʒu���ړ�������		
			pPlayer->rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 00.0f);	//�v���C���[�̈ʒu���ړ�������		
			break;
		}
		else if (pStageMode == STAGEMODE_STAGE3)
		{//�X�e�[�W3����4�Ɉړ�
			SetGameState(GAMESTATE_CLEAR);
			g_SelectMode = STAGESERECTSATE_NONE;
			SetSelect(false);
			pPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�v���C���[�̈ʒu���ړ�������
			break;
		}
	case STAGESERECTSATE_NO:
		g_SelectMode = STAGESERECTSATE_NONE;
		SetSelect(false);
		pPlayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�v���C���[�̈ړ�����߂�
		pPlayer->pos = pPlayer->posOld;				//�v���C���[�̈ʒu���ړ�������
		break;
	}

	//�Z���N�g��ʂ̔w�i�̍X�V����
	UpdateSelectBG();

	//�Z���N�g���No�̍X�V����
	UpdateSelectNo();

	//�Z���N�g���Yes�̍X�V����
	UpdateSelectYes();

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateSelect.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateSelect.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateSelect.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �X�e�[�W�ړ��Z���N�g�`�ʏ���[DrawPolygon]
//=============================================================================
void DrawSelect(void)
{
	//�Z���N�g��ʂ̔w�i�̕`�揈��
	DrawSelectBG();
	
	//�Z���N�g���No�̕`�揈��
	DrawSelectNo();

	//�Z���N�g���Yes�̕`�揈��
	DrawSelectYes();
}