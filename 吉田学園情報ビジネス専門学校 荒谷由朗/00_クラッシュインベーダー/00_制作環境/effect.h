//=============================================================================
//
// �G�t�F�N�g���� [efect.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _EFECT_H_
#define _EFECT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius);

#endif

