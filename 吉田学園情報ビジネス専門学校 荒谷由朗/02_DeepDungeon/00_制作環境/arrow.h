//=============================================================================
//
// �|���� [arrow.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "main.h"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posold;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 rot;			//��]
	D3DXCOLOR col;				//�F
	D3DXVECTOR3 vtxMin;			//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;			//���f���̍ő�l
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nIdxShadow;				//�e�ԍ�
	int nLife;					//���C�t
	bool bUse;					//�g�p��
}ARROW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);

ARROW*GetArrow(void);

void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife);
#endif
