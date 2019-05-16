//=============================================================================
//
// ブロック処理 [block.cpp]
// Author :	荒谷由朗
//
//=============================================================================
#include "block.h"
#include "player.h"
#include "main.h"
#include "item.h"
#include "bullet.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_BLOCK				(256)								//ブロックの最大数
#define BLOCK_TEXTURENAME000	"data/TEXTURE/texture140921002.jpg"	//読み込むテクスチャ
#define BLOCK_TEXTURE_UV_U		(1.0f)								//ブロックのアニメーションU範囲
#define BLOCK_TEXTURE_UV_V		(1.0f)								//ブロックのアニメーションV範囲

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_paTextureBlock = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// 頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];							//ブロックの情報

//=============================================================================
// ブロックの初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0;
		g_aBlock[nCntBlock].fHeight = 0;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].type = BlockType_NORMAL;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME000, &g_paTextureBlock);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BLOCK_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, BLOCK_TEXTURE_UV_V);

		pVtx += 4;				//頂点データへのポインタを4つ進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void UninitBlock(void)
{
	// テクスチャの開放
	if (g_paTextureBlock != NULL)
	{
		g_paTextureBlock->Release();
		g_paTextureBlock = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void UpdateBlock(void)
{
	int nCntBlock;
	
	int nItemKey;
	nItemKey = GetItemNumber();

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (nItemKey == 0 && g_aBlock[nCntBlock].type == BlockType_DELETE)
			{
				g_aBlock[nCntBlock].bUse = false;
			}
		}
	}
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_paTextureBlock);

	// ポリゴンの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// テクスチャの設定
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth,float fHeight, BlockType type)
{
	int nCntBlock;

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		
		if (g_aBlock[nCntBlock].bUse == false)
		{

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].type = type;

			//頂点設定
			pVtx[nCntBlock * 4].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[nCntBlock * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			g_aBlock[nCntBlock].bUse = true;
			break;
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの当たり判定
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int nCntBlock;
	bool bLand = false;		//着地したかどうか

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	Player *pPlayer;
	pPlayer = GetPlayer();		//プレイヤーの取得

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//当たり判定
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			
			if (g_aBlock[nCntBlock].pos.x - 14.9 <= pPos->x
				&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 14.9 >= pPos->x)
			{//プレイヤーが上下の範囲内にいるかどうか
				if (g_aBlock[nCntBlock].pos.y <= pPos->y
					&& g_aBlock[nCntBlock].pos.y >= pPosOld->y)
				{//上
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;	
					pPlayer->nCounterJump = 0;
				}
				else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight > pPos->y - 50
					&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight < pPosOld->y - 50)
				{//下
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + 50;
					pMove->y = 0.0f;
				}
			}
			if (g_aBlock[nCntBlock].pos.y < pPos->y
				&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + 50 > pPos->y)
			{//プレイヤーが左右の範囲内にいるかどうか
				if (g_aBlock[nCntBlock].pos.x - 15 >= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x -15 <= pPos->x)
				{//左
					pPos->x = g_aBlock[nCntBlock].pos.x - 15;
					//pMove->x = 0.0f;
				}
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 15 <= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 15 >= pPos->x)
				{//右
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 15;
					//pMove->x = 0.0f;
				}
			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();


	return bLand;	//値を返す
}
//=============================================================================
// 弾の当たり判定
//=============================================================================
bool CollisionBlock_Bullet(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int nCntBlock;
	bool bLand = false;		//着地したかどうか

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	Bullet *pBullet;
	pBullet = GetBullet();		//弾の取得

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//当たり判定
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].pos.x <= pPos->x
				&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x)
			{//プレイヤーが上下の範囲内にいるかどうか
				if (g_aBlock[nCntBlock].pos.y <= pPos->y
					&& g_aBlock[nCntBlock].pos.y >= pPosOld->y)
				{//上
					bLand = true;
				}
				else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight > pPos->y
					&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight < pPosOld->y)
				{//下
					bLand = true;
				}
			}
			if (g_aBlock[nCntBlock].pos.y < pPos->y
				&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight > pPos->y)
			{//プレイヤーが左右の範囲内にいるかどうか
				if (g_aBlock[nCntBlock].pos.x >= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x <= pPos->x)
				{//左
					bLand = true;
				}
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x)
				{//右
					bLand = true;
				}
			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffBlock->Unlock();


	return bLand;	//値を返す
}
