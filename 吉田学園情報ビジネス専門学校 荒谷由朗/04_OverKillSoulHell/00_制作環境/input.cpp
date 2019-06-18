//=============================================================================
//
// ���͏��� [input.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// ��{���̓N���X�̃R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// ��{���̓N���X�̃f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ��{���̓N���X�̏�����
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// NULL��������
		// DirectInput�I�u�W�F�N�g�̐���
		if (DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================================================
// ��{���̓N���X�̏I������
//=============================================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�N���X�̃R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// �L�[���̃N���A
	for (int nCntKeyState = 0; nCntKeyState < NUM_KEY_MAX; nCntKeyState++)
	{
		m_aKeyState[nCntKeyState] = 0;
	}
}

//=============================================================================
// �L�[�{�[�h�N���X�̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �e�N���X�̏����������̌Ăяo��
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �f�o�C�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// �e�N���X�̏I�������̌Ăяo��
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE	aKeyState[NUM_KEY_MAX];
	int		nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̓��͏��ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �W���C�p�b�h�N���X�̃R���X�g���N�^
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
// �W���C�p�b�h�N���X�̃f�X�g���N�^
//=============================================================================
CInputJoyPad::~CInputJoyPad()
{
}

//=============================================================================
// �W���C�p�b�h�N���X�̏���������
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
			// �f�b�h�]�[���̐ݒ�
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
// �W���C�p�b�h�N���X�̏I������
//=============================================================================
void CInputJoyPad::Uninit(void)
{
	XInputEnable(false);
}

//=============================================================================
// �W���C�p�b�h�N���X�̍X�V����
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
// �W���C�p�b�h��Ԃ̎擾
//=============================================================================
void CInputJoyPad::SetJoyState(JoyState joyState, int type)
{
	m_aJoypadState[type] = joyState;
}