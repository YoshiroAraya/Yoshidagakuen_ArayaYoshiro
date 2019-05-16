//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// 構造体
//=============================================================================
typedef enum
{
	BULLETTYPE_NONE = 0,
	BULLETTYPE_PLAYER,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 posOld;				// 位置
	//D3DXVECTOR3 posDest;			// 目的の位置
	D3DXVECTOR3 posAngle;			// 差分の位置
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 rotDest;			// 目的の位置
	D3DXVECTOR3 rotAngle;			// 差分の位置
	D3DXVECTOR3 move;				// 移動
	D3DXMATRIX  mtxWorld;			// ワールドマトリックス
	D3DXMATRIX mtxView;				// ビューマトリックス
	D3DXVECTOR3 vtxMin;		// モデルの最小値
	D3DXVECTOR3 vtxMax;		// モデルの最大値
	int nIdyShadow;					// 影の番号
	int nLife;						// 寿命
	bool bUse;						// 使用しているかどうか
	BULLETTYPE type;
}Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,int nLife, BULLETTYPE type);
bool CollisionEnemyBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
bool CollisionPlayerBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy);

#endif
