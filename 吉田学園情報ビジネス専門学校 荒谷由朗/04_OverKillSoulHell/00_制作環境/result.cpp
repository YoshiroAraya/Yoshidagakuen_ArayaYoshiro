//=============================================================================
//
// リザルト処理 [result.h]
// Author :		荒谷由朗
//
//=============================================================================
#include "result.h"
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
CResult::CResult()
{

}

//=============================================================================
//　デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
//　初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	// 背景の生成
	CBg::Load();
	CBg::Create();

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM003);

	return S_OK;
}

//=============================================================================
//　終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CBg::Unload();
	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
//　更新処理
//=============================================================================
void CResult::Update(void)
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

	// ジョイパッドの状態更新
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}