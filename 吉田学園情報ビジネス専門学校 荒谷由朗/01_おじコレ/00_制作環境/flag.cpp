//=============================================================================
//
// フラッグ処理 [flag.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "flag.h"
#include "player.h"
#include "main.h"
#include "fade.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_FLAG				(256)							// フラッグの最大数
#define FLAG_TEXTURENAME000		"data/TEXTURE/hata_GALL.png"	// 読み込むテクスチャ
#define FLAG_TEXTURE_UV_U		(1.0f)							// フラッグのアニメーションU範囲
#define FLAG_TEXTURE_UV_V		(1.0f)							// フラッグのアニメーションV範囲

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_paTextureFlag = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlag	= NULL;		// 頂点バッファへのポインタ
Flag					g_aFlag[MAX_FLAG];			// フラッグの情報

//=============================================================================
// フラッグの初期化処理
//=============================================================================
void InitFlag(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFlag;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		g_aFlag[nCntFlag].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFlag[nCntFlag].fWidth	= 0;
		g_aFlag[nCntFlag].fHeight	= 0;
		g_aFlag[nCntFlag].bUse		= false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FLAG_TEXTURENAME000, &g_paTextureFlag);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLAG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFlag,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlag->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(FLAG_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, FLAG_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(FLAG_TEXTURE_UV_U, FLAG_TEXTURE_UV_V);

		pVtx += 4;				// 頂点データへのポインタを4つ進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffFlag->Unlock();
}

//=============================================================================
// フラッグの終了処理
//=============================================================================
void UninitFlag(void)
{
	// テクスチャの開放
	if (g_paTextureFlag != NULL)
	{
		g_paTextureFlag->Release();
		g_paTextureFlag = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffFlag != NULL)
	{
		g_pVtxBuffFlag->Release();
		g_pVtxBuffFlag = NULL;
	}
}

//=============================================================================
// フラッグの更新処理
//=============================================================================
void UpdateFlag(void)
{
}

//=============================================================================
// フラッグの描画処理
//=============================================================================
void DrawFlag(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFlag;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFlag, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_paTextureFlag);

	// ポリゴンの描画
	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		if (g_aFlag[nCntFlag].bUse == true)
		{
			// テクスチャの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFlag * 4, 2);
		}
	}
}

//=============================================================================
// フラッグの設定処理
//=============================================================================
void SetFlag(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntFlag;

	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlag->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		if (g_aFlag[nCntFlag].bUse == false)
		{
			g_aFlag[nCntFlag].pos		= pos;
			g_aFlag[nCntFlag].fWidth	= fWidth;
			g_aFlag[nCntFlag].fHeight	= fHeight;
			g_aFlag[nCntFlag].bUse		= true;

			// 頂点設定
			pVtx[nCntFlag * 4].pos		= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x, g_aFlag[nCntFlag].pos.y, 0.0f);
			pVtx[nCntFlag * 4 + 1].pos	= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth, g_aFlag[nCntFlag].pos.y, 0.0f);
			pVtx[nCntFlag * 4 + 2].pos	= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x, g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight, 0.0f);
			pVtx[nCntFlag * 4 + 3].pos	= D3DXVECTOR3(g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth, g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight, 0.0f);
			break;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffFlag->Unlock();
}

//=============================================================================
// フラッグの当たり判定
//=============================================================================
bool CollisionFlag(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int		nCntFlag;
	bool	bLand = false;		// 着地したかどうか

	VERTEX_2D	*pVtx;							// 頂点情報へのポインタ
	FADE		fade		= GetFade();		// フェードの取得
	Player		*pPlayer	= GetPlayer();		// プレイヤーの取得

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlag->Lock(0, 0, (void**)&pVtx, 0);

	// 当たり判定
	for (nCntFlag = 0; nCntFlag < MAX_FLAG; nCntFlag++)
	{
		if (g_aFlag[nCntFlag].bUse == true)
		{// 使用しているかどうか
			if (g_aFlag[nCntFlag].pos.x - 14.9 <= pPos->x
				&& g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth + 14.9 >= pPos->x)
			{// プレイヤーが上下の範囲内にいるかどうか
				if (g_aFlag[nCntFlag].pos.y <= pPos->y
					&& g_aFlag[nCntFlag].pos.y >= pPosOld->y)
				{// 上
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// モード設定
						SetFade(MODE_RESULT);
					}
				}
				else if (g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight > pPos->y - 50
					&& g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight < pPosOld->y - 50)
				{// 下
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// モード設定
						SetFade(MODE_RESULT);
					}
				}
			}
			if (g_aFlag[nCntFlag].pos.y < pPos->y
				&& g_aFlag[nCntFlag].pos.y + g_aFlag[nCntFlag].fHeight + 50 > pPos->y)
			{// プレイヤーが左右の範囲内にいるかどうか
				if (g_aFlag[nCntFlag].pos.x - 15 >= pPosOld->x
					&& g_aFlag[nCntFlag].pos.x - 15 <= pPos->x)
				{// 左
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// モード設定
						SetFade(MODE_RESULT);
					}
				}
				if (g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth + 15 <= pPosOld->x
					&& g_aFlag[nCntFlag].pos.x + g_aFlag[nCntFlag].fWidth + 15 >= pPos->x)
				{// 右
					if (fade != FADE_OUT)
					{
						SetGameState(GAMESTATE_CLEAR);
						// モード設定
						SetFade(MODE_RESULT);
					}
				}
			}
		}
	}
	// 頂点バッファのアンロック
	g_pVtxBuffFlag->Unlock();
	return bLand;	//値を返す
}