//=============================================================================
//
// ���C�t���� [life.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//****************************************************************************
#define MAX_LIFE (128)
//*****************************************************************************
// �\���̐錾
//****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 ParentPos;
	D3DXVECTOR3 ParentRot;
	D3DXCOLOR col;
	D3DXVECTOR3 fAngle;
	float		nAngle;
	float		nHeight;
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;
	float RADIUS;		// ���a
	bool bUse;
}LIFE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLife(void);		//���C�t������
void UninitLife(void);	//���C�t�I��
void UpdateLife(void);	//���C�t�X�V
void DrawLife(void);		//���C�t�`��
LIFE *GetLife(void);

//void SetLife(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Parentpos, D3DXVECTOR3 Parentrot, D3DXCOLOR col);
void HitDamage(int nDamage);
bool CollisionClinder(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
double Norm(double *vec, int nCntDimensions);
#endif
