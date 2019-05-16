//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author :荒谷由朗
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "camera.h"
#include "txt.h"
#include "obstacle.h"
#include "inputx.h"
#include "bullet.h"
#include "enemy.h"
#include "motion.h"
#include "meshField.h"
#include "life.h"
#include "explosion.h"
#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BULLET_SPEED (5.0f)				// 弾の速度
#define PLAYER_LIFE (10)				// 体力

//=============================================================================
// プロトタイプ宣言
//=============================================================================
//=============================================================================
// グローバル変数
//=============================================================================
PLAYER_MOSIONSTATE g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;		//プレイヤーの状態
PLAYER_MOSIONSTATE g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_NEUTRAL;
DWORD g_nNumMatModel = 0;								//マテリアル情報の数
Player			g_Player;
JoyState		g_JoyStatePlayer;
Motion			*g_Motion;
//int				g_nIdyShadow;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	Tex *g_aTex;
	//ファイルデータの取得
	g_aTex = GetTex();

	// 位置・向きの初期設定
	g_Player.pos = D3DXVECTOR3(0.0f, 90.0f, 550.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest = 0.0f;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.fAngle = 0.0f;
	g_Player.vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);			// 最小値の場合は多めに数値をいれる（比較のため)
	g_Player.vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		// 最大値の場合は少なめに数値をいれる（比較のため)
	g_Player.nLife = PLAYER_LIFE;
	g_Player.MAX_PARTS = g_aTex->MAX_PARTS;

	g_Player.nCntFleam = 0;

	g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	for (int nCntFile = 0; nCntFile < g_Player.MAX_PARTS; nCntFile++)
	{
		g_Player.aModel[nCntFile].FileName[0] = g_aTex->aModelTex[nCntFile].FileName[0];
	}

	// パーツの親子関係
	for (int nCntIdx = 0; nCntIdx < g_Player.MAX_PARTS; nCntIdx++)
	{
		g_Player.aModel[nCntIdx].nIdxModelParent = g_aTex->aModelTex[nCntIdx].Index;
	}

	// パーツの位置
	for (int nCntPos = 0; nCntPos < g_Player.MAX_PARTS; nCntPos++)
	{
		g_Player.aModel[nCntPos].pos = D3DXVECTOR3(g_aTex->aModelTex[nCntPos].PosX, g_aTex->aModelTex[nCntPos].PosY, g_aTex->aModelTex[nCntPos].PosZ);
	}

	// パーツの回転
	for (int nCntRot = 0; nCntRot < g_Player.MAX_PARTS; nCntRot++)
	{
		g_Player.aModel[nCntRot].rot = D3DXVECTOR3(g_aTex->aModelTex[nCntRot].RotX, g_aTex->aModelTex[nCntRot].RotY, g_aTex->aModelTex[nCntRot].RotZ);
	}
	// ファイルの読み込み
	for (int nCntFile = 0; nCntFile < g_Player.MAX_PARTS; nCntFile++)
	{
		D3DXLoadMeshFromX(&g_aTex->aModelTex[nCntFile].FileName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_Player.aModel[nCntFile].pBuffMat, NULL, &g_Player.aModel[nCntFile].nNumMat, &g_Player.aModel[nCntFile].pMash);
	}

	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点バッファへのポインタ

	// 頂点数の取得
	nNumVtx = g_Player.aModel[0].pMash->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[0].pMash->GetFVF());

	// 頂点バッファをロック
	g_Player.aModel[0].pMash->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			// 頂点座標の代入

		if (vtx.x < g_Player.vtxMin.x)
		{
			g_Player.vtxMin.x = vtx.x;
		}
		if (vtx.y < g_Player.vtxMin.y)
		{
			g_Player.vtxMin.y = vtx.y;
		}
		if (vtx.z < g_Player.vtxMin.z)
		{
			g_Player.vtxMin.z = vtx.z;
		}
		if (vtx.x > g_Player.vtxMax.x)
		{
			g_Player.vtxMax.x = vtx.x;
		}
		if (vtx.y > g_Player.vtxMax.y)
		{
			g_Player.vtxMax.y = vtx.y;
		}
		if (vtx.z > g_Player.vtxMax.z)
		{
			g_Player.vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;			// サイズ分のポインタを進める
	}

	// 頂点バッファをアンロック
	g_Player.aModel[0].pMash->UnlockVertexBuffer();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_Player.aModel[0].pMash != NULL)
	{
		g_Player.aModel[0].pMash->Release();
		g_Player.aModel[0].pMash = NULL;
	}
	//頂点バッファの破棄
	if (g_Player.aModel[0].pBuffMat != NULL)
	{
		g_Player.aModel[0].pBuffMat->Release();
		g_Player.aModel[0].pBuffMat = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	Camera *pCamera;
	//カメラの取得
	pCamera = GetCamera();

	g_Motion = GetMotion();

	Tex *g_aTex;
	//ファイルデータの取得
	g_aTex = GetTex();

	LIFE *g_Life;
	// シリンダーの取得
	g_Life = GetLife();

	if (g_Player.PlayerState == PLAYER_STATE_NEUTRAL)
	{
		g_Player.posOld = g_Player.pos;

		// それぞれの条件で動く向きを変える（加速）
		if (GetKeyboardPress(DIK_A) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
		{
			if (GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{	//左上移動
				g_Player.rotDest = (D3DX_PI * 0.75f) + pCamera->rot.y;
				g_Player.move.x += sinf(-(D3DX_PI * 0.25f) + pCamera->rot.y)* 3.0f;
				g_Player.move.z += cosf(-(D3DX_PI * 0.25f) + pCamera->rot.y) * 3.0f;
				//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 10.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
			}
			else if (GetKeyboardPress(DIK_S) == true || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{	//左下移動
				g_Player.rotDest = (D3DX_PI * 0.75f) + pCamera->rot.y;
				g_Player.move.x += sinf(-(D3DX_PI * 0.75f) + pCamera->rot.y) * 3.0f;
				g_Player.move.z += cosf(-(D3DX_PI * 0.75f) + pCamera->rot.y) * 3.0f;
				//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 1w0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
			}
			else
			{	//左移動
				g_Player.rotDest = (D3DX_PI * 0.5f) + pCamera->rot.y;
				g_Player.move.x += sinf(-(D3DX_PI * 0.5f) + pCamera->rot.y)* 3.0f;
				g_Player.move.z += cosf(-(D3DX_PI * 0.5f) + pCamera->rot.y)* 3.0f;
				//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 10.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
		{
			if (GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{	//右上移動
				g_Player.rotDest = (D3DX_PI * -0.75f) + pCamera->rot.y;
				g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y)* 3.0f;
				g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * 3.0f;
				//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 10.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
			}
			else if (GetKeyboardPress(DIK_S) == true || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{	//右下移動
				g_Player.rotDest = (D3DX_PI * -0.75f) + pCamera->rot.y;
				g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * 3.0f;
				g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * 3.0f;
				//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 10.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
			}
			else
			{	//右移動
				g_Player.rotDest = (D3DX_PI * -0.5f) + pCamera->rot.y;
				g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * 3.0f;
				g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y) * 3.0f;
				//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 10.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
		{	//下に移動
				//g_Player.rotDest = (D3DX_PI * 0.0f) + pCamera->rot.y;
			g_Player.move.x += sinf((D3DX_PI)+pCamera->rot.y) * 3.0f;
			g_Player.move.z += cosf((D3DX_PI)+pCamera->rot.y) * 3.0f;
			//SetEffect(g_Player.pos + D3DXVECTOR3(0.0f, -10.0f, 10.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), 5);
		}
		else if (GetKeyboardPress(DIK_W) == true || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
		{	//上に移動
			g_Player.rotDest = (D3DX_PI * 1.0f) + pCamera->rot.y;
			g_Player.move.x += sinf((0) + pCamera->rot.y) * 3.0f;
			g_Player.move.z += cosf((0) + pCamera->rot.y) * 3.0f;
		}

		if (GetKeyboardPress(DIK_E) == true || (state.Gamepad.bRightTrigger == 255.0f && pJoyState.bConnectionJoypad == true))
		{	//下に移動
			if (g_Player.pos.y <= g_Life->nHeight)
			{
				//g_Player.rotDest = /*(D3DX_PI * 0.0f) +*/ pCamera->rot.z;
				g_Player.move.y += /*tanf((D3DX_PI)+pCamera->rot.y) **/ 3.0f;
				SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE_UP);
			}
		}
		else if (GetKeyboardPress(DIK_Q) == true || (state.Gamepad.bLeftTrigger == 255.0f && pJoyState.bConnectionJoypad == true))
		{	//上に移動
			if (g_Player.pos.y >= 0)
			{
				//g_Player.rotDest = pCamera->rot.z;
				g_Player.move.y += /*tanf((0) + pCamera->rot.y) **/ -3.0f;
				SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE_DOWN);
			}
		}

		if (g_PLAYER_MOSIONSTATENow == PLAYER_MOSIONSTATE_NEUTRAL)
		{
			if (GetKeyboardPress(DIK_A) == true
				|| (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{
				SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE_TURNING_L);
			}
			else if (GetKeyboardPress(DIK_D) == true
				|| (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{
				SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE_TURNING_R);
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_W) == true
				|| (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true)
				|| (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
			{
				SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE_MOVE);
			}
		}

		//if (GetKeyboardTrigger(DIK_RETURN) == true || state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && pJoyState.bConnectionJoypad == true)
		//{
		//	if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		//	{//	トリガー


		if (GetKeyboardPress(DIK_SPACE) == true || state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && pJoyState.bConnectionJoypad == true)
		{
			if (g_Player.nCntFleam % 10 == 0)
			{
				// 弾の設定
				//D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);

				//Enemy *pEnemy;
				//pEnemy = GetEnemy();

				//float fAngleXY, fAngleZ;


				//fAngleXY = atan2f(pEnemy->Pos.x - g_Player.pos.x, pEnemy->Pos.y - g_Player.pos.y);
				//fAngleZ = atan2f(pEnemy->Pos.x - g_Player.pos.x, pEnemy->Pos.z - g_Player.pos.z);

				//BulletMove.x = sinf(fAngleXY) * 5.0f;
				//BulletMove.y = cosf(fAngleXY) * 5.0f;
				//BulletMove.z = cosf(fAngleZ) * 5.0f;

				//SetBullet(g_Player.pos, BulletMove, g_Player.rot, 60, BULLETTYPE_PLAYER);
				SetBullet(g_Player.pos + D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(sinf(g_Player.rot.y + (-1.0f * D3DX_PI)) * BULLET_SPEED, 0.0f, cosf(g_Player.rot.y + (-1.0f * D3DX_PI)) * BULLET_SPEED), g_Player.rot, 100, BULLETTYPE_PLAYER);
			}
		}

		//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true)
		//{
		//	if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		//	{//	トリガー
		//		//やりたいしょり
		//	}
		//	g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_PUSH;
		//}

		//減速
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.6f;
		g_Player.move.y += (0.0f - g_Player.move.y) * 0.6f;
		g_Player.move.z += (0.0f - g_Player.move.z) * 0.6f;

		g_Player.fAngle = g_Player.rotDest - g_Player.rot.y;

		if (g_Player.fAngle > D3DX_PI)
		{
			g_Player.fAngle -= D3DX_PI * 2;
		}
		if (g_Player.fAngle < -D3DX_PI)
		{
			g_Player.fAngle += D3DX_PI * 2;
		}
		g_Player.rot.y += g_Player.fAngle * 0.05f;

		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y -= D3DX_PI * 2;
		}
		if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2;
		}

		if (pCamera->rot.y < -D3DX_PI)
		{
			pCamera->rot.y += D3DX_PI * 2;
		}
		if (pCamera->rot.y > D3DX_PI)
		{
			pCamera->rot.y -= D3DX_PI * 2;
		}

		//位置更新（移動）
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;
		g_Player.pos.z += g_Player.move.z;
		CollisionEnemyBULLET(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.vtxMin, &g_Player.vtxMax);
	}

	//if (GetKeyboardPress(DIK_A) == true
	//	|| (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true)
	//	|| GetKeyboardPress(DIK_D) == true
	//	|| (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
	//{
	//	if (g_Motion->KeyFlame == g_aTex->KEYFLAME[g_Motion->nNumPlayermotion] - 1)
	//	{// 最後のキーになったら0に戻す
	//		SetMotion_STATE(MOTIONSTATE_STOP);
	//	}
	//}

	CollisionObstaclel_Player(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.vtxMin, &g_Player.vtxMax);
	CollisionField(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.vtxMin, &g_Player.vtxMax);
	CollisionClinder(&g_Player.pos, &g_Player.posOld, &g_Player.move, &g_Player.vtxMin, &g_Player.vtxMax);

	if (g_Player.nLife == 0)
	{
		if (g_Player.col.a > 0.3f)
		{
			g_Player.col.a -= 0.1f;
		}
		else
		{
			g_Player.col.a = 0.3f;
		}
	}

	switch (g_Player.PlayerState)
	{
	case PLAYER_STATE_NEUTRAL:
		g_Player.col.a = 1.0f;
		break;
	case PLAYER_STATE_DEATH:
		g_Player.nCunterState--;
		if (g_Player.nCunterState <= 0)
		{
			g_Player.nLife = PLAYER_LIFE;
			SetPLAYER_STATE(PLAYER_STATE_NEUTRAL);
		}
		break;
	case PLAYER_STATE_DAMAGE:
		g_Player.nCunterState--;
		if (g_Player.nCunterState <= 0)
		{
			// 透明
			SetPLAYER_STATE(PLAYER_STATE_NEUTRAL);
		}
		return;
		break;
	}

	switch (g_PLAYER_MOSIONSTATE)
	{
	case PLAYER_MOSIONSTATE_NEUTRAL:
		if (g_Motion->KeyFlame == g_aTex->KEYFLAME[g_Motion->nNumPlayermotion] - 1)
		{
			if (g_PLAYER_MOSIONSTATENow == PLAYER_MOSIONSTATE_NEUTRAL)
			{
				SetMotion(0);
			}
			else if (g_PLAYER_MOSIONSTATENow == PLAYER_MOSIONSTATE_TURNING_R
				|| g_PLAYER_MOSIONSTATENow == PLAYER_MOSIONSTATE_TURNING_L)
			{
				if (GetKeyboardPress(DIK_A) == true
					|| (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true)
					|| GetKeyboardPress(DIK_D) == true
					|| (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pJoyState.bConnectionJoypad == true))
				{
					if (g_Motion->KeyFlame == g_aTex->KEYFLAME[g_Motion->nNumPlayermotion] - 1)
					{// 最後のキーになったら0に戻す
						SetMotion_STATE(MOTIONSTATE_STOP);
					}
				}
				else
				{
					g_Motion->KeyFlame = 0;
					SetMotion(0);
					g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_NEUTRAL;
					g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
				}
			}
			else
			{
				g_Motion->KeyFlame = 0;
				SetMotion(0);
				g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_NEUTRAL;
				g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
			}
		}
		break;
	case PLAYER_MOSIONSTATE_MOVE:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_MOVE;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(1);
		break;
	case PLAYER_MOSIONSTATE_UP:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_UP;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(2);
		break;
	case PLAYER_MOSIONSTATE_DOWN:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_DOWN;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(3);
		break;
	case PLAYER_MOSIONSTATE_TURNING_R:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_TURNING_R;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(4);
		break;
	case PLAYER_MOSIONSTATE_TURNING_L:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_TURNING_L;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(5);
		break;
	case PLAYER_MOSIONSTATE_AVOID_R:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_AVOID_R;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(6);
		break;
	case PLAYER_MOSIONSTATE_AVOID_L:
		g_PLAYER_MOSIONSTATENow = PLAYER_MOSIONSTATE_AVOID_L;
		g_PLAYER_MOSIONSTATE = PLAYER_MOSIONSTATE_NEUTRAL;
		SetMotion(7);
		break;
	}

	if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStatePlayer.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStatePlayer.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
	g_Player.nCntFleam++;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;

	// プレイヤー
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// 親モデル
	for (int nCntParts = 0; nCntParts < g_Player.MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].nIdxModelParent == -1)
		{// 体の時、プレイヤーのマトリックスに入れる
			mtxParent = g_Player.mtxWorld;
		}
		else if (g_Player.aModel[nCntParts].nIdxModelParent == 0)
		{// 手(右)の時、腕(右)のマトリックスに入れる
			mtxParent = g_Player.aModel[0].mtxWorld;
		}
		else if (g_Player.aModel[nCntParts].nIdxModelParent == 1)
		{// 手(右)の時、腕(右)のマトリックスに入れる
			mtxParent = g_Player.aModel[1].mtxWorld;
		}
		else if (g_Player.aModel[nCntParts].nIdxModelParent == 8)
		{// 手(右)の時、腕(右)のマトリックスに入れる
			mtxParent = g_Player.aModel[8].mtxWorld;
		}
		else if (g_Player.aModel[nCntParts].nIdxModelParent == 5)
		{// 手(右)の時、腕(右)のマトリックスに入れる
			mtxParent = g_Player.aModel[5].mtxWorld;
		}

		else
		{// 頭、腕(左右)、脚(左右)の時、体のマトリックスに入れる
			mtxParent = g_Player.aModel[nCntParts - 1].mtxWorld;
		}
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player.aModel[nCntParts].rot.y, g_Player.aModel[nCntParts].rot.x, g_Player.aModel[nCntParts].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Player.aModel[nCntParts].pos.x, g_Player.aModel[nCntParts].pos.y, g_Player.aModel[nCntParts].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorld);


		//// 子モデル
		//// ワールドマトリックスの初期化
		//D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorld);

		//// 回転を反映
		//D3DXMatrixRotationYawPitchRoll(&mtxRot,
		//	g_Player.aModel[nCntParts].rot.y, g_Player.aModel[nCntParts].rot.x, g_Player.aModel[nCntParts].rot.z);
		//D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxRot);

		//// 位置を反映
		//D3DXMatrixTranslation(&mtxTrans,
		//	g_Player.aModel[nCntParts].pos.x, g_Player.aModel[nCntParts].pos.y, g_Player.aModel[nCntParts].pos.z);
		//D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxTrans);

		//D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxParent);

		//// ワールドマトリックスの設定
		//pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorld);


		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			pMat[nCntMat].MatD3D.Diffuse.a = g_Player.col.a;
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice->SetTexture(0, NULL);
			//モデル(パーツ)の描画
			g_Player.aModel[nCntParts].pMash->DrawSubset(nCntMat);
		}
		//マテリアルを返す
		pDevice->SetMaterial(&matDef);
	}
}
// プレイヤーのダメージ処理
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	if (g_Player.nLife <= 0)
	{
		SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		SetPLAYER_STATE(PLAYER_STATE_DEATH);
		PlaySound(SOUND_LABEL_SE_PLEYERBAD);
		g_Player.nCunterState = 60;
		//MessageBox(NULL, "エラー", NULL, MB_YESNO);

		/*if (g_Player.col.a > 0.0f)
		{
			g_Player.col.a -= 0.02f;
		}
		else
		{
			g_Player.col.a = 0.0f;
		}*/
	}
	else
	{
		SetPLAYER_STATE(PLAYER_STATE_DAMAGE);
		//PlaySound(SOUND_LABEL_SE_HIT000);
		g_Player.nCunterState = 5;

		//VERTEX_2D * pVtx;
		//g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//g_pVtxBuffPlayer->Unlock();
	}
}
// プレイヤーの状態の設定
void SetPLAYER_STATE(PLAYER_STATE state)
{
	g_Player.PlayerState = state;
}

void SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE state)
{
	g_PLAYER_MOSIONSTATE = state;
}
//=============================================================================
// プレイヤーの状態の取得
//=============================================================================
PLAYER_MOSIONSTATE GetPLAYER_MOSIONSTATE(void)
{
	return g_PLAYER_MOSIONSTATE;
}

//=============================================================================
// プレイヤーの状態の取得(現状)
//=============================================================================
PLAYER_MOSIONSTATE GetPLAYER_MOSIONSTATENow(void)
{
	return g_PLAYER_MOSIONSTATENow;
}
Player *GetPlayer(void)
{
	return &g_Player;
}