//=============================================================================
//
// スキルアイコン処理 [mpicon.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "mpicon.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "score.h"
#include "explosion.h"

LPDIRECT3DTEXTURE9		CMPIcon::m_pTexture = NULL;

//=============================================================================
//　コンストラクタ
//=============================================================================
CMPIcon::CMPIcon()
{
	m_bUse = false;
	m_nSelect = NULL;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CMPIcon::~CMPIcon()
{

}

CMPIcon *CMPIcon::Create()
{
	CMPIcon *pMPIcon = NULL;

	pMPIcon = new CMPIcon;

	return pMPIcon;
}

HRESULT CMPIcon::Load(void)
{
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MP_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

void CMPIcon::Unload(void)
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
HRESULT CMPIcon::Init(D3DXVECTOR3 pos, int mptype)
{
	m_pos = pos;
	// デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 30.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

	//テクスチャ座標の設定
	switch (mptype)
	{
	case MPICONTYPE_MISSILE:
		m_Type = MPICONTYPE_MISSILE;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		break;
	case MPICONTYPE_PAIR:
		m_Type = MPICONTYPE_PAIR;
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		break;
	case MPICONTYPE_SHIELD:
		m_Type = MPICONTYPE_SHIELD;
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(0.75f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(0.75f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		break;
	case MPICONTYPE_HP:
		m_Type = MPICONTYPE_HP;
		pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//Uが幅、Vが高さ　(0.0f～1.0f）
		break;
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMPIcon::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMPIcon::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMPIcon::Draw(void)
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

void CMPIcon::SetType(MPICONTYPE mpicontype)
{
	m_Type = mpicontype;
}

CMPIcon::MPICONTYPE CMPIcon::GetType(void)
{
	return m_Type;
}

D3DXVECTOR3 CMPIcon::GetPos(void)
{
	return m_pos;
}

void CMPIcon::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;			//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 30.0f, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CMPIcon::SetCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;			//頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[1].col = col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[2].col = col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[3].col = col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}