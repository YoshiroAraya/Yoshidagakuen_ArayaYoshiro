//=============================================================================
//
// ����ʏ��� [tuto.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _PROLOGUE_H_
#define _PROLOGUE_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	PROLOGUESTATE_NONE = 0,
	PROLOGUESTATE_USE,
	PROLOGUESTATE_MAX
}PROLOGUESTATESTATE;

typedef enum
{
	PROLOGUESPAGE_ONE = 0,
	PROLOGUESPAGE_TWO,
	PROLOGUESPAGE_THREE,
	PROLOGUESPAGE_FOUR,
	PROLOGUESPAGE_FIVE,
	PROLOGUESPAGE_MAX
}PROLOGUESPAGE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�J���|
	int nType;			//���
	PROLOGUESTATESTATE state;
	PROLOGUESPAGE page;
	bool bUse;
}PROLOGUE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPrologue(void);
void UninitPrologue(void);
void UpdatePrologue(void);
void DrawPrologue(void);


#endif


