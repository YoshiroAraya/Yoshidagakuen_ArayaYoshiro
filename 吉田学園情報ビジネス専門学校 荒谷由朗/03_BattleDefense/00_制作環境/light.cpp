//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "light.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LIGHT		(6)			// ライトの最大数

//=============================================================================
// グローバル変数
//=============================================================================
D3DLIGHT9 g_light[MAX_LIGHT];		// ライトの情報

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3			vecDir0;
	D3DXVECTOR3			vecDir1;
	D3DXVECTOR3			vecDir2;
	D3DXVECTOR3			vecDir3;
	D3DXVECTOR3			vecDir4;
	D3DXVECTOR3			vecDir5;

	// ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;
	g_light[3].Type = D3DLIGHT_DIRECTIONAL;
	g_light[4].Type = D3DLIGHT_DIRECTIONAL;
	g_light[5].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[3].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[4].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[5].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);

	// ライトの方向の設定
	vecDir0 = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	vecDir1 = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vecDir2 = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vecDir3 = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	vecDir4 = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	vecDir5 = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	D3DXVec3Normalize(&vecDir0, &vecDir0);		// 正規化にする
	D3DXVec3Normalize(&vecDir1, &vecDir1);		// 正規化にする
	D3DXVec3Normalize(&vecDir2, &vecDir2);		// 正規化にする
	D3DXVec3Normalize(&vecDir3, &vecDir3);		// 正規化にする
	D3DXVec3Normalize(&vecDir4, &vecDir4);		// 正規化にする
	D3DXVec3Normalize(&vecDir5, &vecDir5);		// 正規化にする

	g_light[0].Direction = vecDir0;
	g_light[1].Direction = vecDir1;
	g_light[2].Direction = vecDir2;
	g_light[3].Direction = vecDir3;
	g_light[4].Direction = vecDir4;
	g_light[5].Direction = vecDir5;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
}