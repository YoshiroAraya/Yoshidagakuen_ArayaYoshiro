//=============================================================================
//
// エフェクト処理 [efect.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _EFECT_H_
#define _EFECT_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius);

#endif

