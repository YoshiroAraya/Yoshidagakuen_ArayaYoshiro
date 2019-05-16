//=============================================================================
//
// ポリゴン処理 [player.cpp]
// Author :荒谷由朗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//プレイヤーの状態の種類
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;
//*****************************************************************************
//プレイヤーの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;
	int nCunterState;
	int nCunterAnim;
	int nLife;
	bool bUse;				//使用されているかどうか
	bool bDisp;
}Player;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif