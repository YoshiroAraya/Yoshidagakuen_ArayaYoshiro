//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			//現在の視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posR;			//現在の注視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 rot;			//現在の向き
	D3DXVECTOR3 rotDest;		//目的の向き
	D3DXVECTOR3 move;			//移動
	D3DXVECTOR3 DiffAngle;		// 向きの記録
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	float CameraDistance;		//距離
	float CameraMove;			//移動量
	int CameraTimer;			//
	float fAngle;
	float nCounterAngle;
	float fLength;				// posVとposRの差分
}Camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif
