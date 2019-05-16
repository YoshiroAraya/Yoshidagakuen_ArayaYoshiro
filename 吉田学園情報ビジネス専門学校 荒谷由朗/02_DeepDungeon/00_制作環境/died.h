//***************************************************************************//
//
// ���S������ [died.h]
// Author : KishidaRei
//
//***************************************************************************//
#ifndef _DIED_H_
#define _DIED_H_

#include "main.h"
//***************************************************************************//
// �\���̐錾
//***************************************************************************//
typedef enum
{
	DIEDTYPE_APPER = 0,
	DIEDTYPE_NORMAL,
	DIEDTYPE_MAX
}DIEDTYPE;

typedef struct
{

	D3DXVECTOR3 pos;								// �ʒu
	D3DXVECTOR3 rot;								// �ړ�
	D3DXCOLOR Col;								//�F
	bool bUse;									//�g�p���Ă��邩
	DIEDTYPE type;								//�^�C�v				
}DIED;
//***************************************************************************//
// �v���g�^�C�v�錾
//***************************************************************************//
void InitDied(void);
void UninitDied(void);
void UpdateDied(void);
void DrawDied(void);
DIED *GetDied(void);

#endif