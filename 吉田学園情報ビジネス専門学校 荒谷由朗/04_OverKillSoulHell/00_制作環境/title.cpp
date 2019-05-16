//=============================================================================
//
// タイトル処理 [title.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "title.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//　コンストラクタ
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
//　デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//　初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// 背景の生成
	CBg::Load();
	CBg::Create();

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//=============================================================================
//　終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CBg::Unload();
	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
//　更新処理
//=============================================================================
void CTitle::Update(void)
{
	CFade::FADE fade = CFade::GetFade();

	CInputKeyboard *pKey = CManager::GetInputKeyboard();		// 入力情報の取得

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
		if (pKey->GetTrigger(DIK_RETURN) == true ||
			state.Gamepad.wButtons & XINPUT_GAMEPAD_B && abConect[0] == true)
		{
			if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
			{
				if (fade != CFade::FADE_OUT)
				{
					//モード設定
					CFade::SetFade(CManager::MODE_TUTORIAL);
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