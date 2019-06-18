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
//敵のタイプ
//=============================================================================
typedef enum
{
	EnemyType_NORMAL = 0,
	EnemyType_MAX
}EnemyType;

//=============================================================================
// 敵の状態
//=============================================================================
typedef enum
{
	ENEMEYSTATE_NEUTRAL = 0,
	ENEMEYSTATE_DEATH,
	ENEMEYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

//=============================================================================
// モデルの構造体
//=============================================================================
typedef struct
{
	LPD3DXMESH				pMash		= NULL;
	LPD3DXBUFFER			pBuffMat	= NULL;
	DWORD					nNumMat;
	D3DXMATRIX				mtxWorld;
	LPDIRECT3DTEXTURE9		pTexture;
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	float					nIdxModelParent = -1;	// 親モデルのインデックス
	char					FileName[256];
}EnemyModel;

//=============================================================================
// 敵の構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX	mtxWorld;
	D3DXVECTOR3 Pos;			// 現在の位置
	D3DXVECTOR3 PosOld;			// 位置
	D3DXVECTOR3 PosDest;		// 目標の座標
	D3DXVECTOR3 fPosAngle;		// 座標の差分
	D3DXVECTOR3 Rot;			// 現在の向き
	D3DXVECTOR3 RotDest;		// 目標の向き
	D3DXVECTOR3 fRotAngle;		// 向きの差分
	D3DXVECTOR3 move;			// 移動
	D3DXVECTOR3 vtxMin;			// モデルの最小値
	D3DXVECTOR3 vtxMax;			// モデルの最大値
	int	nNumParts = 0;			// パーツの番号
	int MAX_PARTS;				// パーツの最大数
	int nCntPlayermotion;		// モーションの番号
	int nLife;					// 寿命
	float		fAngle;			// 差分
	float nSpped;				// 敵の移動速度
	bool bUse;					// 使用しているかどうか
	EnemyModel aModel[256];		// パーツ
	EnemyType type;				// 種類
	ENEMYSTATE EnemyState;		// エネミーの状態
}Enemy;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void		InitEnemy			(void);
void		UninitEnemy			(void);
void		UpdateEnemy			(void);
void		DrawEnemy			(void);
void		SetEnemy			(D3DXVECTOR3 pos);
void		SetEnemyState		(ENEMYSTATE state);
void		HitEnemy			(int nNumEnemy,int nDamage, int typ);
ENEMYSTATE	GetEnemyStateNow	(void);
Enemy		*GetEnemy			(void);
#endif