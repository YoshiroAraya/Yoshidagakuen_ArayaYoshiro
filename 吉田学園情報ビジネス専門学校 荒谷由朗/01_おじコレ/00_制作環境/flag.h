//=============================================================================
//
// �t���b�O���� [flag.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _FLAG_H_
#define _FLAG_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float		fWidth;		// ��
	float		fHeight;	// ����
	bool		bUse;		// �g�p���Ă��邩�ǂ���
}Flag;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitFlag		(void);
void UninitFlag		(void);
void UpdateFlag		(void);
void DrawFlag		(void);
void SetFlag		(D3DXVECTOR3 pos, float fWidth, float fHeight);
bool CollisionFlag	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
#endif