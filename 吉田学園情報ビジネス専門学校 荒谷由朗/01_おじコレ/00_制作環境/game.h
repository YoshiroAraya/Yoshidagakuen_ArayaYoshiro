//=============================================================================
//
// ゲーム処理 [game.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "block.h"
#include "enemy.h"

//=============================================================================
// ゲームの状態
//=============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,			// 何もしていない状態
	GAMESTATE_NORMAL,			// 通常状態
	GAMESTATE_CLEAR,			// クリア
	GAMESTATE_OVER,				// ゲームオーバー
	GAMESTATE_MAX
}GAMESTATE;

//=============================================================================
// 敵情報の構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	float		fWidth;			// 幅
	float		fHeight;		// 高さ
	EnemyType	type;			// 種類
	float		move_bullet;	// 弾の移動量
}EnemyInfo;

//=============================================================================
// ブロック情報の構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	float		fWidth;			// 幅
	float		fHeight;		// 高さ
	BlockType	type;			// 種類
}BlockInfo;

//=============================================================================
// コイン情報の構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	float		fWidth;			// 幅
	float		fHeight;		// 高さ
}CoinInfo;

//=============================================================================
// アイテム情報の構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	float		fWidth;			// 幅
	float		fHeight;		// 高さ
	float		fLimit;
}ItemInfo;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void		InitGame		(void);
void		UninitGame		(void);
void		UpdateGame		(void);
void		DrawGame		(void);
void		SetGameState	(GAMESTATE state);
GAMESTATE	GetGameStateNow	(void);
void		SetPauseState	(bool bPause);
#endif