//=============================================================================
//
// ����ʏ��� [tuto.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	RESULTSTATE_NONE = 0,
	RESULTSTATE_USE,
	RESULTSTATE_MAX
}RESULTSTATE;

typedef enum
{
	RESULTPAGE_ONE = 0,
	RESULTPAGE_TWO,
	RESULTPAGE_THREE,
	RESULTPAGE_FOUR,
	RESULTPAGE_FIVE,
	RESULTPAGE_MAX
}RESULTPAGE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�J���|
	int nType;			//���
	RESULTSTATE state;
	RESULTPAGE page;
	bool bUse;
}RESULT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);


#endif


