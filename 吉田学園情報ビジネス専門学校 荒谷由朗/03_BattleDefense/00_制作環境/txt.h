//=============================================================================
//
// ファイル読み込みの処理 [txt.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _TXT_H_
#define _TXT_H_
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

// 文字列の構造体
typedef struct
{
	char Comments[256];
	char *ret;
}Comments;

// モデルの構造体
typedef struct
{
	char FileName[256];
	float Index;
	float PosX, PosY, PosZ;
	float RotX, RotY, RotZ;
}ModelTex;

// モーションの構造体
typedef struct
{
	int		MAX_FLAME;								// フレームの数
	float   MotionPosX, MotionPosY, MotionPosZ;		// 目的の座標データ
	float   MotionRotX, MotionRotY, MotionRotZ;		// 目的の座標データ
}MotionTex;


// ファイルの構造体
typedef struct
{

	int MAX_PARTS;						// パーツの最大数
	int MAX_MOTION;						// モーションの最大数
	int LOOP[25];						// モーションをループするかどうか
	int KEYFLAME[25];					// キーフレームの数
	int MOVEPARTS[25];					// モーション時に動くパーツ数
	ModelTex aModelTex[100];			// パーツ
	MotionTex aMotionTex[25][50][50];	// モーション
}Tex;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void LoadData(void);    //データのロード
Tex *GetTex(void);

#endif