//=============================================================================
//
// �U���p�Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERATK_H_
#define _SENCERATK_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************
typedef enum
{
	SENCERATKTYPE_NONE = 0,
	SENCERATKTYPE_MAGICSQUARE,
	SENCERATKTYPE_ATACK,
	SENCERATKTYPE_NEXTSTAGE,
	SENCERATKTYPE_COLLISION,
	MAXTYPE_SENCERATK
}SENCERATKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;
	float fRadius;
	SENCERATKTYPE type;
	int nIdxParent;
}SENCERATK;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerAtk(void);		//�Z���T�[������
void UninitSencerAtk(void);	//�Z���T�[�I��
void UpdateSencerAtk(void);	//�Z���T�[�X�V
void DrawSencerAtk(void);		//�Z���T�[�`��


void SetSencerAtk(D3DXVECTOR3 pos);
bool CollisionSencerAtk(float *fRadius, D3DXVECTOR3 *pos);
int CollisionSencerReturnCntAtk(D3DXVECTOR3 *pos);

#endif
