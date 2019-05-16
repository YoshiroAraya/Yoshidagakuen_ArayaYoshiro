//=============================================================================
//
// ビルボード処理 [Bullet.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "bullet.h"
//#include "shadow.h"
#include "player.h"
#include "explosion.h"
#include "obstacle.h"
#include "enemy.h"
#include "PlayerLife.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_BULLET				(128)								// 壁の最大数
#define BULLET_TEXTURENAME		"data/TEXTURE/bullet000.png"		// テクスチャの名前

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//テクスチャへポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME, &g_pTextureBullet);

	// 頂点情報の作成
	MakeVertexBullet(pDevice);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// テクスチャの開放;
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放;
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_3D*pVtx;			//頂点情報へのポインタ
	OBSTACLE *g_aObstacle;
	g_aObstacle = GetObstaclel();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//弾が使用されている

			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//SetPositionShadow(g_aBullet[nCntBullet].nIdyShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));

				pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//弾の位置を移動
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

				//頂点設定
				//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
				//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//SetPositionShadow(g_aBullet[nCntBullet].nIdyShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));

				pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//弾の位置を移動
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

				//頂点設定
				//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 0.0f, g_aBullet[nCntBullet].pos.z - 10);
				//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 0.0f, g_aBullet[nCntBullet].pos.z - 10);
				//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 0.0f, g_aBullet[nCntBullet].pos.z + 10);
				//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 0.0f, g_aBullet[nCntBullet].pos.z + 10);

			}
			//if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT
			//	|| g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH
			//	|| g_aBullet[nCntBullet].pos.z < 0 || g_aBullet[nCntBullet].pos.z > SCREEN_WIDTH)
			//{
			//	g_aBullet[nCntBullet].bUse = false;			//使用されてない状態にする
			//}


			//SetPositionShadow(g_aBullet[nCntBullet].nIdyShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));
			////SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 10);

			//// 差分を計算する
			//g_aBullet[nCntBullet].posAngle = g_aBullet[nCntBullet].posDest - g_aBullet[nCntBullet].pos * 2.0f;		// 差分 = 目的 - 現在

			//if (g_aBullet[nCntBullet].posAngle.x > D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.x -= D3DX_PI * 2;
			//}
			//if (g_aBullet[nCntBullet].posAngle.x < -D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.x += D3DX_PI * 2;
			//}

			//if (g_aBullet[nCntBullet].posAngle.y > D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.y -= D3DX_PI * 2;
			//}
			//if (g_aBullet[nCntBullet].posAngle.y < -D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.y += D3DX_PI * 2;
			//}

			//if (g_aBullet[nCntBullet].posAngle.z > D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.z -= D3DX_PI * 2;
			//}
			//if (g_aBullet[nCntBullet].posAngle.z < -D3DX_PI)
			//{
			//	g_aBullet[nCntBullet].posAngle.z += D3DX_PI * 2;
			//}

			//g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posAngle * 0.002f;

			//// 更新
			//if (g_aBullet[nCntBullet].pos >= g_aBullet[nCntBullet].posAngle)
			//{
			//	g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posAngle * 0.002f;
			//}
			//if (g_aBullet[nCntBullet].pos <= g_aBullet[nCntBullet].posAngle)
			//{
			//	g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].posAngle * 0.002f;
			//}
			if (g_aBullet[nCntBullet].nLife < 0)
			{
				//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		// 頂点バッファのアンロック
		g_pVtxBuffBullet->Unlock();

		g_aBullet[nCntBullet].nLife--;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

		// ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &g_aBullet[nCntBullet].mtxView);

		// カメラの逆行列を設定
		g_aBullet[nCntBullet].mtxWorld._11 = g_aBullet[nCntBullet].mtxView._11;
		g_aBullet[nCntBullet].mtxWorld._12 = g_aBullet[nCntBullet].mtxView._21;
		g_aBullet[nCntBullet].mtxWorld._13 = g_aBullet[nCntBullet].mtxView._31;
		g_aBullet[nCntBullet].mtxWorld._21 = g_aBullet[nCntBullet].mtxView._12;
		g_aBullet[nCntBullet].mtxWorld._22 = g_aBullet[nCntBullet].mtxView._22;
		g_aBullet[nCntBullet].mtxWorld._23 = g_aBullet[nCntBullet].mtxView._32;
		g_aBullet[nCntBullet].mtxWorld._31 = g_aBullet[nCntBullet].mtxView._13;
		g_aBullet[nCntBullet].mtxWorld._32 = g_aBullet[nCntBullet].mtxView._23;
		g_aBullet[nCntBullet].mtxWorld._33 = g_aBullet[nCntBullet].mtxView._33;

		// 回転を反映
		//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBullet[nCntBullet].rot.y, g_aBullet[nCntBullet].rot.x, g_aBullet[nCntBullet].rot.z);
		//D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 10.0f, 0.0f);		// 頂点座標(X座標,Y座標)
		pVtx[1].pos = D3DXVECTOR3(5.0f, 10.0f, 0.0f);		// 頂点座標(X座標,Y座標)
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);		// 頂点座標(X座標,Y座標)
		pVtx[3].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);		// 頂点座標(X座標,Y座標)

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		// Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// Uが幅、Vが高さ　(0.0f～1.0f）
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		// Uが幅、Vが高さ　(0.0f～1.0f）

		pVtx += 4;									// 座標を4ずつ進める
	}

	// 頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nLife, BULLETTYPE type)
{
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;
			//g_aBullet[nCntBullet].nIdyShadow = SetShadow(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// 弾の当たり判定
//=============================================================================
bool CollisionPlayerBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy)
{
	bool bCollision = false;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
		{
			if (g_aBullet[nCntBullet].bUse == true)
			{
				if (pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x
					&& pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y
					&& pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
				{
					if (pPosOld->x + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x)
					{// 右からきたとき
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					else if (pPosOld->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x)
					{// 左からきたとき
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					if (pPosOld->z + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z)
					{// 奥からきたとき
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					else if (pPosOld->z - pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
					{// 手前からきたとき
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					if (pPosOld->y + (pVtxMin->y) >= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y)
					{// 上からきたとき
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					else if (pPosOld->y + (pVtxMax->y) <= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y)
					{// 下からきたとき
						bCollision = true;
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
					}
					PlaySound(SOUND_LABEL_SE_PLEYERDAMEZ);
					g_aBullet[nCntBullet].bUse = false;
					HitEnemy(nNumEnemy, 1,0);
				}
			}
		}
	}
	return bCollision;
}
bool CollisionEnemyBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	bool bCollision = false;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
		{
			if (g_aBullet[nCntBullet].bUse == true)
			{
				if (pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x
					&& pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y
					&& pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
				{
					if (pPosOld->x + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.x + g_aBullet[nCntBullet].pos.x)
					{// 右からきたとき
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					else if (pPosOld->x + pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x && pPos->x + pVtxMin->z <= g_aBullet[nCntBullet].vtxMax.x + g_aBullet[nCntBullet].pos.x)
					{// 左からきたとき
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					if (pPosOld->z + pVtxMax->z <= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z && pPos->z + pVtxMax->z >= g_aBullet[nCntBullet].vtxMin.z + g_aBullet[nCntBullet].pos.z)
					{// 奥からきたとき
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					else if (pPosOld->z - pVtxMax->z >= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z && pPos->z - pVtxMax->z <= g_aBullet[nCntBullet].vtxMax.z + g_aBullet[nCntBullet].pos.z)
					{// 手前からきたとき
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					if (pPosOld->y + (pVtxMin->y) >= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMin->y) <= g_aBullet[nCntBullet].vtxMax.y + g_aBullet[nCntBullet].pos.y)
					{// 上からきたとき
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
						//MessageBox(NULL, "エラー", NULL, MB_YESNO);
					}
					else if (pPosOld->y + (pVtxMax->y) <= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y && pPos->y + (pVtxMax->y) >= g_aBullet[nCntBullet].vtxMin.y + g_aBullet[nCntBullet].pos.y)
					{// 下からきたとき
						bCollision = true;
						HitPlayer(1);
						HitPlayerLife(20);
						//DeleteShadow(g_aBullet[nCntBullet].nIdyShadow);
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}
		}
	}
	return bCollision;
}