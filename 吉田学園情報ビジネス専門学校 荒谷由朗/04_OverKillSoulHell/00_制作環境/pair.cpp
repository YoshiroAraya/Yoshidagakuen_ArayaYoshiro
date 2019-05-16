//=============================================================================
//
// ペア処理 [pair.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "pair.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "explosion.h"
#include "player.h"

LPDIRECT3DTEXTURE9		CPair::m_pTexture[MAX_PAIRTEX] = {};

//=============================================================================
//　コンストラクタ
//=============================================================================
CPair::CPair() :CScene2D(3)
{
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_nPatternAnim = NULL;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CPair::~CPair()
{

}

CPair *CPair::Create(D3DXVECTOR3 pos, float width, float height)
{
	CPair *pEnemy = NULL;

	pEnemy = new CPair;
	pEnemy->Init(pos, width, height);
	pEnemy->BindTexture(m_pTexture[0]);

	return pEnemy;
}

HRESULT CPair::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PAIR_TEXTURENAME00, &m_pTexture[0]);

	return S_OK;
}

void CPair::Unload(void)
{
	// テクスチャの破棄
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_PAIRTEX; nCntEnemyTex++)
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
HRESULT CPair::Init(D3DXVECTOR3 pos, float width, float height)
{
	m_pos = pos;
	m_fWidth = width;
	m_fHeight = height;
	m_DeleteCol = 0.0f;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_PAIR);
	CScene2D::SetPosition(pos, width, height);
	CScene2D::SetTexture(m_nPatternAnim, 11, 3);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPair::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPair::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	m_nCount++;
	m_nCounterAnim++;

	if ((m_nCounterAnim % 2) == 0)		//アニメーションの速さを変えられる
	{
		m_nPatternAnim = (m_nPatternAnim + 1);

		SetTexture(m_nPatternAnim, 11, 3);

		if (m_nPatternAnim > 33)
		{
			m_nPatternAnim = 0;
		}
	}

	if ((m_nCount % 100) == 0)
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
						CBullet::Create(pos + D3DXVECTOR3(70.0f, 0.0f, 0.0f), 25, 25, CBullet::BULLETTYPE_MP_PAIR);
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
void CPair::Draw(void)
{
	CScene2D::Draw();
}