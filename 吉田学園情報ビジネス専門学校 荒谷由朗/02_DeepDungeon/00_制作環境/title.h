//===========================================================================
//
// �^�C�g������ [Title.h]
// Author : TEAM_Fascinator
//
//===========================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//===========================================================================
// �^�C�g���̍\����
//===========================================================================
typedef enum
{
	TITLE_STATE_NONE = 0,
	TITLE_STATE_USE,
	TITLE_STATE_MAX
}TITLE_STATE;

typedef enum
{
	CHOICE_ONE = 0,
	CHOICE_TWO,
	CHOICE_THREE,
	CHOICE_MAX
}TITLE_CHOICE;

//===========================================================================
// �v���g�^�C�v�錾(Title)
//===========================================================================
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
#endif