//=============================================================================
//
// ポリゴン処理 [scene2D.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
//　コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_fRot		= NULL;
	m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================================================================
//　デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9		pDevice = {};
	if (CManager::GetRenderer() != NULL)
	{// GetRenderer()がNULLだったら落ちるため
		pDevice = CManager::GetRenderer()->GetDevice();
	}

	//頂点バッファの読み込み
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	// 頂点バッファの生成
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャの生成
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// オブジェクト(自分自身)の破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9		pDevice = {};
	if (CManager::GetRenderer() != NULL)
	{// GetRenderer()がNULLだったら落ちるため
		pDevice = CManager::GetRenderer()->GetDevice();
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 座標の設定処理
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float width, float height)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	m_pos		= pos;
	m_fWidth	= width;
	m_fHeight	= height;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y - height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y - height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y + height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y + height, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetRot(float rot, float width, float height)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	m_fRot = rot;
	m_fWidth = width;
	m_fHeight = height;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(m_fRot) * m_fHeight) + (cosf(m_fRot) * m_fWidth), m_pos.y - (sinf(m_fRot) * m_fWidth) + (cosf(m_fRot) * m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(m_fRot) * m_fHeight) - (cosf(m_fRot) * m_fWidth), m_pos.y + (sinf(m_fRot) * m_fWidth) + (cosf(m_fRot) * m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(m_fRot) * m_fHeight) + (cosf(m_fRot) * m_fWidth), m_pos.y - (sinf(m_fRot) * m_fWidth) - (cosf(m_fRot) * m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(m_fRot) * m_fHeight) - (cosf(m_fRot) * m_fWidth), m_pos.y + (sinf(m_fRot) * m_fWidth) - (cosf(m_fRot) * m_fHeight), 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
// 色の設定処理
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	if (m_pVtxBuff != NULL)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点情報を設定
		pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// テクスチャの設定処理
//=============================================================================
void CScene2D::SetTexture(int PatternAnim, int X, int Y)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X),				(PatternAnim / X) * (1.0f / Y));
	pVtx[1].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X) + (1.0f / X),	(PatternAnim / X) * (1.0f / Y));
	pVtx[2].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X),				(PatternAnim / X) * (1.0f / Y) + (1.0f / Y));
	pVtx[3].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X) + (1.0f / X),	(PatternAnim / X) * (1.0f / Y) + (1.0f / Y));

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャ(スコア)の設定処理
//=============================================================================
void CScene2D::SetScore(int nValue)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2((nValue % 10) * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nValue % 10) * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nValue % 10) * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nValue % 10) * 0.1f + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

D3DXCOLOR CScene2D::GetCol(void)
{
	return m_col;
}

float CScene2D::GetWidth(void)
{
	return m_fWidth;
}

float CScene2D::GetHeight(void)
{
	return m_fHeight;
}

LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}