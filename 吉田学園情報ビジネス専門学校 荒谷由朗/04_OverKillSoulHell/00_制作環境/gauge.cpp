//=============================================================================
//
// ゲージ処理 [gauge.h]
// Author :		荒谷由朗
//
//=============================================================================
#include "gauge.h"
#include "scene2D.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9			CGauge::m_pTexture[GAUGE_MAX_TEXTURE] = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CGauge::CGauge() :CScene(0)
{
	m_fWidth		= NULL;
	m_fHeight		= NULL;
	m_nCounterAnim	= NULL;
	m_nPatternAnim	= NULL;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CGauge::~CGauge()
{

}

CGauge *CGauge::Create(void)
{
	CGauge *pBg = NULL;

	pBg = new CGauge;
	pBg->Init();

	return pBg;
}

HRESULT CGauge::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, GAUGE_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, GAUGE_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

void CGauge::Unload(void)
{
	// テクスチャの破棄
	for (int nCntGauge = 0; nCntGauge < GAUGE_MAX_TEXTURE; nCntGauge++)
	{
		if (m_pTexture[nCntGauge] != NULL)
		{
			m_pTexture[nCntGauge]->Release();
			m_pTexture[nCntGauge] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGauge::Init(void)
{
	m_fWidth = 30;
	m_fHeight = 30;

	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init();
	m_apScene2D[0]->BindTexture(m_pTexture[0]);
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(60, 60, 0.0f), m_fWidth, m_fHeight);
	m_apScene2D[0]->SetObjType(CScene::OBJTYPE_GAUGE0);		// オブジェクトの種類を設定

	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init();
	m_apScene2D[1]->BindTexture(m_pTexture[1]);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(60, 60, 0.0f), m_fWidth - 5, m_fHeight - 5);
	m_apScene2D[1]->SetObjType(CScene::OBJTYPE_GAUGE1);		// オブジェクトの種類を設定

	for (int nCntScore = 0; nCntScore < MAX_CIRCLE; nCntScore++)
	{
		m_apCircle[nCntScore] = new CCircle; // ←ここでCreateされている
		if (nCntScore == 0)
		{
			m_apCircle[nCntScore]->Init(D3DXVECTOR3(60, 60, 0.0f), 40.0f + (14.0f * nCntScore), 14.0f,CCircle::CIRCLETYPE_HP);
		}
		else if (nCntScore == 1)
		{
			m_apCircle[nCntScore]->Init(D3DXVECTOR3(60, 60, 0.0f), 40.0f + (12.0f * nCntScore), 12.0f, CCircle::CIRCLETYPE_MP);
		}
		SetObjType(CScene::OBJTYPE_CIRCLE);		// オブジェクトの種類を設定
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGauge::Uninit(void)
{
	for (int nCntGauge = 0; nCntGauge < GAUGE_MAX_2DPOLIGON; nCntGauge++)
	{
		m_apScene2D[nCntGauge]->Uninit();
		m_apScene2D[nCntGauge] = NULL;
	}

	for (int nCntScore = 0; nCntScore < MAX_CIRCLE; nCntScore++)
	{
		m_apCircle[nCntScore]->Uninit();
		m_apCircle[nCntScore] = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGauge::Update(void)
{
	m_nCounterAnim++;

	if (m_nCounterAnim % 3 == 0)
	{
		m_nPatternAnim++;
		m_apScene2D[0]->SetRot(-m_nPatternAnim/50, m_fWidth, m_fHeight);
		m_apScene2D[1]->SetRot(m_nPatternAnim/50, m_fWidth - 5, m_fHeight - 5);
	}

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
				if (objtype == OBJTYPE_CIRCLE)
				{//	敵の当たり判定
					CCircle *pCircle = ((CCircle*)pScene);
					pCircle->Update();
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGauge::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_CIRCLE; nCntScore++)
	{
		m_apCircle[nCntScore]->Draw();
	}
}