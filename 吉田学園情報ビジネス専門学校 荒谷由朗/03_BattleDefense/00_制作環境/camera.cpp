//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=============================================================================
// グローバル変数
//=============================================================================
Camera g_Camera;	// カメラの情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.posV			= D3DXVECTOR3(0.0f, 120, -300);
	g_Camera.posR			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posVDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU			= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot			= D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Camera.rotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.DiffAngle		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fAngle			= 0.0f;
	g_Camera.fLength		= g_Camera.posV.z - g_Camera.posR.z;
	g_Camera.nCounterAngle	= 0.0f;
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
	// プレイヤーの取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	// 現在のモードを取得
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:
		// カメラの追従
		g_Camera.posR = pPlayer->pos + D3DXVECTOR3(0.0f,50.0f,0.0f);
		g_Camera.posV = D3DXVECTOR3(sinf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.x, g_Camera.posR.y, cosf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.z);

		// プレイヤーの後ろにする
		g_Camera.rotDest.y		= (pPlayer->rot.y + D3DX_PI);
		g_Camera.DiffAngle.y	= g_Camera.rotDest.y - g_Camera.rot.y;

		// 角度の設定
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
		// カウンターの加算
		g_Camera.nCounterAngle++;

		if (g_Camera.nCounterAngle < 300)
		{
			g_Camera.posV = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
			g_Camera.posR = D3DXVECTOR3(500.0f, 0.0f, -600.0f);
		}

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
		D3DXToRadian(45.0f),								// 画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			// 画面比率
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

//=============================================================================
// カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera;
}