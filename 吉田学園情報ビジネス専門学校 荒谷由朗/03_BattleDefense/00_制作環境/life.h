//=============================================================================
//
// ライフ処理 [life.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LIFE (128)

//=============================================================================
// 構造体宣言
//=============================================================================
typedef struct
{
	D3DXMATRIX	mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置(中心座標)
	D3DXVECTOR3 ParentPos;	// 座標(オフセット)
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 ParentRot;	// 向き(オフセット)
	D3DXVECTOR3 fAngle;		// 差分
	D3DXCOLOR	col;		// 色
	D3DXVECTOR3 vecA;		// ベクトルA
	D3DXVECTOR3 vecB;		// ベクトルB
	float		nAngle;		// 差分
	float		nHeight;	// 高さ
	float		RADIUS;		// 半径
	bool		bUse;		// 使用しているか
}LIFE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitLife			(void);
void	UninitLife			(void);
void	UpdateLife			(void);
void	DrawLife			(void);
LIFE	*GetLife			(void);
void	HitDamage			(int nDamage);
bool	CollisionClinder	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
double	Norm				(double *vec, int nCntDimensions);
#endif