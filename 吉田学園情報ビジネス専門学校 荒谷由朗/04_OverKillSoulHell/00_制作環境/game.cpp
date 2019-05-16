//=============================================================================
//
// ゲーム処理 [game.h]
// Author :		荒谷由朗
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "lasteenemy.h"
#include "bullet.h"
#include "bulleticon.h"
#include "explosion.h"
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "gauge.h"
#include "item.h"
#include "barrier.h"
#include "soul.h"
#include "mp.h"
#include "mpicon.h"
#include "pair.h"
#include "pause.h"
#include "sound.h"

CPlayer			*CGame::m_pPlayer = NULL;

//=============================================================================
//　コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_pPlayer = NULL;
	m_nCounter = 0;
	m_bPause = false;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
//　初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	// 背景の生成
	CBg::Load();
	CBg::Create();

	// スコアの生成
	CNumber::Load();
	CScore::Create(D3DXVECTOR3(1220.0f, 60.0f, 0.0f));

	// プレイヤーの生成
	m_pPlayer = new CPlayer;
	m_pPlayer->Load();
	m_pPlayer->Init();

	// 子機の生成
	CPair::Load();

	// ゲージの生成
	CGauge::Load();
	CGauge::Create();

	// スキルアイコンの生成
	CMPIcon::Load();
	CMP::Create(D3DXVECTOR3(400.0f, 70.0f, 0.0f));

	// 弾アイコンの生成
	CBulletIcon::Load();
	CBulletIcon::Create();

	// 敵の生成
	CEnemy::Load();
	CLastEnemy::Load();

	// アイテムの生成
	CItem::Load();

	// ソウルの生成
	CSoul::Load();

	// バリアの生成
	CBarrier::Load();

	// 弾の生成
	CBullet::Load();

	// 爆発の生成
	CExplosion::Load();

	// エフェクトの生成
	CEffect::Load();

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

	return S_OK;
}

//=============================================================================
//　終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CBg::Unload();
	CNumber::Unload();
	m_pPlayer->Unload();
	CPair::Unload();
	CGauge::Unload();
	CMPIcon::Unload();
	CBulletIcon::Unload();
	CEnemy::Unload();
	CLastEnemy::Unload();
	CItem::Unload();
	CSoul::Unload();
	CBarrier::Unload();
	CBullet::Unload();
	CExplosion::Unload();
	CEffect::Unload();

	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
//　更新処理
//=============================================================================
void CGame::Update(void)
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

	if (m_bPause == false)
	{
		m_nCounter++;
	}

	if (fade == CFade::FADE_IN)
	{
		if (pKey->GetTrigger(DIK_P) == true ||
			state.Gamepad.wButtons & XINPUT_GAMEPAD_START && abConect[0] == true)
		{
			if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
			{
				m_bPause = m_bPause ? false : true;
				CSound *pSound = CManager::GetSound();
				if (m_bPause == true)
				{
					pSound->StopSound(CSound::SOUND_LABEL_BGM002);
					pSound->PlaySound(CSound::SOUND_LABEL_PAUSE);
				}
				else if (m_bPause == false)
				{
					pSound->PlaySound(CSound::SOUND_LABEL_BGM002);
					pSound->PlaySound(CSound::SOUND_LABEL_PAUSE);
				}
			}
			apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
		}
	}

	if (m_nCounter == 100)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 200.0f, 0.0f), 30, 30, 0);
	}
	else if (m_nCounter == 450)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 500.0f, 0.0f), 60, 60, 0);
	}
	else if (m_nCounter == 750)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 300.0f, 0.0f), 60, 60, 1);
	}
	else if (m_nCounter == 950)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 170.0f, 0.0f), 30, 30, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 250.0f, 0.0f), 30, 30, 0);
	}
	else if (m_nCounter == 1350)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 390.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 460.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 530.0f, 0.0f), 30, 30, 1);
	}
	else if (m_nCounter == 1650)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 200.0f, 0.0f), 50, 50, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 490.0f, 0.0f), 30, 30, 0);
	}
	else if (m_nCounter == 1850)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 340.0f, 0.0f), 30, 30, 1);
	}
	else if (m_nCounter == 2250)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 200.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 490.0f, 0.0f), 30, 30, 1);
	}

	else if (m_nCounter == 2750)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2), 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 80, (SCREEN_HEIGHT / 2) - 80, 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 80, (SCREEN_HEIGHT / 2) + 80, 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 160, (SCREEN_HEIGHT / 2) - 160, 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 160, (SCREEN_HEIGHT / 2) + 160, 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 240, (SCREEN_HEIGHT / 2) - 80, 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 240, (SCREEN_HEIGHT / 2) + 80, 0.0f), 40, 40, 0);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 320, (SCREEN_HEIGHT / 2), 0.0f), 40, 40, 0);
	}
	else if (m_nCounter == 3500)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2) + 140.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2) + 60.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2) - 20.0f, 0.0f), 30, 30, 1);
	}
	else if (m_nCounter == 3750)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 100.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 180.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), 260.0f, 0.0f), 30, 30, 1);
	}
	else if (m_nCounter == 4000)
	{
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2) + 140.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2) + 60.0f, 0.0f), 30, 30, 1);
		CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2) - 20.0f, 0.0f), 30, 30, 1);
	}
	else if (m_nCounter == 4700)
	{
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f), (SCREEN_HEIGHT / 2), 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 80, (SCREEN_HEIGHT / 2) - 80, 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 80, (SCREEN_HEIGHT / 2) + 80, 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 160, (SCREEN_HEIGHT / 2) - 160, 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 160, (SCREEN_HEIGHT / 2) + 160, 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 240, (SCREEN_HEIGHT / 2) - 80, 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 240, (SCREEN_HEIGHT / 2) + 80, 0.0f), 40, 40, 0);
		CLastEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH - 50.0f) + 320, (SCREEN_HEIGHT / 2), 0.0f), 40, 40, 0);
	}


	if (m_nCounter >= 6000)
	{
		if (fade != CFade::FADE_OUT)
		{
			//モード設定
			CFade::SetFade(CManager::MODE_RESULT);
		}
	}
	// ジョイパッドの状態更新
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}

CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// ポーズの状態
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;
}