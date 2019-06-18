//=============================================================================
//
// ���͏��� [input.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define JOYPAD_MAX			(1)		// �W���C�p�b�h�̐ڑ���

//=============================================================================
// ���̓N���X
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
	static LPDIRECTINPUT8	m_pInput;		// �I�u�W�F�N�g�{�̂�1��
	LPDIRECTINPUTDEVICE8	m_pDevice;		// �f�o�C�X�̐��������
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
	BYTE m_aKeyState		[NUM_KEY_MAX];		// �v���X�̏��
	BYTE m_aKeyStateTrigger	[NUM_KEY_MAX];		// �g���K�[�̏��
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
	JoyState	m_aJoypadState[JOYPAD_MAX];		// �W���C�p�b�h�̏��
	bool		m_abConnection[JOYPAD_MAX];		// �W���C�p�b�h�̐ڑ����
};
#endif