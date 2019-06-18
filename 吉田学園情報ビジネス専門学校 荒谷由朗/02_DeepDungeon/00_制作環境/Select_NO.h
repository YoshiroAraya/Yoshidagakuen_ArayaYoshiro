//=============================================================================
//
// �w�i���� [Select.h]
// Author :TEAM_Fascinator
//
//=============================================================================
#ifndef _SELECTNO_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _SELECTNO_H_

#include "main.h"

typedef enum
{
	NOSTATE_SELECT = 0,
	NOSTATE_NOSELECT,
	NOSTATE_MAX

} NOSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSelectNo(void);
void UninitSelectNo(void);
void UpdateSelectNo(void);
void DrawSelectNo(void);

void SetSelectNo(NOSTATE state);

#endif