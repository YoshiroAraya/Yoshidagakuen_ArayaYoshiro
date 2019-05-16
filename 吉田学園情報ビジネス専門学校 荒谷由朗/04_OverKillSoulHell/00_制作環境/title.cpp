//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "title.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// �w�i�̐���
	CBg::Load();
	CBg::Create();

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CTitle::Uninit(void)
{
	CBg::Unload();
	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
//�@�X�V����
//=============================================================================
void CTitle::Update(void)
{
	CFade::FADE fade = CFade::GetFade();

	CInputKeyboard *pKey = CManager::GetInputKeyboard();		// ���͏��̎擾

	CInputJoyPad *apInputJoyPad[1] = {};
	apInputJoyPad[0] = CManager::GetInputJoyPad();
	// �W���C�p�b�h�{�^����Ԃ̎擾
	CInputJoyPad::JoyState apJoyState[1];
	apJoyState[0] = apInputJoyPad[0]->GetJoyState(0);
	// �W���C�p�b�h�ڑ���Ԃ̎擾
	bool abConect[1] = {};
	abConect[0] = apInputJoyPad[0]->GetConnect(0);
	// �W���C�p�b�h���̎擾
	XINPUT_STATE state;
	XInputGetState(0, &state);

	if (pKey != NULL)
	{
		if (pKey->GetTrigger(DIK_RETURN) == true ||
			state.Gamepad.wButtons & XINPUT_GAMEPAD_B && abConect[0] == true)
		{
			if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
			{
				if (fade != CFade::FADE_OUT)
				{
					//���[�h�ݒ�
					CFade::SetFade(CManager::MODE_TUTORIAL);
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
				}
			}
			apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
		}
	}
	// �W���C�p�b�h�̏�ԍX�V
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}