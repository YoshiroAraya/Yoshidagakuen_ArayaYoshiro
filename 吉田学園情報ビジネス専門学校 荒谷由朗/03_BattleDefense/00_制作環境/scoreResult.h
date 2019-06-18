//=============================================================================
//
// スコア処理 [scoreResult.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _SCORERESULT_H_
#define _SCORERESULT_H_

#include "main.h"

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9		pTextureScoreResult = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffScoreResult = NULL;		// 頂点バッファへのポインタ
	int						nScoreResult;					// スコア
	int						MAX_SCORERESULT		= 8;		// 桁数
	int						nCntTimeScoreResult;			// カウンター
	int						nTimeScoreResult;				// リザルトカウンター
}SCORERESULT;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitScoreResult	(void);
void UninitScoreResult	(void);
void UpdateScoreResult	(void);
void DrawScoreResult	(void);
void AddTimeScore		(int nValue);
#endif