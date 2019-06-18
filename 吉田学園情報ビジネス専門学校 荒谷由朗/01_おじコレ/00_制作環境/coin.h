//=============================================================================
//
// コイン処理 [coin.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _COIN_H_
#define _COIN_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	int			nCounterAnim;		// アニメーションカウンター
	int			nPatternAnim;		// アニメーションパターンNo.
	float		fWidth;				// 幅
	float		fHeight;			// 高さ
	bool		bUse;				// 使用しているかどうか
}Coin;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCoin		(void);
void UninitCoin		(void);
void UpdateCoin		(void);
void DrawCoin		(void);
void SetCoin		(D3DXVECTOR3 pos, float fWidth, float fHeight);
bool CollisionCoin	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
#endif