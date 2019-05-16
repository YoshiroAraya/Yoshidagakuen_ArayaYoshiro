//=============================================================================
//
// アイテム処理 [item.cpp]
// Author :	荒谷由朗
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "fade.h"
#include "game.h"
#include "block.h"
#include "flag.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_ITEM				(128)							//アイテムの最大数
#define POYGON_TEXTURENAME		"data/TEXTURE/ozisan.png"		//読み込むテクスチャ
#define ITEM_TEXTURE_SPEED		(6)								//アイテムアニメーションスピード
#define ITEM_TEXTURE_UV_U		(0.125f)						//アイテムアニメーションU範囲
#define ITEM_TEXTURE_UV_V		(1.0f)							//アイテムアニメーションV範囲
#define MAX_PATTERN				(8)								//パターンの数
#define COLLISION_AREA			(11.0f)							//当たり判定の調整

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ
Item g_aItem[MAX_ITEM];							// アイテムの情報
int g_nNumItem;									// アイテムの総数

//=============================================================================
// アイテムの初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;
	g_nNumItem = 0;	//総数をクリア

	// デバイスの取得
	pDevice = GetDevice();

	//アイテムの情報の初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nDirectionMove = 0;
		g_aItem[nCntItem].fHeight = 0.0f;
		g_aItem[nCntItem].fWidth = 0.0f;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureItem);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);

		pVtx += 4;				//頂点データへのポインタを4つ進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの終了処理
//=============================================================================
void UninitItem(void)
{
	// テクスチャの開放
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{//アイテムが使用されている
			g_aItem[nCntItem].nCounterAnim++;			//カウンター加算

			if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0)		//アニメーションの速さを変えられる
			{
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1) % MAX_PATTERN;	//パターンNo.更新
				//前回位置を保存
				g_aItem[nCntItem].posOld = g_aItem[nCntItem].pos;
				//位置情報を更新
				g_aItem[nCntItem].pos += g_aItem[nCntItem].move;

				if (g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth <= g_aItem[nCntItem].posStart.x - g_aItem[nCntItem].fHorLimit		//左
					|| g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth >= g_aItem[nCntItem].posStart.x + g_aItem[nCntItem].fHorLimit)	//右
				{//移動制限(左右)
					g_aItem[nCntItem].move.x *= -1;
				}

				if (g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth <= g_aItem[nCntItem].posStart.x - g_aItem[nCntItem].fHorLimit)
				{//左端までいったとき
					g_aItem[nCntItem].nDirectionMove = 0;
				}
				if (g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth >= g_aItem[nCntItem].posStart.x + g_aItem[nCntItem].fHorLimit)
				{//右端までいったとき
					g_aItem[nCntItem].nDirectionMove = 1;
				}

				// 頂点設定
				pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
				pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
				pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);
				pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);

				//テクスチャ更新
				pVtx[nCntItem * 4].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f), 0.5f * g_aItem[nCntItem].nDirectionMove);
				pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f) + 0.125f, 0.5f * g_aItem[nCntItem].nDirectionMove);
				pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f), 0.5f * g_aItem[nCntItem].nDirectionMove + 0.5f);
				pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f) + 0.125f, 0.5f * g_aItem[nCntItem].nDirectionMove + 0.5f);

			}
		}
	}
	//ステージ
	if (g_nNumItem <= 0)
	{
		//フラッグ
		SetFlag(D3DXVECTOR3(1150.0f, SCREEN_HEIGHT - 70.0f, 0.0f), 30.0f, 40.0f);
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureItem);

	// ポリゴンの描画
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//=============================================================================
// アイテムの設定処理
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fHorLimit, float fWidth, float fHeight)
{
	int nCntItem;

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].posStart = pos;
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].fWidth = fWidth;
			g_aItem[nCntItem].fHeight = fHeight;
			g_aItem[nCntItem].fHorLimit = fHorLimit;

			//頂点設定
			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);

			g_aItem[nCntItem].bUse = true;
			g_nNumItem++;			//総数を加算
			break;
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// アイテムの設定処理
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth)
{
	int nCntItem;
	bool bLand = false;		//着地したかどうか

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	FADE fade;
	fade = GetFade();

	Player *pPlayer;
	pPlayer = GetPlayer();		//プレイヤーの取得

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//当たり判定
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (g_aItem[nCntItem].pos.x - fWidth / 2 <= pPos->x
				&& g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth + fWidth / 2 >= pPos->x
				&& g_aItem[nCntItem].pos.y < pPos->y
				&& g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight + fHeight > pPos->y)
			{
				AddScore(1000);
				PlaySound(SOUND_LABEL_SE_OZISANGET);
				g_nNumItem--;
				g_aItem[nCntItem].bUse = false;
			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();

	return bLand;
}
//=============================================================================
// アイテムの取得
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}
//=============================================================================
// アイテムの取得(個数)
//=============================================================================
int GetItemNumber(void)
{
	return g_nNumItem;
}