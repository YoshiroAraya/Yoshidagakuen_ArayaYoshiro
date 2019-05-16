//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM_�^�C�g��
	// BGM_�`���[�g���A��
	SOUND_LABEL_BGM001,			// BGM_�Q�[��
	SOUND_LABEL_BGM002,			// BGM_�N���A
	SOUND_LABEL_BGM003,			// BGM_�I�[�o�[
	// ����
	SOUND_LABEL_SE_PLEYERDAMEZ,	// �_���[�W
	SOUND_LABEL_SE_POUZU,		// �|�[�Y�I��
	SOUND_LABEL_SE_PLEYERBAD,	// ���S
	SOUND_LABEL_SE_SELEKUTO,	// ���艹
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
