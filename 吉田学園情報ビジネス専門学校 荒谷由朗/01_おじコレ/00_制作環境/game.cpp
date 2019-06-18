//=============================================================================
//
// �Q�[������ [game.cpp]
// Author :	�r�J�R�N
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "block.h"
#include "coin.h"
#include "time.h"
#include "item.h"
#include "flag.h"
#include "pause.h"
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "sound.h"
#include "life.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_STAGE  (26)						// �u���b�N�̍ő吔

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
GAMESTATE	g_gameState			= GAMESTATE_NONE;		// �Q�[�����
GAMESTATE	g_gameStateNow		= GAMESTATE_NONE;		// �Q�[��(����)���
int			g_nCounterGameState = 0;					// �Q�[����Ԃ̃J�E���^�[
bool		g_bPause;									// �|�[�Y�����ǂ���

//=============================================================================
// �G���̃f���^
//=============================================================================
EnemyInfo g_aEnemyInfo[] =
{
	{ D3DXVECTOR3(25.0f, 420.0f, 0.0f), 30.0f, 30.0f,EnemyType_NORMAL1 ,2.0f},
	{ D3DXVECTOR3(1250.0f, 420.0f, 0.0f), 30.0f, 30.0f,EnemyType_NORMAL1,-2.0f },
	{ D3DXVECTOR3(1250.0f, 240.0f, 0.0f), 30.0f, 30.0f,EnemyType_NORMAL1,-2.0f }
};

//=============================================================================
// �u���b�N���̃f���^
//=============================================================================
BlockInfo g_aBlockInfo[] =
{
	{ D3DXVECTOR3(315.0f, 600.0f, 0.0f), 120.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(835.0f, 600.0f, 0.0f), 140.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(0.0f, 550.0f, 0.0f), 180.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(1100.0f, 550.0f, 0.0f), 180.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(0.0f, 450.0f, 0.0f), 50.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(1220.0f, 450.0f, 0.0f), 70.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(170.0f, 380.0f, 0.0f), 100.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(1020.0f, 380.0f, 0.0f), 100.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(1040.0f, 270.0f, 0.0f), 260.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(0.0f, 170.0f, 0.0f), 700.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(380.0f, 300.0f, 0.0f), 300.0f, 400.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(780.0f, 400.0f, 0.0f), 120.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(1100.0f,580.0f, 0.0f), 30.0f, 120.0f,BlockType_DELETE }
};

//=============================================================================
// �R�C�����̃f���^
//=============================================================================
CoinInfo g_aCoinInfo[] =
{
	{D3DXVECTOR3(10.0f, 500.0f, 0.0f), 30.0f, 40.0f},
	{D3DXVECTOR3(60.0f, 500.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(110.0f, 500.0f, 0.0f), 30.0f, 40.0f },

	{D3DXVECTOR3(200.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(300.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(400.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(500.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(600.0f, 40.0f, 0.0f), 30.0f, 40.0f },

	{D3DXVECTOR3(150.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(250.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(350.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(450.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(550.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(650.0f, 120.0f, 0.0f), 30.0f, 40.0f },

	{D3DXVECTOR3(425.0f, 250.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(475.0f, 250.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(525.0f, 250.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(575.0f, 250.0f, 0.0f), 30.0f, 40.0f },
};

//=============================================================================
// �A�C�e�����̃f���^
//=============================================================================
ItemInfo g_aItemInfo[] =
{
	{D3DXVECTOR3(820.0f, SCREEN_HEIGHT - 55.0f, 0.0f),D3DXVECTOR3(5.0f,0.0f,0.0f),30.0f,30.0f,130.0f },
	{D3DXVECTOR3(80.0f, 140.0f, 0.0f),D3DXVECTOR3(5.0f,0.0f,0.0f), 30.0f, 30.0f, 90.0f },
	{D3DXVECTOR3(845.0f, 370.0f, 0.0f),D3DXVECTOR3(5.0f,0.0f,0.0f), 30.0f, 30.0f, 75.0f },
};

//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	int nCountStage;
	g_bPause = false;

	// �e����������
	InitBG();			// �w�i
	InitScore();		// �X�R�A
	InitPlayer();		// �v���C���[
	InitEnemy();		// �G
	InitBullet();		// �e
	InitExplosion();	// ����
	InitBlock();		// �u���b�N
	InitFlag();			// �t���b�O
	InitCoin();			// �R�C��
	InitTime();			// �^�C��
	InitLife();			// ���C�t
	InitItem();			// �A�C�e��
	InitPause();		// �|�[�Y

	// �n�ʂ̐���
	for (nCountStage = 0; nCountStage < MAX_STAGE; nCountStage++)
	{
		SetBlock(D3DXVECTOR3(50.0f * nCountStage, SCREEN_HEIGHT - 25.0f, 0.0f), 50.0f, 25.0f, BlockType_NORMAL);
	}
	// �G�̐���
	for (int nCntEnemy = 0; nCntEnemy < sizeof g_aEnemyInfo / sizeof(EnemyInfo); nCntEnemy++)
	{
		SetEnemy(g_aEnemyInfo[nCntEnemy].pos, g_aEnemyInfo[nCntEnemy].fWidth, g_aEnemyInfo[nCntEnemy].fHeight, g_aEnemyInfo[nCntEnemy].type, g_aEnemyInfo[nCntEnemy].move_bullet);
	}
	// �X�e�[�W�̐���
	for (int nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCntBlock++)
	{
		SetBlock(g_aBlockInfo[nCntBlock].pos, g_aBlockInfo[nCntBlock].fWidth, g_aBlockInfo[nCntBlock].fHeight, g_aBlockInfo[nCntBlock].type);
	}

	// �R�C���̐���
	for (int nCntCoin = 0; nCntCoin < sizeof g_aCoinInfo / sizeof(CoinInfo); nCntCoin++)
	{
		SetCoin(g_aCoinInfo[nCntCoin].pos, g_aCoinInfo[nCntCoin].fWidth, g_aCoinInfo[nCntCoin].fHeight);
	}

	// �A�C�e���̐���
	for (int nCntItem = 0; nCntItem < sizeof g_aItemInfo / sizeof(ItemInfo); nCntItem++)
	{
		SetItem(g_aItemInfo[nCntItem].pos, g_aItemInfo[nCntItem].move, g_aItemInfo[nCntItem].fLimit,g_aItemInfo[nCntItem].fWidth, g_aItemInfo[nCntItem].fHeight);
	}

	g_gameState			= GAMESTATE_NORMAL;		// �ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;					// �J�E���^�[�̏�����
	PlaySound(SOUND_LABEL_BGM001);				// BGM�̍Đ�
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// �e�I������
	UninitBG();				// �w�i
	UninitScore();			// �X�R�A
	UninitPlayer();			// �v���C���[
	UninitBullet();			// �e
	UninitExplosion();		// ����
	UninitEnemy();			// �G
	UninitBlock();			// �u���b�N
	UninitFlag();			// �t���b�O
	UninitCoin();			// �R�C��
	UninitTime();			// �^�C��
	UninitLife();			// ���C�t
	UninitItem();			// �A�C�e��
	UninitPause();			// �|�[�Y

	// �T�E���h�̒�~
	StopSound();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{// �|�[�Y
		PlaySound(SOUND_LABEL_SE_POUZU);		// �T�E���h�̍Đ�
		g_bPause = g_bPause ? false : true;		// �|�[�Y�̐؂�ւ�
	}
	if (g_bPause == false)
	{// �|�[�Y����Ȃ��Ƃ�
		// �e�X�V����
		UpdateBG();			// �w�i
		UpdateScore();		// �X�R�A
		UpdatePlayer();		// �v���C���[
		UpdateBullet();		// �e
		UpdateExplosion();	// ����
		UpdateEnemy();		// �G
		UpdateBlock();		// �u���b�N
		UpdateFlag();		// �t���b�O
		UpdateCoin();		// �R�C��
		UpdateTime();		// �^�C��
		UpdateLife();		// ���C�t
		UpdateItem();		// �A�C�e��

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_CLEAR:
			g_gameStateNow	= GAMESTATE_CLEAR;
			g_gameState		= GAMESTATE_NONE;
			SetFade(MODE_RESULT);				// ���(���[�h)�̐ݒ�
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 30)
			{
				g_gameStateNow	= GAMESTATE_OVER;
				g_gameState		= GAMESTATE_NONE;
			}
			break;
		}
	}
	else if(g_bPause == true)
	{
		// �|�[�Y�̍X�V����
		UpdatePause();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �e�`�揈��
	DrawBG();			// �w�i
	DrawScore();		// �X�R�A
	DrawPlayer();		// �v���C���[
	DrawBullet();		// �e
	DrawExplosion();	// ����
	DrawEnemy();		// �G
	DrawBlock();		// �u���b�N
	DrawFlag();			// �t���b�O
	DrawCoin();			// �R�C��
	DrawTime();			// �^�C��
	DrawLife();			// ���C�t
	DrawItem();			// �A�C�e��

	if (g_bPause == true)
	{
		// �|�[�Y�̕`�揈��
		DrawPause();
	}
}

//=============================================================================
// �Q�[���̏�Ԃ̐ݒ�
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
// �|�[�Y�̏��
//=============================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}