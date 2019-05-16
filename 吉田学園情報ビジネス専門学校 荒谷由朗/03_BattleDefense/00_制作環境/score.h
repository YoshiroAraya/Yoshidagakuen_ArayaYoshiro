//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

typedef struct
{
	LPDIRECT3DTEXTURE9		pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	int						nScore;					// �X�R�A
	int						MAX_SCORE;				// ����
}SCORE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue);
SCORE GetScore(void);

#endif