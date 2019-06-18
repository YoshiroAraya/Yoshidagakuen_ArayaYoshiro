//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERENABLEBOSS_H_
#define _SENCERENABLEBOSS_H_

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
}SENCERENABLEBOSS;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerEnableBoss(void);		//�Z���T�[������
void UninitSencerEnableBoss(void);	//�Z���T�[�I��
void UpdateSencerEnableBoss(void);	//�Z���T�[�X�V
void DrawSencerEnableBoss(void);		//�Z���T�[�`��

void SetPositionSencerEnableBoss(int nIdxSencer, D3DXVECTOR3 pos);
void DeleteSencerEnableBoss(int nIdxSencerCol);

int SetSencerEnableBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

bool CollisionSencer_EnableBoss(D3DXVECTOR3 *pos);

#endif
