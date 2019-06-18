//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERENABLEATTACK_H_
#define _SENCERENABLEATTACK_H_

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
}SENCERENABLEATTACK;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerEnableAttack(void);		//�Z���T�[������
void UninitSencerEnableAttack(void);	//�Z���T�[�I��
void UpdateSencerEnableAttack(void);	//�Z���T�[�X�V
void DrawSencerEnableAttack(void);		//�Z���T�[�`��

void SetPositionSencerEnableAttack(int nIdxSencer, D3DXVECTOR3 pos);
void DeleteSencerEnableAttack(int nIdxSencerCol);

int SetSencerEnableAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

bool CollisionSencer_Enable(D3DXVECTOR3 *pos);

#endif
