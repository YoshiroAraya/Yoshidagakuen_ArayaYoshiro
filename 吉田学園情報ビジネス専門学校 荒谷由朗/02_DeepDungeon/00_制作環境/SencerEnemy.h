//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERENEMY_H_
#define _SENCERENEMY_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************
typedef enum
{
	SENCERENEMYTYPE_PLAYER = 0,
	SENCERENEMYTYPE_ENEMY,
	SENCERENEMYTYPE_MAX
}SENCERENEMYTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	SENCERENEMYTYPE type;
	bool bUse;
	float fRadius;
}SENCERENEMY;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerEnemy(void);		//�Z���T�[������
void UninitSencerEnemy(void);	//�Z���T�[�I��
void UpdateSencerEnemy(void);	//�Z���T�[�X�V
void DrawSencerEnemy(void);		//�Z���T�[�`��

void SetPositionSencerEnemy(int nIdxSencer, D3DXVECTOR3 pos);
void DeleteSencerEnemy(int nIdxSencerCol);

int SetSencerEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
int CollisionSencer_Lock_ReturnEnemy(D3DXVECTOR3 *pos, int nCntEnemy);

bool CollisionSencer_Enemy(D3DXVECTOR3 *pos, int nCntSencerEnemy);
bool CollisionSencer_Enemy_Arrow(D3DXVECTOR3 *pos);

#endif
