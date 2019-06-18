//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : �r�J �R�N
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
// �O���[�o��
//=============================================================================
GAMESTATE	g_gameState			= GAMESTATE_NONE;	// �Q�[�����
GAMESTATE	g_gameStateNow		= GAMESTATE_NONE;	// �Q�[��(����)���
JoyState	g_JoyStateGame;
int			g_nCounterGameState = 0;
bool		g_bPause;								// �|�[�Y�����ǂ���

//=============================================================================
// �Q�[����ʂ̏�����
//=============================================================================
void InitGame(void)
{
	g_bPause = false;
	g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�L�X�g�̓ǂݍ���
	LoadData();

	// ���b�V���̏���������
	InitMeshField();

	// �ǂ̏���������
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

	// �v���C���[���C�t�̏�����
	InitPlayerLife();

	// �I�u�W�F�N�g���C�t�̏�����
	InitOBLife();

	// �|�[�Y�̏�����
	InitPause();

	g_gameState			= GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
}

//=============================================================================
// �Q�[����ʂ̏I������
//=============================================================================
void UninitGame(void)
{
	// ���b�V���̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitLife();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �e�̏I������
	UninitBullet();

	// �����̏I������
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

	// �v���C���[���C�t�̏I������
	UninitPlayerLife();

	// �I�u�W�F�N�g���C�t�̏I������
	UninitOBLife();

	// �|�[�Y�̏I������
	UninitPause();
}

//=============================================================================
// �Q�[����ʂ̍X�V����
//=============================================================================
void UpdateGame(void)
{
	JoyState		pJoyState = GetJoystate();
	XINPUT_STATE	state;
	XInputGetState(0, &state);

	// �|�[�Y
	if (GetKeyboardTrigger(DIK_P) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && pJoyState.bConnectionJoypad == true))
	{// �|�[�Y�{�^������������
		if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	�g���K�[
			PlaySound(SOUND_LABEL_SE_POUZU);
			g_bPause = g_bPause ? false : true;
		}
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (g_bPause == false)
	{// �|�[�Y�{�^���������ĂȂ���
		// ���b�V���̍X�V����
		UpdateMeshField();

		// �ǂ̍X�V����
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

		// ���[�V�����̍X�V����
		UpdateMotion();

		// �v���C���[���C�t�̍X�V����
		UpdatePlayerLife();

		// �I�u�W�F�N�g���C�t�̍X�V����
		UpdateOBLife();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_CLEAR:
			g_gameStateNow	= GAMESTATE_CLEAR;
			g_gameState		= GAMESTATE_NONE;
			// ���U���g���(CLEAR)�̐ݒ�
			SetFade(MODE_RESULT);
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 30)
			{
				g_gameStateNow	= GAMESTATE_OVER;
				g_gameState		= GAMESTATE_NONE;
				// ���U���g���(OVER)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		}

		// �G�l�~�[�̐���
		if (rand() % 200 == 0 && g_gameState == GAMESTATE_NORMAL)
		{
			float fAngle;
			LIFE *g_aCllinder;
			g_aCllinder = GetLife();

			fAngle = atan2f((float)(rand() % 360), (float)(rand() % 360));

			SetEnemy(D3DXVECTOR3((FLOAT)(sinf(fAngle) * g_aCllinder->RADIUS), (FLOAT)((rand() % (200 - 50)) + 50), (FLOAT)(cosf(fAngle) * g_aCllinder->RADIUS)));
		}
		if (rand() % 200 == 0 && g_gameState == GAMESTATE_NORMAL)
		{
			float fAngle;
			LIFE *g_aCllinder;
			g_aCllinder = GetLife();

			fAngle = atan2f((float)(rand() % 360), (float)(rand() % 360));

			SetEnemy(D3DXVECTOR3((FLOAT)(sinf(fAngle) * -g_aCllinder->RADIUS), (FLOAT)((rand() % (200 - 50)) + g_aCllinder->nHeight), (FLOAT)(cosf(fAngle) * g_aCllinder->RADIUS)));
		}if (rand() % 200 == 0 && g_gameState == GAMESTATE_NORMAL)
		{
			float fAngle;
			LIFE *g_aCllinder;
			g_aCllinder = GetLife();

			fAngle = atan2f((float)(rand() % 360), (float)(rand() % 360));

			SetEnemy(D3DXVECTOR3((FLOAT)(sinf(fAngle) * g_aCllinder->RADIUS), (FLOAT)((rand() % (200 - 50)) + g_aCllinder->nHeight), (FLOAT)(cosf(fAngle) * -g_aCllinder->RADIUS)));
		}if (rand() % 200 == 0 && g_gameState == GAMESTATE_NORMAL)
		{
			float fAngle;
			LIFE *g_aCllinder;
			g_aCllinder = GetLife();

			fAngle = atan2f((float)(rand() % 360), (float)(rand() % 360));

			SetEnemy(D3DXVECTOR3((FLOAT)(sinf(fAngle) * -g_aCllinder->RADIUS), (FLOAT)((rand() % (200 - 50)) + g_aCllinder->nHeight), (FLOAT)(cosf(fAngle) * -g_aCllinder->RADIUS)));
		}
	}
	else if (g_bPause == true)
	{// �|�[�Y�{�^������������
		// �|�[�Y�̍X�V����
		UpdatePause();
	}

	// �R���g���[���[�̏��
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
// �Q�[����ʂ̕`�揈��
//=============================================================================
void DrawGame(void)
{
	// ���b�V���̕`�揈��
	DrawMeshField();

	// �ǂ̕`�揈��
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

	// �v���C���[���C�t�̕`�揈��
	DrawPlayerLife();

	// �I�u�W�F�N�g���C�t�̕`�揈��
	DrawOBLife();

	if (g_bPause == true)
	{// �|�[�Y�{�^������������
		// �|�[�Y�̕`�揈��
		DrawPause();
	}
}

//=============================================================================
//�Q�[���̏�Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState			= state;
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
// �|�[�Y�̏�Ԃ̐ݒ�
//=============================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}