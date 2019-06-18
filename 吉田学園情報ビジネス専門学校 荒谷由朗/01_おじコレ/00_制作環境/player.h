//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// プレイヤーの状態
//=============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// プレイヤーの位置(現在)
	D3DXVECTOR3 posOld;				// プレイヤーの位置(過去)
	D3DXVECTOR3 move;				// プレイヤーの移動量
	PLAYERSTATE state;
	float		fWidth;				// 幅
	float		fHeight;			// 高さ
	int			nCounterJump;		// ジャンプカウンター
	int			nCounterAnim;		// アニメーションカウンター
	int			nPatternAnim;		// アニメーションパターンNoを初期化
	int			nLife;				// プレイヤーの体力
	int			nCounterState;		// 状態管理のカウンタ
	int			nDirectionMove;		// 0->右を向いている、1->左を向いている
	bool		bUse;				// 使用されているかどうか
	bool		bDisp;				// 表示しているかどうか
	bool		bJump;				// ジャンプしているかどうか
}Player;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitPlayer	(void);
void	UninitPlayer(void);
void	UpdatePlayer(void);
void	DrawPlayer	(void);
void	HitPlayer	(int nDamage);
Player	*GetPlayer	(void);
#endif