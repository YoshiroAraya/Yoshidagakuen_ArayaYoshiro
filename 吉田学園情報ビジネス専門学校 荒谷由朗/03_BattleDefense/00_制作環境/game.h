//=============================================================================
//
// ゲーム処理 [game.h]
// Author :荒谷由朗
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0,			//何もしていない状態
	GAMESTATE_NORMAL,			//通常状態
	GAMESTATE_CLEAR,
	GAMESTATE_OVER,
	GAMESTATE_MAX
}GAMESTATE;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameStateNow(void);
void SetPauseState(bool bPause);

#endif // _GAME_H_
