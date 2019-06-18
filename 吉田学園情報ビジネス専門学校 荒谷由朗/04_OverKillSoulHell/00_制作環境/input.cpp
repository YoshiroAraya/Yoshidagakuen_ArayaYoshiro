//=============================================================================
//
// 入力処理 [input.cpp]
// Author :	荒谷 由朗
//
//=============================================================================
#include "input.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// 基本入力クラスのコンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// 基本入力クラスのデストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 基本入力クラスの初期化
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// NULLだったら
		// DirectInputオブジェクトの生成
		if (DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================================================
// 基本入力クラスの終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// 入力デバイスの開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// キーボードクラスのコンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// キー情報のクリア
	for (int nCntKeyState = 0; nCntKeyState < NUM_KEY_MAX; nCntKeyState++)
	{
		m_aKeyState[nCntKeyState] = 0;
	}
}

//=============================================================================
// キーボードクラスのデストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 親クラスの初期化処理の呼び出し
	CInput::Init(hInstance, hWnd);

	// 入力デバイスの生成
	if (m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// デバイスへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// 親クラスの終了処理の呼び出し
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE	aKeyState[NUM_KEY_MAX];
	int		nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// キーボードの入力情報保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();		// キーボードへのアクセス権を獲得
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// ジョイパッドクラスのコンストラクタ
//=============================================================================
CInputJoyPad::CInputJoyPad()
{
	for (int nCntPad = 0; nCntPad < JOYPAD_MAX; nCntPad++)
	{
		m_aJoypadState[nCntPad] = INPUT_JOYSTATE_NOTPUSH;
		m_abConnection[nCntPad] = false;
	}
}

//=============================================================================
// ジョイパッドクラスのデストラクタ
//=============================================================================
CInputJoyPad::~CInputJoyPad()
{
}

//=============================================================================
// ジョイパッドクラスの初期化処理
//=============================================================================
void CInputJoyPad::Init(void)
{
	DWORD dwResult;

	for (DWORD dCnt = 0; dCnt < JOYPAD_MAX; dCnt++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(dCnt, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			// デッドゾーンの設定
			if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbLX = 0;
				state.Gamepad.sThumbLY = 0;
			}

			if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbRX = 0;
				state.Gamepad.sThumbRY = 0;
			}

			m_abConnection[dCnt] = true;
		}
		else
		{
			m_abConnection[dCnt] = false;
		}
	}
}

//=============================================================================
// ジョイパッドクラスの終了処理
//=============================================================================
void CInputJoyPad::Uninit(void)
{
	XInputEnable(false);
}

//=============================================================================
// ジョイパッドクラスの更新処理
//=============================================================================
void CInputJoyPad::Update(void)
{
	for (int nCntPad = 0; nCntPad < JOYPAD_MAX; nCntPad++)
	{
		if (m_aJoypadState[nCntPad] == INPUT_JOYSTATE_PUSH)
		{
			m_aJoypadState[nCntPad] = INPUT_JOYSTATE_NONE;
		}
		else if (m_aJoypadState[nCntPad] == INPUT_JOYSTATE_NONE)
		{
			m_aJoypadState[nCntPad] = INPUT_JOYSTATE_NOTPUSH;
		}
	}
}

//=============================================================================
// ジョイパッド状態の取得
//=============================================================================
void CInputJoyPad::SetJoyState(JoyState joyState, int type)
{
	m_aJoypadState[type] = joyState;
}