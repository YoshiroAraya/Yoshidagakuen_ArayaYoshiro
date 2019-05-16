//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author :	荒谷由朗
//
//=============================================================================
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "block.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET				(256)								// 弾の最大数
#define MAX_TYPE_BULLET			(1)									//弾の種類の最大数
#define BULLET_TEXTURENAME000	"data/TEXTURE/bullet000.png"	//読み込むテクスチャ
#define BULLET_POS_X			(1000)								//弾の左上X座標
#define BULLET_POS_Y			(1200)								//弾の左上Y座標
#define BULLET_WIDTH			(1090)								//弾の幅
#define BULLET_HEIGHT			(1200)								//弾の高さ
#define BULLET_TEXTURE_SPEED	(5)									//弾アニメーションスピード
#define BULLET_TEXTURE_UV_U		(1.0f)								//弾アニメーションU範囲
#define BULLET_TEXTURE_UV_V		(1.0f)								//弾アニメーションV範囲

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_paTextureBullet[MAX_TYPE_BULLET] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報

//=============================================================================
// 弾の初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
		g_aBullet[nCntBullet].nType = 0;
		g_aBullet[nCntBullet].nLife = 1;
		g_aBullet[nCntBullet].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME000, &g_paTextureBullet[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
		pVtx[1].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BULLET_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, BULLET_TEXTURE_UV_V);

		pVtx += 4;				//頂点データへのポインタを4つ進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の終了処理
//=============================================================================
void UninitBullet(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_TYPE_BULLET; nCntTex++)
	{
		// テクスチャの開放
		if (g_paTextureBullet[nCntTex] != NULL)
		{
			g_paTextureBullet[nCntTex]->Release();
			g_paTextureBullet[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//弾が使用されている
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;
			//弾の位置を移動
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//頂点設定
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
			}
			//敵の取得（先頭）
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)	//敵の弾
			{
				Player *pPlayer;
				//プレイヤーの取得
				pPlayer = GetPlayer();
				if (pPlayer->pos.x + 30 > g_aBullet[nCntBullet].pos.x
					&& g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - 30
					&& pPlayer->pos.y + 30 > g_aBullet[nCntBullet].pos.y
					&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 30
					&& pPlayer->bDisp == true)
				{	//当り判定
					HitPlayer(1);
					HitLife(1);
					g_aBullet[nCntBullet].bUse = false;		//使用されてない状態にする
				}
			}
			if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT || g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;			//使用されてない状態にする
			}
			if(CollisionBlock_Bullet(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].posOld, &g_aBullet[nCntBullet].move) == true)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		//頂点バッファのアンロック
		g_pVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// 弾の描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_paTextureBullet[g_aBullet[nCntBullet].type]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type, int nType)
{
	int nCntBullet;
	
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{

			g_aBullet[nCntBullet].pos = pos;

			//頂点設定
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].bUse = true;					
			break;
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

void HitBullet(int nDamage)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].nLife -= nDamage;
		if (g_aBullet[nCntBullet].nLife <= 0)
		{
			//g_aBullet[nCntBullet].bUse = false;
		}
	}
}
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}
