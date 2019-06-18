//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POYGON_TEXTURENAME		"data/TEXTURE/player000.png"			// 読み込むテクスチャ
#define POYGON_POS_X			(300)									// 頂点座標（X座標）(位置)
#define POYGON_POS_Y			(200)									// 頂点座標（Y座標）(位置)
#define POYGON_POS_WIDTH		(500)									// 画像の大きさ（X座標)
#define POYGON_POS_HEIGHT		(500)									// 画像の大きさ(Y座標)
#define POYGON_ANIM_PATTERN		(10)									// アニメーションのパターン
#define POYGON_ANIM_WIDTH		(1.0f)									// アニメーションの幅
#define POLYGON_ANIM_HEIGHT		(1.0f)									// アニメーションの高さ
#define POLYGON_SPEED			(3.0f)									// ポリゴンを動かす速度
#define BULLET_SPEED			(-5.0f)									// 弾のスピード

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;	// テクスチャへポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// 頂点バッファへのポインタ
Player					g_player;


//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();
	g_player.bDisp	= true;
	g_player.nLife	= 10;
	g_player.state	= PLAYERSTATE_NORMAL;
	g_player.pos	= D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT - 50, 0.0f);			// ポリゴンの中心点
	g_player.move	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// ポリゴンの移動速度

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTexturePlayer);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(POYGON_POS_WIDTH, POYGON_POS_Y, 0.0f);			// 頂点座標(X座標,Y座標)
	pVtx[1].pos = D3DXVECTOR3(POYGON_POS_WIDTH, POYGON_POS_HEIGHT, 0.0f);		// 頂点座標(X座標,Y座標)
	pVtx[2].pos = D3DXVECTOR3(POYGON_POS_X, POYGON_POS_Y, 0.0f);				// 頂点座標(X座標,Y座標)
	pVtx[3].pos = D3DXVECTOR3(POYGON_POS_X, POYGON_POS_HEIGHT, 0.0f);			// 頂点座標(X座標,Y座標)

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // 色の指定（０～２５５）&透明度（０～２５５）
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // 色の指定（０～２５５）&透明度（０～２５５）
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // 色の指定（０～２５５）&透明度（０～２５５)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // 色の指定（０～２５５）&透明度（０～２５５)

	 // テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, 0.0f);						// Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, POLYGON_ANIM_HEIGHT);		// Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);									// Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(0.0f, POLYGON_ANIM_HEIGHT);					// Uが幅、Vが高さ　(0.0f～1.0f）

	// 頂点バッファのアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCunterState--;
		if (g_player.nCunterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			VERTEX_2D * pVtx;
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_pVtxBuffPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCunterState--;
		if (g_player.nCunterState == 0)
		{
			SetFade(MODE_RESULT);
		}
		return;
		break;
	}
	VERTEX_2D*pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// それぞれの条件で動く向きを変える(加速)
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{	// 左上移動
				g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED + 1.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * POLYGON_SPEED + 1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{	// 左下移動
				g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED + 1.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * POLYGON_SPEED - 1.0f;
			}
			else
			{	// 左移動
				g_player.move.x += sinf(-D3DX_PI * 0.5) * POLYGON_SPEED + 1.0f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{	// 右上移動
				g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED - 1.0f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * POLYGON_SPEED + 1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{	// 右下移動
				g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED - 1.0f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * POLYGON_SPEED - 1.0f;
			}
			else
			{	// 右移動
				g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED - 1.0f;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{	// Sか↓を押すと下に移動
			g_player.move.y += cosf(0) * POLYGON_SPEED - 1.0f;
		}
		else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{	// Wか↑を押すと上に移動
			g_player.move.y += cosf(D3DX_PI) * POLYGON_SPEED + 1.0f;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
	{
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{	// 左上移動
			g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * POLYGON_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{	// 左下移動
			g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * POLYGON_SPEED;
		}
		else
		{	// 左移動
			g_player.move.x += sinf(-D3DX_PI * 0.5) * POLYGON_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{	// 右上移動
			g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * POLYGON_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{	// 右下移動
			g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * POLYGON_SPEED;
		}
		else
		{	// 右移動
			g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
	{	// Sか↓を押すと下に移動
		g_player.move.y += cosf(0) * POLYGON_SPEED;
	}
	else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
	{	// Wか↑を押すと上に移動
		g_player.move.y += cosf(D3DX_PI) * POLYGON_SPEED;
	}

	// 弾の設定
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{	// Xキーで弾を出す(右下斜め)
		SetBullet(g_player.pos, D3DXVECTOR3(0.0f, -5.0f, 0.0f), BULLETTYPE_PLAYER, 0);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * -1.0f, cosf(D3DX_PI * 0.1f) * -5.0f, 0.0f), BULLETTYPE_PLAYER1, 0);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * -1.0f, cosf(D3DX_PI * 0.1f) * -5.0f, 0.0f), BULLETTYPE_PLAYER2, 0);
		PlaySound(SOUND_LABEL_SE_SHOT);
	}
	g_player.nCunterAnim++;

	// 位置更新(移動)
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	// 減速
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.5f;

	// 枠外に出た場合
	if (g_player.pos.x < 40)
	{	// 右から出たら左から戻る
		g_player.pos.x = 40;
	}
	if (g_player.pos.x > SCREEN_WIDTH - 40)
	{	// 左から出たら右から戻る
		g_player.pos.x = SCREEN_WIDTH - 40;
	}
	if (g_player.pos.y < 50)
	{	// 上から出たら下から戻る
		g_player.pos.y = 50;
	}
	if (g_player.pos.y > SCREEN_HEIGHT - 50)
	{	// 下から出たら上から戻る
		g_player.pos.y = SCREEN_HEIGHT - 50;
	}

	// 頂点情報の更新
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x -30, g_player.pos.y- 30, 0.0f);		// 頂点座標(X座標,Y座標)
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 30, g_player.pos.y- 30, 0.0f);		// 頂点座標(X座標,Y座標)
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 30, g_player.pos.y + 30, 0.0f);		// 頂点座標(X座標,Y座標)
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 30, g_player.pos.y + 30, 0.0f);		// 頂点座標(X座標,Y座標)

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);											// Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, 0.0f);								// Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.0f, POLYGON_ANIM_HEIGHT);							// Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, POLYGON_ANIM_HEIGHT);				// Uが幅、Vが高さ　(0.0f～1.0f）

	// 頂点バッファのアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスのポインタ

	// デバイスを取得する
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		// 頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// ダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos,D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f));
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		SetGameState(GAMESTATE_OVER);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_player.nCunterState = 60;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		PlaySound(SOUND_LABEL_SE_HIT000);
		g_player.nCunterState = 5;

		VERTEX_2D * pVtx;
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_pVtxBuffPlayer->Unlock();
	}
}