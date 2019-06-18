//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 posStart;				// �A�C�e���̏����ʒu
	D3DXVECTOR3 pos;					// �A�C�e���̈ʒu
	D3DXVECTOR3 posOld;					// �A�C�e���̈ʒu(�ߋ�)
	D3DXVECTOR3 move;					// �A�C�e���̈ړ���
	int			nCounterAnim;			// �A�j���[�V�����J�E���^�[
	int			nPatternAnim;			// �A�j���[�V�����p�^�[��No.
	int			fAngle;
	int			nDirectionMove;			// 0->�E�������Ă���A1->���������Ă���
	float		fWidth;					// ��
	float		fHeight;				// ����
	float		fVerLimit;
	float		fLimit;
	bool		bUse;					// �g�p���Ă��邩�ǂ���
}Item;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitItem		(void);
void	UninitItem		(void);
void	UpdateItem		(void);
void	DrawItem		(void);
void	SetItem			(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fHorLimit, float fWidth, float fHeight);
bool	CollisionItem	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,float fHeight, float fWidth);
Item	*GetItem		(void);
int		GetItemNumber	(void);
#endif