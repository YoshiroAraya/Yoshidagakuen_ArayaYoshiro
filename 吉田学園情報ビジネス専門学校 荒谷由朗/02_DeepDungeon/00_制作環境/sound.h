//***************************************************************************//
//
// �T�E���h���� [sound.h]
// Author : TEAM_Fascinator
//
//***************************************************************************//
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//***************************************************************************//
// �T�E���h�t�@�C��
//***************************************************************************//
typedef enum
{
	SOUND_LABEL_BGM000 = 0,				// �^�C�g��
	SOUND_LABEL_BGM001,					// �L�����N�^�[�Z���N�g
	SOUND_LABEL_BGM002,					// �M�������[
	SOUND_LABEL_BGM003,					// �v�����[�O
	SOUND_LABEL_BGM004,					// �Q�[��
	SOUND_LABEL_BGM005,					// �{�X�o�g��
	SOUND_LABEL_BGM006,					// �cᏋC75��
	SOUND_LABEL_BGM007,					// �cᏋC50��
	SOUND_LABEL_BGM008,					// �cᏋC25��
	SOUND_LABEL_BGM009,					// �cᏋC0��
	SOUND_LABEL_SE_DECISION,			// ����
	SOUND_LABEL_SE_PROLOGUE_DECISION,	// �`���[�g���A������
	SOUND_LABEL_SE_SELECT,				// �I��
	SOUND_LABEL_SE_PAUSE_DECISION,		// �|�[�Y����
	SOUND_LABEL_SE_CANCEL,				// �L�����Z��
	SOUND_LABEL_SE_FOOTSTEP,				// �L�����Z��
	SOUND_LABEL_SE_DEAD,				// ���S
	SOUND_LABEL_SE_SLASH,				// �a��
	SOUND_LABEL_SE_FIRE,				// ��
	SOUND_LABEL_SE_SLASH2,				// �a��2
	SOUND_LABEL_SE_HIT,					// �a��2
	SOUND_LABEL_SE_HIT2,					// �a��2
	SOUND_LABEL_SE_EXPLOSION,					// �a��2
	SOUND_LABEL_SE_HIT3,					// �a��2
	SOUND_LABEL_SE_MEKURI,					// �a��2
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//***************************************************************************//
// �v���g�^�C�v�錾(Sound)
//***************************************************************************//
HRESULT InitSound(HWND hWnd);
HRESULT PlaySound(SOUND_LABEL label); // �Q�[���̏������߂��@
void UninitSound(void);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
