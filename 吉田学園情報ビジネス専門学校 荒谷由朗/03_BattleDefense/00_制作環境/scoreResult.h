//=============================================================================
//
// �X�R�A���� [scoreResult.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _SCORERESULT_H_
#define _SCORERESULT_H_

#include "main.h"

//=============================================================================
// �\����
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9		pTextureScoreResult = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffScoreResult = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	int						nScoreResult;					// �X�R�A
	int						MAX_SCORERESULT		= 8;		// ����
	int						nCntTimeScoreResult;			// �J�E���^�[
	int						nTimeScoreResult;				// ���U���g�J�E���^�[
}SCORERESULT;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitScoreResult	(void);
void UninitScoreResult	(void);
void UpdateScoreResult	(void);
void DrawScoreResult	(void);
void AddTimeScore		(int nValue);
#endif