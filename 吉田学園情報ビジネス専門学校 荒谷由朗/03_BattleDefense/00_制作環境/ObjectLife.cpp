//=============================================================================
//
// オブジェクトのライフゲージ処理 [ObjectLife.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "ObjectLife.h"
#include "game.h"
#include "player.h"
#include "obstacle.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_OBLife001		"data/TEXTURE/gauge.png"			// 読み込むテクスチャフェイル名
#define TEXTURE_OBLife000		"data/TEXTURE/Metre000.png"			// 読み込むテクスチャフェイル名
#define MAX_OBLife				(2)									// ゲージの最大数
#define REDUCE_OBLife			(0.3f)								// ゲージの減る量(毎フレーム)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexOBLife(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureOBLife[MAX_OBLife] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffOBLife = NULL;			// 頂点バッファへのポインタ
float					g_fOBLife;							// ゲージの値
float					g_fOBLifeColR;						// ゲージの色(赤)
float					g_fOBLifeColG;						// ゲージの色(緑)
float					g_fOBLifeColB;						// ゲージの色(青)

//=============================================================================
// 初期化処理
//=============================================================================
void InitOBLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ゲージの初期化
	g_fOBLife		= 400.0f;
	g_fOBLifeColR	= 1.0f;
	g_fOBLifeColG	= 0.0f;
	g_fOBLifeColB	= 0.0f;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OBLife000, &g_pTextureOBLife[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OBLife001, &g_pTextureOBLife[1]);

	// 頂点情報の作成
	MakeVertexOBLife(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOBLife(void)
{
	for (int nCntOBLife = 0; nCntOBLife < MAX_OBLife; nCntOBLife++)
	{
		// テクスチャの開放
		if (g_pTextureOBLife[nCntOBLife] != NULL)
		{
			g_pTextureOBLife[nCntOBLife]->Release();
			g_pTextureOBLife[nCntOBLife] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffOBLife != NULL)
	{
		g_pVtxBuffOBLife->Release();
		g_pVtxBuffOBLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateOBLife(void)
{
	OBSTACLE *g_aObstacle;
	g_aObstacle = GetObstaclel();

	// 頂点情報の作成
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffOBLife->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aObstacle->ObjectState == OBJECTSTATE_DAMAGE)
	{
		g_fOBLife -= ((400.0f - 17.0f) / g_aObstacle->nLifeMAX);
	}

	if (g_aObstacle->nLife == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
	}
	else
	{
		pVtx[0].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_fOBLife, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_fOBLife, 65.0f, 0.0f);
	}

	// 色の変化(ゲージ)
	if (g_fOBLife >= 17.0f && g_fOBLife <= 100.0f)
	{
		g_fOBLifeColG -= 0.002f;

		if (g_fOBLifeColG <= 0.0f)
		{
			g_fOBLifeColG = 0.0f;
		}

		pVtx[0].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fOBLifeColR, g_fOBLifeColG, g_fOBLifeColB, 0.8f);
	}

	//頂点バッファのアンロック
	g_pVtxBuffOBLife->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOBLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffOBLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntOBLife = 0; nCntOBLife < MAX_OBLife; nCntOBLife++)
	{// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureOBLife[nCntOBLife]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntOBLife * 4, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexOBLife(LPDIRECT3DDEVICE9 pDevice)
{

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBLife,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffOBLife,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffOBLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntOBLife = 0; nCntOBLife < MAX_OBLife; nCntOBLife++)
	{
		if (nCntOBLife == 0)
		{
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3(17.0f, 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(400.0f, 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(17.0f, 65.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(400.0f, 65.0f, 0.0f);

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(415.0f, 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(415.0f, 80.0f, 0.0f);

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// 1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// 頂点データのポインタを４つ分進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffOBLife->Unlock();
}

//=============================================================================
// ライフの取得
//=============================================================================
float GetOBLife(void)
{
	return g_fOBLife;
}