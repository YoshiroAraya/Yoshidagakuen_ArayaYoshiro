//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 荒谷 由朗
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

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_TYPE_ENEMY					(4)								// 敵の種類
#define POYGON_TEXTURENAME000			"data/TEXTURE/enemy000.png"		// 読み込むテクスチャ
#define POYGON_TEXTURENAME001			"data/TEXTURE/enemy001.png"		// 読み込むテクスチャ
#define POYGON_TEXTURENAME002			"data/TEXTURE/enemy002.png"		// 読み込むテクスチャ
#define POYGON_TEXTURENAME003			"data/TEXTURE/enemy003.png"		// 読み込むテクスチャ
#define ENEMY_TEXTURE_UV_U				(1.0f)							// 弾アニメーションU範囲
#define ENEMY_TEXTURE_UV_V				(1.0f)							// 弾アニメーションV範囲

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY]	= {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy						= NULL;		// 頂点バッファへのポインタ
Enemy					g_aEnemy[MAX_ENEMY];							// 敵の情報
int						g_nNumEnemy;									// 敵の総数
int						nHitEnemy;
int						nCountEnemy;

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
		g_aEnemy[nCntEnemy].pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].col				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEnemy[nCntEnemy].nType			= 0;
		g_aEnemy[nCntEnemy].nCounterAnim	= 0;
		g_aEnemy[nCntEnemy].nPatternAnim	= 0;
		g_aEnemy[nCntEnemy].nLife			= 0;
		g_aEnemy[nCntEnemy].nSpped			= 0;
		g_aEnemy[nCntEnemy].bUse			= false;
		g_aEnemy[nCntEnemy].state			= ENEMTSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState	= 0;
	}

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME000, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME001, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME002, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME003, &g_apTextureEnemy[3]);

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
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;				// 頂点データへのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0;		// 敵の総数をクリア
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
	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	// 敵が使用されている時
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMTSTATE_NORMAL:
				break;
			case ENEMTSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMTSTATE_NORMAL;

					// 頂点情報(頂点カラー)の設定
					pVtx[nCntEnemy * 4].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					g_pVtxBuffEnemy->Unlock();
				}
				nHitEnemy++;
				break;
			}
			g_aEnemy[nCntEnemy].nCounterAnim++;			// カウンター加算

			if (g_nNumEnemy == 12)
			{
				if (rand() % 250 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}

			else if (g_nNumEnemy >= 10 && g_nNumEnemy <= 11)
			{
				if (rand() % 190 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}
			else if (g_nNumEnemy >= 8 && g_nNumEnemy <= 9)
			{
				if (rand() % 120 == 0)
				{
					D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
					Player *pPlayer;
					static float fAngle;

					pPlayer = GetPlayer();

					fAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

					BulletMove.x = sinf(fAngle) * 5.0f;
					BulletMove.y = cosf(fAngle) * 5.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, BulletMove, BULLETTYPE_ENEMY, 0);
				}
			}
			else if (g_nNumEnemy >= 6 && g_nNumEnemy <= 7)
			{
				if (rand() % 70 == 0)
				{
					D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
					Player *pPlayer;
					static float fAngle;

					pPlayer = GetPlayer();

					fAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

					BulletMove.x = sinf(fAngle) * 5.0f;
					BulletMove.y = cosf(fAngle) * 5.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, BulletMove, BULLETTYPE_ENEMY, 0);
				}
			}
			else if (g_nNumEnemy >= 4 && g_nNumEnemy <= 5)
			{
				if (rand() % 50 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);

				}
			}
			else if (g_nNumEnemy >= 2 && g_nNumEnemy <= 3)
			{
				if (rand() % 35 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}
			else
			{
				if (rand() % 10 == 0)
				{

					D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
					Player *pPlayer;
					static float fAngle;

					pPlayer = GetPlayer();

					fAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

					BulletMove.x = sinf(fAngle) * 5.0f;
					BulletMove.y = cosf(fAngle) * 5.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, BulletMove, BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}


			// 敵の移動速度
			g_aEnemy[nCntEnemy].nSpped = 5.0f;
			g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].nSpped;
			if (g_aEnemy[nCntEnemy].pos.x < 0 && g_aEnemy[nCntEnemy].pos.y > 0)
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnim % 10) == 0)		// アニメーションの速さを変えられる
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;

				// 頂点更新
				pVtx[nCntEnemy * 4].pos		= D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y - 30, 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y - 30, 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y + 30, 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y + 30, 0.0f);

				// テクスチャ更新
				pVtx[nCntEnemy * 4].tex		= D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim  * 0.5f), 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f), ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, ENEMY_TEXTURE_UV_V);

				// 色の変化
				if (g_aEnemy[nCntEnemy].col.r != 1.0f)
				{
					static int nCntAnim = 0;
					nCntAnim++;

					if ((nCntAnim % 3) == 0)
					{
						g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}
			}
		}
	}
	// 頂点バッファのアンロック
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

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			// 頂点設定
			pVtx[nCntEnemy * 4].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//テクスチャ設定
			pVtx[nCntEnemy * 4].tex		= D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
			pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
			pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

			g_aEnemy[nCntEnemy].nType			= nType;
			g_aEnemy[nCntEnemy].nLife			= 15;
			g_aEnemy[nCntEnemy].nSpped			= 0;
			g_aEnemy[nCntEnemy].bUse			= true;
			g_aEnemy[nCntEnemy].state			= ENEMTSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState	= 0;

			g_nNumEnemy++;				// 敵の総数を加算する
			break;
		}
	}
	// 頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
//敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	GAMESTATE GetGameStateNow();

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aEnemy[nCntEnemy].bUse = false;
		nCountEnemy++;
		g_nNumEnemy--;				// 敵の総数を減らす
		if (g_nNumEnemy <= 0)		// 敵が全滅したら
		{
			SetGameState(GAMESTATE_CLEAR);
		}
		if (g_aEnemy[nCntEnemy].nType = 0)
		{
			AddScore(200);
		}
		else if (g_aEnemy[nCntEnemy].nType = 1)
		{
			AddScore(400);
		}
		else if (g_aEnemy[nCntEnemy].nType = 2)
		{
			AddScore(800);
		}
		else if (g_aEnemy[nCntEnemy].nType = 3)
		{
			AddScore(1000);
		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMTSTATE_DAMAGE;
		PlaySound(SOUND_LABEL_SE_HIT001);
		g_aEnemy[nCntEnemy].nCounterState = 5;
		VERTEX_2D * pVtx;
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4); // 該当の位置まで進める
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		g_pVtxBuffEnemy->Unlock();
	}
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}