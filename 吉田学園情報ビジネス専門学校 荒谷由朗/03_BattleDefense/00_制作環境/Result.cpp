//=============================================================================
//
// リザルト処理 [result.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAME_MAX		(1)										//読み込むテクスチャ
#define BG_TEXTURENAME_WIN		"data/TEXTURE/Battle Defense_CLEAR.png"		//読み込むテクスチャ
#define BG_TEXTURENAME_LOSE		"data/TEXTURE/Battle Defense_OVER.png"		//読み込むテクスチャ
#define BG_TEXTURENAME_RETRY	"data/TEXTURE/pause001.png"				//読み込むテクスチャ
#define BG_TEXTURENAME_QUIT		"data/TEXTURE/pause002.png"				//読み込むテクスチャ

#define BG_POS_X			(0)											//頂点座標（X座標）
#define BG_POS_Y			(0)											//頂点座標（Y座標）
#define BG_POS_WIDTH		(SCREEN_WIDTH)								//DirectXの幅
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)								//DirectXの高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[BG_TEXTURENAME_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	// 頂点バッファへのポインタ
JoyState		g_JoyStateResult;
int								g_nResultNum;					// 選択番号
float							g_fResultCol;					// 選択色

//タイトル画面の初期化処理
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	g_nResultNum = 0;							// 選択番号
	g_fResultCol = 1.0f;						// 選択カラー

	GAMESTATE pGame;

	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	//デバイスの取得
	pDevice = GetDevice();
	pGame = GetGameStateNow();

	//テクスチャの読み込み
	if (pGame == GAMESTATE_CLEAR)
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_WIN, &g_pTextureResult[0]);
		PlaySound(SOUND_LABEL_BGM002);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_LOSE, &g_pTextureResult[0]);
		PlaySound(SOUND_LABEL_BGM003);
	}
	//D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_RETRY, &g_pTextureResult[1]);
	//D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_QUIT, &g_pTextureResult[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BG_TEXTURENAME_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSelect = 0; nCntSelect < BG_TEXTURENAME_MAX; nCntSelect++)
	{
		if (nCntSelect == 0)
		{	//背景
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
		}
		if (nCntSelect == 1)
		{	//プレイヤー0
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(70.0f, 450.0f, 0.0f);			//頂点座標(X座標,Y座標)
			pVtx[1].pos = D3DXVECTOR3(1180.0f, 450.0f, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[2].pos = D3DXVECTOR3(70.0f, 525.0f, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[3].pos = D3DXVECTOR3(1180.0f, 525.0f, 0.0f);	//頂点座標(X座標,Y座標)

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
		}
		else if (nCntSelect == 2)
		{	//プレイヤー1
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(70.0f, 525.0f, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[1].pos = D3DXVECTOR3(1180.0f, 525.0f, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[2].pos = D3DXVECTOR3(70.0f, 600.0f, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[3].pos = D3DXVECTOR3(1180.0f, 600.0f, 0.0f);		//頂点座標(X座標,Y座標)

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
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffResult->Unlock();
}

//=============================================================================
// キャラクター選択の終了処理
//=============================================================================
void UninitResult(void)
{
	for (int nCntTex = 0; nCntTex < BG_TEXTURENAME_MAX; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCntTex] != NULL)
		{
			g_pTextureResult[nCntTex]->Release();
			g_pTextureResult[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	StopSound();
}

//=============================================================================
// キャラクター選択の更新処理
//=============================================================================
void UpdateResult(void)
{

	//VERTEX_2D *pVtx;	// 頂点情報へのポインタ
	//// 頂点バッファをロック
	//g_pVtxBuffResult->Lock
	//(
	//	0,
	//	0,
	//	(void**)&pVtx,
	//	0
	//);
	//if (GetKeyboardTrigger(DIK_LEFT) == true || GetKeyboardTrigger(DIK_A) == true)
	//{
	//	// 頂点カラー設定
	//	pVtx[g_nResultNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	//	g_nResultNum = (g_nResultNum + 1) % 2;
	//	g_fResultCol = 1.0f;
	//	//PlaySound(SOUND_LABEL_SE_RESULT);
	//}
	//if (GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_D) == true)
	//{
	//	// 頂点カラー設定
	//	pVtx[g_nResultNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	//	g_nResultNum = (g_nResultNum + 1) % 2;
	//	g_fResultCol = 1.0f;
	//	//PlaySound(SOUND_LABEL_SE_RESULT);
	//}

	//// 頂点カラー設定
	//pVtx[g_nResultNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);
	//pVtx[g_nResultNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);
	//pVtx[g_nResultNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);
	//pVtx[g_nResultNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);

	//// 頂点バッファをアンロック
	//g_pVtxBuffResult->Unlock();

	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	FADE fade;

	fade = GetFade();

	//決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && pJoyState.bConnectionJoypad == true))
	{
		PlaySound(SOUND_LABEL_SE_SELEKUTO);
		if (fade != FADE_OUT)
		{
			if (g_nResultNum == 1)
			{
				//モード
				SetFade(MODE_GAME);
				//PlaySound(SOUND_LABEL_BGM001);
			}
			else if (g_nResultNum == 0)
			{
				//モード
				SetFade(MODE_SCOER);
			}


		}
	}
	if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// キャラクター選択の描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSelect = 0; nCntSelect < BG_TEXTURENAME_MAX; nCntSelect++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCntSelect]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSelect * 4, 2);
	}
}