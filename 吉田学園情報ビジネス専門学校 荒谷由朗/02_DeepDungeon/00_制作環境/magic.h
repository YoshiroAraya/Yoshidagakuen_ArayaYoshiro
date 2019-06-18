//=============================================================================
//
// ���@�U������ [magic.h]
// Author : komatsu keisuke
//
//=============================================================================
#ifndef _MAGIC_H_
#define _MAGIC_H_

#include "main.h"

//=============================================================================
// ���@�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 move;			//�ړ���
	D3DXMATRIX mtxWorldMagic;	//���[���h�}�g���b�N�X
	int nLife;					//���ł܂ł̎���
	int nIdxShadow;				//�e�ԍ�
	bool bUse;					//�g�p��
	int nType;
}BULLET;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitMagic(void);
void UninitMagic(void);
void UpdateMagic(void);
void DrawMagic(void);
void SetMagic(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move , int nLife, int nType);
void Set_L_Magic(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife , int nType);

#endif
