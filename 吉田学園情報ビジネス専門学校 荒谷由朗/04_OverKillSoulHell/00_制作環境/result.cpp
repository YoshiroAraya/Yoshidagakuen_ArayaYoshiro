//=============================================================================
//
// ���U���g���� [result.h]
// Author :		�r�J�R�N
//
//=============================================================================
#include "result.h"
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
CResult::CResult()
{

}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CResult::Init(void)
{
	// �w�i�̐���
	CBg::Load();
	CBg::Create();

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM003);

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CResult::Uninit(void)
{
	CBg::Unload();
	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
//�@�X�V����
//=============================================================================
void CResult::Update(void)
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

	// �W���C�p�b�h�̏�ԍX�V
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}