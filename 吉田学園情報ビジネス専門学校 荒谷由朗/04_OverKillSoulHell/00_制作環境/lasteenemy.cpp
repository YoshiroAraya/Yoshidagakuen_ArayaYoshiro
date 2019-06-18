//=============================================================================
//
// 最終エネミー処理 [lasteenemy.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "lasteenemy.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "score.h"
#include "fade.h"
#include "explosion.h"
#include "player.h"
#include "soul.h"
#include "item.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9		CLastEnemy::m_pTexture[MAX_LASTENEMYTEX] = {};
int						CLastEnemy::m_nDed = NULL;

//=============================================================================
//　コンストラクタ
//=============================================================================
CLastEnemy::CLastEnemy() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_life		= 10;
	m_nDed		= 0;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CLastEnemy::~CLastEnemy()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CLastEnemy *CLastEnemy::Create(D3DXVECTOR3 pos, float width, float height, int texID)
{
	CLastEnemy *pEnemy = NULL;

	pEnemy = new CLastEnemy;
	pEnemy->Init(pos, width, height, texID);
	pEnemy->BindTexture(m_pTexture[texID]);

	return pEnemy;
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CLastEnemy::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, LASTENEMY_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, LASTENEMY_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CLastEnemy::Unload(void)
{
	// テクスチャの破棄
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_LASTENEMYTEX; nCntEnemyTex++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCntEnemyTex]->Release();
			m_pTexture[nCntEnemyTex] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLastEnemy::Init(D3DXVECTOR3 pos, float width, float height, int texID)
{
	srand((unsigned int)time(0));		// ランダム関数

	// 各データの代入
	m_pos		= pos;
	m_fWidth	= width;
	m_fHeight	= height;
	m_TypeNum	= texID;
	m_life		= (rand() % 10 + 2);
	m_Statse	= LASTENEMYSTATSE_NONE;
	m_nBlink	= false;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_ENEMY);
	CScene2D::SetPosition(pos, width, height);
	CScene2D::SetTexture(m_nPatternAnim, 1, 1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLastEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLastEnemy::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = CScene2D::GetVtxBuff();		// バーテックスバッファの取得
	CFade::FADE				fade	= CFade::GetFade();				// フェードの取得
	D3DXVECTOR3				pos		= CScene2D::GetPosition();		// 座標の取得

	m_nCount++;
	m_nCounterAnim++;

	if ((m_nCount % (rand() % 180 + 50)) == 0)
	{
		CPlayer *pPlayer = CManager::GetPlayer();
		if (pPlayer != NULL)
		{
			CPlayer::PLAYER_STATUSTYPE playerstatus = pPlayer->GetStatusType();

			if (playerstatus != CPlayer::PLAYER_STATUSTYPE_DEAD)
			{
				CBullet::Create(pos + D3DXVECTOR3(-70.0f, 0.0f, 0.0f), 50, 40, CBullet::BULLETTYPE_ENEMY);
			}
		}
	}

	if (m_TypeNum == 1)
	{
		if (m_bRoundtrip == false)
		{
			if (pos.y < SCREEN_HEIGHT)
			{
				m_move.y += MAX_LASTENEMYSPEED;
			}
			if ((m_nCount % 80) == 0)
			{
				m_bRoundtrip = true;
			}
		}
		else if (m_bRoundtrip == true)
		{
			if (pos.y > 0)
			{
				m_move.y -= MAX_LASTENEMYSPEED;
			}
			if ((m_nCount % 80) == 0)
			{
				m_bRoundtrip = false;
			}
		}

		// 減速
		m_move.y += (0.0f - m_move.y) * 0.25f;

		// 位置更新
		pos.y += m_move.y;

		CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
	}

	m_move.x -= MAX_LASTENEMYSPEED;

	// 減速
	m_move.x += (0.0f - m_move.x) * 0.25f;

	// 位置更新
	pos.x += m_move.x;

	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);

	if (m_Statse == LASTENEMYSTATSE_DAMEGE)
	{// ダメージ状態
		if (m_nBlink == false)
		{//	カラーを赤く
			m_col		= D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f);
			m_nBlink	= true;
		}
		else if (m_nBlink == true)
		{//	カラーを戻す
			if (m_nCntBlink > 5)
			{
				m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_nCntBlink = 0;
				m_nBlink	= false;
				m_Statse	= LASTENEMYSTATSE_NONE;
			}
		}
		CScene2D::SetCol(m_col);
		m_nCntBlink++;
	}

	if (m_life <= 0)
	{
		Uninit();
		CScore::AddScore(1);
		CSoul::Create(pos, 40.0f, 30.0f);
		if (rand() % 5 == 0)
		{
			CItem::Create(pos, 30, 30, rand() % 4);
		}
		m_nDed++;
		if (m_nDed >= 8)
		{
			if (fade != CFade::FADE_OUT)
			{
				//モード設定
				CFade::SetFade(CManager::MODE_RESULT);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLastEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CLastEnemy::HitEnemy(int nDamage, CBullet::BULLETTYPE bullettype)
{
	m_life -= nDamage;

	if (m_life <= 0)
	{// 爆発
		if (bullettype != CBullet::BULLETTYPE_ENEMY)
		{
			D3DXVECTOR3 pos = CScene2D::GetPosition();		// 座標の取得
			switch (bullettype)
			{
			case CBullet::BULLETTYPE_SLASH:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_SLASH);
				break;
			case CBullet::BULLETTYPE_POISON:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_POISON);
				break;
			case CBullet::BULLETTYPE_FLAME:
				CExplosion::Create(pos, 30, 80, CExplosion::EXPLOSIONTYPE_FLAME);
				break;
			case CBullet::BULLETTYPE_WIND:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_WIND);
				break;
			case CBullet::BULLETTYPE_ENEMY:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_ENEMY);
				break;
			case CBullet::BULLETTYPE_MP_HOMING:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_ENEMY);
				break;
			}
			// サウンドの再生
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
			return;		// ←１回だけ通る
		}
	}
	else
	{
		m_Statse = LASTENEMYSTATSE_DAMEGE;
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_ENEMY_DAMEGE);
	}
}