//=============================================================================
//
// �Q�[������ [game.h]
// Author :�r�J�R�N
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,			//�������Ă��Ȃ����
	GAMESTATE_NORMAL,			//�ʏ���
	GAMESTATE_CLEAR,
	GAMESTATE_OVER,
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameStateNow(void);
void SetPauseState(bool bPause);

#endif // _GAME_H_
