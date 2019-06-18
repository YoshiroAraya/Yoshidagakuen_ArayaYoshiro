//=============================================================================
//
// モデル処理 [player.cpp]
// Author : 荒谷 由朗
//
//=============================================================================
#include "enemy.h"
#include "txt.h"
#include "obstacle.h"
#include "bullet.h"
#include "input.h"
#include "game.h"
#include "score.h"
#include "life.h"
#include "player.h"
#include "explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ENEMY_NAME			"data/MODEL/monkey_head.x"				// モデルの名前
#define ENEMY_UV_NAME		"data/TEXTURE/UV/kuroto_head_UV.png"	// モデルUVの名前

//=============================================================================
// グローバル変数
//=============================================================================
ENEMYSTATE	g_EnemyState = ENEMEYSTATE_NEUTRAL;		// プレイヤーの状態
ENEMYSTATE	g_EnemyStateNow = ENEMEYSTATE_NEUTRAL;
DWORD		g_nNumMatModel_Enemy = 0;				// マテリアル情報の数
Enemy		g_aEnemy[MAX_ENEMY];					// 敵の情報
int			g_nNumEnemy;							// 敵の総数
int			g_MAX_ENEMY;							// 敵の総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	g_MAX_ENEMY = 0;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// 位置・向きの初期設定
		g_aEnemy[nCntEnemy].Pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].Rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].RotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].fAngle		= 0.0f;
		g_aEnemy[nCntEnemy].nLife		= 1;
		g_aEnemy[nCntEnemy].bUse		= false;
		g_aEnemy[nCntEnemy].vtxMin		= D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);			// 最小値の場合は多めに数値をいれる（比較のため)
		g_aEnemy[nCntEnemy].vtxMax		= D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		// 最大値の場合は少なめに数値をいれる（比較のため)
		g_aEnemy[nCntEnemy].MAX_PARTS	= 1;

		// ファイルの読み込み
		for (int nCntFile = 0; nCntFile < g_aEnemy[nCntEnemy].MAX_PARTS; nCntFile++)
		{
			D3DXLoadMeshFromX(ENEMY_NAME, D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aEnemy[nCntEnemy].aModel[nCntFile].pBuffMat, NULL, &g_aEnemy[nCntEnemy].aModel[nCntFile].nNumMat, &g_aEnemy[nCntEnemy].aModel[nCntFile].pMash);
			D3DXCreateTextureFromFile(pDevice, ENEMY_UV_NAME, &g_aEnemy[nCntEnemy].aModel[nCntFile].pTexture);
		}

		int nNumVtx;		// 頂点数
		DWORD sizeFVF;		// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;		// 頂点バッファへのポインタ

		// 頂点数の取得
		nNumVtx = g_aEnemy[nCntEnemy].aModel[0].pMash->GetNumVertices();

		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aEnemy[nCntEnemy].aModel[0].pMash->GetFVF());

		// 頂点バッファをロック
		g_aEnemy[nCntEnemy].aModel[0].pMash->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			// 頂点座標の代入

			if (vtx.x < g_aEnemy[nCntEnemy].vtxMin.x)
			{
				g_aEnemy[nCntEnemy].vtxMin.x = vtx.x;
			}
			if (vtx.y < g_aEnemy[nCntEnemy].vtxMin.y)
			{
				g_aEnemy[nCntEnemy].vtxMin.y = vtx.y;
			}
			if (vtx.z < g_aEnemy[nCntEnemy].vtxMin.z)
			{
				g_aEnemy[nCntEnemy].vtxMin.z = vtx.z;
			}
			if (vtx.x > g_aEnemy[nCntEnemy].vtxMax.x)
			{
				g_aEnemy[nCntEnemy].vtxMax.x = vtx.x;
			}
			if (vtx.y > g_aEnemy[nCntEnemy].vtxMax.y)
			{
				g_aEnemy[nCntEnemy].vtxMax.y = vtx.y;
			}
			if (vtx.z > g_aEnemy[nCntEnemy].vtxMax.z)
			{
				g_aEnemy[nCntEnemy].vtxMax.z = vtx.z;
			}

			pVtxBuff += sizeFVF;			// サイズ分のポインタを進める
		}

		// 頂点バッファをアンロック
		g_aEnemy[nCntEnemy].aModel[0].pMash->UnlockVertexBuffer();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// メッシュの破棄
		if (g_aEnemy[nCntEnemy].aModel[0].pMash != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pMash->Release();
			g_aEnemy[nCntEnemy].aModel[0].pMash = NULL;
		}
		// 頂点バッファの破棄
		if (g_aEnemy[nCntEnemy].aModel[0].pBuffMat != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat->Release();
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	OBSTACLE *g_aObstacle;
	g_aObstacle = GetObstaclel();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			float fAngle;

			g_aEnemy[nCntEnemy].PosOld = g_aEnemy[nCntEnemy].Pos;
			fAngle = atan2f(g_aObstacle->pos.x - g_aEnemy[nCntEnemy].Pos.x, g_aObstacle->pos.z - g_aEnemy[nCntEnemy].Pos.z) + D3DX_PI;

			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}
			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI* 2;
			}

			g_aEnemy[nCntEnemy].Rot.y = fAngle;

			// テキストデータから座標情報を取得する
			g_aEnemy[nCntEnemy].PosDest = g_aObstacle->pos;

			// 差分を計算する
			g_aEnemy[nCntEnemy].fPosAngle.x = g_aEnemy[nCntEnemy].PosDest.x - g_aEnemy[nCntEnemy].Pos.x;			// 差分 = 目的 - 現在
			g_aEnemy[nCntEnemy].fPosAngle.y = g_aEnemy[nCntEnemy].PosDest.y - g_aEnemy[nCntEnemy].Pos.y + 20.0f;	// 差分 = 目的 - 現在
			g_aEnemy[nCntEnemy].fPosAngle.z = g_aEnemy[nCntEnemy].PosDest.z - g_aEnemy[nCntEnemy].Pos.z;			// 差分 = 目的 - 現在

			g_aEnemy[nCntEnemy].Pos.x += g_aEnemy[nCntEnemy].fPosAngle.x * 0.00125f;
			g_aEnemy[nCntEnemy].Pos.y += g_aEnemy[nCntEnemy].fPosAngle.y * 0.00125f;
			g_aEnemy[nCntEnemy].Pos.z += g_aEnemy[nCntEnemy].fPosAngle.z * 0.00125f;

			CollisionPlayerBULLET(&g_aEnemy[nCntEnemy].Pos, &g_aEnemy[nCntEnemy].PosOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].vtxMin, &g_aEnemy[nCntEnemy].vtxMax, nCntEnemy);
			CollisionObstaclel_Enemy(&g_aEnemy[nCntEnemy].Pos, &g_aEnemy[nCntEnemy].PosOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].vtxMin, &g_aEnemy[nCntEnemy].vtxMax, nCntEnemy);

			if (rand() % 400 == 0)
			{
				// 弾の設定
				D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);

				// プレイヤーの取得
				Player *g_aPlayer;
				g_aPlayer = GetPlayer();

				float fAngleXY, fAngleZ;

				fAngleXY = atan2f(g_aPlayer->pos.x - g_aEnemy[nCntEnemy].Pos.x, g_aPlayer->pos.y - g_aEnemy[nCntEnemy].Pos.y);
				fAngleZ = atan2f(g_aPlayer->pos.x - g_aEnemy[nCntEnemy].Pos.x, g_aPlayer->pos.z - g_aEnemy[nCntEnemy].Pos.z);

				BulletMove.x = sinf(fAngleXY) * 5.0f;
				BulletMove.y = cosf(fAngleXY) * 5.0f;
				BulletMove.z = cosf(fAngleZ) * 5.0f;

				SetBullet(g_aEnemy[nCntEnemy].Pos, BulletMove, g_aEnemy[nCntEnemy].Rot, 100, BULLETTYPE_ENEMY);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			LPDIRECT3DDEVICE9	pDevice = GetDevice();	// デバイスの取得
			D3DXMATRIX			mtxRot, mtxTrans;		// 計算用マトリックス
			D3DMATERIAL9		matDef;					// 現在のマテリアル
			D3DXMATERIAL		*pMat;					// マテリアルデータへのポインタ
			D3DXMATRIX			mtxParent;				// 親子関係マトリックス

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEnemy[nCntEnemy].Rot.y, g_aEnemy[nCntEnemy].Rot.x, g_aEnemy[nCntEnemy].Rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aEnemy[nCntEnemy].Pos.x, g_aEnemy[nCntEnemy].Pos.y, g_aEnemy[nCntEnemy].Pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			for (int nCntParts = 0; nCntParts < g_aEnemy[nCntEnemy].MAX_PARTS; nCntParts++)
			{
				if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == -1)
				{// 体の時、プレイヤーのマトリックスに入れる
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 0)
				{// 手(右)の時、腕(右)のマトリックスに入れる
					mtxParent = g_aEnemy[nCntEnemy].aModel[0].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 1)
				{// 手(右)の時、腕(右)のマトリックスに入れる
					mtxParent = g_aEnemy[nCntEnemy].aModel[1].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 8)
				{// 手(右)の時、腕(右)のマトリックスに入れる
					mtxParent = g_aEnemy[nCntEnemy].aModel[8].mtxWorld;
				}
				else if (g_aEnemy[nCntEnemy].aModel[nCntParts].nIdxModelParent == 5)
				{// 手(右)の時、腕(右)のマトリックスに入れる
					mtxParent = g_aEnemy[nCntEnemy].aModel[5].mtxWorld;
				}

				else
				{// 頭、腕(左右)、脚(左右)の時、体のマトリックスに入れる
					mtxParent = g_aEnemy[nCntEnemy].aModel[nCntParts - 1].mtxWorld;
				}
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_aEnemy[nCntEnemy].aModel[nCntParts].rot.y, g_aEnemy[nCntEnemy].aModel[nCntParts].rot.x, g_aEnemy[nCntEnemy].aModel[nCntParts].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans,
					g_aEnemy[nCntEnemy].aModel[nCntParts].pos.x, g_aEnemy[nCntEnemy].aModel[nCntParts].pos.y, g_aEnemy[nCntEnemy].aModel[nCntParts].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &mtxTrans);

				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld, &mtxParent);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntParts].mtxWorld);

				//現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntParts].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntParts].nNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					pDevice->SetTexture(0, g_aEnemy[nCntEnemy].aModel[nCntParts].pTexture);
					//モデル(パーツ)の描画
					g_aEnemy[nCntEnemy].aModel[nCntParts].pMash->DrawSubset(nCntMat);
				}
				//マテリアルを返す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].Pos		= pos;
			g_aEnemy[nCntEnemy].bUse	= true;
			g_MAX_ENEMY++;	// 敵の総数を加算
			break;
		}
	}
}

//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitEnemy(int nNumEnemy, int nDamage ,int typ)
{
	g_aEnemy[nNumEnemy].nLife -= nDamage;

	if (g_aEnemy[nNumEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nNumEnemy].Pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aEnemy[nNumEnemy].bUse = false;
		g_aEnemy[nNumEnemy].EnemyState = ENEMEYSTATE_DEATH;
		g_MAX_ENEMY--;
		if (typ == 0)
		{
			AddScore(200);
		}
	}
	else
	{
		g_aEnemy[nNumEnemy].EnemyState = ENEMEYSTATE_DAMAGE;
	}
}

//=============================================================================
// 敵の状態の設定
//=============================================================================
void SetEnemyState(ENEMYSTATE state)
{
	g_EnemyState = state;
}

//=============================================================================
// 敵の状態の取得
//=============================================================================
ENEMYSTATE GetEnemyState(void)
{
	return g_EnemyState;
}

//=============================================================================
// 敵の状態の取得(現状)
//=============================================================================
ENEMYSTATE GetEnemyStateNow(void)
{
	return g_EnemyStateNow;
}
//=============================================================================
// 敵の情報の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}