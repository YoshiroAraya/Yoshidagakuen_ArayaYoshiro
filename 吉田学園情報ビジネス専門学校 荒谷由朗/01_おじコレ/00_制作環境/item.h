//=============================================================================
//
// アイテム処理 [item.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 posStart;				// アイテムの初期位置
	D3DXVECTOR3 pos;					// アイテムの位置
	D3DXVECTOR3 posOld;					// アイテムの位置(過去)
	D3DXVECTOR3 move;					// アイテムの移動量
	int			nCounterAnim;			// アニメーションカウンター
	int			nPatternAnim;			// アニメーションパターンNo.
	int			fAngle;
	int			nDirectionMove;			// 0->右を向いている、1->左を向いている
	float		fWidth;					// 幅
	float		fHeight;				// 高さ
	float		fVerLimit;
	float		fLimit;
	bool		bUse;					// 使用しているかどうか
}Item;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitItem		(void);
void	UninitItem		(void);
void	UpdateItem		(void);
void	DrawItem		(void);
void	SetItem			(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fHorLimit, float fWidth, float fHeight);
bool	CollisionItem	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,float fHeight, float fWidth);
Item	*GetItem		(void);
int		GetItemNumber	(void);
#endif