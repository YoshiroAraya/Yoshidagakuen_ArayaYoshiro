//=============================================================================
//
// 弾の処理 [bullet.h]
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
	BULLETTYPE_ENEMY,		// 敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 弾の位置(現在)
	D3DXVECTOR3 posOld;		// 弾の位置(過去)
	D3DXVECTOR3 move;		// 弾の移動量
	D3DXCOLOR	col;		// 色
	BULLETTYPE	type;		// 弾の種類
	int			nType;		// 種類
	int			nLife;		// 寿命
	bool		bUse;		// 使用しているかどうか
}Bullet;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void	InitBullet	(void);
void	UninitBullet(void);
void	UpdateBullet(void);
void	DrawBullet	(void);
void	SetBullet	(D3DXVECTOR3 pos,
					D3DXVECTOR3 move,
					BULLETTYPE type,
					int nType);
Bullet	*GetBullet	(void);
#endif