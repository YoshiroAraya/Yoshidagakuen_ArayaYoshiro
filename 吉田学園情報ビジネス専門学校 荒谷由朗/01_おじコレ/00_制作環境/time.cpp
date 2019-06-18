//=============================================================================
//
// タイム処理 [time.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "time.h"
#include "fade.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_TIME			(3)								// 桁数
#define TIME_SPEED			(6)								// タイムのスピード

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// 頂点バッファへのポインタ
int						g_nTime;					// タイム
int						nCntTime;					// カウンター

//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスを取得

	g_nTime		= 900;	// タイムの初期化
	nCntTime	= 0;	// カウンターの初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_TIME,		// ファイルの名前
								&g_pTextureTime);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexTime(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	nCntTime++;								// カウンターの加算
	if ((nCntTime % TIME_SPEED) == 0)		// アニメーションの速さを変えられる
	{
		AddTime(-1);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスを取得

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	// ポリゴンの描画
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0, nTimePos = 100; nCntTime < MAX_TIME; nCntTime++, nTimePos -= 30)
	{
		// 頂点設定
		pVtx[0].pos = D3DXVECTOR3((float)nTimePos, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)nTimePos + 30.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((float)nTimePos, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)nTimePos + 30.0f, 80.0f, 0.0f);

		// 1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.9f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.9f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;				// 頂点データへのポインタを4つ進める
	}
	// 頂点バッファのアンロック
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// タイムの加算
//=============================================================================
void AddTime(int nValue)
{
	FADE fade = GetFade();		// フェードの取得

	g_nTime += nValue;			// タイムを代入
	int nTexData = g_nTime;		// タイムを格納

	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffTime->Lock
	(0, 0, (void**)&pVtx, 0);
	if (g_nTime >= 0)
	{
		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{// タイムカウント
			// テクスチャ設定
			pVtx[nCntTime * 4].tex		= D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 1].tex	= D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 2].tex	= D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
			pVtx[nCntTime * 4 + 3].tex	= D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
			nTexData /= 10;
		}
	}
	// タイマーが0以下になったとき
	else if (g_nTime <= 0)
	{
		if (fade != FADE_OUT)
		{
			SetGameState(GAMESTATE_OVER);
			// モード設定
			SetFade(MODE_RESULT);
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}