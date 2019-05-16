//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _STAGEFADE_H_
#define _STAGEFADE_H_

#include "main.h"
#include "game.h"

//*************************************
// �t�F�[�h�̏��
//*************************************
typedef enum
{
	STAGEFADE_NONE = 0,		// �������Ă��Ȃ����
	STAGEFADE_IN,			// �t�F�[�h�C�����
	STAGEFADE_OUT,			// �t�F�[�h�A�E�g���
	STAGEFADE_MAX
} STAGEFADE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStageFade(STAGEMODE modeNext);
void UninitStageFade(void);
void UpdateStageFade(void);
void DrawStageFade(void);

void SetStageFade(STAGEMODE modeNext);
STAGEFADE GetStageFade(void);

#endif
