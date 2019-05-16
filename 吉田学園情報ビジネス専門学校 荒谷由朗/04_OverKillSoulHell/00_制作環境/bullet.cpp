//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"ccvl
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"

LPDIRECT3DTEXTURE9			CBullet::m_pTexture[MAX_BULLETTEXTURE] = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CBullet::CBullet():CScene2D(2)
{
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_fAngle = NULL;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

CBullet *CBullet::Create(D3DXVECTOR3 pos, float width, float height, BULLETTYPE Bullettype)
{
	CBullet *pBullet = NULL;


	pBullet = new CBullet;
	pBullet->Init(pos, width, height, Bullettype);
	pBullet->m_BulletType = Bullettype;

	switch (Bullettype)
	{
	case BULLETTYPE_SLASH:
		pBullet->BindTexture(m_pTexture[0]);
		break;
	case BULLETTYPE_POISON:
		pBullet->BindTexture(m_pTexture[1]);
		break;
	case BULLETTYPE_FLAME:
		pBullet->BindTexture(m_pTexture[2]);
		break;
	case BULLETTYPE_WIND:
		pBullet->BindTexture(m_pTexture[3]);
		break;
	case BULLETTYPE_ENEMY:
		pBullet->BindTexture(m_pTexture[4]);
		break;
	case BULLETTYPE_MP_HOMING:
		pBullet->BindTexture(m_pTexture[5]);
		break;
	case BULLETTYPE_MP_PAIR:
		pBullet->BindTexture(m_pTexture[2]);
		break;
	}

	return pBullet;
}

HRESULT CBullet::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME01, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME02, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME03, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME04, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME05, &m_pTexture[5]);

	return S_OK;
}

void CBullet::Unload(void)
{
	// テクスチャの破棄
	for (int nCntBullet = 0;nCntBullet < MAX_BULLETTEXTURE;nCntBullet++)
	{
		if (m_pTexture[nCntBullet] != NULL)
		{
			m_pTexture[nCntBullet]->Release();
			m_pTexture[nCntBullet] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, float width, float height, BULLETTYPE Bullettype)
{
	m_fWidth = width;
	m_fHeight = height;
	m_nCounterAnim = 0;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_BULLET);		// オブジェクトの種類を設定
	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);

	switch (Bullettype)
	{
	case BULLETTYPE_SLASH:
		CScene2D::SetTexture(m_nPatternAnim, 4, 1);
		break;
	case BULLETTYPE_POISON:
		CScene2D::SetTexture(m_nPatternAnim, 5, 2);
		break;
	case BULLETTYPE_FLAME:
		CScene2D::SetTexture(m_nPatternAnim, 5, 1);
		break;
	case BULLETTYPE_WIND:
		CScene2D::SetTexture(m_nPatternAnim, 8, 2);
		break;
	case BULLETTYPE_ENEMY:
		CScene2D::SetTexture(m_nPatternAnim, 1, 1);
		break;
	case BULLETTYPE_MP_HOMING:
		CScene2D::SetTexture(m_nPatternAnim, 1, 1);
		break;
	case BULLETTYPE_MP_PAIR:
		CScene2D::SetTexture(m_nPatternAnim, 5, 1);
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	CPlayer *pPlayer = CManager::GetPlayer();
	if (pPlayer != NULL)
	{
		m_PlayerPos = pPlayer->GetPosition();
	}
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	BULLETTYPE	BulletType = GetBulletType();
	float 	fWidth, fHeight;

	m_nCounterAnim++;

	if ((m_nCounterAnim % 2) == 0)		//アニメーションの速さを変えられる
	{
		m_nPatternAnim = (m_nPatternAnim + 1);

		switch (BulletType)
		{
		case BULLETTYPE_SLASH:
			if (m_nPatternAnim >= 3)
			{
				m_nPatternAnim = 3;
			}
			break;
		case BULLETTYPE_POISON:
			if (m_nPatternAnim > 9)
			{
				m_nPatternAnim = 9;
			}
			break;
		case BULLETTYPE_FLAME:
			if (m_nPatternAnim > 4)
			{
				m_nPatternAnim = 4;
			}
			break;
		case BULLETTYPE_WIND:
			break;
		case BULLETTYPE_ENEMY:
			if (m_nPatternAnim > 0)
			{
				m_nPatternAnim = 0;
			}
			break;
		case BULLETTYPE_MP_HOMING:
			if (m_nPatternAnim > 0)
			{
				m_nPatternAnim = 0;
			}
			break;
		case BULLETTYPE_MP_PAIR:
			if (m_nPatternAnim > 4)
			{
				m_nPatternAnim = 4;
			}
			break;
		}

		switch (BulletType)
		{
		case BULLETTYPE_SLASH:
			CScene2D::SetTexture(m_nPatternAnim, 4, 1);
			break;
		case BULLETTYPE_POISON:
			CScene2D::SetTexture(m_nPatternAnim, 5, 2);
			break;
		case BULLETTYPE_FLAME:
			CScene2D::SetTexture(m_nPatternAnim, 5, 1);
			break;
		case BULLETTYPE_WIND:
			CScene2D::SetTexture(m_nPatternAnim, 8, 2);
			break;
		case BULLETTYPE_ENEMY:
			CScene2D::SetTexture(m_nPatternAnim, 1, 1);
			break;
		case BULLETTYPE_MP_HOMING:
			CScene2D::SetTexture(m_nPatternAnim, 1, 1);
			break;
		case BULLETTYPE_MP_PAIR:
			CScene2D::SetTexture(m_nPatternAnim, 5, 1);
			break;
		}
	}

	if (pos.x < SCREEN_WIDTH && pos.x > 0)
	{
		if (BulletType == BULLETTYPE_ENEMY)
		{
			if (m_nCounterAnim < 25)
			{
				m_fAngle = atan2f(m_PlayerPos.x - pos.x, m_PlayerPos.y - pos.y);
			}

			m_move.x += sinf(m_fAngle) * ENEMY_SPEED;
			m_move.y += cosf(m_fAngle) * ENEMY_SPEED;

			//位置更新
			pos.x += m_move.x;
			pos.y += m_move.y;

			CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
			CScene2D::SetRot(m_fAngle, m_fWidth, m_fHeight);
		}
		else if (BulletType == BULLETTYPE_MP_HOMING)
		{
			m_mode = CManager::GetMode();
			switch (m_mode)
			{
			case CManager::MODE_TUTORIAL:
				m_fAngle = atan2f((pos.x + 10.0f) - pos.x, pos.y - pos.y);

				m_move.x += sinf(m_fAngle) * 0.25f;
				m_move.y += cosf(m_fAngle) * 0.25f;

				//位置更新
				pos.x += m_move.x;
				pos.y += m_move.y;

				CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
				CScene2D::SetRot(m_fAngle, m_fWidth, m_fHeight);
				break;
			case CManager::MODE_GAME:
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

							if (objtype == OBJTYPE_ENEMY)
							{//	敵の当たり判定
							 // エネミーの座標を取得
								CScene2D *pScene2D = ((CScene2D*)pScene);
								D3DXVECTOR3 posEnemy = pScene2D->GetPosition();

								if (pScene2D != NULL && m_nCounterAnim < 25)
								{
									m_fAngle = atan2f(posEnemy.x - pos.x, posEnemy.y - pos.y);
								}
							}
						}
					}
				}

				m_move.x += sinf(m_fAngle) * 0.25f;
				m_move.y += cosf(m_fAngle) * 0.25f;

				//位置更新
				pos.x += m_move.x;
				pos.y += m_move.y;

				CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
				CScene2D::SetRot(m_fAngle, m_fWidth, m_fHeight);
				break;
			}
		}
		else if (BulletType == BULLETTYPE_MP_PAIR)
		{
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

						if (objtype == OBJTYPE_ENEMY)
						{//	敵の当たり判定
						 // エネミーの座標を取得
							CScene2D *pScene2D = ((CScene2D*)pScene);
							D3DXVECTOR3 posEnemy = pScene2D->GetPosition();

							if (pScene2D != NULL && m_nCounterAnim < 42)
							{
								m_fAngle = atan2f(posEnemy.x - pos.x, posEnemy.y - pos.y);
							}
						}
					}
				}
			}

			if (m_nCounterAnim < 10)
			{
				if (m_PlayerPos.y <= SCREEN_HEIGHT / 2)
				{// 上にいるとき
					m_move.x += 0.5f;
					m_move.y += 0.5f;
					//減速
					m_move.x += (0.0f - m_move.x) * PAIR_SPEED;
					m_move.y += (0.0f - m_move.y) * PAIR_SPEED;
				}
				else if (m_PlayerPos.y > SCREEN_HEIGHT / 2)
				{// 下にいるとき
					m_move.x += 0.5f;
					m_move.y -= 0.5f;
					//減速
					m_move.x += (0.0f - m_move.x) * PAIR_SPEED;
					m_move.y += (0.0f - m_move.y) * PAIR_SPEED;
				}
			}
			else if (m_nCounterAnim < 42)
			{

				m_move.x += sinf(m_fAngle) * PAIR_SPEED;
				m_move.y += cosf(m_fAngle) * PAIR_SPEED;
			}

			//位置更新
			pos.x += m_move.x;
			pos.y += m_move.y;

			CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
			CScene2D::SetRot(m_fAngle, m_fWidth, m_fHeight);
		}
		else
		{
			switch (BulletType)
			{
			case BULLETTYPE_SLASH:
				m_move.x += SLASH_SPEED;
				break;
			case BULLETTYPE_POISON:
				m_move.x += POISON_SPEED;
				break;
			case BULLETTYPE_FLAME:
				m_move.x += FLAME_SPEED;
				break;
			case BULLETTYPE_WIND:
				m_move.x += WIND_SPEED;
				break;
			}

			//減速
			m_move.x += (0.0f - m_move.x) * 0.25f;
			m_move.y += (0.0f - m_move.y) * 0.25f;

			//位置更新
			pos.x += m_move.x;
			pos.y += m_move.y;

			CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
		}

		for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
		{// 当たり判定
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{
				CScene *pScene;
				pScene = CScene::GetScene(nCntPri, nCntScene);

				if (pScene != NULL)
				{
					// オブジェクトの種類を取得
					CScene::OBJTYPE objtype;
					objtype = pScene->GetObjType();

					if (objtype == OBJTYPE_ENEMY && BulletType != BULLETTYPE_ENEMY)
					{//	敵の当たり判定
						// エネミーの座標を取得
						CScene2D *pScene2D = ((CScene2D*)pScene);
						D3DXVECTOR3 posEnemy = pScene2D->GetPosition();
						fWidth = pScene2D->GetWidth();
						fHeight = pScene2D->GetHeight();

						if (pScene2D != NULL)
						{
							if (posEnemy.x + fWidth > pos.x && pos.x > posEnemy.x - fWidth
								&& posEnemy.y + fHeight > pos.y && pos.y > posEnemy.y - fHeight)
							{	//当り判定
								CEnemy *pEnemy = ((CEnemy*)pScene);
								switch (BulletType)
								{
								case BULLETTYPE_SLASH:
									pEnemy->HitEnemy(SLASH_POWER, BulletType);
									break;
								case BULLETTYPE_POISON:
									pEnemy->HitEnemy(POISON_POWER, BulletType);
									break;
								case BULLETTYPE_FLAME:
									pEnemy->HitEnemy(FLAME_POWER, BulletType);
									break;
								case BULLETTYPE_WIND:
									pEnemy->HitEnemy(WIND_POWER, BulletType);
									break;
								case BULLETTYPE_MP_HOMING:
									pEnemy->HitEnemy(HOMING_POWER, BulletType);
									break;
								case BULLETTYPE_MP_PAIR:
									pEnemy->HitEnemy(PAIR_POWER, BulletType);
									break;
								}
								Uninit();
								break;
							}
						}
					}
					else if (objtype == OBJTYPE_PLAYER && BulletType == BULLETTYPE_ENEMY)
					{
						CScene2D *pScene2D = ((CScene2D*)pScene);
						D3DXVECTOR3 posPlayer = pScene2D->GetPosition();
						fWidth = pScene2D->GetWidth();
						fHeight = pScene2D->GetHeight();

						if (pScene2D != NULL)
						{
							if (posPlayer.x + fWidth > pos.x && pos.x > posPlayer.x - fWidth
								&& posPlayer.y + fHeight > pos.y && pos.y > posPlayer.y - fHeight)
							{	//当り判定
								CPlayer *pPlayer = ((CPlayer*)pScene);
								pPlayer->HitPlayer(1);
								if (pPlayer != NULL)
								{
									Uninit();
								}
								break;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		Uninit();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// タイプの設定
//=============================================================================
void CBullet::SetBulletType(BULLETTYPE bullettype)
{
	m_BulletType = bullettype;
}

//=============================================================================
// タイプの取得
//=============================================================================
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}
