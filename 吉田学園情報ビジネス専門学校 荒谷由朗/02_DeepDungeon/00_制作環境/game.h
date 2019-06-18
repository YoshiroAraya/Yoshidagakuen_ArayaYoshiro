//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//=============================================================================
// �Q�[���̏��
//=============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,		// �������Ă��Ȃ����
	GAMESTATE_NORMAL,		// �ʏ���
	GAMESTATE_CLEAR,		// �N���A���
	GAMESTATE_GAMEOVER,		// �Q�[���I�[�o�[���
	GAMESTATE_CLEAR_75,
	GAMESTATE_CLEAR_50,
	GAMESTATE_CLEAR_25,
	GAMESTATE_CLEAR_TRUE,
	GAMESTATE_MAX
}GAMESTATE;

//�X�e�[�W�J��
typedef enum
{//�񋓌^
	STAGEMODE_STAGE1 = 0,
	STAGEMODE_STAGE2,
	STAGEMODE_STAGE3,
	STAGEMODE_MAX
}STAGEMODE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetStageMode(STAGEMODE Stagemode);
void SetGameState(GAMESTATE state);
STAGEMODE GetStageMode(void);
GAMESTATE GetGameState(void);
GAMESTATE *GetGameState2(void);
void SetPauseState(bool bPause);
void SetSelect(bool bSelect);
bool GetSelect(void);

void MagicSquareSet(void);
void Set_Stage1(void);
void Set_Stage2(void);
void Set_BossStage(void);


void Delete_Stage1(void);
void Delete_Stage2(void);
void Delete_BossStage(void);

#endif