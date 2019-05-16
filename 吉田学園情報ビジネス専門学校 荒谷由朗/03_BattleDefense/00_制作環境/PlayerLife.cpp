//=============================================================================
//
// プレイヤーのライフゲージ処理 [PlayerLife.cpp]
// Author : 荒谷由朗
//
//=============================================================================
#include "PlayerLife.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_PlayerLife001		"data/TEXTURE/PlayerLife.png"			// 読み込むテクスチャフェイル名
#define TEXTURE_PlayerLife000		"data/TEXTURE/Metre000.png"			// 読み込むテクスチャフェイル名
#define MAX_PlayerLife				(1)									// ゲージの最大数	
#define REDUCE_PlayerLife			(0.3f)								// ゲージの減る量(毎フレーム)

#define LIFE_VERTEX ((g_PlayerLife_h + 1) * (g_PlayerLife_v + 1))
#define LIFE_INDEX ( (g_PlayerLife_h * g_PlayerLife_v )* 2 + (4 * (g_PlayerLife_v - 1)) + 2 )
#define LIFE_POLYGON ( (g_PlayerLife_h * g_PlayerLife_v) * 2 + (4 * (g_PlayerLife_v - 1)) )

#define LIFE_RADIUS (85.0f)
#define LIFE_RADIUS2 (50.0f)

#define LIFE_POS_X (95.0f)
#define LIFE_POS_Y (630.0f)

//#define LIFE_HEIGHT (5.0f)

#define LIFE_H (100) //メッシュの分割数(H)
#define LIFE_V (1) //メッシュの分割数(V)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPlayerLife(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexPlayerLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePlayerLife[MAX_PlayerLife] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerLife = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffPlayerLife = NULL; //インデックスバッファへのポインタ

float g_fPlayerLife;												// ゲージの値
float g_fPlayerLifeColR;											// ゲージの色(赤)
float g_fPlayerLifeColG;											// ゲージの色(緑)
float g_fPlayerLifeColB;											// ゲージの色(青)

int g_nPlayerLife;

int g_PlayerLife_h, g_PlayerLife_v;
float g_PosLife_x, g_PosLife_y;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_PlayerLife_h = LIFE_H;
	g_PlayerLife_v = LIFE_V;
	g_PosLife_x = LIFE_POS_X;
	g_PosLife_y = LIFE_POS_Y;
	int Polygon = (g_PlayerLife_h * g_PlayerLife_v) * 2 + (4 * (g_PlayerLife_v - 1));
	// ゲージの初期化
	g_fPlayerLife = 583.0f;
	g_fPlayerLifeColR = 1.0f;
	g_fPlayerLifeColG = 0.0f;
	g_fPlayerLifeColB = 0.0f;
	g_nPlayerLife = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PlayerLife000, &g_pTexturePlayerLife[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PlayerLife001, &g_pTexturePlayerLife[1]);

	// 頂点情報の作成
	MakeVertexPlayerLife(pDevice);
	MakeIndexPlayerLife(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerLife(void)
{
	for (int nCntPlayerLife = 0; nCntPlayerLife < MAX_PlayerLife; nCntPlayerLife++)
	{
		// テクスチャの開放
		if (g_pTexturePlayerLife[nCntPlayerLife] != NULL)
		{
			g_pTexturePlayerLife[nCntPlayerLife]->Release();
			g_pTexturePlayerLife[nCntPlayerLife] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPlayerLife != NULL)
	{
		g_pVtxBuffPlayerLife->Release();
		g_pVtxBuffPlayerLife = NULL;
	}
	//インデックスバッファの解放
	if (g_pIdxBuffPlayerLife != NULL)
	{
		g_pIdxBuffPlayerLife->Release();
		g_pIdxBuffPlayerLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerLife(void)
{
	if (g_nPlayerLife <= -LIFE_H *2)
	{
		g_nPlayerLife = 0;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerLife, 0, sizeof(VERTEX_2D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffPlayerLife);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, 0);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, LIFE_VERTEX, 0, LIFE_POLYGON + g_nPlayerLife);
	// ポリゴンの描画
	for (int nCntPlayerLife = 0; nCntPlayerLife < MAX_PlayerLife; nCntPlayerLife++)
	{// テクスチャの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayerLife * 4, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPlayerLife(LPDIRECT3DDEVICE9 pDevice)
{

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * LIFE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerLife,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = D3DX_PI * 2 / g_PlayerLife_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_PlayerLife_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_PlayerLife_h + 1; nCntLife_H++)
		{
			if (nCntLife_V == 0)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.x = -sinf(fDestAngle) * LIFE_RADIUS + g_PosLife_x;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.y = cosf(fDestAngle) * LIFE_RADIUS + g_PosLife_y;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.z = 0.0f;

				//頂点カラー
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

				//テクスチャ座標
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_PlayerLife_h / 2)), nCntLife_V * -1.0f);
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
			if (nCntLife_V == 1)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.x = -sinf(fDestAngle) * (LIFE_RADIUS - LIFE_RADIUS2) + g_PosLife_x;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.y = cosf(fDestAngle) * (LIFE_RADIUS - LIFE_RADIUS2) + g_PosLife_y;
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].pos.z = 0.0f;

				//頂点カラー
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].col = D3DXCOLOR(0.5f, 1.0f, 0.5f, 0.9f);

				//テクスチャ座標
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_PlayerLife_h / 2)), nCntLife_V * -1.0f);
				pVtx[nCntLife_V * (g_PlayerLife_h + 1) + nCntLife_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
		}
	}
	//for (int nCntGauge = 0; nCntGauge < MAX_PlayerLife; nCntGauge++)
	//{
	//	if (nCntGauge == 0)
	//	{
	//		//頂点設定
	//		pVtx[0].pos = D3DXVECTOR3(68.0f, 652.0f, 0.0f);
	//		pVtx[1].pos = D3DXVECTOR3(583.0f, 652.0f, 0.0f);
	//		pVtx[2].pos = D3DXVECTOR3(68.0f, 690.0f, 0.0f);
	//		pVtx[3].pos = D3DXVECTOR3(583.0f, 690.0f, 0.0f);

	//		//頂点カラー設定
	//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	//	}
	//	else
	//	{
	//		// メモリ
	//		//頂点設定
	//		pVtx[0].pos = D3DXVECTOR3(50.0f, 630.0f, 0.0f);
	//		pVtx[1].pos = D3DXVECTOR3(600.0f, 630.0f, 0.0f);
	//		pVtx[2].pos = D3DXVECTOR3(50.0f, 700.0f, 0.0f);
	//		pVtx[3].pos = D3DXVECTOR3(600.0f, 700.0f, 0.0f);

	//		//頂点カラー設定
	//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	}

	//	//1.0fで固定
	//	pVtx[0].rhw = 1.0f;
	//	pVtx[1].rhw = 1.0f;
	//	pVtx[2].rhw = 1.0f;
	//	pVtx[3].rhw = 1.0f;

	//	//テクスチャ設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	pVtx += 4;	//頂点データのポインタを４つ分進める
	//}
	//頂点バッファのアンロック
	g_pVtxBuffPlayerLife->Unlock();
}
//=============================================================================
// インデックス情報の作成
//=============================================================================
void MakeIndexPlayerLife(LPDIRECT3DDEVICE9 pDevice)
{
	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * LIFE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffPlayerLife,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//インデックスのカウント

						//インデックスバッファをロック
	g_pIdxBuffPlayerLife->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_PlayerLife_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_PlayerLife_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_PlayerLife_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_PlayerLife_h && nCntIndex_V <= g_PlayerLife_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_PlayerLife_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//頂点バッファをアンロック
	g_pIdxBuffPlayerLife->Unlock();

}
void HitPlayerLife(int nDamage)
{
	g_nPlayerLife -= nDamage;
}

float GetPlayerLife(void)
{
	return g_fPlayerLife;
}