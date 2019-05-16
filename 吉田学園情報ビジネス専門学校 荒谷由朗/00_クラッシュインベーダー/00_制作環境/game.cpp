//=============================================================================
//
// �Q�[������ [game.cpp]
// Author :	�r�J�R�N
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "input.h"
#include"score.h"
#include"effect.h"
#include"fade.h"

//�O���[�o��
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[�����
GAMESTATE g_gameStateNow = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//�Q�[����ʂ̏�����
void InitGame(void)
{
	//�w�i�̏���������
	InitBG();

	//�|���S���̏���������
	InitPlayer();

	//�e�̏�����
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�X�R�A�̏���������
	InitScore();

	//�G�̏�����
	InitEnemy();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//����
	SetEnemy(D3DXVECTOR3(250.0f, 50.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 50.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(650.0f, 50.0f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(850.0f, 50.0f, 0.0f), 3);

	//����
	SetEnemy(D3DXVECTOR3(350.0f, 100.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(550.0f, 100.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(750.0f, 100.0f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(950.0f, 100.0f, 0.0f), 3);

	//�O���
	SetEnemy(D3DXVECTOR3(250.0f, 150.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 150.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(650.0f, 150.0f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(850.0f, 150.0f, 0.0f), 3);

	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
}

void UninitGame(void)
{
	//�w�i�̏I������
	UninitBG();

	//�|���S���̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�X�R�A�̏I������
	UninitScore();

	//�G�̏I������
	UninitEnemy();

	//�X�R�A�̏I������
	UninitEffect();
}

//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	//�w�i�̍X�V����
	UpdateBG();

	//�e�̍X�V����
	UpdateBullet();

	//�����̍X�V����
	UpdateExplosion();

	//�X�V����
	UpdateEnemy();

	//�|���S���̍X�V����
	UpdatePlayer();

	//�X�R�A�̍X�V����
	UpdateScore();

	//�X�R�A�̍X�V����
	UpdateEffect();

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
			//SetFade(MODE_RESULT);

		}
		break;
	}
}

void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�|���S���̕`�揈��
	DrawPlayer();

	//�e�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

	//�G�̕`�揈��
	DrawEnemy();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();
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