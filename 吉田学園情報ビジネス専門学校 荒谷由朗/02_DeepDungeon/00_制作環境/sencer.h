//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCER_H_
#define _SENCER_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************
typedef enum
{
	SENCERTYPE_NONE = 0,
	SENCERTYPE_MAGICSQUARE,
	SENCERTYPE_ATACK,
	SENCERTYPE_NEXTSTAGE,
	SENCERTYPE_COLLISION,
	MAXTYPE_SENCER
}SENCERTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;
	float fRadius;
	SENCERTYPE type;
}SENCER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencer(void);		//�Z���T�[������
void UninitSencer(void);	//�Z���T�[�I��
void UpdateSencer(void);	//�Z���T�[�X�V
void DrawSencer(void);		//�Z���T�[�`��

void DeleteSencer(int nIdxSencer);
int SetSencer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SENCERTYPE type);
bool CollisionSencer(D3DXVECTOR3 *pos);
int CollisionSencerReturnCnt(D3DXVECTOR3 *pos);

#endif
