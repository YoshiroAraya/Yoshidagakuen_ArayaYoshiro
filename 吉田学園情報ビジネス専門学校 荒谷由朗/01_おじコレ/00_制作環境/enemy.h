//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_ENEMY	(256)	// 敵の最大数

//=============================================================================
// 敵の構造体
//=============================================================================
typedef enum
{
	EnemyType_NORMAL1 = 0,
	EnemyType_NORMAL2,
	EnemyType_MAX
}EnemyType;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	D3DXCOLOR	col;			// 色
	float		move_bullet;	// 弾の移動量
	float		fWidth;			// 幅
	float		fHeight;		// 高さ
	EnemyType	type;			// 種類
	int			nCounterAnim;	// アニメーションカウンター
	int			nPatternAnim;	// アニメーションパターンNo.
	int			nCounterState;	// 状態管理のカウンター
	float		nSpped;			// 敵の移動速度
	bool		bUse;			// 使用されているかどうか
}Enemy;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEnemy	(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy	(void);
void SetEnemy	(D3DXVECTOR3 pos, float fWidth, float fHeight, EnemyType type, float move_bullet);
#endif