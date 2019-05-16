//=============================================================================
//
// スコア処理 [life.cpp]
// Author : 荒谷由朗
//
//=============================================================================
#include "life.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/stock000.png"		// 読み込むテクスチャファイル名
#define MAX_LIFE			(5)								//ライフの数								

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// 頂点バッファへのポインタ
bool g_bUse[MAX_LIFE];

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_LIFE,		// ファイルの名前
								&g_pTextureLife);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLife(pDevice);

	for (int nCount = 0; nCount < MAX_LIFE; nCount++)
	{
		g_bUse[nCount] = true;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	// テクスチャの開放
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//敵の弾
	Player *pPlayer;

	//プレイヤーの取得
	pPlayer = GetPlayer();
	int nCntScore;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < MAX_LIFE; nCntScore++)
	{
		if (g_bUse[nCntScore] == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
		}
	}
	
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScore;
	float nScorePos;				//スコア位置

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0, nScorePos = 700; nCntScore < MAX_LIFE; nCntScore++, nScorePos += 40)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(nScorePos, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(nScorePos + 30.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(nScorePos, 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(nScorePos + 30.0f, 60.0f, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// ライフの取得
//=============================================================================
void HitLife(int nLife)
{
	Player *pPlayer;
	//プレイヤーの取得
	pPlayer = GetPlayer();

	g_bUse[pPlayer->nLife] = false;
	
}

//=============================================================================
// ライフの取得
//=============================================================================
bool GetLife(void)
{
	return g_bUse[0];
}