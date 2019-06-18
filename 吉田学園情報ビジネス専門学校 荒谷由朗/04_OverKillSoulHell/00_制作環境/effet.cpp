//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
D3DXVECTOR3					CEffect::m_move = {};
LPDIRECT3DTEXTURE9			CEffect::m_pTexture = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect():CScene2D(1)
{
	m_fWidth = NULL;
	m_fHeight = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, float width, float height)
{
	CEffect *pEffect = NULL;

	pEffect = new CEffect;
	pEffect->Init(pos, width, height);
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CEffect::Load(void)
{
	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CEffect::Unload(void)
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
HRESULT CEffect::Init(D3DXVECTOR3 pos, float width, float height)
{
	// 各データの代入
	m_fWidth	= width;
	m_fHeight	= height;

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EFFECT);					// オブジェクトの種類を設定
	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);	// 座標の設定
	CScene2D::SetCol(m_col);							// カラーの設定
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	m_col.a -= 0.05f;

	CScene2D::SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));	// カラーの設定

	if (m_col.a <=  0.0f)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}