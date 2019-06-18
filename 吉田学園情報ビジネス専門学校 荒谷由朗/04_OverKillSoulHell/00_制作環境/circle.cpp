//=============================================================================
//
// ゲージ(円)の処理 [circle.h]
// Author : 荒谷 由朗
//
//=============================================================================
#include "circle.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
//　コンストラクタ
//=============================================================================
CCircle::CCircle()
{
	m_Radius	= NULL;
	m_Radius2	= NULL;
	m_fCircle	= 583.0f;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CCircle::~CCircle()
{
}

//=============================================================================
//　生成処理
//=============================================================================
CCircle *CCircle::Create(D3DXVECTOR3 pos, float radius, float radius2, CIRCLETYPE type)
{
	CCircle *pCircle = NULL;

	pCircle = new CCircle;
	pCircle->Init(pos, radius, radius2, type);

	return pCircle;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCircle::Init(D3DXVECTOR3 pos, float radius, float radius2,CIRCLETYPE type)
{
	// 各データの代入
	m_pos			= pos;
	m_Radius		= radius;
	m_Radius2		= radius2;
	m_CircleType	= type;

	// デバイスの取得
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	switch (type)
	{// タイプごとにカラーを設定
	case CIRCLETYPE_HP:
		m_col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		break;
	case CIRCLETYPE_MP:
		m_col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}

	MakeVertex	(pDevice);
	MakeIndex	(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCircle::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CCircle::Update(void)
{
}

//=============================================================================
// 描画処理7
//=============================================================================
void CCircle::Draw(void)
{
	// プレイヤーの取得
	CPlayer *pPlayer = CManager::GetPlayer();

	if (pPlayer != NULL)
	{
		// デバイスの取得
		LPDIRECT3DDEVICE9		pDevice = {};
		if (CManager::GetRenderer() != NULL)
		{// GetRenderer()がNULLだったら落ちるため
			pDevice = CManager::GetRenderer()->GetDevice();
		}

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(m_pIdxBuff);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, 0);

		if (m_CircleType == CIRCLETYPE_HP)
		{
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CIRCLE_VERTEX, 0, (UINT)(CIRCLE_POLYGON * 2 * (pPlayer->GetPlayerLife() / 100.0f)));
		}
		else if (m_CircleType == CIRCLETYPE_MP)
		{
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CIRCLE_VERTEX, 0, (UINT)(CIRCLE_POLYGON * 2 * (pPlayer->GetPlayerMp() / 200.0f)));
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void CCircle::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * CIRCLE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;		// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = D3DX_PI * 2 / CIRCLE_H;
	float fDestAngle;

	for (int nCntCIRCLE_V = 0; nCntCIRCLE_V < CIRCLE_V + 1; nCntCIRCLE_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntCIRCLE_H = 0; nCntCIRCLE_H < CIRCLE_H + 1; nCntCIRCLE_H++)
		{
			if (nCntCIRCLE_V == 0)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				// 頂点座標
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.x = -sinf(fDestAngle) * m_Radius + m_pos.x;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.y = cosf(fDestAngle) * m_Radius + m_pos.y;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.z = 0.0f;

				// 頂点カラー
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].col = m_col;

				// テクスチャ座標
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].tex = D3DXVECTOR2(nCntCIRCLE_H * (1.0f / (CIRCLE_H / 2)), nCntCIRCLE_V * -1.0f);
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
			if (nCntCIRCLE_V == 1)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				// 頂点座標
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.x = -sinf(fDestAngle) * (m_Radius - m_Radius2) + m_pos.x;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.y = cosf(fDestAngle) * (m_Radius - m_Radius2) + m_pos.y;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.z = 0.0f;

				// 頂点カラー
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].col = m_col;

				// テクスチャ座標
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].tex = D3DXVECTOR2(nCntCIRCLE_H * (1.0f / (CIRCLE_H / 2)), nCntCIRCLE_V * -1.0f);
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
		}
	}
	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// インデックス情報の作成
//=============================================================================
void CCircle::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * CIRCLE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	// インデックスのカウント

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < CIRCLE_V; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= CIRCLE_H; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (CIRCLE_H + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == CIRCLE_H && nCntIndex_V <= CIRCLE_V)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (CIRCLE_H + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	// 頂点バッファをアンロック
	m_pIdxBuff->Unlock();
}