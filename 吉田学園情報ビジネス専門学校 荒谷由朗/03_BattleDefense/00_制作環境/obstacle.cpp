//=============================================================================
//
// 障害物の処理 [obstacle.cpp]
// Author : 荒谷由朗
//
//=============================================================================
#include "obstacle.h"
#include "input.h"
//#include "shadow.h"
#include "camera.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBSTACLE_NAME		"data/MODEL/TOWADA_Class.x"				// モデルの名前
#define OBSTACLE_NAME0		"data/MODEL/ramieru.x"				// モデルの名前

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH		g_pMeshObstacle = NULL;				//メッシュ情報へのポインタ
LPD3DXBUFFER	g_pBuffMatObstacle = NULL;			// マテリアル情報へのポインタ
DWORD			g_nNumMatObstacle = 0;				// マテリアルの情報
OBSTACLE		g_aObstacle;
//=============================================================================
// 初期化処理
//=============================================================================
void InitObstaclel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・向きの初期設定
	g_aObstacle.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aObstacle.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aObstacle.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aObstacle.nIdyShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_aObstacle.bUse = true;
	g_aObstacle.nLife = 20;
	g_aObstacle.nLifeMAX = 20;
	g_aObstacle.vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);			// 最小値の場合は多めに数値をいれる（比較のため)
	g_aObstacle.vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		// 最大値の場合は少なめに数値をいれる（比較のため)

	// Xファイルの読み込み
	D3DXLoadMeshFromX(OBSTACLE_NAME, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObstacle, NULL, &g_nNumMatObstacle, &g_pMeshObstacle);

	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点バッファへのポインタ

	// 頂点数の取得
	nNumVtx = g_pMeshObstacle->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle->GetFVF());

	// 頂点バッファをロック
	g_pMeshObstacle->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			// 頂点座標の代入

		if (vtx.x < g_aObstacle.vtxMin.x)
		{
			g_aObstacle.vtxMin.x = vtx.x;
		}
		if (vtx.y < g_aObstacle.vtxMin.y)
		{
			g_aObstacle.vtxMin.y = vtx.y;
		}
		if (vtx.z < g_aObstacle.vtxMin.z)
		{
			g_aObstacle.vtxMin.z = vtx.z;
		}
		if (vtx.x > g_aObstacle.vtxMax.x)
		{
			 g_aObstacle.vtxMax.x = vtx.x;
		}
		if (vtx.y > g_aObstacle.vtxMax.y)
		{
			g_aObstacle.vtxMax.y = vtx.y;
		}
		if (vtx.z > g_aObstacle.vtxMax.z)
		{
			g_aObstacle.vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;			// サイズ分のポインタを進める
	}

	// 頂点バッファをアンロック
	g_pMeshObstacle->UnlockVertexBuffer();


}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObstaclel(void)
{
	// メッシュの開放
	if (g_pMeshObstacle != NULL)
	{
		g_pMeshObstacle->Release();
		g_pMeshObstacle = NULL;
	}

	// マテリアルの開放
	if (g_pBuffMatObstacle != NULL)
	{
		g_pBuffMatObstacle->Release();
		g_pBuffMatObstacle = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObstaclel(void)
{
	FADE fade;
	fade = GetFade();

	if (g_aObstacle.bUse == true)
	{
		//SetPositionShadow(g_aObstacle.nIdyShadow, D3DXVECTOR3(g_aObstacle.pos.x, 0.0f, g_aObstacle.pos.z));

		switch (g_aObstacle.ObjectState)
		{
		case OBJECTSTATE_NORMAL:
			break;
		case OBJECTSTATE_DAMAGE:
			g_aObstacle.nCunterState--;
			if (g_aObstacle.nCunterState <= 0)
			{
				g_aObstacle.ObjectState = OBJECTSTATE_NORMAL;
			}
			break;
		case OBJECTSTATE_DEATH:
			g_aObstacle.nCunterState--;
			if (g_aObstacle.nCunterState == 0)
			{
				if (fade != FADE_OUT)
				{
					//SetGameState(GAMESTATE_CLEAR);
					//モード設定
					/*SetFade(MODE_RESULT);*/
				}
			}
			return;
			break;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObstaclel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	if (g_aObstacle.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aObstacle.mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObstacle.rot.y, g_aObstacle.rot.x, g_aObstacle.rot.z);
		D3DXMatrixMultiply(&g_aObstacle.mtxWorld, &g_aObstacle.mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aObstacle.pos.x, g_aObstacle.pos.y, g_aObstacle.pos.z);
		D3DXMatrixMultiply(&g_aObstacle.mtxWorld, &g_aObstacle.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aObstacle.mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatObstacle->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatObstacle; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_pMeshObstacle->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// 障害物の当り判定
//=============================================================================
//void CollisionObstaclel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
//{
//	FADE fade;
//	fade = GetFade();
//
//	Player *g_aModel;
//	//プレイヤーの取得
//	g_aModel = GetPlayer();
//
//	if (g_aObstacle.bUse == true)
//	{
//		if (g_aObstacle.pos.x + g_aObstacle.vtxMax.x >= pPosOld->x - pVtxMax->x &&
//			g_aObstacle.pos.x - g_aObstacle.vtxMax.x <= pPosOld->x + pVtxMax->x)
//		{
//			if (g_aObstacle.pos.z + g_aObstacle.vtxMax.z >= pPos->z - pVtxMax->z &&
//				g_aObstacle.pos.z + g_aObstacle.vtxMax.z <= pPosOld->z - pVtxMax->z)
//			{// 上
//				AddScore(200);
//				g_aObstacle.bUse = false;
//				pPos->z = pPosOld->z;
//				pMove->z = 0.0f;
//				if (fade != FADE_OUT)
//				{
//					SetGameState(GAMESTATE_CLEAR);
//					//モード設定
//					SetFade(MODE_RESULT);
//				}
//			}
//			else if (g_aObstacle.pos.z - g_aObstacle.vtxMax.z <= pPos->z + pVtxMax->z &&
//				g_aObstacle.pos.z - g_aObstacle.vtxMax.z >= pPosOld->z + pVtxMax->z)
//			{// 下
//				AddScore(200);
//				g_aObstacle.bUse = false;
//				pPos->z = pPosOld->z;
//				pMove->z = 0.0f;
//				if (fade != FADE_OUT)
//				{
//					SetGameState(GAMESTATE_CLEAR);
//					//モード設定
//					SetFade(MODE_RESULT);
//				}
//			}
//
//		}
//		if (g_aObstacle.pos.z + g_aObstacle.vtxMax.z >= pPosOld->z - pVtxMax->z &&
//			g_aObstacle.pos.z - g_aObstacle.vtxMax.z <= pPosOld->z + pVtxMax->z)
//		{
//			if (g_aObstacle.pos.x + g_aObstacle.vtxMax.x >= pPos->x - pVtxMax->x &&
//				g_aObstacle.pos.x + g_aObstacle.vtxMax.x <= pPosOld->x - pVtxMax->x)
//			{// 右
//				AddScore(200);
//				g_aObstacle.bUse = false;
//				pPos->x = pPosOld->x;
//				if (fade != FADE_OUT)
//				{
//					SetGameState(GAMESTATE_CLEAR);
//					//モード設定
//					SetFade(MODE_RESULT);
//				}
//			}
//			else if (g_aObstacle.pos.x - g_aObstacle.vtxMax.x <= pPos->x + pVtxMax->x &&
//				g_aObstacle.pos.x - g_aObstacle.vtxMax.x >= pPosOld->x + pVtxMax->x)
//			{// 左
//				AddScore(200);
//				g_aObstacle.bUse = false;
//				pPos->x = pPosOld->x;
//				if (fade != FADE_OUT)
//				{
//					SetGameState(GAMESTATE_CLEAR);
//					//モード設定
//					SetFade(MODE_RESULT);
//				}
//			}
//		}
//	}
//}
//pPosOld->x + pVtxMax->z >= g_aObstacle.vtxMax.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x

bool CollisionObstaclel_Player(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	bool bCollision = false;

	if (g_aObstacle.bUse == true)
	{
		if (pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x
			&& pPos->y + (pVtxMax->y +15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y
			&& pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
		{
			if (pPosOld->x + pVtxMax->z <= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x)
			{// 右からきたとき
				bCollision = true;
				//pPos->x = g_aObstacle.vtxMin.x + g_aObstacle.pos.x - pVtxMax->z;
				pPos->x = pPosOld->x;
			}
			else if (pPosOld->x + pVtxMax->z >= g_aObstacle.vtxMax.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x)
			{// 左からきたとき
				bCollision = true;
				//pPos->x = g_aObstacle.vtxMax.x + g_aObstacle.pos.x + pVtxMax->z;
				pPos->x = pPosOld->x;
				//MessageBox(NULL, "エラー", NULL, MB_YESNO);
			}
			if (pPosOld->z + pVtxMax->z <= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z)
			{// 奥からきたとき
				bCollision = true;
				//pPos->z = g_aObstacle.vtxMin.z + g_aObstacle.pos.z - pVtxMax->z;
				pPos->z = pPosOld->z;
			}
			else if (pPosOld->z - pVtxMax->z >= g_aObstacle.vtxMax.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
			{// 手前からきたとき
				bCollision = true;
				//pPos->z = g_aObstacle.vtxMax.z + g_aObstacle.pos.z + pVtxMax->z;
				pPos->z = pPosOld->z;
			}
			if (pPosOld->y + (pVtxMin->y + 10.0f) >= g_aObstacle.vtxMax.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y)
			{// 上からきたとき
				bCollision = true;
				pPos->y = pPosOld->y;
			}
			else if (pPosOld->y + (pVtxMax->y + 15.0f) <= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMax->y + 15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y)
			{// 下からきたとき
				bCollision = true;
				pPos->y = pPosOld->y;
			}
		}
	}
	return bCollision;
}

bool CollisionObstaclel_Enemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy)
{
	bool bCollision = false;

	Enemy *g_Enemy;
	g_Enemy	= GetEnemy();

	if (g_aObstacle.bUse == true)
	{
		if (pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x
			&& pPos->y + (pVtxMax->y + 15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y
			&& pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
		{
			if (pPosOld->x + pVtxMax->z <= g_aObstacle.vtxMin.x + g_aObstacle.pos.x && pPos->x + pVtxMax->z >= g_aObstacle.vtxMin.x + g_aObstacle.pos.x)
			{// 右からきたとき
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
				//HitObstaclel(1);
				//pPos->x = g_aObstacle.vtxMin.x + g_aObstacle.pos.x - pVtxMax->z;
				//pPos->x = pPosOld->x;
				//MessageBox(NULL, "エラー", NULL, MB_YESNO);
			}
			else if (pPosOld->x + pVtxMax->z >= g_aObstacle.vtxMax.x + g_aObstacle.pos.x && pPos->x + pVtxMin->z <= g_aObstacle.vtxMax.x + g_aObstacle.pos.x)
			{// 左からきたとき
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
				//HitObstaclel(1);
				//pPos->x = g_aObstacle.vtxMax.x + g_aObstacle.pos.x + pVtxMax->z;
				//pPos->x = pPosOld->x;
				//MessageBox(NULL, "エラー", NULL, MB_YESNO);
			}
			if (pPosOld->z + pVtxMax->z <= g_aObstacle.vtxMin.z + g_aObstacle.pos.z && pPos->z + pVtxMax->z >= g_aObstacle.vtxMin.z + g_aObstacle.pos.z)
			{// 奥からきたとき
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
				//HitObstaclel(1);
				//pPos->z = g_aObstacle.vtxMin.z + g_aObstacle.pos.z - pVtxMax->z;
				//pPos->z = pPosOld->z;
			}
			else if (pPosOld->z - pVtxMax->z >= g_aObstacle.vtxMax.z + g_aObstacle.pos.z && pPos->z - pVtxMax->z <= g_aObstacle.vtxMax.z + g_aObstacle.pos.z)
			{// 手前からきたとき
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
				//HitObstaclel(1);
				//pPos->z = g_aObstacle.vtxMax.z + g_aObstacle.pos.z + pVtxMax->z;
				//pPos->z = pPosOld->z;
			}
			if (pPosOld->y + (pVtxMin->y + 10.0f) >= g_aObstacle.vtxMax.y + g_aObstacle.pos.y && pPos->y + (pVtxMin->y + 10.0f) <= g_aObstacle.vtxMax.y + g_aObstacle.pos.y)
			{// 上からきたとき
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
				//HitObstaclel(1);
				//pPos->y = pPosOld->y;
			}
			else if (pPosOld->y + (pVtxMax->y + 15.0f) <= g_aObstacle.vtxMin.y + g_aObstacle.pos.y && pPos->y + (pVtxMax->y + 15.0f) >= g_aObstacle.vtxMin.y + g_aObstacle.pos.y)
			{// 下からきたとき
				bCollision = true;
				g_Enemy[nNumEnemy].bUse = false;
				//HitObstaclel(1);
				//pPos->y = pPosOld->y;
			}
			HitObstaclel(1);
		}
	}
	return bCollision;
}

void HitObstaclel(int nDamage)
{
	g_aObstacle.nLife -= nDamage;
	if (g_aObstacle.nLife <= 0)
	{
		SetExplosion(g_aObstacle.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aObstacle.bUse = false;
		g_aObstacle.ObjectState = OBJECTSTATE_DEATH;
		SetGameState(GAMESTATE_OVER);
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aObstacle.nCunterState = 60.0f;
		//MessageBox(NULL, "エラー", NULL, MB_YESNO);
	}
	else
	{
		g_aObstacle.ObjectState = OBJECTSTATE_DAMAGE;
		//PlaySound(SOUND_LABEL_SE_HIT000);
		g_aObstacle.nCunterState = 1.15f;

		//VERTEX_2D * pVtx;
		//g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//g_pVtxBuffPlayer->Unlock();
	}
}

//=============================================================================
// モデルの取得
//=============================================================================
OBSTACLE *GetObstaclel(void)
{
	return &g_aObstacle;
}
