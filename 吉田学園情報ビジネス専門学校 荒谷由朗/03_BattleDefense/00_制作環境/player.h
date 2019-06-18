//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 荒谷 由朗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// プレイヤーのアニメーションの状態
//=============================================================================
typedef enum
{
	PLAYER_STATE_NEUTRAL = 0,		// 通常
	PLAYER_STATE_DAMAGE,			// ダメージ
	PLAYER_STATE_DEATH,				// 死亡
	PLAYER_STATE_MAX
}PLAYER_STATE;

//=============================================================================
//
//=============================================================================
typedef enum
{
	PLAYER_MOSIONSTATE_NEUTRAL = 0,		// ニュートラル
	PLAYER_MOSIONSTATE_MOVE,			// 移動
	PLAYER_MOSIONSTATE_UP,				// 上昇
	PLAYER_MOSIONSTATE_DOWN,			// 下降
	PLAYER_MOSIONSTATE_TURNING_R,		// 右旋回
	PLAYER_MOSIONSTATE_TURNING_L,		// 左旋回
	PLAYER_MOSIONSTATE_MAX
}PLAYER_MOSIONSTATE;

//=============================================================================
// モデルの構造体
//=============================================================================
typedef struct
{
	LPD3DXMESH				pMash = NULL;			// メッシュ
	LPD3DXBUFFER			pBuffMat = NULL;		// バッファ
	DWORD					nNumMat;				// マテリアルデータ
	D3DXMATRIX				mtxWorld;				// ワールドマトリックス
	LPDIRECT3DTEXTURE9		*pTexture;				// テクスチャデータへのポインタ
	D3DXMATERIAL			*pmat;					// マテリアルデータへのポインタ
	D3DXVECTOR3				pos;					// 座標
	D3DXVECTOR3				rot;					// 向き
	float					nIdxModelParent = -1;	// 親モデルのインデックス
	char					FileName[256];			// テキストファイルのアドレス
}Model;

//=============================================================================
// プレイヤーの構造体
//=============================================================================
typedef struct
{
	D3DXMATRIX		mtxWorld;
	D3DXVECTOR3		pos;					// 現在の位置
	D3DXVECTOR3		posOld;					// 位置
	D3DXVECTOR3		rot;					// 向き
	D3DXVECTOR3		move;					// 移動
	D3DXVECTOR3		vtxMin;					// モデルの最小値
	D3DXVECTOR3		vtxMax;					// モデルの最大値
	D3DXCOLOR		col;					// 色
	int				nLife;					// ライフ
	int				nCunterState;			// カウンターステータス
	int				nCntFleam;				// フレームのカウンター
	int				PlayerAnim;				// モーションカウンター
	int				nNumParts = 0;			// パーツの番号
	int				MAX_PARTS;				// パーツの最大数
	int				nCntPlayermotion;		// モーションの番号
	float			rotDest;				// 目標の向き
	float			fAngle;					// 差分
	bool			bUse;					// 使用しているかどうか
	Model			aModel[3];				// パーツ
	PLAYER_STATE	PlayerState;			// プレイヤーの状態
}Player;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void				InitPlayer					(void);
void				UninitPlayer				(void);
void				UpdatePlayer				(void);
void				DrawPlayer					(void);
void				HitPlayer					(int nDamage);
void				SetPLAYER_STATE				(PLAYER_STATE state);
void				SetPLAYER_MOSIONSTATE		(PLAYER_MOSIONSTATE state);
PLAYER_MOSIONSTATE	GetPLAYER_MOSIONSTATENow	(void);
Player				*GetPlayer					(void);
#endif