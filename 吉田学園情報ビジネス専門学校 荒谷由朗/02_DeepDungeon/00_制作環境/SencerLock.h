//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERLOCK_H_
#define _SENCERLOCK_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************
typedef enum
{
	SENCERLOCKTYPE_PLAYER = 0,
	SENCERLOCKTYPE_ENEMY,
	SENCERLOCKTYPE_MAX
}SENCERLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	SENCERLOCKTYPE type;
	bool bUse;
	float fRadius;
}SENCERLOCK;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerLock(void);		//�Z���T�[������
void UninitSencerLock(void);	//�Z���T�[�I��
void UpdateSencerLock(void);	//�Z���T�[�X�V
void DrawSencerLock(void);		//�Z���T�[�`��

void SetPositionSencerLock(int nIdxSencer, D3DXVECTOR3 pos);
void DeleteSencerLock(int nIdxSencerCol);

int SetSencerLock(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
int CollisionSencer_Lock_ReturnEnemy(D3DXVECTOR3 *pos, int nCntEnemy);

bool CollisionSencer_Lock(D3DXVECTOR3 *pos);

#endif
