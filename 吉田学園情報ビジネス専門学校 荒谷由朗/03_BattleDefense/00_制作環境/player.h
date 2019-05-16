//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// プレイヤーのアニメーションの状態
typedef enum
{
	PLAYER_STATE_NEUTRAL = 0,
	PLAYER_STATE_DEATH,
	PLAYER_STATE_DAMAGE,
	PLAYER_STATE_MAX
}PLAYER_STATE;

typedef enum
{
	PLAYER_MOSIONSTATE_NEUTRAL = 0,
	PLAYER_MOSIONSTATE_MOVE,
	PLAYER_MOSIONSTATE_UP,
	PLAYER_MOSIONSTATE_DOWN,
	PLAYER_MOSIONSTATE_TURNING_R,
	PLAYER_MOSIONSTATE_TURNING_L,
	PLAYER_MOSIONSTATE_AVOID_R,
	PLAYER_MOSIONSTATE_AVOID_L,
	PLAYER_MOSIONSTATE_MAX
}PLAYER_MOSIONSTATE;

// モデルの構造体
typedef struct
{
	LPD3DXMESH pMash = NULL;
	LPD3DXBUFFER pBuffMat = NULL;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float nIdxModelParent = -1;	// 親モデルのインデックス
	char FileName[256];
}Model;

// プレイヤーの構造体
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;					// 現在の位置
	D3DXVECTOR3 posOld;					// 位置
	D3DXVECTOR3 rot;					// 向き
	D3DXCOLOR	col;					// 色
	float rotDest;						// 目標の向き
	float fAngle;						// 差分
	D3DXVECTOR3 move;					// 移動
	D3DXVECTOR3 vtxMin;					// モデルの最小値
	D3DXVECTOR3 vtxMax;					// モデルの最大値
	int nLife;							// ライフ
	int nCunterState;
	int nCntFleam;
	int PlayerAnim;
	int	nNumParts = 0;
	int MAX_PARTS;						// パーツの最大数
	int nCntPlayermotion;				// モーションの番号 
	bool bUse;						//使用しているかどうか
	Model aModel[256];					// パーツ
	PLAYER_STATE PlayerState;
}Player;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void SetPLAYER_STATE(PLAYER_STATE state);
void SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE state);
PLAYER_MOSIONSTATE GetPLAYER_MOSIONSTATENow(void);
Player *GetPlayer(void);

#endif
