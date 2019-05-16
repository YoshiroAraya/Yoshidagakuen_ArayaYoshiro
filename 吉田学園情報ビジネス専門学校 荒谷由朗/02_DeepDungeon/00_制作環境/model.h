//=============================================================================
//
// ���f������ [model.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//��]
	D3DXCOLOR col;				//�F
	D3DXVECTOR3 vtxMin;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;			//���f���̍ő�l
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nIdxShadow;				//�e�ԍ�
	bool bUse;					//�g�p��
}Model;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

Model*GetModel(void);
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);
#endif
