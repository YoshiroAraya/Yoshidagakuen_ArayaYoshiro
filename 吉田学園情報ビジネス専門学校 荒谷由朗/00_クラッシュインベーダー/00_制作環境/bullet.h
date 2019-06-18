//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// 弾の種類
//=============================================================================
typedef enum
{

	BULLETTYPE_PLAYER = 0,		// プレイヤーの弾
	BULLETTYPE_PLAYER1 = 0,		// プレイヤーの弾
	BULLETTYPE_PLAYER2 = 0,		// プレイヤーの弾
	BULLETTYPE_ENEMY,			// 敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBullet		(void);
void UninitBullet	(void);
void UpdateBullet	(void);
void DrawBullet		(void);
void SetBullet		(D3DXVECTOR3 pos,
					D3DXVECTOR3 move,
					BULLETTYPE type,
					int nType);
#endif
