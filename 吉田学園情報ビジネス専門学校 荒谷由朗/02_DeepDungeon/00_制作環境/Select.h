//=============================================================================
//
// �w�i���� [Pause.h]
// Author :TEAM_Fascinator
//
//=============================================================================
#ifndef _SELECT_H_ //��\�C���N���[�h�h�~�̃}�N����`
#define _SELECT_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	STAGESERECTSATE_NONE = 0,
	STAGESERECTSATE_YES,	//���̊K�ɐi��
	STAGESERECTSATE_NO,		//�i�܂Ȃ�
	STAGESERECTSATE_MAX

} STAGESERECTSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
#endif
