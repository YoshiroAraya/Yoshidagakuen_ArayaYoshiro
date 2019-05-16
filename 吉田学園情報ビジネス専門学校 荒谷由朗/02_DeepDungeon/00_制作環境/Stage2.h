//=============================================================================
//
// �|���S������ [MeshFild.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef STAGE2_H_
#define STAGE2_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int Width;					//��
	int Heidth;					//�c
	bool bUse;					//�g�p��

}Stage2;
typedef struct
{
	int VertexStage;			//�o�[�e�b�N�X
	int IndexStage;				//�C���f�b�N�X
	int PolygonStage;			//�|���S����

}StageVtx2;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStage2(void);
void UninitStage2(void);
void UpdateStage2(void);
void DrawStage2(void);

Stage2*GetStage2(void);
void SetStageMap2(int Width, int Heidth, D3DXVECTOR3 pos);
#endif
