//***************************************************************************//
//
// ���b�Z�[�W���� [Message.h]
// Author : KishidaRei
//
//***************************************************************************//
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
//***************************************************************************//
// �\���̐錾
//***************************************************************************//
typedef enum
{
	MESSAGETYPE_APPER = 0,
	MESSAGETYPE_NORMAL,
	MESSAGETYPE_MAX
}MESSAGETYPE;

typedef struct
{

	D3DXVECTOR3 pos;								// �ʒu
	D3DXVECTOR3 rot;								// �ړ�
	D3DXCOLOR Col;								//�F
	bool bUse;									//�g�p���Ă��邩
	MESSAGETYPE type;								//�^�C�v	
	int nType;
}MESSAGE;
//***************************************************************************//
// �v���g�^�C�v�錾
//***************************************************************************//
void InitMessage(void);
void UninitMessage(void);
void UpdateMessage(void);
void DrawMessage(void);
void DeleteMessage(void);

MESSAGE *GetMessageBox(void);

void SetMessageBox(D3DXVECTOR3 pos, int ntype);
#endif