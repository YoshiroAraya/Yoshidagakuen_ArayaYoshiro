//=============================================================================
//
// バリア処理 [barrier.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "barrier.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9			CBarrier::m_pTexture = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CBarrier::CBarrier() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
}

//=============================================================================
//　デストラクタ
//=============================================================================
CBarrier::~CBarrier()
{
}

//=============================================================================
//　生成処理
//=============================================================================
CBarrier *CBarrier::Create(D3DXVECTOR3 pos)
{
	CBarrier *pBarrier = NULL;

	pBarrier = new CBarrier;
	pBarrier->Init(pos);

	return pBarrier;
}

//=============================================================================
//　ロード
//=============================================================================
HRESULT CBarrier::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BARRIER_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

//=============================================================================
//　アンロード
//=============================================================================
void CBarrier::Unload(void)
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
HRESULT CBarrier::Init(D3DXVECTOR3 pos)
{
	m_fWidth	= 50;
	m_fHeight	= 50;
	CScene2D::Init();									// 初期化処理
	SetObjType				(CScene::OBJTYPE_BARRIER);	// オブジェクトタイプの設定
	CScene2D::SetPosition	(pos, m_fWidth, m_fHeight);	// 座標の設定
	CScene2D::SetCol		(m_col);					// 色の設定
	BindTexture				(m_pTexture);				// テキストの設定
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBarrier::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBarrier::Update(void)
{
	m_nCntFrame++;	// カウンターの加算

	CPlayer *pPlayer = CManager::GetPlayer();	// 情報の取得
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();			// 座標の取得
		CScene2D::SetPosition(posPlayer, m_fWidth, m_fHeight);	// プレイヤーと同じ座標に

		if ((m_nCntFrame % 600) == 0)
		{// 時間が切れたらバリアを消す
			pPlayer->SetStatusType(CPlayer::PLAYER_STATUSTYPE_NORMAL);
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBarrier::Draw(void)
{
	CScene2D::Draw();
}