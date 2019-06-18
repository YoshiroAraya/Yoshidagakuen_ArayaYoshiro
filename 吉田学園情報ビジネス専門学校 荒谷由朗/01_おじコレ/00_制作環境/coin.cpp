//=============================================================================
//
// コイン処理 [coin.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "coin.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_COIN				(128)								// コインの最大数
#define POYGON_TEXTURENAME		"data/TEXTURE/coin000.png"			// 読み込むテクスチャ
#define COIN_TEXTURE_SPEED		(10)								// コインアニメーションスピード
#define COIN_TEXTURE_UV_U		(0.25f)								// コインアニメーションU範囲
#define COIN_TEXTURE_UV_V		(1.0f)								// コインアニメーションV範囲


//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureCoin = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCoin = NULL;	// 頂点バッファへのポインタ
Coin					g_aCoin[MAX_COIN];		// コインの情報

//=============================================================================
// コインの初期化処理
//=============================================================================
void InitCoin(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntCoin;

	// デバイスの取得
	pDevice = GetDevice();

	// コインの情報の初期化
	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		g_aCoin[nCntCoin].pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCoin[nCntCoin].nCounterAnim	= 0;
		g_aCoin[nCntCoin].nPatternAnim	= 0;
		g_aCoin[nCntCoin].bUse			= false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureCoin);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCoin,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		// 頂点設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(COIN_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, COIN_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(COIN_TEXTURE_UV_U, COIN_TEXTURE_UV_V);

		pVtx += 4;				// 頂点データへのポインタを4つ進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffCoin->Unlock();
}

//=============================================================================
// コインの終了処理
//=============================================================================
void UninitCoin(void)
{
	// テクスチャの開放
	if (g_pTextureCoin != NULL)
	{
		g_pTextureCoin->Release();
		g_pTextureCoin = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffCoin != NULL)
	{
		g_pVtxBuffCoin->Release();
		g_pVtxBuffCoin = NULL;
	}
}

//=============================================================================
// コインの更新処理
//=============================================================================
void UpdateCoin(void)
{
	int nCntCoin;
	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == true)
		{	// コインが使用されている
			g_aCoin[nCntCoin].nCounterAnim++;			// カウンター加算

			if ((g_aCoin[nCntCoin].nCounterAnim % COIN_TEXTURE_SPEED) == 0)		// アニメーションの速さを変えられる
			{
				g_aCoin[nCntCoin].nPatternAnim = (g_aCoin[nCntCoin].nPatternAnim + 1);

				// 頂点設定
				pVtx[nCntCoin * 4].pos		= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x, g_aCoin[nCntCoin].pos.y, 0.0f);
				pVtx[nCntCoin * 4 + 1].pos	= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth, g_aCoin[nCntCoin].pos.y, 0.0f);
				pVtx[nCntCoin * 4 + 2].pos	= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x, g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight, 0.0f);
				pVtx[nCntCoin * 4 + 3].pos	= D3DXVECTOR3(g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth, g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight, 0.0f);

				// テクスチャ設定
				pVtx[nCntCoin * 4].tex		= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f), 0.0f);
				pVtx[nCntCoin * 4 + 1].tex	= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f) + 0.25f, 0.0f);
				pVtx[nCntCoin * 4 + 2].tex	= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f), COIN_TEXTURE_UV_V);
				pVtx[nCntCoin * 4 + 3].tex	= D3DXVECTOR2((g_aCoin[nCntCoin].nPatternAnim * 0.25f) + 0.25f, COIN_TEXTURE_UV_V);
			}
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffCoin->Unlock();
}

//=============================================================================
// コインの描画処理
//=============================================================================
void DrawCoin(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntCoin;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffCoin, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCoin);

	// ポリゴンの描画
	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntCoin * 4, 2);
		}
	}
}

//=============================================================================
// コインの設定処理
//=============================================================================
void SetCoin(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntCoin;

	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == false)
		{
			g_aCoin[nCntCoin].pos		= pos;
			g_aCoin[nCntCoin].fWidth	= fWidth;
			g_aCoin[nCntCoin].fHeight	= fHeight;

			// 頂点設定
			pVtx[nCntCoin * 4].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntCoin * 4 + 1].pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntCoin * 4 + 2].pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntCoin * 4 + 3].pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aCoin[nCntCoin].bUse = true;
			break;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffCoin->Unlock();
}

//=============================================================================
// コインの設定処理
//=============================================================================
bool CollisionCoin(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int		nCntCoin;
	bool	bLand = false;		// 着地したかどうか

	VERTEX_2D *pVtx;					// 頂点情報へのポインタ
	FADE fade = GetFade();				// フェードの取得
	Player *pPlayer = GetPlayer();		// プレイヤーの取得

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	// 当たり判定
	for (nCntCoin = 0; nCntCoin < MAX_COIN; nCntCoin++)
	{
		if (g_aCoin[nCntCoin].bUse == true)
		{
			if (g_aCoin[nCntCoin].pos.x - 30 <= pPos->x
				&& g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth + 30 >= pPos->x)
			{// 上下の範囲内
				if (g_aCoin[nCntCoin].pos.y <= pPos->y
					&& g_aCoin[nCntCoin].pos.y >= pPosOld->y)
				{// 上
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// 使用していない状態
				}
				else if (g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight > pPos->y
					&& g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight < pPosOld->y)
				{// 下
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// 使用していない状態
				}
			}
			if (g_aCoin[nCntCoin].pos.y < pPos->y
				&& g_aCoin[nCntCoin].pos.y + g_aCoin[nCntCoin].fHeight + 40 > pPos->y)
			{// 左右の範囲内
				if (g_aCoin[nCntCoin].pos.x - 15 >= pPosOld->x
					&& g_aCoin[nCntCoin].pos.x - 15 <= pPos->x)
				{// 左
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// 使用していない状態
				}
				if (g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth + 15 <= pPosOld->x
					&& g_aCoin[nCntCoin].pos.x + g_aCoin[nCntCoin].fWidth + 15 >= pPos->x)
				{// 右
					AddScore(200);
					PlaySound(SOUND_LABEL_SE_COINGET);
					g_aCoin[nCntCoin].bUse = false;			// 使用していない状態
				}
			}
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffCoin->Unlock();

	return bLand;
}