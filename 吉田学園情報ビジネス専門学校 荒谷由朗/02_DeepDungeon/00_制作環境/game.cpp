//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "light.h"
#include "camera.h"
#include "player.h"
#include "shadow.h"
#include "pause.h"
#include "Stage1.h"
#include "Stage2.h"
#include "StageBoss.h"
#include "Stagefade.h"
#include "Wall1.h"
#include "Wall2.h"
#include "WallBoss.h"
#include "Select.h"
#include "life.h"
#include "txt.h"
#include "motion.h"
#include "magic.h"
#include "particle.h"
#include "magicsquare.h"
#include "sencer.h"
#include "brazen.h"
#include "erosion.h"
#include "SencerAtk.h"
#include "model.h"

//�G
#if 1
#include "enemy.h"
#include "enemymotion.h"
#include "enemytext.h"

#include "enemy0.h"
#include "enemymotion0.h"
#include "enemytext0.h"

#include "enemy1.h"
#include "enemymotion1.h"
#include "enemytext1.h"

#include "enemy2.h"
#include "enemymotion2.h"
#include "enemytext2.h"

#include "enemy3.h"
#include "enemymotion3.h"
#include "enemytext3.h"

#include "enemy4.h"
#include "enemymotion4.h"
#include "enemytext4.h"


#include "enemy5.h"
#include "enemymotion5.h"
#include "enemytext5.h"

#include "enemy6.h"
#include "enemymotion6.h"
#include "enemytext6.h"


#include "enemy7.h"
#include "enemymotion7.h"
#include "enemytext7.h"

#include "enemy8.h"
#include "enemymotion8.h"
#include "enemytext8.h"

#endif

//�G(�|)
#if 1

#include "enemy_arrow.h"
#include "enemy_arrow_motion.h"
#include "enemy_arrow_text.h"

#include "enemyarcher0.h"
#include "enemyarchermotion0.h"
#include "enemyarchertext0.h"


#include "enemyarcher1.h"
#include "enemyarchermotion1.h"
#include "enemyarchertext1.h"


#include "enemyarcher2.h"
#include "enemyarchermotion2.h"
#include "enemyarchertext2.h"

#endif

//�G(��)
#if 1

#include "enemy_axe.h"
#include "enemy_axe_motion.h"
#include "enemy_axe_text.h"

#include "enemy_axe2.h"
#include "enemy_axe_motion2.h"
#include "enemy_axe_text2.h"
#endif


#include "SencerCol.h"
#include "SencerLock.h"
#include "SencerEnemy.h"
#include "sencerArrow.h"
#include "SencerNextStage.h"
#include "SencerEnableAttack.h"
#include "SencerEnableBoss.h"
#include "fog.h"
#include "died.h"
#include "boss.h"
#include "bossmotion.h"
#include "bosstext.h"
#include "message.h"
#include "arrow.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_NCNT (50)
//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_gameState;			// �Q�[���̏��
GAMESTATE g_gameState2;	// �Q�[���̍ŏI���
int g_nCounterGameState = 0;					// ��ԊǗ��J�E���^
STAGEMODE g_StageMode = STAGEMODE_STAGE1;		// �X�e�[�W�̏��
JoyState g_PauseJoyState;						// �|�[�Y�̃W���C�p�b�h���
bool g_bPause = false;							// �|�[�Y�̏��
bool g_bSelect = false;							// �K�i�ړ�


int nCntMagicSquare[MAX_NCNT];
int nCntSencer[MAX_NCNT];
int nCntEnemy[MAX_NCNT];

//=============================================================================
// �Q�[����ʂ̏���������
//=============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;		// �ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;			// �J�E���^��������
	g_bPause = false;
	g_bSelect = false;
	g_StageMode = STAGEMODE_STAGE1;
	//�X�e�[�W�t�F�[�h�̏�����
	InitStageFade(g_StageMode);

	/////////////////////////////////////////////////////////////////////////////////
	/////					�e�L�X�g											////
	///////////////////////////////////////////////////////////////////////////////

	//�G�l�~�[�e�L�X�g�ǂݍ���(�X�P��)
#if 1
	LoadEnemyData();
	LoadEnemyData_0();
	LoadEnemyData_1();
	LoadEnemyData_2();
	LoadEnemyData_3();
	LoadEnemyData_4();
	LoadEnemyData_5();
	LoadEnemyData_6();
	LoadEnemyData_7();
	LoadEnemyData_8();

#endif

	//�G�l�~�[�e�L�X�g�ǂݍ���(�X�P�|)
#if 1

	LoadEnemyArrowData();
	LoadEnemyArcherData_0();
	LoadEnemyArcherData_1();
	LoadEnemyArcherData_2();
#endif

	//�G�l�~�[�e�L�X�g�ǂݍ���(��)
#if 1

	LoadEnemyAxeData();
	LoadEnemyAxeData2();
#endif

	//�{�X�e�L�X�g�̓ǂݍ���
	LoadBossData();
	//�e�L�X�g�f�[�^�̓ǂݍ���
	LoadData();
	//�J�����̏�����
	InitCamera();
	//���C�g�̏�����
	InitLight();



	//���[�V�����f�[�^�̏�����
	InitMotion();
	
	

	//�{�X���[�V����������
	InitBossMotion();
	//�e�̏�����
	InitShadow();
	//�p�[�e�B�N���̏�����
	InitParticle();
	//���@�w�̏�����
	InitMagicSquare();
	//���@�w�̐ݒu
	MagicSquareSet();
	//�����蔻��p�Z���T�[������
	InitSencerCollision();
	//���b�N�p�Z���T�[������
	InitSencerLock();
	//�G�l�~�[�p�Z���T�[������
	InitSencerEnemy();
	InitSencerEnemyArrow();
	//�U���Z���T�[������
	InitSencerAtk();
	//�U���\�Z���T�[������
	InitSencerEnableAttack();
	//�U���\�Z���T�[������
	InitSencerEnableBoss();

	//�|
	InitArrow();

	//���X�e�[�W�ړ��Z���T�[
	InitSencerNext();
	//�v���C���[�̏�����
	InitPlayer();
	
	//���C�t�̏�����
	InitLife();
	//ᏋC�Z�x������
	InitBrazen();
	//�Z�H�x������
	InitErosion();

	//���@�̏�����
	InitMagic();
	//�I�����̏�����
	InitSelect();
	//�|�[�Y�̏�����
	InitPause();
	//�e��Z���T�[������
	InitSencer();

	/////////////////////////////////////////////////////////////////////////////////
	/////					�G													////
	///////////////////////////////////////////////////////////////////////////////
	//�G�̏�����
#if 1
	InitEnemy();
	InitEnemy_0();
	InitEnemy_1();
	InitEnemy_2();
	InitEnemy_3();
	InitEnemy_4();
	InitEnemy_5();
	InitEnemy_6();
	InitEnemy_7();
	InitEnemy_8();

#endif
	//�G(�|)�̏�����
#if 1
	InitEnemyArrow();
	InitEnemyARCHER_0();
	InitEnemyARCHER_1();
	InitEnemyARCHER_2();
#endif
	//��
#if 1

	InitEnemyAxe();
	//��
	InitEnemyAxe2();
#endif
	//�{�X�̏�����
	InitBoss();

	//�G�l�~�[���[�V����������(�X�P��)
#if 1
	InitEnemyMotion();
	InitEnemyMotion_0();
	InitEnemyMotion_1();
	InitEnemyMotion_2();
	InitEnemyMotion_3();
	InitEnemyMotion_4();
	InitEnemyMotion_5();
	InitEnemyMotion_6();
	InitEnemyMotion_7();
	InitEnemyMotion_8();
#endif

	//�G�l�~�[���[�V����������(�|)
#if 1
	InitEnemyArrowMotion();
	InitEnemyArcherMotion_0();
	InitEnemyArcherMotion_1();
	InitEnemyArcherMotion_2();

#endif

	//�G�l�~�[���[�V����������(��)
#if 1
	InitEnemyAxeMotion();
	InitEnemyAxeMotion2();
#endif
	//���b�Z�[�W������
	InitMessage();
	//���S������
	InitDied();
	//�t�H�O
	//InitFog();
	//SetStageMode(STAGEMODE_STAGE1);
	SetStageMode(g_StageMode);
	//�X�e�[�W�̏���������
	switch (g_StageMode)
	{
	case STAGEMODE_STAGE1://�X�e�[�W�P�̎�
		InitStage1();
		InitWall1();
		InitModel();

		break;
	case STAGEMODE_STAGE2://�X�e�[�W2�̎�
		InitStage2();
		InitWall2();
		break;
	case STAGEMODE_STAGE3://�X�e�[�W3�̎�
		InitStageBoss();
		InitWallBoss();
		break;
	}
}

//=============================================================================
// �Q�[����ʂ̏I������
//=============================================================================
void UninitGame(void)
{
	//�J�����̏I������
	UninitCamera();
	//���C�g�̏I������
	UninitLight();

	

	//�X�e�[�W�̏I������
	switch (g_StageMode)
	{
	case STAGEMODE_STAGE1:
		UninitStage1();
		//�ǂ̏I������
		UninitWall1();
		UninitModel();
		break;
	case STAGEMODE_STAGE2:
		UninitStage2();
		UninitWall2();
		break;

	case STAGEMODE_STAGE3:
		UninitStageBoss();
		UninitWallBoss();
		break;
	}
	//�e�̏I������
	UninitShadow();
	//���@�w�̏I������
	UninitMagicSquare();
	//�v���C���[�̏I������
	UninitPlayer();
	//�|
	UninitArrow();
	
	//���C�t�̏I������
	UninitLife();
	//���@�̏I������
	UninitMagic();
	//�p�[�e�B�N���̏I������
	UninitParticle();
	//�I�����̏I������
	UninitSelect();
	//�X�e�[�W�t�F�[�h�̏I������
	UninitStageFade();
	//�|�[�Y�̏I������
	UninitPause();
	//�e��Z���T�[�I������
	UninitSencer();
	//���b�N�p�Z���T�[�I������
	UninitSencerLock();
	//�G�l�~�[�p�Z���T�[�I������
	UninitSencerEnemy();
	UninitSencerEnemyArrow();

	//���X�e�[�W�ړ��Z���T�[
	UninitSencerNext();
	//�U���\�Z���T�[�I������
	UninitSencerEnableAttack();
	//�U���\�Z���T�[�I������
	UninitSencerEnableBoss();

	//ᏋC�Z�x�I������
	UninitBrazen();
	//�Z�H�x������
	UninitErosion();

	//�U���Z���T�[�I������
	UninitSencerAtk();

	/////////////////////////////////////////////////////////////////////////////////
	/////					�G													////
	///////////////////////////////////////////////////////////////////////////////
	//�G�̏I������
#if 1
	UninitEnemy();
	UninitEnemy_0();
	UninitEnemy_1();
	UninitEnemy_2();
	UninitEnemy_3();
	UninitEnemy_4();
	UninitEnemy_5();
	UninitEnemy_6();
	UninitEnemy_7();
	UninitEnemy_8();

#endif
	//�G(�|)�̏�����
#if 1
	UninitEnemyArrow();
	UninitEnemyARCHER_0();
	UninitEnemyARCHER_1();
	UninitEnemyARCHER_2();

#endif 
	//�G(��)�̏�����
#if 1
	UninitEnemyAxe();
	//�G(��)�̏�����
	UninitEnemyAxe2();
#endif
	//�{�X�̏I������
	UninitBoss();


	//�����蔻��p�Z���T�[�I������
	UninitSencerCollision();
	//���S������
	UninitDied();
	//���b�Z�[�W�I������
	UninitMessage();


}

//=============================================================================
// �Q�[����ʂ̍X�V����
//=============================================================================
void UpdateGame(void)
{
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_P) == true || state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{// P�L�[����
		if (g_PauseJoyState.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			g_bPause = g_bPause ? false : true;
		}
		g_PauseJoyState.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (g_bPause == false)
	{// �Q�[���v���C���
		if (g_bSelect == false)
		{
			//�J�����̍X�V����
			UpdateCamera();
			//���C�g�̍X�V����
			UpdateLight();
			
			//�X�e�[�W�̍X�V����
			switch (g_StageMode)
			{
			case STAGEMODE_STAGE1:
				UpdateStage1();
				//�ǂ̍X�V����
				UpdateWall1();
				UpdateModel();
				break;
			case STAGEMODE_STAGE2:
				UpdateStage2();
				UpdateWall2();
				break;
			case STAGEMODE_STAGE3:
				UpdateStageBoss();
				UpdateWallBoss();

				break;
			}
			//�e�̍X�V����
			UpdateShadow();
			//���@�w�̍X�V����
			UpdateMagicSquare();
			
			//���C�t�̍X�V����
			UpdateLife();
			//���@�̍X�V����
			UpdateMagic();
			//�p�[�e�B�N���̍X�V����
			UpdateParticle();


			/////////////////////////////////////////////////////////////////////////////////
			/////				���[�V����												////
			///////////////////////////////////////////////////////////////////////////////
			//���[�V�����f�[�^�̍X�V����
			UpdateMotion();

			
			//�G�l�~�[���[�V�����f�[�^�̍X�V����
#if  1

			UpdateEnemyMotion();
			UpdateEnemyMotion_0();
			UpdateEnemyMotion_1();
			UpdateEnemyMotion_2();
			UpdateEnemyMotion_3();
			UpdateEnemyMotion_4();
			UpdateEnemyMotion_5();
			UpdateEnemyMotion_6();
			UpdateEnemyMotion_7();
			UpdateEnemyMotion_8();

#endif 

			//�G�l�~�[���[�V�����f�[�^�̍X�V����(�|)
#if  1
			UpdateEnemyArrowMotion();
			UpdateEnemyArcherMotion_0();
			UpdateEnemyArcherMotion_1();
			UpdateEnemyArcherMotion_2();

#endif
			//�G�l�~�[���[�V�����f�[�^�̍X�V����(��)
#if 1
			UpdateEnemyAxeMotion();
			UpdateEnemyAxeMotion2();
#endif
			//�{�X���[�V�����f�[�^�̍X�V����
			UpdateBossMotion();
			//���b�N�p�Z���T�[�X�V����
			UpdateSencerLock();
			//�G�l�~�[�p�Z���T�[�X�V����
			UpdateSencerEnemy();
			UpdateSencerEnemyArrow();
			

			//�U���\�Z���T�[�X�V����
			UpdateSencerEnableAttack();
			UpdateSencerEnableBoss();
			//�e��Z���T�[�X�V����
			UpdateSencer();
			//���X�e�[�W�ړ��Z���T�[
			UpdateSencerNext();
			//ᏋC�Z�x�X�V����
			UpdateBrazen();
			//�Z�H�x�X�V����
			UpdateErosion();
			//�|
			UpdateArrow();
			//�U���Z���T�[�X�V����
			UpdateSencerAtk();

			/////////////////////////////////////////////////////////////////////////////////
			/////					�G													////
			///////////////////////////////////////////////////////////////////////////////
#if  1
#endif
			//�G�̍X�V����
#if  1
			UpdateEnemy();
			UpdateEnemy_0();
			UpdateEnemy_1();
			UpdateEnemy_2();
			UpdateEnemy_3();
			UpdateEnemy_4();
			UpdateEnemy_5();
			UpdateEnemy_6();
			UpdateEnemy_7();
			UpdateEnemy_8();

#endif

#if 1
			//�G(�|)�̏�����
			UpdateEnemyArrow();
			UpdateEnemyARCHER_0();
			UpdateEnemyARCHER_1();
			UpdateEnemyARCHER_2();

#endif

			//�G(��)�̏�����
#if 1
			UpdateEnemyAxe();
			//�G(��)�̏�����
			UpdateEnemyAxe2();
#endif
			//�{�X�̏I������
			UpdateBoss();
			//�����蔻��p�Z���T�[������
			UpdateSencerCollision();
			//�v���C���[�̍X�V����
			UpdatePlayer();
			//���S������
			UpdateDied();
			//���b�Z�[�W�X�V����
			UpdateMessage();
		}
		else
		{
			//�G���A�ړ��̑I���̍X�V����
			UpdateSelect();
		}

		//�X�e�[�W�t�F�[�h�̍X�V����
		UpdateStageFade();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_CLEAR:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 50)
			{
				g_gameState2 = GAMESTATE_CLEAR;
				g_gameState = GAMESTATE_NONE;
				// ���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		

		case GAMESTATE_CLEAR_75:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 50)
			{
				g_gameState2 = GAMESTATE_CLEAR_75;
				g_gameState = GAMESTATE_NONE;
				// ���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_CLEAR_50:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 50)
			{
				g_gameState2 = GAMESTATE_CLEAR_50;
				g_gameState = GAMESTATE_NONE;
				// ���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_CLEAR_25:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 50)
			{
				g_gameState2 = GAMESTATE_CLEAR_25;
				g_gameState = GAMESTATE_NONE;
				// ���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_CLEAR_TRUE:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 50)
			{
				g_gameState2 = GAMESTATE_CLEAR_TRUE;
				g_gameState = GAMESTATE_NONE;
				// ���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		}
	}
	else
	{// �|�[�Y���
		// �|�[�Y�̍X�V����
		UpdatePause();
	}

	// �W���C�p�b�h�̏�ԍX�V
	if (g_PauseJoyState.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_PauseJoyState.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_PauseJoyState.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_PauseJoyState.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �Q�[����ʂ̕`�揈��
//=============================================================================
void DrawGame(void)
{
	//�J�����̐ݒu
	SetCamera();
	//�X�e�[�W�̕`�揈��
	switch (g_StageMode)
	{
	case STAGEMODE_STAGE1:
		DrawStage1();
		//�ǂ̕`�揈��
		DrawWall1();
		DrawModel();

		break;
	case STAGEMODE_STAGE2:
		DrawStage2();
		DrawWall2();
		break;
	case STAGEMODE_STAGE3:
		DrawStageBoss();
		DrawWallBoss();
		break;
	}
	//�e�̕`�揈��
	DrawShadow();
	//���@�w�̕`�揈��
	DrawMagicSquare();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	
	//���C�t�̕`�揈��
	DrawLife();
	//ᏋC�Z�x�`�揈��
	DrawBrazen();
	DrawErosion();
	//���@�̕`�揈��
	DrawMagic();
	//�p�[�e�B�N���̕`�揈��
	DrawParticle();
	

	/////////////////////////////////////////////////////////////////////////////////
	/////				�Z���T�[												////
	///////////////////////////////////////////////////////////////////////////////
	//�U���Z���T�[�`�揈��
	//DrawSencerAtk();
	//�U���\�Z���T�[�X�V����
	//DrawSencerEnableAttack();
	//DrawSencerEnableBoss();
	//���b�N�p�Z���T�[�`�揈��
	//DrawSencerLock();
	//�G�l�~�[�p�Z���T�[�`�揈��
	//DrawSencerEnemy();
	//DrawSencerEnemyArrow();
	//�����蔻��p�Z���T�[�`�揈��
	//DrawSencerCollision();

	/////////////////////////////////////////////////////////////////////////////////
	/////					�G													////
	///////////////////////////////////////////////////////////////////////////////
	//�G�̕`�揈��
#if  1
	DrawEnemy();
	DrawEnemy_0();
	DrawEnemy_1();
	DrawEnemy_2();
	DrawEnemy_3();
	DrawEnemy_4();
	DrawEnemy_5();
	DrawEnemy_6();
	DrawEnemy_7();
	DrawEnemy_8();

#endif 

	
	//�G(�|)�̏�����
#if 1
	DrawEnemyArrow();
	DrawEnemyARCHER_0();
	DrawEnemyARCHER_1();
	DrawEnemyARCHER_2();
#endif

	//�G(��)�̏�����
#if 1
	DrawEnemyAxe();
	//�G(��)�̏�����
	DrawEnemyAxe2();
#endif
	//�|
	DrawArrow();
	//�{�X�̏I������
	DrawBoss();
	//�e��Z���T�[�`�揈��
	DrawSencer();

	//���X�e�[�W�ړ��Z���T�[
	DrawSencerNext();
	
	//���S������
	DrawDied();
	//���b�Z�[�W�`�揈��
	DrawMessage();
	if (g_bSelect == true)
	{
		//�G���A�ړ��̑I���̕`�揈��
		DrawSelect();
	}

	//�X�e�[�W�t�F�[�h�̕`�揈��
	DrawStageFade();

	if (g_bPause == true)
	{// �|�[�Y���
		DrawPause();
	}
}

//=============================================================================
//���[�h�̐ݒ�
//=============================================================================
void SetStageMode(STAGEMODE Stagemode)
{
	switch (g_StageMode)
	{
	case STAGEMODE_STAGE1:
		UninitStage1();
		UninitWall1();

		break;
	case STAGEMODE_STAGE2:
		UninitStage2();
		UninitWall2();
		break;
	case STAGEMODE_STAGE3:
		UninitStageBoss();
		UninitWallBoss();

		break;
	}

	//�V������ʃ��[�h�̏������ݒ�
	switch (Stagemode)
	{
	case STAGEMODE_STAGE1:
		InitStage1();
		InitWall1();
		Set_Stage1();

		break;
	case STAGEMODE_STAGE2:
		Delete_Stage1();

		InitStage2();
		InitWall2();
		Set_Stage2();
		break;
	case STAGEMODE_STAGE3:
		InitStageBoss();
		InitWallBoss();
		Set_BossStage();

		break;
	}

	g_StageMode = Stagemode;//���݂̃��[�h��؂�ւ���
}

//=============================================================================
// �Q�[���̏�Ԃ̐ݒ�
//=============================================================================
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
// ���݂̃Q�[���̏�Ԃ̎擾
//=============================================================================
GAMESTATE *GetGameState2(void)
{
	return &g_gameState2;
}

//=============================================================================
// �|�[�Y�̏��
//=============================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}

//=============================================================================
// �Q�[���̎擾����[SetStage]
//=============================================================================
STAGEMODE GetStageMode(void)
{
	return g_StageMode;
}

//=============================================================================
// �I����Ԃ̎擾����[SetGame]
//=============================================================================
void SetSelect(bool bSelect)
{
	g_bSelect = bSelect;
}

//=============================================================================
// �I����Ԃ̎擾[SetGame]
//=============================================================================
bool GetSelect(void)
{
	return g_bSelect;
}

//=============================================================================
// ���@�w�̐ݒu
//=============================================================================
void MagicSquareSet(void)
{
}
//=============================================================================
// �e�X�e�[�W�̓G�̔z�u
//=============================================================================
void Set_Stage1(void)
{
	//�G�z�u
	nCntEnemy[0] =	SetEnemy(D3DXVECTOR3(0.0f, 0.1f, 2650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	nCntEnemy[1] =	SetEnemyArrow(D3DXVECTOR3(0.0f, 0.1f, 650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);
	nCntEnemy[2] = SetEnemyAxe(D3DXVECTOR3(500.0f, 0.1f, 2200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20);
	nCntEnemy[3] = SetEnemyAxe2(D3DXVECTOR3(200.0f, 0.1f, 2050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20);
	nCntEnemy[4] = SetEnemy_0(D3DXVECTOR3(700.0f, 0.1f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	nCntEnemy[4] = SetEnemy_1(D3DXVECTOR3(0.0f, 0.1f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	nCntEnemy[5] = SetEnemy_2(D3DXVECTOR3(-100.0f, 0.1f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);

	//�e��Z���T�[�ݒu
	nCntSencer[0] =		 SetSencerNext(D3DXVECTOR3(180.0f, 0.0f, 1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	nCntMagicSquare[0] = SetMagicSquare(D3DXVECTOR3(730.0f, 0.1f, 2130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f);
}
void Set_Stage2(void)
{
	nCntEnemy[0] = SetEnemy(D3DXVECTOR3(0.0f, 0.1f, 2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	nCntEnemy[1] = SetEnemyArrow(D3DXVECTOR3(100.0f, 0.1f, 2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
	nCntEnemy[2] = SetEnemyAxe(D3DXVECTOR3(1500.0f, 0.0f, 750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20);
	nCntEnemy[3] = SetEnemyAxe2(D3DXVECTOR3(1250.0f, 0.1f, 1050), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20);
	nCntEnemy[4] = SetEnemy_0(D3DXVECTOR3(0, 0.1f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	nCntEnemy[5] = SetEnemy_1(D3DXVECTOR3(0, 0.1f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);


	nCntMagicSquare[0] = SetMagicSquare(D3DXVECTOR3(600.0f, 0.1f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f);
	nCntMagicSquare[1] = SetMagicSquare(D3DXVECTOR3(-680.0f, 0.1f, 2330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f);

	nCntSencer[0] = SetSencerNext(D3DXVECTOR3(1500.0f, 0.0f, 950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

}
void Set_BossStage(void)
{
	SetBoss(D3DXVECTOR3(0.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70);
}


//=============================================================================
// �e�X�e�[�W�̍폜
//=============================================================================
void Delete_Stage1(void)
{
	MAGICSQUARE *pMagicSquare;
	pMagicSquare = GetMagicSquare();

	DeleteEnemy(nCntEnemy[0]);
	DeleteEnemyArrow(nCntEnemy[1]);	
	DeleteEnemyAxe(nCntEnemy[2]);
	DeleteEnemyAxe2(nCntEnemy[3]);
	DeleteEnemy_0(nCntEnemy[3]);
	DeleteEnemy_1(nCntEnemy[4]);
	DeleteEnemy_2(nCntEnemy[5]);

	DeleteOnlyMagicSquare(nCntMagicSquare[0]);
	DeleteSencerNext(nCntSencer[0]);


	//nCntEnemy[0] = SetEnemy(D3DXVECTOR3(0.0f, 0.1f, 2650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	//nCntEnemy[1] = SetEnemyArrow(D3DXVECTOR3(0.0f, 0.1f, 650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);
	//nCntEnemy[2] = SetEnemyAxe(D3DXVECTOR3(500.0f, 0.1f, 2200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20);
	//nCntEnemy[3] = SetEnemyAxe2(D3DXVECTOR3(200.0f, 0.1f, 2050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20);
	//nCntEnemy[4] = SetEnemy_0(D3DXVECTOR3(700.0f, 0.1f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	//nCntEnemy[4] = SetEnemy_1(D3DXVECTOR3(0.0f, 0.1f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);
	//nCntEnemy[5] = SetEnemy_2(D3DXVECTOR3(-100.0f, 0.1f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15);


}

void Delete_Stage2(void)
{
	DeleteEnemy(nCntEnemy[0]);
	DeleteEnemyArrow(nCntEnemy[1]);
	DeleteEnemyAxe(nCntEnemy[2]);
	DeleteEnemyAxe2(nCntEnemy[3]);


	DeleteSencerNext(nCntSencer[2]);
	DeleteOnlyMagicSquare(nCntMagicSquare[0]);

}

void Delete_BossStage(void)
{

}