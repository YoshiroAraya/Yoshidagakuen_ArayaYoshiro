//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : 荒谷由朗
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "inputx.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PAUSE_POLYGON		(5)								// ポーズポリゴン最大数
#define MAX_PAUSE_TEXTURE		(4)								// ポーズテクスチャ最大数
#define PAUSE_TEXTURE_NAME_1	"data\\TEXTURE\\pause100.png"	// 読み込むテクスチャファイル1
#define PAUSE_TEXTURE_NAME_2	"data\\TEXTURE\\pause000.png"	// 読み込むテクスチャファイル2
#define PAUSE_TEXTURE_NAME_3	"data\\TEXTURE\\pause001.png"	// 読み込むテクスチャファイル3
#define PAUSE_TEXTURE_NAME_4	"data\\TEXTURE\\pause002.png"	// 読み込むテクスチャファイル4
#define PAUSE_POS_X				(0)								// ポーズの左上X座標
#define PAUSE_POS_Y				(0)								// ポーズの左上Y座標
#define PAUSE_WIDTH				(SCREEN_WIDTH)					// ポーズの幅
#define PAUSE_HEIGHT			(SCREEN_HEIGHT)					// ポーズの高さ
#define PAUSE_TEXTURE_SPEED		(5)								// テクスチャアニメーションスピード
#define PAUSE_TEXTURE_PATTERN	(10)							// テクスチャアニメーションパターン数
#define PAUSE_TEXTURE_UV_U		(1.0f)							// テクスチャアニメーションU範囲
#define PAUSE_TEXTURE_UV_V		(1.0f)							// テクスチャアニメーションV範囲
#define PAUSE_BACKTEXTURE_UV_U	(1.0f)							// 前テクスチャアニメーションU範囲
#define PAUSE_BACKTEXTURE_UV_V	(1.0f)							// 前テクスチャアニメーションV範囲
#define PAUSE_SPEED				(0.002f)						// ポーズスピード

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9				g_pTexturePause[MAX_PAUSE_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffPause = NULL;						// 頂点バッファへのポインタ
D3DXVECTOR3						g_posPause;									// ポーズの位置
JoyState						g_JoyStatePause;
int								g_SelectNum;								// 選択番号
float							g_SelectColor;								// 選択色

//=============================================================================
// ポーズ初期化処理
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスを取得
	g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	int nCntPause;								// ポーズカウンタ

	g_posPause		= D3DXVECTOR3((PAUSE_POS_X + PAUSE_WIDTH) / 2, (PAUSE_POS_Y + PAUSE_HEIGHT) / 2, 0.0f);		// ポーズの中心値
	g_SelectNum		= 0;						// 選択番号
	g_SelectColor	= 1.0f;						// 選択カラー
	float fPosPause = -150;						// ポーズ位置

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(// ポーズ
		pDevice,
		PAUSE_TEXTURE_NAME_1,
		&g_pTexturePause[0]
	);
	D3DXCreateTextureFromFile
	(// コンテニュー
		pDevice,
		PAUSE_TEXTURE_NAME_2,
		&g_pTexturePause[1]
	);
	D3DXCreateTextureFromFile
	(// リトライ
		pDevice,
		PAUSE_TEXTURE_NAME_3,
		&g_pTexturePause[2]
	);
	D3DXCreateTextureFromFile
	(// クウィット
		pDevice,
		PAUSE_TEXTURE_NAME_4,
		&g_pTexturePause[3]
	);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_PAUSE_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL
	);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntPause = 0; nCntPause < MAX_PAUSE_POLYGON; nCntPause++)
	{// ポーズをカウント
		if (nCntPause == 0)
		{// BG
		 // 頂点設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
		}
		else if (nCntPause == 1)
		{// ポーズ
		 // 頂点設定
			pVtx[0].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) - 180, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) - 180, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + 180, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + 180, 0.0f);
			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.5f);
		}
		else
		{// ポーズメニュー
		 // 頂点設定
			pVtx[0].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) - 180, (PAUSE_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((PAUSE_WIDTH / 2) + 180, (PAUSE_HEIGHT / 2) + fPosPause + 100, 0.0f);

			if (nCntPause == 2)
			{
				// 頂点カラー設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				// 頂点カラー設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			}

			fPosPause += 100;
		}
		// 1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, PAUSE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, PAUSE_TEXTURE_UV_V);

		pVtx += 4;	// 頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// ポーズ終了処理
//=============================================================================
void UninitPause(void)
{
	// 変数宣言
	int nCntTex;		// テクスチャカウンタ

	// テクスチャの破棄
	for (nCntTex = 0; nCntTex < MAX_PAUSE_TEXTURE; nCntTex++)
	{// テクスチャをカウント
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
// ポーズ更新処理
//=============================================================================
void UpdatePause(void)
{
	JoyState		pJoyState = GetJoystate();
	XINPUT_STATE	state;
	XInputGetState(0, &state);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	if (GetKeyboardTrigger(DIK_W) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	トリガー
		 // 頂点カラー設定
			pVtx[g_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			g_SelectNum		= (g_SelectNum + 2) % 3;
			g_SelectColor	= 1.0f;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	if (GetKeyboardTrigger(DIK_S) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	トリガー
		 // 頂点カラー設定
			pVtx[g_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[g_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			g_SelectNum		= (g_SelectNum + 1) % 3;
			g_SelectColor	= 1.0f;
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	g_SelectColor -= 0.004f;

	if (g_SelectColor < 0.65f)
	{
		g_SelectColor = 1.0f;
	}

	// 頂点カラー設定
	pVtx[g_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);
	pVtx[g_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);
	pVtx[g_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);
	pVtx[g_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, g_SelectColor);

	// 頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//	トリガー
		PlaySound(SOUND_LABEL_SE_SELEKUTO);
			if (g_SelectNum == 0)
			{
				SetPauseState(false);
			}
			else if (g_SelectNum == 1)
			{
				SetFade(MODE_GAME);
			}
			else if (g_SelectNum == 2)
			{
				SetFade(MODE_TITLE);
			}
		}
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_PUSH;
	}

	if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStatePause.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStatePause.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}

}

//=============================================================================
// ポーズ描画処理
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスポインタ
	int nCntPause;					// ポーズカウンタ
	int nCntTex = 0;				// テクスチャカウンタ

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffPause,
		0,
		sizeof(VERTEX_2D)
	);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < MAX_PAUSE_POLYGON; nCntPause++)
	{// ポーズをカウント
		if (nCntPause >= 1)
		{
			// テクスチャ設定
			pDevice->SetTexture(0, g_pTexturePause[nCntTex]);
			nCntTex++;
		}

		// ポーズの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}