//=============================================================================
//
// �Q�[������ [game.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
#include "inputx.h"
#include "bullet.h"
#include "meshField.h"
#include "explosion.h"
#include "obstacle.h"
#include "fade.h"
#include "score.h"
#include "time.h"
#include "scoreResult.h"
#include "txt.h"
#include "enemy.h"
#include "life.h"
#include "motion.h"
#include "PlayerLife.h"
#include "ObjectLife.h"
#include "pause.h"
#include "sound.h"
//=============================================================================
//�O���[�o��
//=============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[�����
GAMESTATE g_gameStateNow = GAMESTATE_NONE;
JoyState		g_JoyStateGame;
int g_nCounterGameState = 0;
bool g_bPause;								//�|�[�Y�����ǂ���

//=============================================================================
//�Q�[����ʂ̏�����
//=============================================================================
void InitGame(void)
{
	g_bPause = false;
	g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	LoadData();

	// ���b�V���̏���������
	InitMeshField();

	// �ǂ̏���������
	//InitMeshCylinder();
	InitLife();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �e�̏���������
	InitBullet();

	// �����̏���������
	InitExplosion();

	// ���f���̏���������
	InitPlayer();

	// �G�̏���������
	InitEnemy();

	// ��Q���̏���������
	InitObstaclel();

	// �X�R�A�̏���������
	InitScore();

	// �^�C���̏���������
	InitTime();

	// ���[�V�����̏�����
	InitMotion();
	InitPlayerLife();
	InitOBLife();
	// �|�[�Y�̏�����
	InitPause();

	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	/*SetEnemy(D3DXVECTOR3(400.0f, 80.0f, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/
	//PlaySound(SOUND_LABEL_BGM001);
}

//=============================================================================
//�Q�[����ʂ̏I������
//=============================================================================
void UninitGame(void)
{
	// ���b�V���̏I������
	UninitMeshField();

	// �ǂ̏I������
	//UninitMeshCylinder();
	UninitLife();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �e�̏I������
	UninitBullet();

	UninitExplosion();

	// ���f���̏I������
	UninitPlayer();

	// �G�̏I������
	UninitEnemy();

	// ��Q���̏I������
	UninitObstaclel();

	//�@�X�R�A�̏I������
	UninitScore();

	// �^�C���̏I������
	UninitTime();

	// ���[�V�����̏I������
	UninitMotion();
	UninitPlayerLife();
	UninitOBLife();

	// �|�[�Y�̏�����
	UninitPause();

	//StopSound();
}

//=============================================================================
//�Q�[����ʂ̍X�V����
//=============================================================================
void UpdateGame(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_P) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	�g���K�[
			PlaySound(SOUND_LABEL_SE_POUZU);
			g_bPause = g_bPause ? false : true;
		}
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (g_bPause == false)
	{

		// ���b�V���̍X�V����
		UpdateMeshField();

		// �ǂ̍X�V����
		//UpdateMeshCylinder();
		UpdateLife();

		// �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		// �e�̍X�V����
		UpdateBullet();

		// �����̍X�V����
		UpdateExplosion();

		// ���f���̍X�V����
		UpdatePlayer();

		// �G�̍X�V����
		UpdateEnemy();

		// ��Q���̍X�V����
		UpdateObstaclel();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �^�C���̍X�V����
		UpdateTime();

		// ���[�V�����̍X�V
		UpdateMotion();
		UpdatePlayerLife();
		UpdateOBLife();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_CLEAR:
			g_gameStateNow = GAMESTATE_CLEAR;
			g_gameState = GAMESTATE_NONE;
			//��ʁi���[�h)�̐ݒ�
			SetFade(MODE_RESULT);
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 30)
			{
				g_gameStateNow = GAMESTATE_OVER;
				g_gameState = GAMESTATE_NONE;
				//��ʁi���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		}
	}
	else if (g_bPause == true)
	{
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
//�Q�[����ʂ̕`�揈��
//=============================================================================
void DrawGame(void)
{
	// ���b�V���̕`�揈��
	DrawMeshField();

	// �ǂ̕`�揈��
	//DrawMeshCylinder();
	DrawLife();

	// �J�����̐ݒ�
	SetCamera();

	// �e�̕`�揈��
	DrawBullet();

	// �����̕`�揈��
	DrawExplosion();

	// ���f���̕`�揈��
	DrawPlayer();

	// �G�̕`�揈��
	DrawEnemy();

	// ��Q���̕`�揈��
	DrawObstaclel();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �^�C���̕`�揈��
	DrawTime();

	// ���[�V�����̕`�揈��
	DrawMotion();
	DrawPlayerLife();
	DrawOBLife();

	if (g_bPause == true)
	{
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//�Q�[���̏�Ԃ̐ݒ�
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// �Q�[���̏�Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// �Q�[���̏�Ԃ̎擾(����)
//=============================================================================
GAMESTATE GetGameStateNow(void)
{
	return g_gameStateNow;
}
//=============================================================================
// �|�[�Y�̏��
//=============================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}