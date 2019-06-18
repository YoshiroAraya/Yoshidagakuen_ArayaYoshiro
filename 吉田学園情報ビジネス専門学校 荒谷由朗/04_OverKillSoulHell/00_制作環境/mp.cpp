//=============================================================================
//
// スキルアイコン処理 [mp.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "scene2D.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "mp.h"
#include "player.h"
#include "mpicon.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CMPIcon			*CMP::m_apMPIcon[MAX_SKILL] = {};
D3DXVECTOR3		CMP::m_pos					= {};
int				CMP::m_nNumSelect			= NULL;
int				CMP::m_nNumSelectPast		= NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CMP::CMP() : CScene(1)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMP::~CMP()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CMP *CMP::Create(D3DXVECTOR3 pos)
{
	CMP *pMP = NULL;

	// データの代入
	m_pos = pos;

	pMP = new CMP;
	pMP->Init();

	return pMP;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMP::Init(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		m_apMPIcon[nCntSkill] = new CMPIcon; // ←ここでCreateされている
		m_apMPIcon[nCntSkill]->Init(D3DXVECTOR3(m_pos.x - (60.0f * nCntSkill), m_pos.y, m_pos.z), nCntSkill);
		SetObjType(CScene::OBJTYPE_MPICON);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMP::Uninit(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		m_apMPIcon[nCntSkill]->Uninit();
		m_apMPIcon[nCntSkill] = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMP::Update(void)
{
	CInputKeyboard	*pKey		= CManager::GetInputKeyboard();		// 入力情報の取得
	CPlayer			*pPlayer	= CManager::GetPlayer();			// プレイヤーの取得

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


	if (pPlayer != NULL)
	{
		int nMpNow = pPlayer->GetPlayerMp();

		if (nMpNow >= 1)
		{
			m_apMPIcon[0]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
		else
		{
			m_apMPIcon[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (nMpNow >= 5)
		{
			m_apMPIcon[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apMPIcon[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (nMpNow >= 10)
		{
			m_apMPIcon[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apMPIcon[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (nMpNow >= 20)
		{
			m_apMPIcon[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apMPIcon[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene = CScene::GetScene(nCntPri, nCntScene);

			if (pScene != NULL)
			{
				// オブジェクトの種類を取得
				CScene::OBJTYPE objtype;
				objtype = pScene->GetObjType();

				if (objtype == OBJTYPE_BULLETICON)
				{//	敵の当たり判定
					// エネミーの座標を取得
					CScene2D *pScene2D = ((CScene2D*)pScene);
					if (pScene2D != NULL)
					{
						if (pKey != NULL)
						{
							if (pKey->GetTrigger(DIK_LEFT) == true ||
								state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && abConect[0] == true)
							{
								if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
								{
									m_nNumSelectPast	= m_nNumSelect;
									m_nNumSelect		= (m_nNumSelect + 1) % 4;
									CSound *pSound		= CManager::GetSound();
									pSound->PlaySound(CSound::SOUND_LABEL_SKILL_SELECT);
								}
								apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
							}

							if (pKey->GetTrigger(DIK_RIGHT) == true ||
								state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && abConect[0] == true)
							{
								if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
								{
									m_nNumSelectPast	= m_nNumSelect;
									m_nNumSelect		= (m_nNumSelect + 3) % 4;
									CSound *pSound		= CManager::GetSound();
									pSound->PlaySound(CSound::SOUND_LABEL_SKILL_SELECT);
								}
								apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
							}

						}
					}
					for (int nCntNumber = 0; nCntNumber < 4; nCntNumber++)
					{
						if (nCntNumber == m_nNumSelect)
						{
							D3DXVECTOR3 posnow = m_apMPIcon[nCntNumber]->GetPos();
							posnow += D3DXVECTOR3(0.0f, 60.0f, 0.0f);
							m_apMPIcon[nCntNumber]->SetPos(posnow);
						}
						else if (nCntNumber == m_nNumSelectPast)
						{
							D3DXVECTOR3 posnow = m_apMPIcon[m_nNumSelectPast]->GetPos();
							m_apMPIcon[m_nNumSelectPast]->SetPos(posnow);
						}
					}
				}
			}
		}
	}
	// ジョイパッドの状態更新
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}

//=============================================================================
// 描画処理
//=============================================================================
void CMP::Draw(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		m_apMPIcon[nCntSkill]->Draw();
	}
}

//=============================================================================
// スキルアイコン情報の取得
//=============================================================================
int CMP::GetNumber(void)
{
	return m_nNumSelect;
}