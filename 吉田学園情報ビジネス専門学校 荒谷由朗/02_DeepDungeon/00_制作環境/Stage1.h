//=============================================================================
//
// �|���S������ [MeshFild.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef STAGE1_H_
#define STAGE1_H_

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

}Stage1;
typedef struct
{
	int VertexStage;			//�o�[�e�b�N�X
	int IndexStage;				//�C���f�b�N�X
	int PolygonStage;			//�|���S����

}StageVtx1;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStage1(void);
void UninitStage1(void);
void UpdateStage1(void);
void DrawStage1(void);

Stage1*GetStage1(void);
void SetStageMap1(int Width, int Heidth, D3DXVECTOR3 pos);
#endif
