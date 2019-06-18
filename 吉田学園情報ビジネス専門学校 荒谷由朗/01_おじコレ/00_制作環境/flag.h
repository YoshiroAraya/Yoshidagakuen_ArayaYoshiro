//=============================================================================
//
// フラッグ処理 [flag.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _FLAG_H_
#define _FLAG_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float		fWidth;		// 幅
	float		fHeight;	// 高さ
	bool		bUse;		// 使用しているかどうか
}Flag;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitFlag		(void);
void UninitFlag		(void);
void UpdateFlag		(void);
void DrawFlag		(void);
void SetFlag		(D3DXVECTOR3 pos, float fWidth, float fHeight);
bool CollisionFlag	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
#endif