//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "tutorial.h"
#include "bg.h"
#include "player.h"
#include "bullet.h"
#include "bulleticon.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "gauge.h"
#include "item.h"
#include "barrier.h"
#include "mp.h"
#include "mpicon.h"
#include "pair.h"
#include "description.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CPlayer		*CTutorial::m_pPlayer = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	m_pPlayer = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	// 背景の生成
	CBg::Load();
	CBg::Create();

	// 説明画面の生成
	CDescription::Load();
	CDescription::Create();

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

	// バリアの生成
	CBarrier::Load();

	// 弾の生成
	CBullet::Load();

	// サウンドの再生
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//=============================================================================
//　終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// 各終了処理
	CBg::Unload();				// 背景
	CDescription::Unload();		// 説明画面
	m_pPlayer->Unload();		// プレイヤー
	CPair::Unload();			// ペア
	CGauge::Unload();			// ゲージ
	CMPIcon::Unload();			// MPアイコン
	CBulletIcon::Unload();		// 弾アイコン
	CBarrier::Unload();			// バリア
	CBullet::Unload();			// 弾

	// サウンドの停止
	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}