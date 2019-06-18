//=============================================================================
//
// ライフゲージ処理 [life.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "life.h"
#include "input.h"
#include "camera.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIFE_VERTEX				((g_Life_h + 1) * (g_Life_v + 1))
#define LIFE_INDEX				( (g_Life_h * g_Life_v )* 2 + (4 * (g_Life_v - 1)) + 2 )
#define LIFE_POLYGON			( (g_Life_h * g_Life_v) * 2 + (4 * (g_Life_v - 1)) )
#define LIFE_RADIUS				(1000.0f)													// 円(外側)の半径
#define LIFE_RADIUS2			(100.0f)													// 円(内側)の半径
#define LIFE_HEIGHT				(600.0f)
#define LIFE_H					(100)														// メッシュの分割数(H)
#define LIFE_V					(1)															// メッシュの分割数(V)
#define MESHCYLINDER_TEXTURE	"data/TEXTURE/WallClinder.png"								// 読み込むテクスチャ

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexLife	(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexLife	(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffLife = NULL;		// インデックスバッファへのポインタ
D3DXMATRIX				g_mtxWorldLife;				// ワールドマトリックス
LIFE g_Life;
int g_nLife;
int g_Life_h, g_Life_v;

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	g_Life_h = LIFE_H;
	g_Life_v = LIFE_V;

	int Polygon = (g_Life_h * g_Life_v) * 2 + (4 * (g_Life_v - 1));
	g_nLife		= 0;

	MakeVertexLife	(pDevice);
	MakeIndexLife	(pDevice);

	// プレイヤーの取得
	Player pPlayer;
	pPlayer = *GetPlayer();

	g_Life.pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Life.rot		= D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	g_Life.RADIUS	= LIFE_RADIUS;
	g_Life.bUse		= false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	// テクスチャの破棄
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffLife != NULL)
	{
		g_pIdxBuffLife->Release();
		g_pIdxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX			mtxrot, mtxtrans;


	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldLife);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxrot,
		g_Life.rot.y, g_Life.rot.x, g_Life.rot.z);

	D3DXMatrixMultiply(&g_mtxWorldLife, &g_mtxWorldLife, &mtxrot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxtrans,
		g_Life.pos.x, g_Life.pos.y, g_Life.pos.z);

	D3DXMatrixMultiply(&g_mtxWorldLife, &g_mtxWorldLife, &mtxtrans);


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldLife);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffLife);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	// メッシュシリンダーの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, LIFE_VERTEX, 0, LIFE_POLYGON + g_nLife);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ライフの取得
//=============================================================================
LIFE *GetLife(void)
{
	return &g_Life;
}

//=============================================================================
// ライフ減少
//=============================================================================
void HitDamage(int nDamage)
{
	g_nLife += nDamage;
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEXTURE, &g_pTextureLife);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * LIFE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = D3DX_PI * 2 / g_Life_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_Life_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_Life_h + 1; nCntLife_H++)
		{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.x = -sinf(fDestAngle) * LIFE_RADIUS;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.y = nCntLife_V * LIFE_HEIGHT;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * LIFE_RADIUS;

				// 法線の設定
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].nor = D3DXVECTOR3(sinf(fDestAngle), 0.0f, cosf(fDestAngle));

				// 頂点カラー
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_Life_h / 2)), nCntLife_V * -1.0f);

				fDestAngle += fAngle;
				g_Life.nHeight = nCntLife_V * LIFE_HEIGHT;
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// インデックス情報の作成
//=============================================================================
void MakeIndexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * LIFE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffLife,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	// インデックスのカウント

	// インデックスバッファをロック
	g_pIdxBuffLife->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_Life_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_Life_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_Life_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_Life_h && nCntIndex_V <= g_Life_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_Life_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	// 頂点バッファをアンロック
	g_pIdxBuffLife->Unlock();
}

bool CollisionClinder(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	bool bCollision = false;

	Player *g_aPlayer;
	//プレイヤーの取得
	g_aPlayer = GetPlayer();

	g_Life.fAngle = g_aPlayer->pos - g_Life.pos;
	g_Life.nAngle = (g_Life.fAngle.x * g_Life.fAngle.x) + (g_Life.fAngle.z * g_Life.fAngle.z);

	if (g_Life.nAngle > (LIFE_RADIUS * LIFE_RADIUS))
	{
		float fAngle;

		fAngle= atan2f(g_aPlayer->pos.x, g_aPlayer->pos.z);

		g_aPlayer->pos = D3DXVECTOR3(sinf(fAngle) * LIFE_RADIUS, g_aPlayer->pos.y,cosf(fAngle) * LIFE_RADIUS);
	}

	return bCollision;
}

double Norm(double *vec, int nCntDimensions)
{
	double sVecNorm = 0.0;

	for (int i = 0; i < nCntDimensions; i++)
	{
		sVecNorm += vec[i] * vec[i];
	}

	return sqrt(sVecNorm);
}