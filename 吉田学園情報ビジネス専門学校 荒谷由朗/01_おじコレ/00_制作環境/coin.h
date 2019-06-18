//=============================================================================
//
// �R�C������ [coin.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _COIN_H_
#define _COIN_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	int			nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int			nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	float		fWidth;				// ��
	float		fHeight;			// ����
	bool		bUse;				// �g�p���Ă��邩�ǂ���
}Coin;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitCoin		(void);
void UninitCoin		(void);
void UpdateCoin		(void);
void DrawCoin		(void);
void SetCoin		(D3DXVECTOR3 pos, float fWidth, float fHeight);
bool CollisionCoin	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
#endif