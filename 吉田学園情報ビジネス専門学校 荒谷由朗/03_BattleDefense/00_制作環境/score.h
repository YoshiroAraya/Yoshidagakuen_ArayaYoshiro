//=============================================================================
//
// スコア処理 [score.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

typedef struct
{
	LPDIRECT3DTEXTURE9		pTextureScore = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
	int						nScore;					// スコア
	int						MAX_SCORE;				// 桁数
}SCORE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue);
SCORE GetScore(void);

#endif