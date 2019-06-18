//=============================================================================
//
// ブロック処理 [block.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	BlockType_NORMAL = 0,
	BlockType_DELETE,
	BlockType_MAX
}BlockType;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float		fWidth;		// 幅
	float		fHeight;	// 高さ
	bool		bUse;		// 使用しているかどうか
	BlockType	type;		// ブロックの状態
}Block;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBlock				(void);
void UninitBlock			(void);
void UpdateBlock			(void);
void DrawBlock				(void);
void SetBlock				(D3DXVECTOR3 pos, float fWidth, float fHeight, BlockType type);
bool CollisionBlock			(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionBlock_Bullet	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
#endif
