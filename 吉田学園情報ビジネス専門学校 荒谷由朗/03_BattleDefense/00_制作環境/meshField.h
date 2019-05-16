//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXCOLOR col;
	bool bUse;
}MeshField;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);

#endif
