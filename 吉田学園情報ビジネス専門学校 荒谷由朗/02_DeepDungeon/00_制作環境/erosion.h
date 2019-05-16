//=============================================================================
//
// �Z�H�x���� [erosion.h]
// Author : �N�H�x 
//
//=============================================================================
#ifndef _EROSION_H_
#define _EROSION_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//****************************************************************************
#define MAX_EROSION (2)
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
	bool bUse;
	int nErosion;		//�������̐Z�H�x
	int nErosionNum;		//�������l

}EROSION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitErosion(void);		//�u�[�X�g�Q�[�W������
void UninitErosion(void);	//�u�[�X�g�Q�[�W�I��
void UpdateErosion(void);	//�u�[�X�g�Q�[�W�X�V
void DrawErosion(void);		//�u�[�X�g�Q�[�W�`��

void IncreaseErosion(int nNumErosion);

int GetnCntErosion(void);

#endif
