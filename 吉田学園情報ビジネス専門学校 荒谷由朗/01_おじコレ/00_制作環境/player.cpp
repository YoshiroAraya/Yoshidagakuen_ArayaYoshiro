//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "coin.h"
#include "item.h"
#include "flag.h"
#include "game.h"
#include "sound.h"
#include "explosion.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER			(1)								// プレイヤーの数
#define PLAYER_TEXTURENAME  "data/TEXTURE/player000.png"	// テクスチャのファイル名
#define TEX_LEFT			(0.0f)							// テクスチャ座標U左
#define TEX_RIGHT			(0.25f)							// テクスチャ座標U右
#define TEX_TOP				(0.0f)							// テクスチャ座標V上
#define TEX_BOT				(0.5f)							// テクスチャ座標V下
#define POLYGON_SPEED		(0.65f)							// ポリゴンを動かす速度
#define COUNTER_RESET		(5)								// カウンターリセット
#define RISING_SPEED		(8.0f)							// 上昇速度
#define GRAVITY_POWER		(0.5f)							// 重力

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureRunPlayer = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRunPlayer = NULL;			// 頂点バッファへのポインタ
Player					g_player;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	VERTEX_2D			*pVtx;					// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// デバイスを取得

	g_player.nCounterAnim	= 0;
	g_player.nPatternAnim	= 0;
	g_player.nCounterJump	= 0;
	g_player.nDirectionMove = 0;
	g_player.state			= PLAYERSTATE_NORMAL;
	g_player.nLife			= 5;
	g_player.fWidth			= 30;
	g_player.fHeight		= 50;
	g_player.bDisp			= true;
	g_player.bUse			= true;
	g_player.bJump			= false;
	g_player.pos			= D3DXVECTOR3(20.0f, 695.0f, 0.0f);
	g_player.move			= D3DXVECTOR3(0, 0, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURENAME,
		&g_pTextureRunPlayer);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRunPlayer,
		NULL);

	// 頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y + g_player.fHeight, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y + g_player.fHeight, g_player.pos.z);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 頂点バッファをアンロックする
	g_pVtxBuffRunPlayer->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// テクスチャの破棄
	if (g_pTextureRunPlayer != NULL)
	{
		g_pTextureRunPlayer->Release();
		g_pTextureRunPlayer = NULL;
	}
	// 頂点バッファの破棄の破棄
	if (g_pVtxBuffRunPlayer != NULL)
	{
		g_pVtxBuffRunPlayer->Release();
		g_pVtxBuffRunPlayer = NULL;
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
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			VERTEX_2D *pVtx;
			g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);
			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_pVtxBuffRunPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState == 0)
		{
			SetFade(MODE_RESULT);
		}
		return;
		break;
	}

	g_player.posOld =	g_player.pos;		// 座標の更新
	g_player.pos	+=	g_player.move;		// 位置の更新
	g_player.nCounterAnim++;				// カウンター加算

	VERTEX_2D *pVtx;						// 頂点情報へのポインタ

	// 頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);


	// それぞれの条件で動く向きを変える(加速)
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{	// ジャンプ
		if (g_player.bJump == false)
		{
			g_player.move.y = cosf(D3DX_PI) * RISING_SPEED;
			g_player.bJump	= false;
			g_player.nCounterJump++;
			PlaySound(SOUND_LABEL_SE_PLEYERJUMP);		// サウンドの再生
		}
	}
	if (GetKeyboardPress(DIK_A) == true)
	{	// 左移動
		g_player.move.x -= POLYGON_SPEED;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{	// 右移動
		g_player.move.x += POLYGON_SPEED;
	}

	// 重力
	g_player.move.y += cosf(0) * GRAVITY_POWER;

	// 位置更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;


	// テクスチャの更新
	if (GetKeyboardPress(DIK_A) == true && g_player.bJump == false)
	{// 左移動
		if ((g_player.nCounterAnim % 10) == 0)		// アニメーションの速さを変えられる
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
		g_player.nDirectionMove = 1;
	}
	else if (GetKeyboardPress(DIK_D) == true && g_player.bJump == false)
	{// 右移動
		if ((g_player.nCounterAnim % 10) == 0)		// アニメーションの速さを変えられる
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
		g_player.nDirectionMove = 0;
	}
	else if (g_player.bJump == true && g_player.nPatternAnim % 2 == 0)
	{// ジャンプ
		if ((g_player.nCounterAnim % 10) == 0)		// アニメーションの速さを変えられる
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
	}
	else if (g_player.bJump == false && g_player.nPatternAnim % 2 == 1)
	{// 地上
		if ((g_player.nCounterAnim % 10) == 0)		// アニメーションの速さを変えられる
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
	}

	// 減速
	g_player.move.x += (0.0f - g_player.move.x) * 0.25f;

	// ブロックの当たり判定
	if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move) == true)
	{
		g_player.bJump = false;
	}
	else
	{
		if (g_player.bJump == false && g_player.nCounterJump >= 2)
		{
			g_player.bJump = true;
		}
	}

	// フラッグの当たり判定
	CollisionFlag(&g_player.pos, &g_player.posOld, &g_player.move);
	// コインの当たり判定
	CollisionCoin(&g_player.pos, &g_player.posOld, &g_player.move);
	// アイテムの当たり判定
	CollisionItem(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fHeight, g_player.fWidth);

	// 頂点座標更新
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, g_player.pos.z);

	// テクスチャ更新
	pVtx[0].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f), 0.5f * g_player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f) + 0.25f, 0.5f * g_player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f), 0.5f * g_player.nDirectionMove + 0.5f);
	pVtx[3].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f) + 0.25f, 0.5f * g_player.nDirectionMove + 0.5f);

	// 枠外に出た場合
	if (g_player.pos.y <= 0 + g_player.fWidth)
	{// 上
		g_player.pos.y = 0 + g_player.fWidth;
		g_player.move.y += cosf(0) * GRAVITY_POWER;
	}
	if (g_player.pos.x - g_player.fWidth / 2 < 0)
	{// 左から出たら左に戻る
		g_player.pos.x = g_player.fWidth / 2;
		g_player.move.x = 0;
	}
	if (g_player.pos.x + g_player.fWidth / 2 > SCREEN_WIDTH)
	{// 右から出たら右に戻る
		g_player.pos.x = SCREEN_WIDTH - g_player.fWidth / 2;
		g_player.move.x = 0;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffRunPlayer->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスを取得する

	if (g_player.bDisp == true)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffRunPlayer, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットを設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRunPlayer);

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
	g_player.nLife -= nDamage;		// ライフの減算
	if (g_player.nLife <= 0)
	{// ライフが0以下になった時
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_player.bDisp	= false;
		g_player.bUse	= false;
		g_player.state	= PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_PLEYERBAD);		// サウンドの再生
		g_player.nCounterState = 60;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		PlaySound(SOUND_LABEL_SE_PLEYERDAMEZ);		// サウンドの再生
		g_player.nCounterState = 5;

		VERTEX_2D *pVtx;

		//頂点バッファをロックし頂点データのポインタを取得
		g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_pVtxBuffRunPlayer->Unlock();
	}
}