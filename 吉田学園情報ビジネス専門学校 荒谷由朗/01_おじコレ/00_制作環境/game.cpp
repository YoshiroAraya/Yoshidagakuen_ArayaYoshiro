//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author :	荒谷由朗
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "block.h"
#include "coin.h"
#include "time.h"
#include "item.h"
#include "flag.h"
#include "pause.h"
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "sound.h"
#include "life.h"

//=============================================================================
//グローバル
//=============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲーム状態
GAMESTATE g_gameStateNow = GAMESTATE_NONE;
int g_nCounterGameState = 0;
#define MAX_STAGE  (26)						//
bool g_bPause;								//ポーズ中かどうか

//=============================================================================
// 敵情報のデンタ
//=============================================================================
EnemyInfo g_aEnemyInfo[] =
{
	{ D3DXVECTOR3(25.0f, 420.0f, 0.0f), 30.0f, 30.0f,EnemyType_NORMAL1 ,2.0f},
	{ D3DXVECTOR3(1250.0f, 420.0f, 0.0f), 30.0f, 30.0f,EnemyType_NORMAL1,-2.0f },
	{ D3DXVECTOR3(1250.0f, 240.0f, 0.0f), 30.0f, 30.0f,EnemyType_NORMAL1,-2.0f }
};
//=============================================================================
// ブロック情報のデンタ
//=============================================================================
BlockInfo g_aBlockInfo[] =
{
	{ D3DXVECTOR3(315.0f, 600.0f, 0.0f), 120.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(835.0f, 600.0f, 0.0f), 140.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(0.0f, 550.0f, 0.0f), 180.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(1100.0f, 550.0f, 0.0f), 180.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(0.0f, 450.0f, 0.0f), 50.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(1220.0f, 450.0f, 0.0f), 70.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(170.0f, 380.0f, 0.0f), 100.0f, 30.0f,BlockType_NORMAL },
	
	{ D3DXVECTOR3(1020.0f, 380.0f, 0.0f), 100.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(1040.0f, 270.0f, 0.0f), 260.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(0.0f, 170.0f, 0.0f), 700.0f, 30.0f,BlockType_NORMAL },
	{ D3DXVECTOR3(380.0f, 300.0f, 0.0f), 300.0f, 400.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(780.0f, 400.0f, 0.0f), 120.0f, 30.0f,BlockType_NORMAL },

	{ D3DXVECTOR3(1100.0f,580.0f, 0.0f), 30.0f, 120.0f,BlockType_DELETE }
};
//=============================================================================
// コイン情報のデンタ
//=============================================================================
CoinInfo g_aCoinInfo[] =
{
	{D3DXVECTOR3(10.0f, 500.0f, 0.0f), 30.0f, 40.0f},
	{D3DXVECTOR3(60.0f, 500.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(110.0f, 500.0f, 0.0f), 30.0f, 40.0f },

	{D3DXVECTOR3(200.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(300.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(400.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(500.0f, 40.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(600.0f, 40.0f, 0.0f), 30.0f, 40.0f },

	{D3DXVECTOR3(150.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(250.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(350.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(450.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(550.0f, 120.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(650.0f, 120.0f, 0.0f), 30.0f, 40.0f },

	{D3DXVECTOR3(425.0f, 250.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(475.0f, 250.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(525.0f, 250.0f, 0.0f), 30.0f, 40.0f },
	{D3DXVECTOR3(575.0f, 250.0f, 0.0f), 30.0f, 40.0f },
};
//=============================================================================
// アイテム情報のデンタ
//=============================================================================
ItemInfo g_aItemInfo[] =
{
	//SetItem(D3DXVECTOR3 pos(位置), D3DXVECTOR3 move(移動速度), float fHorLimit(高さ), float fWidth(幅), float fHeight(移動範囲));
	{D3DXVECTOR3(820.0f, SCREEN_HEIGHT - 55.0f, 0.0f),D3DXVECTOR3(5.0f,0.0f,0.0f),30.0f,30.0f,130.0f },
	{D3DXVECTOR3(80.0f, 140.0f, 0.0f),D3DXVECTOR3(5.0f,0.0f,0.0f), 30.0f, 30.0f, 90.0f },
	{D3DXVECTOR3(845.0f, 370.0f, 0.0f),D3DXVECTOR3(5.0f,0.0f,0.0f), 30.0f, 30.0f, 75.0f },
};

//=============================================================================
//ゲーム画面の初期化
//=============================================================================
void InitGame(void)
{
	int nCountStage;
	g_bPause = false;

	// ゲーム背景
	InitBG();
	//スコアの初期化処理
	InitScore();
	//プレイヤー
	InitPlayer();
	//敵の初期化
	InitEnemy();
	//弾の初期化
	InitBullet();
	//爆発の初期化処理
	InitExplosion();
	//ブロック
	InitBlock();
	//フラッグ
	InitFlag();
	//コイン
	InitCoin();
	//タイム
	InitTime();
	InitLife();
	//アイテム
	InitItem();
	InitPause();						//ポーズの初期化

	//地面
	for (nCountStage = 0; nCountStage < MAX_STAGE; nCountStage++)
	{
		SetBlock(D3DXVECTOR3(50.0f * nCountStage, SCREEN_HEIGHT - 25.0f, 0.0f), 50.0f, 25.0f, BlockType_NORMAL);
	}
	//敵
	for (int nCntEnemy = 0; nCntEnemy < sizeof g_aEnemyInfo / sizeof(EnemyInfo); nCntEnemy++)
	{
		SetEnemy(g_aEnemyInfo[nCntEnemy].pos, g_aEnemyInfo[nCntEnemy].fWidth, g_aEnemyInfo[nCntEnemy].fHeight, g_aEnemyInfo[nCntEnemy].type, g_aEnemyInfo[nCntEnemy].move_bullet);
	}
	//ステージ
	for (int nCntBlock = 0; nCntBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCntBlock++)
	{
		SetBlock(g_aBlockInfo[nCntBlock].pos, g_aBlockInfo[nCntBlock].fWidth, g_aBlockInfo[nCntBlock].fHeight, g_aBlockInfo[nCntBlock].type);
	}

	//コイン
	for (int nCntCoin = 0; nCntCoin < sizeof g_aCoinInfo / sizeof(CoinInfo); nCntCoin++)
	{
		SetCoin(g_aCoinInfo[nCntCoin].pos, g_aCoinInfo[nCntCoin].fWidth, g_aCoinInfo[nCntCoin].fHeight);
	}

	//アイテム
	for (int nCntItem = 0; nCntItem < sizeof g_aItemInfo / sizeof(ItemInfo); nCntItem++)
	{
		SetItem(g_aItemInfo[nCntItem].pos, g_aItemInfo[nCntItem].move, g_aItemInfo[nCntItem].fHorLimit,g_aItemInfo[nCntItem].fWidth, g_aItemInfo[nCntItem].fHeight);
	}

	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	g_nCounterGameState = 0;
	PlaySound(SOUND_LABEL_BGM001);
}

void UninitGame(void)
{
	// 背景
	UninitBG();
	//スコア
	UninitScore();
	// プレイヤー
	UninitPlayer();
	//弾の終了処理
	UninitBullet();
	//爆発の終了処理
	UninitExplosion();
	//敵の終了処理
	UninitEnemy();
	//ブロック
	UninitBlock();
	//フラッグ
	UninitFlag();
	//コイン
	UninitCoin();
	//タイム
	UninitTime();
	UninitLife();
	//アイテム
	UninitItem();
	UninitPause();				//ポーズの終了処理
	StopSound();
}

//ゲーム画面の更新処理
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		PlaySound(SOUND_LABEL_SE_POUZU);
		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == false)
	{
		// ゲーム背景
		UpdateBG();
		//スコア
		UpdateScore();
		// プレイヤー
		UpdatePlayer();
		//弾の更新処理
		UpdateBullet();
		//爆発の更新処理
		UpdateExplosion();
		//更新処理
		UpdateEnemy();
		//ブロック
		UpdateBlock();
		//フラッグ
		UpdateFlag();
		//ブロック
		UpdateCoin();
		//タイム
		UpdateTime();
		UpdateLife();
		//アイテム
		UpdateItem();

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
			}
			break;
		}
	}
	else if(g_bPause == true)
	{
		//ポーズの更新処理
		UpdatePause();
	}
}

void DrawGame(void)
{
	// ゲーム背景
	DrawBG();
	//スコア
	DrawScore();
	// プレイヤー
	DrawPlayer();
	//弾の描画処理
	DrawBullet();
	//爆発の描画処理
	DrawExplosion();
	//敵の描画処理
	DrawEnemy();
	//ブロック
	DrawBlock();
	//フラッグ
	DrawFlag();
	//コイン
	DrawCoin();
	//タイム
	DrawTime();
	DrawLife();
	//アイテム
	DrawItem();
	if (g_bPause == true)
	{
		//ポーズの描画処理
		DrawPause();
	}
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
//=============================================================================
// ポーズの状態
//=============================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}