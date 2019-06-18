//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_EXPLOSION				(128)								// 弾の最大数
#define POYGON_TEXTURENAME			"data/TEXTURE/explosion000.png"		// 読み込むテクスチャ
#define EXPLOSION_TEXTURE_UV_U		(1.0f)								// 弾アニメーションU範囲
#define EXPLOSION_TEXTURE_UV_V		(1.0f)								// 弾アニメーションV範囲

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXCOLOR	col;			// 色
	D3DXMATRIX  mtxWorld;		// ワールドマトリックス
	D3DXMATRIX	mtxView;		// ビューマトリックス
	int			nCounterAnim;	// アニメーションカウンター
	int			nPatternAnim;	// アニメーションパターンNo.
	bool		bUse;			// 使用しているかどうか
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	int nCntExplosion;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureExplosion);

	// 爆発の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim	= 0;
		g_aExplosion[nCntExplosion].nPatternAnim	= 0;
		g_aExplosion[nCntExplosion].bUse			= false;
	}

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 25.0f, 0.0f);		// 頂点座標(X座標,Y座標)
		pVtx[1].pos = D3DXVECTOR3(15.0f, 25.0f, 0.0f);		// 頂点座標(X座標,Y座標)
		pVtx[2].pos = D3DXVECTOR3(-15.0f, 0.0f, 0.0f);		// 頂点座標(X座標,Y座標)
		pVtx[3].pos = D3DXVECTOR3(15.0f, 0.0f, 0.0f);		// 頂点座標(X座標,Y座標)

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			// Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);		// Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			// Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);		// Uが幅、Vが高さ　(0.0f～1.0f）

		pVtx += 4;										// 座標を4ずつ進める
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
	VERTEX_3D *pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	// 爆発が使用されている
			g_aExplosion[nCntExplosion].nCounterAnim++;			// カウンター加算

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 4) == 0)		// アニメーションの速さを変えられる
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1);

				// テクスチャ設定
				pVtx[nCntExplosion * 4].tex		= D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, EXPLOSION_TEXTURE_UV_V);

				if (g_aExplosion[nCntExplosion].nPatternAnim > 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;			// 使用していない状態
				}
			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		// ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &g_aExplosion[nCntExplosion].mtxView);

		// カメラの逆行列を設定
		g_aExplosion[nCntExplosion].mtxWorld._11 = g_aExplosion[nCntExplosion].mtxView._11;
		g_aExplosion[nCntExplosion].mtxWorld._12 = g_aExplosion[nCntExplosion].mtxView._21;
		g_aExplosion[nCntExplosion].mtxWorld._13 = g_aExplosion[nCntExplosion].mtxView._31;
		g_aExplosion[nCntExplosion].mtxWorld._21 = g_aExplosion[nCntExplosion].mtxView._12;
		g_aExplosion[nCntExplosion].mtxWorld._22 = g_aExplosion[nCntExplosion].mtxView._22;
		g_aExplosion[nCntExplosion].mtxWorld._23 = g_aExplosion[nCntExplosion].mtxView._32;
		g_aExplosion[nCntExplosion].mtxWorld._31 = g_aExplosion[nCntExplosion].mtxView._13;
		g_aExplosion[nCntExplosion].mtxWorld._32 = g_aExplosion[nCntExplosion].mtxView._23;
		g_aExplosion[nCntExplosion].mtxWorld._33 = g_aExplosion[nCntExplosion].mtxView._33;

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureExplosion);

		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos				= pos;
			g_aExplosion[nCntExplosion].col				= col;
			g_aExplosion[nCntExplosion].nCounterAnim	= 0;
			g_aExplosion[nCntExplosion].nPatternAnim	= 0;
			g_aExplosion[nCntExplosion].bUse			= true;
			break;
		}
	}
}