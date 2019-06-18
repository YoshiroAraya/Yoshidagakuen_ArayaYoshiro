//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_EXPLOSION				(128)								// 弾の最大数
#define POYGON_TEXTURENAME			"data/TEXTURE/explosion000.png"		// 読み込むテクスチャ
#define EXPLOSION_POS_X				(300)								// 弾の左上X座標
#define EXPLOSION_POS_Y				(450)								// 弾の左上Y座標
#define EXPLOSION_WIDTH				(600)								// 弾の幅
#define EXPLOSION_HEIGHT			(600)								// 弾の高さ
#define EXPLOSIONT_TEXTURE_SPEED	(1)									// 弾アニメーションスピード
#define EXPLOSION_TEXTURE_UV_U		(1.0f)								// 弾アニメーションU範囲
#define EXPLOSION_TEXTURE_UV_V		(1.0f)								// 弾アニメーションV範囲

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXCOLOR	col;				// 色
	int			nCounterAnim;		// アニメーションカウンター
	int			nPatternAnim;		// アニメーションパターンNo.
	bool		bUse;				// 使用しているかどうか
}Explosion;

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// 頂点バッファへのポインタ
Explosion				g_aExplosion[MAX_EXPLOSION];	// 爆発の情報

//=============================================================================
// 爆破の初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureExplosion);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		pVtx[1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, EXPLOSION_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

		pVtx += 4;				// 頂点データへのポインタを4つ進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 爆発の更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{// 爆発が使用されている
			g_aExplosion[nCntExplosion].nCounterAnim++;			// カウンター加算

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 4) == 0)		// アニメーションの速さを変えられる
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1);

				// 頂点設定
				pVtx[nCntExplosion * 4].pos		= D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 30, g_aExplosion[nCntExplosion].pos.y - 30, 0.0f);
				pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 30, g_aExplosion[nCntExplosion].pos.y - 30, 0.0f);
				pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 30, 30 + g_aExplosion[nCntExplosion].pos.y, 0.0f);
				pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 30, 30 + g_aExplosion[nCntExplosion].pos.y, 0.0f);

				// 頂点カラー設定
				pVtx[nCntExplosion * 4].col		= D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
				pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
				pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
				pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);

				// テクスチャ設定
				pVtx[nCntExplosion * 4].tex		= D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, EXPLOSION_TEXTURE_UV_V);

				if (g_aExplosion[nCntExplosion].nPatternAnim > 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;			// 使用していない状態にする
				}
			}
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	// ポリゴンの描画
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	VERTEX_2D *pVtx;		// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos				= pos;
			g_aExplosion[nCntExplosion].col				= col;
			g_aExplosion[nCntExplosion].nCounterAnim	= 0;
			g_aExplosion[nCntExplosion].nPatternAnim	= 0;
			g_aExplosion[nCntExplosion].bUse			= true;

			// 頂点設定
			pVtx[nCntExplosion * 4].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// カラー設定
			pVtx[nCntExplosion * 4].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ設定
			pVtx[nCntExplosion * 4].tex		= D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.0f, EXPLOSION_TEXTURE_UV_V);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

			break;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();
}