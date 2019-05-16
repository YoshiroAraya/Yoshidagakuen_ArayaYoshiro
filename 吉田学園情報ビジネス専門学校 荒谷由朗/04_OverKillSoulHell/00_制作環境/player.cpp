//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "fade.h"
#include "barrier.h"
#include "mp.h"
#include "pair.h"
#include "sound.h"

LPDIRECT3DTEXTURE9			CPlayer::m_pTexture = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CPlayer::CPlayer():CScene2D(3)
{
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_Life = MAX_LIFE;

	m_mode = CManager::GetMode();
	switch (m_mode)
	{
	case CManager::MODE_TUTORIAL:
		m_Mp = 200;
		break;
	case CManager::MODE_GAME:
		m_Mp = 0;
		break;
	}

	m_StatusType = PLAYER_STATUSTYPE_NORMAL;
	m_BuletType = PLAYER_BULLETTYPE_SLASH;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCount = NULL;
	CManager::GetPlayer() = this;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer = NULL;

	pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}

HRESULT CPlayer::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	m_fWidth = 50;
	m_fHeight = 50;
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_PLAYER);
	CScene2D::SetPosition(D3DXVECTOR3(100.0f, SCREEN_HEIGHT / 2, 0.0f), m_fWidth, m_fHeight);
	CScene2D::SetCol(m_col);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
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

	m_nCount++;
	m_nSkillCount++;

	if (m_StatusType != PLAYER_STATUSTYPE_DEAD)
	{
		m_pos = CScene2D::GetPosition();

		if (pKey != NULL)
		{
			if (pKey->GetPress(DIK_SPACE) == true ||
				state.Gamepad.wButtons & XINPUT_GAMEPAD_A && abConect[0] == true)
			{
				CSound *pSound = CManager::GetSound();
				switch (m_BuletType)
				{
				case PLAYER_BULLETTYPE_SLASH:
					if (m_nCount > 20)
					{
						CBullet::Create(m_pos + D3DXVECTOR3(70.0f, 0.0f, 0.0f), 50, 50, CBullet::BULLETTYPE_SLASH);
						m_nCount = 0;
						pSound->PlaySound(CSound::SOUND_LABEL_PLAYER_BULLET);
					}
					break;
				case PLAYER_BULLETTYPE_POISON:
					if (m_nCount > 45)
					{
						CBullet::Create(m_pos + D3DXVECTOR3(70.0f, 0.0f, 0.0f), 50, 50, CBullet::BULLETTYPE_POISON);
						m_nCount = 0;
						pSound->PlaySound(CSound::SOUND_LABEL_PLAYER_BULLET);
					}
					break;
				case PLAYER_BULLETTYPE_FLAME:
					if (m_nCount > 30)
					{
						CBullet::Create(m_pos + D3DXVECTOR3(70.0f, 0.0f, 0.0f), 30, 30, CBullet::BULLETTYPE_FLAME);
						m_nCount = 0;
						pSound->PlaySound(CSound::SOUND_LABEL_PLAYER_BULLET);
					}
					break;
				case PLAYER_BULLETTYPE_WIND:
					if (m_nCount > 10)
					{
						CBullet::Create(m_pos + D3DXVECTOR3(70.0f, 0.0f, 0.0f), 50, 50, CBullet::BULLETTYPE_WIND);
						m_nCount = 0;
						pSound->PlaySound(CSound::SOUND_LABEL_PLAYER_BULLET);
					}
					break;
				}
			}
			if (pKey->GetPress(DIK_W) == true ||
				state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				m_move.y -= 3;
			}
			else if (pKey->GetPress(DIK_S) == true ||
				state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				m_move.y += 3;
			}
			if (pKey->GetPress(DIK_A) == true ||
				state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				m_move.x -= 3;
			}
			else if (pKey->GetPress(DIK_D) == true ||
				state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
			{
				m_move.x += 3;
			}
			if (pKey->GetTrigger(DIK_B) == true ||
				state.Gamepad.wButtons & XINPUT_GAMEPAD_X && abConect[0] == true)
			{
				if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
				{
					CSound *pSound = CManager::GetSound();
					int nSkillNum = CMP::GetNumber();

					if (m_nSkillCount > 20)
					{
						if (nSkillNum == 0)
						{
							if (m_Mp >= 1)
							{
								MpAbsorption(-1);
								CBullet::Create(m_pos + D3DXVECTOR3(70.0f, -50.0f, 0.0f), 50, 50, CBullet::BULLETTYPE_MP_HOMING);
								pSound->PlaySound(CSound::SOUND_LABEL_SKILL);
							}
						}
						else if (nSkillNum == 1)
						{
							if (m_Mp >= 5)
							{
								MpAbsorption(-5);
								CPair::Create(m_pos, 50, 50);
								pSound->PlaySound(CSound::SOUND_LABEL_SKILL);
							}
						}
						else if (nSkillNum == 2)
						{
							if (m_Mp >= 10)
							{
								MpAbsorption(-10);
								SetStatusType(PLAYER_STATUSTYPE_MP_BARRIER);
								CBarrier::Create(m_pos);
								pSound->PlaySound(CSound::SOUND_LABEL_SKILL);
							}
						}
						else if (nSkillNum == 3)
						{
							if (m_Mp >= 20)
							{
								MpAbsorption(-20);
								Recovery(20);
								pSound->PlaySound(CSound::SOUND_LABEL_SKILL);
							}
						}
						m_nSkillCount = 0;
					}
				}
				apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
			}

			//枠外に出た場合
			if (m_pos.y <= 0 + m_fHeight)
			{	//上
				m_pos.y = 0 + m_fHeight;
			}
			if (m_pos.y >= SCREEN_HEIGHT - m_fHeight)
			{	//下
				m_pos.y = SCREEN_HEIGHT - m_fHeight;
			}
			if (m_pos.x - m_fWidth < 0)
			{	//左から出たら左に戻る
				m_pos.x = m_fWidth;
			}
			if (m_pos.x + m_fWidth > SCREEN_WIDTH)
			{	//右から出たら右に戻る
				m_pos.x = SCREEN_WIDTH - m_fWidth;
			}

			//位置更新
			m_pos.x += m_move.x;
			m_pos.y += m_move.y;

			//減速
			m_move.x += (0.0f - m_move.x) * 0.25f;
			m_move.y += (0.0f - m_move.y) * 0.25f;
		}
		CScene2D::SetPosition(m_pos, m_fWidth, m_fHeight);
	}

	if (m_StatusType == PLAYER_STATUSTYPE_DAMAGE)
	{
		m_nCntDamage++;
		if (m_nCntDamage < 30)
		{
			m_GamageCol -= 0.045f;

			if (m_GamageCol < 0.4f)
			{
				m_GamageCol = 1.0f;
			}
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_GamageCol));
		}
		else
		{
			m_nCntDamage = 0;
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetStatusType(PLAYER_STATUSTYPE_NORMAL);
		}
	}
	if (m_StatusType == PLAYER_STATUSTYPE_MP_BARRIER)
	{
		if (m_GamageCol < 1.0f)
		{
			CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	if (m_Life <= 0)
	{// 死亡
		CManager::GetPlayer() = NULL;
		CManager::SetResult(CManager::GAMERESULT_LOSE);
		SetStatusType(PLAYER_STATUSTYPE_DEAD);
		Uninit();
		if (fade != CFade::FADE_OUT)
		{
			//モード設定
			CFade::SetFade(CManager::MODE_RESULT);
		}
	}

	m_mode = CManager::GetMode();
	switch (m_mode)
	{
	case CManager::MODE_TUTORIAL:
		if ((m_nCount % 10) == 0)
		{
			MpAbsorption(1);
		}
		break;
	}


	// ジョイパッドの状態更新
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CPlayer::HitPlayer(int nDamage)
{
	if (m_StatusType != PLAYER_STATUSTYPE_MP_BARRIER)
	{
		m_Life -= nDamage;

		if (m_Life <= 0)
		{// 爆発
			for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
			{
				for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
				{
					CScene *pScene;
					pScene = CScene::GetScene(nCntPri, nCntScene);

					if (pScene != NULL)
					{
						// オブジェクトの種類を取得
						CScene::OBJTYPE objtype;
						objtype = pScene->GetObjType();

						if (objtype == OBJTYPE_BULLET)
						{
							CExplosion::Create(m_pos, 30, 30, CExplosion::EXPLOSIONTYPE_ENEMY);
							CSound *pSound = CManager::GetSound();
							pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
						}
					}
				}
			}
			SetStatusType(PLAYER_STATUSTYPE_DEAD);
		}
		else
		{
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			SetStatusType(PLAYER_STATUSTYPE_DAMAGE);
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYER_DAMEGE);
		}
	}
}

void CPlayer::Recovery(int nRecovery)
{
	m_Life += nRecovery;
	if (m_Life >= MAX_LIFE)
	{
		m_Life = MAX_LIFE;
	}
}

void CPlayer::MpAbsorption(int nAbsorption)
{
	m_Mp += nAbsorption;
	if (m_Mp >= MAX_MP)
	{
		m_Mp = MAX_MP;
	}
}

int CPlayer::GetPlayerLife(void)
{
	return m_Life;
}

int CPlayer::GetPlayerMp(void)
{
	return m_Mp;
}

void CPlayer::SetStatusType(PLAYER_STATUSTYPE statustype)
{
	m_StatusType = statustype;
}

CPlayer::PLAYER_STATUSTYPE CPlayer::GetStatusType(void)
{
	return m_StatusType;
}

void CPlayer::SetBulletType(PLAYER_BULLETTYPE bullettype)
{
	m_BuletType = bullettype;
}

CPlayer::PLAYER_BULLETTYPE CPlayer::GetBulletType(void)
{
	return m_BuletType;
}
