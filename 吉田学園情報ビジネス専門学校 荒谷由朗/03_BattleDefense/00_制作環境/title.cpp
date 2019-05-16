//=============================================================================
//
// タイトル処理 [title.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define BG_TEXTURENAME		"data/TEXTURE/Battle Defense_TITOL.png"		//読み込むテクスチャ
#define BG_TEXTURENAME0		"data/TEXTURE/[PLEASE PLESS BUTTON].png"		//読み込むテクスチャ
#define BG_POS_X			(0)								//頂点座標（X座標）
#define BG_POS_Y			(0)								//頂点座標（Y座標）
#define BG_POS_WIDTH		(SCREEN_WIDTH)					//DirectXの幅
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)					//DirectXの高さ
#define TIME_SPEED (60)		//タイムのスピード
#define MAX_TITLE_TEXTURE		(2)								// ポーズテクスチャ最大数

//=============================================================================
//グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE_TEXTURE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	// 頂点バッファへのポインタ
JoyState		g_JoyStateTitle;
int						g_nTimeTitle;					// タイム
int						nCntTimeTitle;
float					g_TitleColor;					// 選択色

//=============================================================================
//タイトル画面の初期化処理
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// タイムの初期化
	g_nTimeTitle = 4;

	nCntTimeTitle = 0;

	g_TitleColor = 1.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME0, &g_pTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < 2; nCntPause++)
	{// ポーズをカウント
		if (nCntPause == 0)
		{// BG
		 // 頂点設定
		 //頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);			//頂点座標(X座標,Y座標)
			pVtx[1].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_Y, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_HEIGHT, 0.0f);		//頂点座標(X座標,Y座標)
			pVtx[3].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_HEIGHT, 0.0f);	//頂点座標(X座標,Y座標)

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// ポーズメニュー
		 // 頂点設定
			pVtx[0].pos = D3DXVECTOR3(400.0f, 600.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1200.0f, 600.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 750.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200.0f, 750.0f, 0.0f);

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// 1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

		pVtx += 4;	// 頂点データのポインタを４つ分進める
	}

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();
}

//終了処理
void UninitTitle(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}


}

//更新処理
void UpdateTitle(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ
	FADE fade;

	fade = GetFade();

	nCntTimeTitle++;

	g_pVtxBuffTitle->Lock(0,0,(void**)&pVtx,0);

	if ((nCntTimeTitle % TIME_SPEED) == 0)		//アニメーションの速さを変えられる
	{
		AddTimeTitle(-1);
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
			SetFade(MODE_TUTORIARU);
		}
	}

	g_TitleColor -= 0.004f;

	if (g_TitleColor < 0.65f)
	{
		g_TitleColor = 1.0f;
	}

	// 頂点カラー設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);
	pVtx[1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);
	pVtx[2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);
	pVtx[3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);

	// 頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//描画処理
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < 2; nCntPause++)
	{// ポーズをカウント
			//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntPause]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}

//=============================================================================
// タイムの加算
//=============================================================================
void AddTimeTitle(int nValue)
{
	//変数宣言
	//int nCntTimeTitle;
	int nTexData;

	//MODE pMode;
	FADE fade;

	fade = GetFade();
	//pMode = GetModeNow();

	g_nTimeTitle += nValue;		//タイムを代入
	nTexData = g_nTimeTitle;		//タイムを格納

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//if (g_nTimeTitle >= 0)
	//{
	//	for (nCntTimeTitle = 0; nCntTimeTitle < MAX_TIME; nCntTimeTitle++)
	//	{//タイムカウント
	//	 //テクスチャ設定
	//		pVtx[nCntTimeTitle * 4].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
	//		pVtx[nCntTimeTitle * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
	//		pVtx[nCntTimeTitle * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
	//		pVtx[nCntTimeTitle * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
	//		nTexData /= 10;
	//	}
	//}
	//タイマーが0以下になったとき
	if (g_nTimeTitle <= 0)
	{
		if (fade != FADE_OUT)
		{
			//モード設定
			SetFade(MODE_SCOER);
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();
}