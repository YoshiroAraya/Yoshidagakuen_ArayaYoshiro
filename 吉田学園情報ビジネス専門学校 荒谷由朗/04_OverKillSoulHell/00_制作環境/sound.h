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
// クラス
//*************************************
class CSound
{
public:
	//*************************************
	// サウンドファイル
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,			// タイトルBGM
		SOUND_LABEL_BGM001,				// チュートリアルBGM
		SOUND_LABEL_BGM002,				// ゲームBGM
		SOUND_LABEL_BGM003,				// リザルトBGM
		SOUND_LABEL_SELECT000,			// 決定音(タイトル、リザルト、ポーズ)
		SOUND_LABEL_SELECT001,			// 選択音(チュートリアル、ポーズ、リザルト)
		SOUND_LABEL_PAUSE,				// ポーズ表示(ポーズ)
		SOUND_LABEL_PLAYER_BULLET,		// PLAYER発射音(プレイヤー)
		SOUND_LABEL_ENEMY_BULLET,		// ENEMEY発射音(エネミー)る
		SOUND_LABEL_PLAYER_DAMEGE,		// ダメージ(プレイヤー)音
		SOUND_LABEL_ENEMY_DAMEGE,		// ダメージ(エネミー)
		SOUND_LABEL_SKILL,				// スキル発動
		SOUND_LABEL_SKILL_SELECT,		// スキル切り替え
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void AllStopSound(void);

private:
	typedef struct
	{
		char					*m_pFilename;						// ファイル名
		int						m_nCntLoop;							// ループカウント(-1でループ再生)
	}SOUNDPARAM;

	IXAudio2					*m_pXAudio2;						// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice		*m_pMasteringVoice;					// マスターボイスへのポインタ
	IXAudio2SourceVoice			*m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイスへのポインタ
	BYTE						*m_apDataAudio[SOUND_LABEL_MAX];	// オーディオデータへのポインタ
	DWORD						m_aSizeAudio[SOUND_LABEL_MAX];		// オーディオデータサイズ
	SOUNDPARAM					m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/BGM000.wav", -1 },			// タイトルBGM
		{ "data/BGM/BGM001.wav", -1 },			// チュートリアルBGM
		{ "data/BGM/BGM002.wav", -1 },			// ゲームBGM
		{ "data/BGM/BGM003.wav", -1 },			// リザルトBGM
		{ "data/SE/select000.wav", 0 },			// 決定音(タイトル、リザルト、ポーズ)
		{ "data/SE/select001.wav", 0 },			// 選択音(チュートリアル、ポーズ、リザルト)
		{ "data/SE/puse000.wav", 0 },			// ポーズ表示(ポーズ)
		{ "data/SE/bullet000.wav", 0 },			// PLAYER発射音(プレイヤー)
		{ "data/SE/bullet001.wav", 0 },			// ENEMEY発射音(エネミー)
		{ "data/SE/DamageSound000.wav", 0 },	// ダメージ(プレイヤー)
		{ "data/SE/emenyDamege.wav", 0 },		// ダメージ(エネミー)
		{ "data/SE/skill_select000.wav", 0 },	// スキル発動
		{ "data/SE/skill_select001.wav", 0 },	// スキル切り替え
	};											// 各音素材のパラメータ
};
#endif