//=============================================================================
//
// アイテム処理 [item.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "player.h"
#include "bulleticon.h"

LPDIRECT3DTEXTURE9		CItem::m_pTexture[MAX_ITEMTEX] = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CItem::CItem() :CScene2D(3)
{
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_Type = ITEMTYPE_SLASH;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CItem::~CItem()
{

}

CItem *CItem::Create(D3DXVECTOR3 pos, float width, float height, int texID)
{
	CItem *pItem = NULL;

	pItem = new CItem;
	pItem->Init(pos, width, height, texID);
	pItem->BindTexture(m_pTexture[0]);

	return pItem;
}

HRESULT CItem::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURENAME00, &m_pTexture[0]);

	return S_OK;
}

void CItem::Unload(void)
{
	// テクスチャの破棄
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_ITEMTEX; nCntEnemyTex++)
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
HRESULT CItem::Init(D3DXVECTOR3 pos, float width, float height, int texID)
{
	m_pos = pos;
	m_fWidth = width;
	m_fHeight = height;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_ITEM);
	CScene2D::SetPosition(pos, width, height);
	CScene2D::SetTexture(texID, 4, 1);

	switch (texID)
	{
	case 0:
		m_Type = ITEMTYPE_SLASH;
		break;
	case 1:
		m_Type = ITEMTYPE_FLAME;
		break;
	case 2:
		m_Type = ITEMTYPE_POISON;
		break;
	case 3:
		m_Type = ITEMTYPE_WIND;
		break;
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();
	float 	fWidth, fHeight;

	m_nCount++;

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

				if (objtype == OBJTYPE_BULLETICON)
				{//	敵の当たり判定
				 // エネミーの座標を取得
					CPlayer *pPlayer = CManager::GetPlayer();
					if (pPlayer != NULL)
					{
						D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
						fWidth = pPlayer->GetWidth();
						fHeight = pPlayer->GetHeight();

						if (posPlayer.x + fWidth > pos.x && pos.x > posPlayer.x - fWidth
							&& posPlayer.y + fHeight > pos.y && pos.y > posPlayer.y - fHeight)
						{	//当り判定
							CBulletIcon *pBulletIcon = ((CBulletIcon*)pScene);
							switch (m_Type)
							{
							case ITEMTYPE_SLASH:
								pPlayer->SetBulletType(CPlayer::PLAYER_BULLETTYPE_SLASH);
								pBulletIcon->SetIconType(CBulletIcon::ICONTYPE_SLASH);
								break;
							case ITEMTYPE_POISON:
								pPlayer->SetBulletType(CPlayer::PLAYER_BULLETTYPE_POISON);
								pBulletIcon->SetIconType(CBulletIcon::ICONTYPE_POISON);
								break;
							case ITEMTYPE_FLAME:
								pPlayer->SetBulletType(CPlayer::PLAYER_BULLETTYPE_FLAME);
								pBulletIcon->SetIconType(CBulletIcon::ICONTYPE_FLAME);
								break;
							case ITEMTYPE_WIND:
								pPlayer->SetBulletType(CPlayer::PLAYER_BULLETTYPE_WIND);
								pBulletIcon->SetIconType(CBulletIcon::ICONTYPE_WIND);
								break;
							}

							Uninit();
						}
					}
				}
			}
		}
	}
	if (m_nCount >= 300)
	{
		m_nDeleteCount++;

		m_DeleteCol -= (0.001f + ((float)m_nDeleteCount * 0.0005f));

		if (m_DeleteCol < 0.3f)
		{
			m_DeleteCol = 1.0f;
		}

		// 頂点カラー設定
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_DeleteCol));

		if ((m_nCount % 550) == 0)
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}