//=============================================================================
//
// �v���C���[�̃��C�t�Q�[�W���� [PlayerLife.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _PLAYERLIFE_H_
#define _PLAYERLIFE_H_

#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitPlayerLife		(void);
void	UninitPlayerLife	(void);
void	UpdatePlayerLife	(void);
void	DrawPlayerLife		(void);
void	HitPlayerLife		(int nDamage);
float	GetPlayerLife		(void);
#endif