//=============================================================================
//
// �w�i���� [Select_Yes.h]
// Author :TEAM_Fascinator
//
//=============================================================================
#ifndef _SELECT_YES_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _SELECT_YES_

#include "main.h"

typedef enum
{
	YESSTATE_SELECT = 0,
	YESSTATE_NOSELECT,
	YESSTATE_MAX

} YESSTATE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSelectYes(void);
void UninitSelectYes(void);
void UpdateSelectYes(void);
void DrawSelectYes(void);

void SetSelectYes(YESSTATE state);

#endif
