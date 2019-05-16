//=============================================================================
//
// ライフ処理 [life.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//****************************************************************************
#define MAX_LIFE (128)
//*****************************************************************************
// 構造体宣言
//****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置(中心座標)
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 ParentPos;
	D3DXVECTOR3 ParentRot;
	D3DXCOLOR col;
	D3DXVECTOR3 fAngle;
	float		nAngle;
	float		nHeight;
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;
	float RADIUS;		// 半径
	bool bUse;
}LIFE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLife(void);		//ライフ初期化
void UninitLife(void);	//ライフ終了
void UpdateLife(void);	//ライフ更新
void DrawLife(void);		//ライフ描画
LIFE *GetLife(void);

//void SetLife(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Parentpos, D3DXVECTOR3 Parentrot, D3DXCOLOR col);
void HitDamage(int nDamage);
bool CollisionClinder(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
double Norm(double *vec, int nCntDimensions);
#endif
