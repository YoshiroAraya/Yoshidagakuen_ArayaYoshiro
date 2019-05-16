//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY					(2)									// 敵の種類
#define POYGON_TEXTURENAME000			"data/TEXTURE/enemy002.png"			//読み込むテクスチャ
#define ENEMY_TEXTURE_UV_U				(1.0f)								//弾アニメーションU範囲
#define ENEMY_TEXTURE_UV_V				(1.0f)								//弾アニメーションV範囲

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy;												//敵の総数
int nHitEnemy;
int nCountEnemy;

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].type = EnemyType_NORMAL1;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME000, &g_apTextureEnemy[0]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;				//頂点データへのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0;		//敵の総数をクリア
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//敵が使用されている時
			g_aEnemy[nCntEnemy].nCounterAnim++;			//カウンター加算

			if (rand() % 100 == 0)
			{
				SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(g_aEnemy[nCntEnemy].move_bullet, 0.0f, 0.0f), BULLETTYPE_ENEMY, 0);
			}

			//敵の移動速度
			if (g_aEnemy[nCntEnemy].pos.x < 0 && g_aEnemy[nCntEnemy].pos.y > 0)
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnim % 10) == 0)		//アニメーションの速さを変えられる
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;

				// 頂点更新
				pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);

				//テクスチャ更新
				pVtx[nCntEnemy * 4].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim  * 0.5f), 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f), ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, ENEMY_TEXTURE_UV_V);

			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureEnemy[0]);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, EnemyType type, float move_bullet)
{
	int nCntEnemy;

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].fWidth = fWidth;
			g_aEnemy[nCntEnemy].type = type;
			g_aEnemy[nCntEnemy].move_bullet = move_bullet;

			//頂点設定
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);

			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();
}
//=============================================================================
// ブロックの当たり判定
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int nCntEnemy;
	bool bLand = false;		//着地したかどうか

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	Player *pPlayer;
	pPlayer = GetPlayer();		//プレイヤーの取得

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//当たり判定
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			if (g_aEnemy[nCntEnemy].pos.x - 14.9 <= pPos->x
				&& g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 14.9 >= pPos->x)
			{//プレイヤーが上下の範囲内にいるかどうか
				if (g_aEnemy[nCntEnemy].pos.y <= pPos->y
					&& g_aEnemy[nCntEnemy].pos.y >= pPosOld->y)
				{//上
					bLand = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y;
					pMove->y = 0.0f;
					pPlayer->nCounterJump = 0;
				}
				else if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight > pPos->y - 50
					&& g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight < pPosOld->y - 50)
				{//下
					bLand = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight + 50;
					pMove->y = 0.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].pos.y < pPos->y
				&& g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight + 50 > pPos->y)
			{//プレイヤーが左右の範囲内にいるかどうか
				if (g_aEnemy[nCntEnemy].pos.x - 15 >= pPosOld->x
					&& g_aEnemy[nCntEnemy].pos.x - 15 <= pPos->x)
				{//左
					pPos->x = g_aEnemy[nCntEnemy].pos.x - 15;
					pMove->x = 0.0f;
				}
				if (g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 15 <= pPosOld->x
					&& g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 15 >= pPos->x)
				{//右
					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 15;
					pMove->x = 0.0f;
				}
			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();


	return bLand;	//値を返す
}
////=============================================================================
//// 敵の取得
////=============================================================================
//Enemy *GetEnemy(void)
//{
//	return &g_aEnemy[0];
//}
