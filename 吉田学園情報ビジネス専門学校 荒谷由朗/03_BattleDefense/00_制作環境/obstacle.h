//=============================================================================
//
// 障害物の処理 [obstacle.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"

//=============================================================================
// オブジェクトの状態
//=============================================================================
typedef enum
{
	OBJECTSTATE_NORMAL = 0,		// 通常
	OBJECTSTATE_DAMAGE,			// ダメージ
	OBJECTSTATE_DEATH,			// 死亡
	OBJECTSTATE_MAX
}OBJECTSTATE;

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX	mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 pos;			// 現在の位置
	D3DXVECTOR3 posOld;			// 過去の位置
	D3DXVECTOR3 move;			// 移動
	D3DXVECTOR3	rot;			// 向き
	D3DXVECTOR3 vtxMin;			// モデルの最小値
	D3DXVECTOR3 vtxMax;			// モデルの最大値
	int			nLife;			// ライフ
	int			nLifeMAX;		// ライフの最大数
	int			nIdyShadow;		// 影の番号
	float		nCunterState;	// ステータスカウンター
	bool		bUse;			// 使用しているかどうか
	OBJECTSTATE ObjectState;
}OBSTACLE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void		InitObstaclel				(void);
void		UninitObstaclel				(void);
void		UpdateObstaclel				(void);
void		DrawObstaclel				(void);
bool		CollisionObstaclel_Player	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
bool		CollisionObstaclel_Enemy	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy);
void		HitObstaclel				(int nDamage);
OBSTACLE	*GetObstaclel				(void);
#endif