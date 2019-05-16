//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM_タイトル
	// BGM_チュートリアル
	SOUND_LABEL_BGM001,			// BGM_ゲーム
	SOUND_LABEL_BGM002,			// BGM_クリア
	SOUND_LABEL_BGM003,			// BGM_オーバー
	// 発射
	SOUND_LABEL_SE_PLEYERDAMEZ,	// ダメージ
	SOUND_LABEL_SE_POUZU,		// ポーズ選択
	SOUND_LABEL_SE_PLEYERBAD,	// 死亡
	SOUND_LABEL_SE_SELEKUTO,	// 決定音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
