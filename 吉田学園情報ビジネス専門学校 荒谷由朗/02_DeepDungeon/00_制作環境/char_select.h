//=============================================================================
//
// ����ʏ��� [char_select.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _CHAR_SELECT_H_
#define _CHAR_SELECT_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	CHARACTER_TYPE_SOLDIER = 0,
	CHARACTER_TYPE_WARRIOR,
	CHARACTER_TYPE_SORCERER,
	CHARACTER_TYPE_MAX,
}CHARACTER_TYPE;

typedef enum
{
	SELECTSTATE_NONE = 0,
	SELECTSTATE_USE,
	SELECTSTATE_MAX
}SELECT_STATE;

typedef enum
{
	PAGE_ONE = 0,
	PAGE_TWO,
	PAGE_THREE,
	PAGE_MAX
}PAGE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�J���|
	int nType;			//���
	SELECT_STATE state;
	PAGE page;
	bool bUse;
	bool select;
}SELECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCharSelect(void);
void UninitCharSelect(void);
void UpdateCharSelect(void);
void DrawCharSelect(void);
CHARACTER_TYPE GetCharaType(void);

#endif


