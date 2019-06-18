//=============================================================================
//
// 弾アイコン処理 [bulleticon.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "bulleticon.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9		CBulletIcon::m_pTexture[MAX_BI_TEX] = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CBulletIcon::CBulletIcon() :CScene(0)
{
	m_Type = ICONTYPE_SLASH;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CBulletIcon::~CBulletIcon()
{
}

//=============================================================================
//　生成処理
//=============================================================================
CBulletIcon *CBulletIcon::Create()
{
	CBulletIcon *pBulletIcon = NULL;

	pBulletIcon = new CBulletIcon;
	pBulletIcon->Init();

	return pBulletIcon;
}

//=============================================================================
//　ロード
//=============================================================================
HRESULT CBulletIcon::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BI_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BI_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

//=============================================================================
//　アンロード
//=============================================================================
void CBulletIcon::Unload(void)
{
	// テクスチャの破棄
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_BI_TEX; nCntEnemyTex++)
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
HRESULT CBulletIcon::Init()
{
	// 背景
	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init();
	m_apScene2D[0]->BindTexture(m_pTexture[0]);
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(640, 60, 0.0f), 30, 30);

	SetObjType(CScene::OBJTYPE_BULLETICON);		// オブジェクトタイプを設定

	// アイコン
	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init();
	m_apScene2D[1]->BindTexture(m_pTexture[1]);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(645, 60, 0.0f), 25, 25);
	m_apScene2D[1]->SetTexture(0,4,1);

	SetObjType(CScene::OBJTYPE_BULLETICON);		// オブジェクトタイプを設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBulletIcon::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_BI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();
		m_apScene2D[nCntBg] = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBulletIcon::Update(void)
{
	switch (m_Type)
	{// タイプごとにテクスチャ座標を設定
	case ICONTYPE_SLASH:
		m_apScene2D[1]->SetTexture(0, 4, 1);
		break;
	case ICONTYPE_POISON:
		m_apScene2D[1]->SetTexture(2, 4, 1);
		break;
	case ICONTYPE_FLAME:
		m_apScene2D[1]->SetTexture(1, 4, 1);
		break;
	case ICONTYPE_WIND:
		m_apScene2D[1]->SetTexture(3, 4, 1);
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBulletIcon::Draw(void)
{
}

//=============================================================================
//　アイコンの設定
//=============================================================================
void CBulletIcon::SetIconType(ICONTYPE icontype)
{
	m_Type = icontype;
}
