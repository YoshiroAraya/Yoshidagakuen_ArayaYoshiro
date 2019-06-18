//=============================================================================
//
// ���C�t���� [life.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LIFE (128)

//=============================================================================
// �\���̐錾
//=============================================================================
typedef struct
{
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu(���S���W)
	D3DXVECTOR3 ParentPos;	// ���W(�I�t�Z�b�g)
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 ParentRot;	// ����(�I�t�Z�b�g)
	D3DXVECTOR3 fAngle;		// ����
	D3DXCOLOR	col;		// �F
	D3DXVECTOR3 vecA;		// �x�N�g��A
	D3DXVECTOR3 vecB;		// �x�N�g��B
	float		nAngle;		// ����
	float		nHeight;	// ����
	float		RADIUS;		// ���a
	bool		bUse;		// �g�p���Ă��邩
}LIFE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitLife			(void);
void	UninitLife			(void);
void	UpdateLife			(void);
void	DrawLife			(void);
LIFE	*GetLife			(void);
void	HitDamage			(int nDamage);
bool	CollisionClinder	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
double	Norm				(double *vec, int nCntDimensions);
#endif