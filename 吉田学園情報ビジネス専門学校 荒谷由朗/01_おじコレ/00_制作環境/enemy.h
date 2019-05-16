//=============================================================================
//
// 敵処理 [enemy.h]
// Author :荒谷由朗
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(256)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//敵の状態の種類（列挙型）
//typedef enum
//{
//	ENEMTSTATE_NORMAL = 0,		//敵の通常状態
//	ENEMTSTATE_DAMAGE,			//敵のダメージ状態
//	ENMEYSTATE_MAX				//敵の状態種類の総数
//}ENEMYSTATE;

//敵の構造体
typedef enum
{
	EnemyType_NORMAL1 = 0,
	EnemyType_NORMAL2,
	EnemyType_MAX
}EnemyType;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//弾の移動量
	D3DXCOLOR col;			//色
	float move_bullet;
	float fWidth;			//幅
	float fHeight;			//高さ
	EnemyType type;			//種類
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	int nCounterState;		//状態管理のカウンター
	float nSpped;			//敵の移動速度
	bool bUse;				//使用されているかどうか
}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, EnemyType type, float move_bullet);
//Enemy *GetEnemy(void);
#endif