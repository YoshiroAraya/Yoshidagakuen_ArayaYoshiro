//=============================================================================
//
// プレイヤーのライフゲージ処理 [PlayerLife.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _PLAYERLIFE_H_
#define _PLAYERLIFE_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitPlayerLife		(void);
void	UninitPlayerLife	(void);
void	UpdatePlayerLife	(void);
void	DrawPlayerLife		(void);
void	HitPlayerLife		(int nDamage);
float	GetPlayerLife		(void);
#endif