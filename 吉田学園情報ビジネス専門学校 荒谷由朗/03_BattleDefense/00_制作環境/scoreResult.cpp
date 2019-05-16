//=============================================================================
//
// ハイスコア処理 [scoreResult.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "main.h"
#include "scoreResult.h"
#include "score.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BG_TEXTURENAME_MAX		(2)										//読み込むテクスチャ
#define	TEXTURE_SCORERSULT		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define SCORERSULT_BGTEXTURE		"data/TEXTURE/Battle Defense_SCOER.png"		//読み込むテクスチャ
#define MAX_SCORERSULT (8)	//桁数
#define BG_POS_X			(0)											//頂点座標（X座標）
#define BG_POS_Y			(0)											//頂点座標（Y座標）
#define BG_POS_WIDTH		(SCREEN_WIDTH)								//DirectXの幅
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)								//DirectXの高さ
#define TIME_SPEED (60)		//タイムのスピード

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexScoreResult(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScoreResult[BG_TEXTURENAME_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreResult = NULL;		// 頂点バッファへのポインタ
SCORERESULT				g_ScoreResult;
JoyState		g_JoyStateScoreResult;

//=============================================================================
// 初期化処理
//=============================================================================
void InitScoreResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SCORE g_Score;
	g_Score = GetScore();

	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateScoreResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// スコアの初期化
	g_ScoreResult.nScoreResult = g_Score.nScore;

	// タイムの初期化
	g_ScoreResult.nTimeScoreResult = 4;

	g_ScoreResult.nCntTimeScoreResult = 0;


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		SCORERSULT_BGTEXTURE,		// ファイルの名前
		&g_pTextureScoreResult[1]);	// テクスチャへのポインタ
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_SCORERSULT,		// ファイルの名前
		&g_pTextureScoreResult[0]);	// テクスチャへのポインタ

								// 頂点情報の作成
	MakeVertexScoreResult(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScoreResult(void)
{
	for (int nCntTex = 0; nCntTex < BG_TEXTURENAME_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (g_pTextureScoreResult[nCntTex] != NULL)
		{
			g_pTextureScoreResult[nCntTex]->Release();
			g_pTextureScoreResult[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScoreResult != NULL)
	{
		g_pVtxBuffScoreResult->Release();
		g_pVtxBuffScoreResult = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScoreResult(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//変数宣言
	int nTexData;

	FADE fade;
	fade = GetFade();

	g_ScoreResult.nCntTimeScoreResult++;
	if ((g_ScoreResult.nCntTimeScoreResult % TIME_SPEED) == 0)		//アニメーションの速さを変えられる
	{
		AddTimeScore(-1);
	}
	//決定キーが押されたか
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && pJoyState.bConnectionJoypad == true))
	{
		PlaySound(SOUND_LABEL_SE_SELEKUTO);
		if (fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_TITLE);
		}
	}

	nTexData = g_ScoreResult.nScoreResult;	//スコアを格納

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScoreResult = 1; nCntScoreResult < MAX_SCORERSULT; nCntScoreResult++)
	{//スコアカウント
	 //テクスチャ設定
		pVtx[nCntScoreResult * 4].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
		pVtx[nCntScoreResult * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
		pVtx[nCntScoreResult * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
		pVtx[nCntScoreResult * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
		nTexData /= 10;
	}

	//頂点バッファをアンロック
	g_pVtxBuffScoreResult->Unlock();

	if (g_JoyStateScoreResult.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateScoreResult.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateScoreResult.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateScoreResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScoreResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScoreResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScoreResult[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	for (int nCntScoreResult = 1; nCntScoreResult < MAX_SCORERSULT; nCntScoreResult++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScoreResult[0]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScoreResult * 4, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScoreResult(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScoreResult;
	float fScoreResultPos;				//スコア位置

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORERSULT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreResult,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	//背景
	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);			//頂点座標(X座標,Y座標)
	pVtx[1].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_Y, 0.0f);		//頂点座標(X座標,Y座標)
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_HEIGHT, 0.0f);		//頂点座標(X座標,Y座標)
	pVtx[3].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_HEIGHT, 0.0f);	//頂点座標(X座標,Y座標)

																	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //色の指定（０～２５５）&透明度（０～２５５）
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //色の指定（０～２５５）&透明度（０～２５５)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //色の指定（０～２５５）&透明度（０～２５５)

													  //テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

												//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx += 4;				//頂点データへのポインタを4つ進める

	//スコア
	for (nCntScoreResult = 0, fScoreResultPos = 900; nCntScoreResult < MAX_SCORERSULT; nCntScoreResult++, fScoreResultPos -= 100)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(fScoreResultPos, 390.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(fScoreResultPos + 60.0f, 390.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(fScoreResultPos, 590.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fScoreResultPos + 60.0f, 590.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				//頂点データへのポインタを4つ進める
	}

	//頂点バッファのアンロック
	g_pVtxBuffScoreResult->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
//void AddScoreResult(int nValue)
//{
//}
//=============================================================================
// タイムの加算
//=============================================================================
void AddTimeScore(int nValue)
{
	//変数宣言
	int nTexData;

	FADE fade;

	fade = GetFade();

	g_ScoreResult.nTimeScoreResult += nValue;		//タイムを代入
	nTexData = g_ScoreResult.nTimeScoreResult;		//タイムを格納

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	//タイマーが0以下になったとき
	if (g_ScoreResult.nTimeScoreResult <= 0)
	{
		if (fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_TITLE);
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffScoreResult->Unlock();
}