//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// プレイヤーの状態の種類
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
// プレイヤーの構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 座標
	D3DXVECTOR3 move;				// 移動量
	PLAYERSTATE state;				// 状態
	int			nCunterState;		// 状態カウンタ
	int			nCunterAnim;		// アニメーションカウンタ
	int			nLife;				// ライフ
	bool		bUse;				// 使用されているかどうか
	bool		bDisp;				// 死亡フラグ
}Player;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitPlayer		(void);
void	UninitPlayer	(void);
void	UpdatePlayer	(void);
void	DrawPlayer		(void);
void	HitPlayer		(int nDamage);
Player	*GetPlayer		(void);
#endif