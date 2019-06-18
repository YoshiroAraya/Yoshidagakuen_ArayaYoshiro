//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERARROW_H_
#define _SENCERARROW_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************
typedef enum
{
	SENCERARROWTYPE_PLAYER = 0,
	SENCERARROWTYPE_ENEMY,
	SENCERARROWTYPE_MAX
}SENCERARROWTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	SENCERARROWTYPE type;
	bool bUse;
	float fRadius;
}SENCERARROW;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerEnemyArrow(void);		//�Z���T�[������
void UninitSencerEnemyArrow(void);	//�Z���T�[�I��
void UpdateSencerEnemyArrow(void);	//�Z���T�[�X�V
void DrawSencerEnemyArrow(void);		//�Z���T�[�`��

void SetPositionSencerEnemyArrow(int nIdxSencer, D3DXVECTOR3 pos);
void DeleteSencerEnemyArrow(int nIdxSencerCol);

int SetSencerEnemyArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

bool CollisionSencer_EnemyArrow(D3DXVECTOR3 *pos, int nCntSencerEnemy);

#endif
