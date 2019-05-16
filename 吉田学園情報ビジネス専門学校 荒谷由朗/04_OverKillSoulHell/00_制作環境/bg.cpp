//=============================================================================
//
// 背景処理 [bg.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "bg.h"
#include "player.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

LPDIRECT3DTEXTURE9			CBg::m_pTexture[BG_MAX_TEXTURE] = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CBg::CBg() :CScene(0)
{
	m_nCounterAnim	= NULL;
	m_nPatternAnim	= NULL;
	m_SelectNum		= 3;
	m_SelectNumDest = 0;

	// ゲーム状態を取得
	m_mode = CManager::GetMode();

	switch (m_mode)
	{// テクスチャ最大数の設定
	case CManager::MODE_TITLE:
		m_Num2DPoligon = 7;
		break;
	case CManager::MODE_TUTORIAL:
		m_Num2DPoligon = 2;
		break;
	case CManager::MODE_GAME:
		m_Num2DPoligon = 3;
		break;
	case CManager::MODE_RESULT:
		m_Num2DPoligon = 5;
		break;
	}
}

//=============================================================================
//　デストラクタ
//=============================================================================
CBg::~CBg()
{

}

CBg *CBg::Create(void)
{
	CBg *pBg = NULL;

	pBg = new CBg;
	pBg->Init();

	return pBg;
}

HRESULT CBg::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer		= CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice	= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_GAMETEX00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BG_GAMETEX01, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, BG_GAMETEX02, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TITLETEX00, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, BG_TITLETEX01, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, BG_TITLETEX02, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, BG_TITLETEX03, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, BG_TITLETEX04, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX00, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX01, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX02, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX03, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX04, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX05, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, BG_RESULTTEX06, &m_pTexture[14]);

	return S_OK;
}

void CBg::Unload(void)
{
	// テクスチャの破棄
	for (int nCntBg = 0; nCntBg < BG_MAX_TEXTURE; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	switch (m_mode)
	{
	case CManager::MODE_TITLE:
		// 背景
		m_apScene2D[0] = new CScene2D;
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[3]);
		m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		// タイトルロゴ
		m_apScene2D[1] = new CScene2D;
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[4]);
		m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f), 480.0f, 380.0f);
		// 松明(火)左
		m_apScene2D[2] = new CScene2D;
		m_apScene2D[2]->Init();
		m_apScene2D[2]->BindTexture(m_pTexture[5]);
		m_apScene2D[2]->SetTexture(0, 11, 3);
		m_apScene2D[2]->SetPosition(D3DXVECTOR3(100.0f, 420.0f, 0.0f), 200.0f, 100.0f);
		// 松明(台)左
		m_apScene2D[3] = new CScene2D;
		m_apScene2D[3]->Init();
		m_apScene2D[3]->BindTexture(m_pTexture[6]);
		m_apScene2D[3]->SetPosition(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 80.0f, 120.0f);
		// 松明(火)右
		m_apScene2D[4] = new CScene2D;
		m_apScene2D[4]->Init();
		m_apScene2D[4]->BindTexture(m_pTexture[5]);
		m_apScene2D[4]->SetTexture(0, 11, 3);
		m_apScene2D[4]->SetPosition(D3DXVECTOR3(1180.0f, 420.0f, 0.0f), 200.0f, 100.0f);
		// 松明(台)右
		m_apScene2D[5] = new CScene2D;
		m_apScene2D[5]->Init();
		m_apScene2D[5]->BindTexture(m_pTexture[6]);
		m_apScene2D[5]->SetPosition(D3DXVECTOR3(1180.0f, 600.0f, 0.0f), 80.0f, 120.0f);
		// PRESS
		m_apScene2D[6] = new CScene2D;
		m_apScene2D[6]->Init();
		m_apScene2D[6]->BindTexture(m_pTexture[7]);
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 620.0f, 0.0f), 210.0f, 50.0f);
		break;
	case CManager::MODE_TUTORIAL:
		m_apScene2D[0] = new CScene2D;
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT / 2);
		m_apScene2D[0]->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f));

		m_apScene2D[1] = new CScene2D;
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[1]);
		m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT / 2);
		m_apScene2D[1]->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f));

		break;
	case CManager::MODE_GAME:
		m_apScene2D[0] = new CScene2D;
		m_apScene2D[0]->Init();
		m_apScene2D[0]->BindTexture(m_pTexture[0]);
		m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT / 2);
		m_apScene2D[0]->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f));

		m_apScene2D[1] = new CScene2D;
		m_apScene2D[1]->Init();
		m_apScene2D[1]->BindTexture(m_pTexture[1]);
		m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT / 2);
		m_apScene2D[1]->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f));

		m_apScene2D[2] = new CScene2D;
		m_apScene2D[2]->Init();
		m_apScene2D[2]->BindTexture(m_pTexture[2]);
		m_apScene2D[2]->SetPosition(D3DXVECTOR3(1050.0f, 50.0f, 0.0f), 100.0f, 45.0f);
		m_apScene2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	case CManager::MODE_RESULT:
		CManager::GAMERESULT gameresult = CManager::GetResult();
		switch (gameresult)
		{
		case CManager::GAMERESULT_WIN:
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[8]);
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

			m_apScene2D[1] = new CScene2D;
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[9]);
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f), 600.0f, 250.0f);

			m_apScene2D[2] = new CScene2D;
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[12]);
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(950.0f, 500.0f, 0.0f), 250.0f, 200.0f);

			m_apScene2D[3] = new CScene2D;
			m_apScene2D[3]->Init();
			m_apScene2D[3]->BindTexture(m_pTexture[13]);
			m_apScene2D[3]->SetPosition(D3DXVECTOR3(950.0f, 425.0f, 0.0f), 200.0f, 50.0f);
			m_apScene2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			m_apScene2D[4] = new CScene2D;
			m_apScene2D[4]->Init();
			m_apScene2D[4]->BindTexture(m_pTexture[14]);
			m_apScene2D[4]->SetPosition(D3DXVECTOR3(950.0f, 555.0f, 0.0f), 175.0f, 50.0f);
			m_apScene2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;
		case CManager::GAMERESULT_LOSE:
			m_apScene2D[0] = new CScene2D;
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[10]);
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

			m_apScene2D[1] = new CScene2D;
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[11]);
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f), 600.0f, 125.0f);

			m_apScene2D[2] = new CScene2D;
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[12]);
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(950.0f, 500.0f, 0.0f), 250.0f, 200.0f);

			m_apScene2D[3] = new CScene2D;
			m_apScene2D[3]->Init();
			m_apScene2D[3]->BindTexture(m_pTexture[13]);
			m_apScene2D[3]->SetPosition(D3DXVECTOR3(950.0f, 425.0f, 0.0f), 200.0f, 50.0f);
			m_apScene2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			m_apScene2D[4] = new CScene2D;
			m_apScene2D[4]->Init();
			m_apScene2D[4]->BindTexture(m_pTexture[14]);
			m_apScene2D[4]->SetPosition(D3DXVECTOR3(950.0f, 555.0f, 0.0f), 175.0f, 50.0f);
			m_apScene2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;
		}
		break;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < m_Num2DPoligon; nCntBg++)
	{
		if (m_apScene2D[nCntBg] != NULL)
		{
			m_apScene2D[nCntBg]->Uninit();
			m_apScene2D[nCntBg] = NULL;
		}
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	if (m_mode == CManager::MODE_TITLE)
	{
		m_nCounterAnim++;

		if ((m_nCounterAnim % 2) == 0)		//アニメーションの速さを変えられる
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			m_apScene2D[2]->SetTexture(m_nPatternAnim, 11, 3);
			m_apScene2D[4]->SetTexture(m_nPatternAnim, 11, 3);

			if (m_nPatternAnim > 33)
			{
				m_nPatternAnim = 0;
			}
		}
	}

	if (m_mode == CManager::MODE_GAME || m_mode == CManager::MODE_TUTORIAL)
	{
		LPDIRECT3DVERTEXBUFFER9 VtxBuff;

		m_nCounterAnim++;
		if ((m_nCounterAnim % 3) == 0)
		{
			VtxBuff = m_apScene2D[0]->GetVtxBuff();

			m_nPatternAnim = (m_nPatternAnim + 1) % 400;		//パターンNo.更新

			VERTEX_2D*pVtx;			//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f), 0.0f); 			//Uが幅、Vが高さ　(0.0f～1.0f）
			pVtx[1].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f) + 1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
			pVtx[2].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f), 1.0f); 			//Uが幅、Vが高さ　(0.0f～1.0f）
			pVtx[3].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f) + 1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

			//頂点バッファのアンロック
			VtxBuff->Unlock();
		}
		if ((m_nCounterAnim % 3) == 0)
		{
			VtxBuff = m_apScene2D[1]->GetVtxBuff();

			m_nPatternAnim = (m_nPatternAnim + 1) % 400;		//パターンNo.更新

			VERTEX_2D*pVtx;		//頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f), 0.0f); 			//Uが幅、Vが高さ　(0.0f～1.0f）
			pVtx[1].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f) + 1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
			pVtx[2].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f), 1.0f); 			//Uが幅、Vが高さ　(0.0f～1.0f）
			pVtx[3].tex = D3DXVECTOR2((m_nPatternAnim * 0.0025f) + 1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）

			//頂点バッファのアンロック
			VtxBuff->Unlock();
		}
	}
	if (m_mode == CManager::MODE_RESULT)
	{
		CFade::FADE fade = CFade::GetFade();
		CInputKeyboard *pKey = CManager::GetInputKeyboard();		// 入力情報の取得
																	// ジョイパッド入力状態の取得
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

		if (pKey != NULL)
		{
			if (pKey->GetPress(DIK_W) == true ||
				state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
				{
					m_apScene2D[m_SelectNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));;
					m_SelectNumDest = (m_SelectNumDest + 1) % 2;
					if (m_SelectNumDest == 0)
					{
						m_SelectNum = 3;
					}
					else if (m_SelectNumDest == 1)
					{
						m_SelectNum = 4;
					}
					m_apScene2D[m_SelectNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));;
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT001);
				}
				apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
			}
			else if (pKey->GetPress(DIK_S) == true ||
				state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
				{
					m_apScene2D[m_SelectNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));;
					m_SelectNumDest = (m_SelectNumDest + 1) % 2;
					if (m_SelectNumDest == 0)
					{
						m_SelectNum = 3;
					}
					else if (m_SelectNumDest == 1)
					{
						m_SelectNum = 4;
					}
					m_apScene2D[m_SelectNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));;
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT001);
				}
				apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
			}
			if (pKey->GetTrigger(DIK_RETURN) == true ||
				state.Gamepad.wButtons & XINPUT_GAMEPAD_B && abConect[0] == true)
			{
				if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
				{
					CGame *pGame = CManager::GetGame();
					CGame *pPause = ((CGame*)pGame);

					if (fade != CFade::FADE_OUT)
					{
						if (m_SelectNum == 3)
						{
							CFade::SetFade(CManager::MODE_GAME);
						}
						else if (m_SelectNum == 4)
						{
							CFade::SetFade(CManager::MODE_TITLE);
						}
						CSound *pSound = CManager::GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
					}
				}
				apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
			}
		}



		// ジョイパッドの状態更新
		apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{

}