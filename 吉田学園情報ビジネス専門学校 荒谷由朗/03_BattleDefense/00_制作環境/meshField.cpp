//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "meshField.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MESHFIELD_TEXTURE	"data/TEXTURE/see.png"			// 読み込むテクスチャ
#define MAX_POS				(9)								// 頂点の最大数
#define MAX_MESH			(14)							// メッシュの最大数
#define MESH_Z				(2)								// メッシュの縦
#define MESH_X				(2)								// メッシュの横

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pldxBuffMeshField = NULL;	// インデックスバッファへのポインタ
D3DXVECTOR3				g_posMeshField;				// 位置
D3DXVECTOR3				g_rotMeshField;				// 向き
D3DXMATRIX				g_mtxWorldMeshField;		// ワールドマトリックス
int						g_nNumVertexMeshField;		// 頂点数
int						g_nNumIndexMeshField;		// インデックス数
int						g_nNumPolygonMeshField;		// ポリゴン数

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	VERTEX_3D*pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE, &g_pTextureMeshField);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MESH,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshField,
		NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMeshFiled = 0; nCntMeshFiled < MESH_Z; nCntMeshFiled++)
	{	// 縦軸
		for (int nCntMeshField1 = 0; nCntMeshField1 < MESH_X + 1; nCntMeshField1++)
		{	// 横軸
			// 頂点座標の設定
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f) + 1000.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f));
			// 法線の設定
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ設定
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(1.0f, 0.0f);

			if (nCntMeshField1 == MESH_X - 1)
			{
				// 頂点座標の設定
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f) + 1000.0f);
				pVtx[nCntMeshField1 + MESH_X + 2 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f));
				// 法線の設定
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 頂点カラーの設定
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				// テクスチャ設定
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
		}
	}

	// テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);

	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);

	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();

	int nCntIndex = 0;

	WORD*pldx;		// インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	g_pldxBuffMeshField->Lock(0, 0, (void**)&pldx, 0);
	// インデックスの設定
	for (int nCntIndex_V = 0; nCntIndex_V < MESH_Z; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= MESH_X; nCntIndex_H++, nCntIndex++)
		{
			pldx[0] = (MESH_X + 1) + nCntIndex;
			pldx[1] = nCntIndex;

			pldx += 2;

			if (nCntIndex == MESH_X && nCntIndex_V <= MESH_Z)
			{
				pldx[0] = nCntIndex;
				pldx[1] = (MESH_X + 1) + nCntIndex + 1;

				pldx += 2;
			}
		}
	}
	// インデックスバッファをアンロックする
	g_pldxBuffMeshField->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	// テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// インデックスバッファの破棄
	if (g_pldxBuffMeshField != NULL)
	{
		g_pldxBuffMeshField->Release();
		g_pldxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX			mtxRot, mtxTrans;		// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pldxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_POS, 0, MAX_MESH);
}