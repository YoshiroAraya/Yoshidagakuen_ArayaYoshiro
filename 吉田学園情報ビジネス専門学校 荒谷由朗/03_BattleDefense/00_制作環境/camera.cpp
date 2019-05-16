//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 荒谷由朗
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_Camera;	//カメラの情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	//Player *g_aEnemy;
	////プレイヤーの取得
	//g_aEnemy = GetPlayer();
	//g_Camera.posV = g_aEnemy->pos + D3DXVECTOR3(0.0f,100.0f,-200.0f);		//視点
	//g_Camera.posR = g_aEnemy->pos;											//注視点
	//g_Camera.vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);									//上方向ベクトル
	//g_Camera.CameraMove = 0;														//移動量
	//g_Camera.CameraDistance = -g_Camera.posV.z;										//距離
	//g_Camera.CameraTimer = 0;
	g_Camera.posV = D3DXVECTOR3(0.0f, 120, -300);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fAngle = 0.0f;
	g_Camera.fLength = g_Camera.posV.z - g_Camera.posR.z;
	g_Camera.nCounterAngle = 0.0f;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	////カメラ移動(WSAD)
	//if (GetKeyboardPress(DIK_UP))
	//{//上
	//	g_Camera.posV.x += sinf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;
	//	g_Camera.posV.z += cosf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_DOWN))
	//{//下
	//	g_Camera.posV.x -= sinf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;
	//	g_Camera.posV.z -= cosf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) *g_Camera.CameraDistance;
	//}
	//if (GetKeyboardPress(DIK_RIGHT))
	//{//左
	//	g_Camera.posV.x += sinf(D3DX_PI*0.5f + g_Camera.CameraMove) * 2.0f;
	//	g_Camera.posV.z += cosf(D3DX_PI*0.5f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_LEFT))
	//{//右
	//	g_Camera.posV.x -= sinf(D3DX_PI*0.5f + g_Camera.CameraMove) * 2.0f;
	//	g_Camera.posV.z -= cosf(D3DX_PI*0.5f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) *g_Camera.CameraDistance;
	//}
	//視点操作(YNZC)
	//if (GetKeyboardPress(DIK_Y))
	//{//上
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posV.y = g_Camera.posR.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_N))
	//{//下
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posV.y = g_Camera.posR.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//if (GetKeyboardPress(DIK_Z) == true)
	//{//左
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{//右
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	////注視点操作(TBQE)
	//if (GetKeyboardPress(DIK_T))
	//{//上
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posR.y = g_Camera.posV.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_B))
	//{//下
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posR.y = g_Camera.posV.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//if (GetKeyboardPress(DIK_Q))
	//{//左
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_E))
	//{//右
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}

	Player *pPlayer;
	//プレイヤーの取得
	pPlayer = GetPlayer();

	////カメラの追従
	//g_Camera.posR = g_aEnemy->pos;
	//g_Camera.posV = D3DXVECTOR3(sinf(g_Camera.CameraMove) * g_Camera.CameraDistance + g_Camera.posR.x, g_Camera.posV.y, cosf(g_Camera.CameraMove) * g_Camera.CameraDistance + g_Camera.posR.z);

	//現在のモードを取得
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:
		////視点旋回キーが押された場合
		//if (GetKeyboardPress(DIK_Z) == true)
		//{	// Zで左旋回
		//	g_Camera.rot.y += 0.02f;
		//	g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
		//	g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
		//	if (g_Camera.rot.y > D3DX_PI)
		//	{
		//		g_Camera.fAngle -= D3DX_PI * 2.0f;
		//	}
		//}
		//if (GetKeyboardPress(DIK_C) == true)
		//{	// Cで右旋回
		//	g_Camera.rot.y -= 0.02f;
		//	g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
		//	g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
		//	if (g_Camera.rot.y < -D3DX_PI)
		//	{
		//		g_Camera.fAngle += D3DX_PI * 2.0f;
		//	}
		//}

		/*g_Camera.posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.x) * 80, pPlayer->pos.y, pPlayer->pos.z + cosf(pPlayer->rot.z) * 80);
		g_Camera.posVDest = D3DXVECTOR3(pPlayer->pos.x + sinf(g_Camera.fAngle) * g_Camera.fLength, pPlayer->pos.y, pPlayer->pos.z + cosf(g_Camera.fAngle) * g_Camera.fLength);*/

		/*g_Camera.posR += (g_Camera.posRDest - g_Camera.posR) * 0.2f;
		g_Camera.posV += (g_Camera.posVDest - g_Camera.posV) * 0.2f;*/

		/*g_Camera.rotDest = D3DXVECTOR3(g_Camera.rot.x, g_Camera.rot.y + sinf(pPlayer->rot.y + g_Camera.rot.y) * g_Camera.fLength, g_Camera.rot.z);
		g_Camera.rot += (g_Camera.rotDest - g_Camera.rot) * 0.2f;*/

		//カメラの追従
		g_Camera.posR = pPlayer->pos + D3DXVECTOR3(0.0f,50.0f,0.0f);
		g_Camera.posV = D3DXVECTOR3(sinf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.x, g_Camera.posR.y, cosf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.z);

		//プレイヤーの後ろにする
		g_Camera.rotDest.y = (pPlayer->rot.y + D3DX_PI);
		g_Camera.DiffAngle.y = g_Camera.rotDest.y - g_Camera.rot.y;

		//角度の設定
		if (g_Camera.DiffAngle.y > D3DX_PI)
		{
			g_Camera.DiffAngle.y -= D3DX_PI* 2.0f;
		}
		if (g_Camera.DiffAngle.y < -D3DX_PI)
		{
			g_Camera.DiffAngle.y += D3DX_PI* 2.0f;
		}

		g_Camera.rot.y += g_Camera.DiffAngle.y * 0.03f;

		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI* 2.0f;
		}
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI* 2.0f;
		}
		break;

	case MODE_TITLE:
		//カウンターの加算
		g_Camera.nCounterAngle++;

		if (g_Camera.nCounterAngle < 300)
		{
			g_Camera.posV = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
			g_Camera.posR = D3DXVECTOR3(500.0f, 0.0f, -600.0f);
		}
		/*if (g_Camera.nCounterAngle == 300)
		{
		g_Camera.posV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		}
		if (g_Camera.nCounterAngle == 600)
		{
		g_Camera.posV = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		g_Camera.fLength = 200;
		}
		if (g_Camera.nCounterAngle == 900)
		{
		g_Camera.nCounterAngle = 0;
		}
		if (g_Camera.nCounterAngle < 300)
		{
		g_Camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
		}*/

		g_Camera.rot.y += 0.003f;
		// 3.14を上回った
		if (g_Camera.rot.y > D3DX_PI)
		{
			// 3.14を -3.14にする
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}
		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y + D3DX_PI)* g_Camera.fLength;
		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y + D3DX_PI)* g_Camera.fLength;

		break;
	}

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),								//画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//画面比率
		10.0f,
		2000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
						&g_Camera.posV,
						&g_Camera.posR,
						&g_Camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

Camera *GetCamera(void)
{
	return &g_Camera;
}