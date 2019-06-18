//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "pause.h"
#include "scene2D.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9				CPause::m_pTexture[PAUSE_MAX_TEXTURE]	= {};
LPDIRECT3DVERTEXBUFFER9			CPause::m_pVtxBuff						= NULL;
int								CPause::m_SelectNum						= NULL;			// 選択番号
float							CPause::m_SelectColor					= NULL;			// 選択色

//=============================================================================
//	コンストラクタ
//=============================================================================
CPause::CPause()
{
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SelectNum		= NULL;
	m_SelectColor	= 0.0f;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CPause::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME01, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME02, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME03, &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CPause::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PAUSE_MAX_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	m_SelectNum		= 0;						// 選択番号
	m_SelectColor	= 0.0f;						// 選択カラー

	int nCntPause;								// ポーズカウンタ
	float fPosPause = -170;						// ポーズ位置

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * PAUSE_MAX_POLIGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	Load();

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロック
	m_pVtxBuff->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntPause = 0; nCntPause < PAUSE_MAX_POLIGON; nCntPause++)
	{// ポーズをカウント
		if (nCntPause == 0)
		{// BG
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (nCntPause == 1)
		{// ポーズ
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 190, (SCREEN_HEIGHT / 2) - 210, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 190, (SCREEN_HEIGHT / 2) - 210, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 190, (SCREEN_HEIGHT / 2) + 210, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 190, (SCREEN_HEIGHT / 2) + 210, 0.0f);
			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (nCntPause == 2)
		{// ポーズメニュー
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 170, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 170, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 170, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 170, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			fPosPause += 100;
		}
		else if (nCntPause == 3)
		{// ポーズメニュー
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 150, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 150, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			fPosPause += 100;
		}
		else if (nCntPause == 4)
		{// ポーズメニュー
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 130, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 130, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 130, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 130, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);

			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			fPosPause += 100;
		}
		// 1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// 頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	Unload();

	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	CFade::FADE		fade	= CFade::GetFade();					// フェードの取得
	CInputKeyboard	*pKey	= CManager::GetInputKeyboard();		// 入力情報の取得

	CInputJoyPad *apInputJoyPad[1] = {};
	apInputJoyPad[0] = CManager::GetInputJoyPad();
	// ジョイパッドボタン状態の取得
	CInputJoyPad::JoyState apJoyState[1];
	apJoyState[0] = apInputJoyPad[0]->GetJoyState(0);
	// ジョイパッド接続状態の取得
	bool abConect[1] = {};
	abConect[0] = apInputJoyPad[0]->GetConnect(0);
	// ジョイパッド情報の取得
	XINPUT_STATE state;
	XInputGetState(0, &state);

	// 頂点バッファをロック
	m_pVtxBuff->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	if (pKey->GetTrigger(DIK_UP) == true || pKey->GetTrigger(DIK_W) == true ||
		state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
	{
		if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
		{
		// 頂点カラー設定
		pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		m_SelectNum		= (m_SelectNum + 2) % 3;
		m_SelectColor	= 1.0f;

		// サウンドの再生
		CSound *pSound	= CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT001);
		}
		apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
	}
	if (pKey->GetTrigger(DIK_DOWN) == true || pKey->GetTrigger(DIK_S) == true ||
		state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
	{
		if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
		{
		// 頂点カラー設定
		pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		m_SelectNum		= (m_SelectNum + 1) % 3;
		m_SelectColor	= 1.0f;

		// サウンドの再生
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT001);
		}
		apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
	}

	m_SelectColor -= 0.004f;

	if (m_SelectColor < 0.65f)
	{
		m_SelectColor = 1.0f;
	}

	// 頂点カラー設定
	pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);
	pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);
	pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);
	pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	if (pKey->GetTrigger(DIK_RETURN) == true ||
		state.Gamepad.wButtons & XINPUT_GAMEPAD_B && abConect[0] == true)
	{
		if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
		{
			CGame *pGame	= CManager::GetGame();
			CGame *pPause	= ((CGame*)pGame);
			bool bPause		= pPause->GetPause();

			if (m_SelectNum == 0)
			{
				pPause->SetPause(false);

				// サウンドの再生
				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
			}
			else if (m_SelectNum == 1)
			{
				if (fade != CFade::FADE_OUT)
				{
					CFade::SetFade(CManager::MODE_GAME);
					pPause->SetPause(false);

					// 頂点カラー設定
					pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

					m_SelectNum	= 0;

					// サウンドの再生
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
				}
			}
			else if (m_SelectNum == 2)
			{
				if (fade != CFade::FADE_OUT)
				{
					CFade::SetFade(CManager::MODE_TITLE);
					pPause->SetPause(false);

					// 頂点カラー設定
					pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

					m_SelectNum = 0;

					// サウンドの再生
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
				}
			}
		}
		apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
	}
	// ジョイパッドの状態更新
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{
	int nCntPause;					// ポーズカウンタ
	int nCntTex = 0;				// テクスチャカウンタ

	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D)
	);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < PAUSE_MAX_POLIGON; nCntPause++)
	{// ポーズをカウント
		if (nCntPause >= 1)
		{
			// テクスチャ設定
			pDevice->SetTexture(0, m_pTexture[nCntTex]);
			nCntTex++;
		}

		// ポーズの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}