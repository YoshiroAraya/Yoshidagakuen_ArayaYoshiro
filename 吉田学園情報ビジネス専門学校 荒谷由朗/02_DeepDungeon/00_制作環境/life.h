//=============================================================================
//
// ���C�t���� [life.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//****************************************************************************
#define MAX_LIFE (128)

//*****************************************************************************
// �\���̐錾
//****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 ParentPos;
	D3DXVECTOR3 ParentRot;
	D3DXCOLOR col;
	int nMaxLife;		//�������l�̍ő�l
	int nMaxLifeGuage; //��������HP�̍ő�l
	bool bUse;
}LIFE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLife(void);		//���C�t������
void UninitLife(void);		//���C�t�I��
void UpdateLife(void);		//���C�t�X�V
void DrawLife(void);		//���C�t�`��
void HitDamage(int nDamage);
void DecreaseMaxLife(int nLife);

#endif
