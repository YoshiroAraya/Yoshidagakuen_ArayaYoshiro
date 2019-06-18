//=============================================================================
//
// 影の処理 [shadow.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitShadow			(void);
void	UninitShadow		(void);
void	UpdateShadow		(void);
void	DrawShadow			(void);
void	SetPositionShadow	(int nIdyShadow, D3DXVECTOR3 pos);
void	DeleteShadow		(int nIdyShadow);
int		SetShadow			(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif