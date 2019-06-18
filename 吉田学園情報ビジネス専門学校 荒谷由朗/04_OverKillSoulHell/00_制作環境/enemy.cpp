//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "enemy.h"
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
LPDIRECT3DTEXTURE9		CEnemy::m_pTexture[MAX_ENEMYTEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_life		= 10;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, float width, float height, int texID)
{
	CEnemy *pEnemy = NULL;

	pEnemy = new CEnemy;
	pEnemy->Init(pos, width, height, texID);
	pEnemy->BindTexture(m_pTexture[texID]);

	return pEnemy;
}

//=============================================================================
//　ロード
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CEnemy::Unload(void)
{
	// テクスチャの破棄
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_ENEMYTEX; nCntEnemyTex++)
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
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float width, float height, int texID)
{
	srand((unsigned int)time(0));	// ランダム関数

	// 各データの代入
	m_pos		= pos;
	m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fWidth	= width;
	m_fHeight	= height;
	m_TypeNum	= texID;
	m_life		= (rand() % 10 + 2);
	m_Statse	= ENEMYSTATSE_NONE;
	m_nBlink	= false;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_ENEMY);				// オブジェクトタイプの設定
	CScene2D::SetPosition(pos, width, height);		// 座標の設定
	CScene2D::SetTexture(m_nPatternAnim, 1, 1);		// テクスチャ座標の設定
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = CScene2D::GetVtxBuff();	// バーテックスバッファの取得
	CFade::FADE				fade	= CFade::GetFade();			// フェードの取得
	D3DXVECTOR3				pos		= CScene2D::GetPosition();	// 座標の取得

	// カウンターの加算
	m_nCount++;
	m_nCounterAnim++;

	if ((m_nCount % (rand() % 180 + 50)) == 0)
	{// 攻撃頻度
		CPlayer *pPlayer = CManager::GetPlayer();	// プレイヤーの取得
		if (pPlayer != NULL)
		{
			CPlayer::PLAYER_STATUSTYPE playerstatus = pPlayer->GetStatusType();		// プレイヤー状態の取得

			if (playerstatus != CPlayer::PLAYER_STATUSTYPE_DEAD)
			{// プレイヤーが死んでいなかったら
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
				m_move.y += MAX_ENEMYSPEED;
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
				m_move.y -= MAX_ENEMYSPEED;
			}
			if ((m_nCount % 80) == 0)
			{
				m_bRoundtrip = false;
			}
		}

		//減速
		m_move.y += (0.0f - m_move.y) * 0.25f;

		//位置更新
		pos.y += m_move.y;

		CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
	}

	m_move.x -= MAX_ENEMYSPEED;

	//減速
	m_move.x += (0.0f - m_move.x) * 0.25f;

	//位置更新
	pos.x += m_move.x;

	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);

	if (m_Statse == ENEMYSTATSE_DAMEGE)
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
				m_Statse	= ENEMYSTATSE_NONE;
			}
		}
		CScene2D::SetCol(m_col);
		m_nCntBlink++;
	}

	if (m_life <= 0)
	{
		Uninit();
		CScore::AddScore(1);				// スコアの加算
		CSoul::Create(pos, 40.0f, 30.0f);	// ソウルの生成
		if (rand() % 5 == 0)
		{
			CItem::Create(pos, 30, 30, rand() % 4);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CEnemy::HitEnemy(int nDamage, CBullet::BULLETTYPE bullettype)
{
	m_life -= nDamage;		// ライフの減算

	if (m_life <= 0)
	{// 爆発
		if (bullettype != CBullet::BULLETTYPE_ENEMY)
		{
			D3DXVECTOR3 pos = CScene2D::GetPosition();		// 座標の取得
			switch (bullettype)
			{// タイプごとに生成
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
		m_Statse = ENEMYSTATSE_DAMEGE;		// 状態の更新
		// サウンドの再生
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_ENEMY_DAMEGE);
	}
}