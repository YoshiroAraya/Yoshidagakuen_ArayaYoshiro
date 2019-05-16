//=============================================================================
//
// ���@�w���� [magicsquare.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _MAGICSQUARE_H_
#define _MAGICSQUARE_H_

#include "main.h"

//=============================================================================
// �e�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ��]
	D3DXCOLOR col;				//�J���[
	D3DXMATRIX mtxWorldMagicSquare;	// ���[���h�}�g���b�N�X
	float fRadius;				// ��
	float fWidth;				// ��
	float fDepth;				// ���s
	int nIdxSencer;				//�Z���T�[�̔ԍ�
	bool bUse;
}MAGICSQUARE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitMagicSquare(void);
void UninitMagicSquare(void);
void UpdateMagicSquare(void);
void DrawMagicSquare(void);
int SetMagicSquare(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
void DeleteMagicSquare(int nIdxMagicSquare);

void DeleteOnlyMagicSquare(int nCntMagicsquare);
MAGICSQUARE *GetMagicSquare(void);

#endif
