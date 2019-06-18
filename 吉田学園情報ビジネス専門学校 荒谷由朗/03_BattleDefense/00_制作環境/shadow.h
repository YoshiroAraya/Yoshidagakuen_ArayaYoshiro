//=============================================================================
//
// �e�̏��� [shadow.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitShadow			(void);
void	UninitShadow		(void);
void	UpdateShadow		(void);
void	DrawShadow			(void);
void	SetPositionShadow	(int nIdyShadow, D3DXVECTOR3 pos);
void	DeleteShadow		(int nIdyShadow);
int		SetShadow			(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif