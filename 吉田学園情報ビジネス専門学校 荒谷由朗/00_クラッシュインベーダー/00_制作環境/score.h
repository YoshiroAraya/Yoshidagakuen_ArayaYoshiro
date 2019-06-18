//=============================================================================
//
// スコア処理 [score.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitScore		(void);
void UninitScore	(void);
void UpdateScore	(void);
void DrawScore		(void);
void AddScore		(int nValue);
#endif