//=============================================================================
//
// ソウル処理 [soul.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "soul.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9		CSoul::m_pTexture[MAX_SOULTEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CSoul::CSoul() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSoul::~CSoul()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSoul *CSoul::Create(D3DXVECTOR3 pos, float width, float height)
{
	CSoul *pItem = NULL;

	pItem = new CSoul;
	pItem->Init(pos, width, height);
	pItem->BindTexture(m_pTexture[0]);

	return pItem;
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CSoul::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, SOUL_TEXTURENAME00, &m_pTexture[0]);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CSoul::Unload(void)
{
	// テクスチャの破棄
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_SOULTEX; nCntEnemyTex++)
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
HRESULT CSoul::Init(D3DXVECTOR3 pos, float width, float height)
{
	srand((unsigned int)time(0));		// ランダム関数

	// 各データの代入
	m_pos		= pos;
	m_fWidth	= width;
	m_fHeight	= height;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_SOUL);
	CScene2D::SetPosition(pos, width, height);
	CScene2D::SetTexture(0, 1, 1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSoul::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSoul::Update(void)
{
	CPlayer		*pPlayer	= CManager::GetPlayer();		// プレイヤーの取得
	D3DXVECTOR3 pos			= CScene2D::GetPosition();		// 座標の取得

	m_GaugePos = D3DXVECTOR3(60.0f, 60.0f, 0.0f);

	m_fAngle = atan2f(m_GaugePos.x - pos.x, m_GaugePos.y - pos.y);
	m_move.x += sinf(m_fAngle) * 0.25f;
	m_move.y += cosf(m_fAngle) * 0.25f;

	// 位置更新
	pos.x += m_move.x;
	pos.y += m_move.y;

	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);

	bool bOnOff = false;

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

				if (objtype == OBJTYPE_GAUGE0)
				{//	敵の当たり判定
					// エネミーの座標を取得
					if (m_GaugePos.x + 30.0f > pos.x && pos.x > m_GaugePos.x - 30.0f
						&& m_GaugePos.y + 30.0f > pos.y && pos.y > m_GaugePos.y - 30.0f && bOnOff == false)
					{	//当り判定
						if (pPlayer != NULL)
						{
							pPlayer->MpAbsorption(rand() % 20 + 1);
							Uninit();
							bOnOff = true;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CSoul::Draw(void)
{
	CScene2D::Draw();
}