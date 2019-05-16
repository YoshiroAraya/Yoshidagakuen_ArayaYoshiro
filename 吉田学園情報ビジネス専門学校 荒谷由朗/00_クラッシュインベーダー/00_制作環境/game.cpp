//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author :	荒谷由朗
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "input.h"
#include"score.h"
#include"effect.h"
#include"fade.h"

//グローバル
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲーム状態
GAMESTATE g_gameStateNow = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//ゲーム画面の初期化
void InitGame(void)
{
	//背景の初期化処理
	InitBG();

	//ポリゴンの初期化処理
	InitPlayer();

	//弾の初期化
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//スコアの初期化処理
	InitScore();

	//敵の初期化
	InitEnemy();

	//エフェクトの初期化処理
	InitEffect();

	//一列目
	SetEnemy(D3DXVECTOR3(250.0f, 50.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 50.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(650.0f, 50.0f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(850.0f, 50.0f, 0.0f), 3);

	//二列目
	SetEnemy(D3DXVECTOR3(350.0f, 100.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(550.0f, 100.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(750.0f, 100.0f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(950.0f, 100.0f, 0.0f), 3);

	//三列目
	SetEnemy(D3DXVECTOR3(250.0f, 150.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 150.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(650.0f, 150.0f, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(850.0f, 150.0f, 0.0f), 3);

	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	g_nCounterGameState = 0;
}

void UninitGame(void)
{
	//背景の終了処理
	UninitBG();

	//ポリゴンの終了処理
	UninitPlayer();

	//弾の終了処理
	UninitBullet();

	//爆発の終了処理
	UninitExplosion();

	//スコアの終了処理
	UninitScore();

	//敵の終了処理
	UninitEnemy();

	//スコアの終了処理
	UninitEffect();
}

//ゲーム画面の更新処理
void UpdateGame(void)
{
	//背景の更新処理
	UpdateBG();

	//弾の更新処理
	UpdateBullet();

	//爆発の更新処理
	UpdateExplosion();

	//更新処理
	UpdateEnemy();

	//ポリゴンの更新処理
	UpdatePlayer();

	//スコアの更新処理
	UpdateScore();

	//スコアの更新処理
	UpdateEffect();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
		g_gameStateNow = GAMESTATE_CLEAR;
		g_gameState = GAMESTATE_NONE;
		//画面（モード)の設定
		SetFade(MODE_RESULT);
		break;

	case GAMESTATE_OVER:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gameStateNow = GAMESTATE_OVER;
			g_gameState = GAMESTATE_NONE;

			//画面（モード)の設定
			//SetFade(MODE_RESULT);

		}
		break;
	}
}

void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//ポリゴンの描画処理
	DrawPlayer();

	//弾の描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

	//敵の描画処理
	DrawEnemy();

	//スコアの描画処理
	DrawScore();

	//エフェクトの描画処理
	DrawEffect();
}

//ゲームの状態の設定
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// ゲームの状態の取得
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// ゲームの状態の取得(現状)
//=============================================================================
GAMESTATE GetGameStateNow(void)
{
	return g_gameStateNow;
}