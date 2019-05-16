//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERNEXT_H_
#define _SENCERNEXT_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;
	float fRadius;
}SENCERNEXT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerNext(void);		//�Z���T�[������
void UninitSencerNext(void);	//�Z���T�[�I��
void UpdateSencerNext(void);	//�Z���T�[�X�V
void DrawSencerNext(void);		//�Z���T�[�`��

int SetSencerNext(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool CollisionSencerNext(D3DXVECTOR3 *pos);

void DeleteSencerNext(int nCnt);
#endif
