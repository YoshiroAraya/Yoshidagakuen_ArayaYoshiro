//=============================================================================
//
// 入力処理 [input.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define JOYPAD_MAX			(1)		// ジョイパッドの接続数

//=============================================================================
// 入力クラス
//=============================================================================
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init	(HINSTANCE hInstance, HWND hWnd);
	virtual void	Uninit	(void);
	virtual void	Update	(void) = 0;

protected:
	static LPDIRECTINPUT8	m_pInput;		// オブジェクト本体は1つ
	LPDIRECTINPUTDEVICE8	m_pDevice;		// デバイスの数だけ作る
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init		(HINSTANCE hInstance, HWND hWnd);
	void	Uninit		(void);
	void	Update		(void);

	bool	GetPress	(int nKey);
	bool	GetTrigger	(int nKey);

private:
	BYTE m_aKeyState		[NUM_KEY_MAX];		// プレスの状態
	BYTE m_aKeyStateTrigger	[NUM_KEY_MAX];		// トリガーの状態
};

class CInputJoyPad : public CInput
{
public:
	typedef enum
	{
		INPUT_JOYSTATE_NOTPUSH = 0,
		INPUT_JOYSTATE_PUSH,
		INPUT_JOYSTATE_NONE,
	}JoyState;

	CInputJoyPad();
	~CInputJoyPad();

	void Init		(void);
	void Uninit		(void);
	void Update		(void);

	void SetJoyState(JoyState joyState, int type);

	JoyState	GetJoyState	(int type) { return m_aJoypadState[type]; };
	bool		GetConnect	(int type) { return m_abConnection[type]; };

private:
	JoyState	m_aJoypadState[JOYPAD_MAX];		// ジョイパッドの状態
	bool		m_abConnection[JOYPAD_MAX];		// ジョイパッドの接続状態
};
#endif