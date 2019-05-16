//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
#include "inputx.h"
#include "bullet.h"
#include "meshField.h"
#include "explosion.h"
#include "obstacle.h"
#include "fade.h"
#include "score.h"
#include "time.h"
#include "scoreResult.h"
#include "txt.h"
#include "enemy.h"
#include "life.h"
#include "motion.h"
#include "PlayerLife.h"
#include "ObjectLife.h"
#include "pause.h"
#include "sound.h"
//=============================================================================
//グローバル
//=============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲーム状態
GAMESTATE g_gameStateNow = GAMESTATE_NONE;
JoyState		g_JoyStateGame;
int g_nCounterGameState = 0;
bool g_bPause;								//ポーズ中かどうか

//=============================================================================
//ゲーム画面の初期化
//=============================================================================
void InitGame(void)
{
	g_bPause = false;
	g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	LoadData();

	// メッシュの初期化処理
	InitMeshField();

	// 壁の初期化処理
	//InitMeshCylinder();
	InitLife();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// 弾の初期化処理
	InitBullet();

	// 爆発の初期化処理
	InitExplosion();

	// モデルの初期化処理
	InitPlayer();

	// 敵の初期化処理
	InitEnemy();

	// 障害物の初期化処理
	InitObstaclel();

	// スコアの初期化処理
	InitScore();

	// タイムの初期化処理
	InitTime();

	// モーションの初期化
	InitMotion();
	InitPlayerLife();
	InitOBLife();
	// ポーズの初期化
	InitPause();

	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	g_nCounterGameState = 0;
	/*SetEnemy(D3DXVECTOR3(400.0f, 80.0f, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/
	//PlaySound(SOUND_LABEL_BGM001);
}

//=============================================================================
//ゲーム画面の終了処理
//=============================================================================
void UninitGame(void)
{
	// メッシュの終了処理
	UninitMeshField();

	// 壁の終了処理
	//UninitMeshCylinder();
	UninitLife();

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// 弾の終了処理
	UninitBullet();

	UninitExplosion();

	// モデルの終了処理
	UninitPlayer();

	// 敵の終了処理
	UninitEnemy();

	// 障害物の終了処理
	UninitObstaclel();

	//　スコアの終了処理
	UninitScore();

	// タイムの終了処理
	UninitTime();

	// モーションの終了処理
	UninitMotion();
	UninitPlayerLife();
	UninitOBLife();

	// ポーズの初期化
	UninitPause();

	//StopSound();
}

//=============================================================================
//ゲーム画面の更新処理
//=============================================================================
void UpdateGame(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (GetKeyboardTrigger(DIK_P) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	トリガー
			PlaySound(SOUND_LABEL_SE_POUZU);
			g_bPause = g_bPause ? false : true;
		}
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (g_bPause == false)
	{

		// メッシュの更新処理
		UpdateMeshField();

		// 壁の更新処理
		//UpdateMeshCylinder();
		UpdateLife();

		// カメラの更新処理
		UpdateCamera();

		// ライトの更新処理
		UpdateLight();

		// 弾の更新処理
		UpdateBullet();

		// 爆発の更新処理
		UpdateExplosion();

		// モデルの更新処理
		UpdatePlayer();

		// 敵の更新処理
		UpdateEnemy();

		// 障害物の更新処理
		UpdateObstaclel();

		// スコアの更新処理
		UpdateScore();

		// タイムの更新処理
		UpdateTime();

		// モーションの更新
		UpdateMotion();
		UpdatePlayerLife();
		UpdateOBLife();

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
				SetFade(MODE_RESULT);
			}
			break;
		}
	}
	else if (g_bPause == true)
	{
		//ポーズの更新処理
		UpdatePause();
	}
	if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateGame.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateGame.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
//ゲーム画面の描画処理
//=============================================================================
void DrawGame(void)
{
	// メッシュの描画処理
	DrawMeshField();

	// 壁の描画処理
	//DrawMeshCylinder();
	DrawLife();

	// カメラの設定
	SetCamera();

	// 弾の描画処理
	DrawBullet();

	// 爆発の描画処理
	DrawExplosion();

	// モデルの描画処理
	DrawPlayer();

	// 敵の描画処理
	DrawEnemy();

	// 障害物の描画処理
	DrawObstaclel();

	// スコアの描画処理
	DrawScore();

	// タイムの描画処理
	DrawTime();

	// モーションの描画処理
	DrawMotion();
	DrawPlayerLife();
	DrawOBLife();

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