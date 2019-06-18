//=============================================================================
//
// �|���S������ [MeshFild.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef STAGEBOSS_H_
#define STAGEBOSS_H_

#include "main.h"
#include "Game.h"

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct
{
	int VertexStage;			//�o�[�e�b�N�X
	int IndexStage;				//�C���f�b�N�X
	int PolygonStage;			//�|���S����
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int Width;					//��
	int Heidth;					//�c
	bool bUse;					//�g�p��

}StageBoss;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitStageBoss(void);
void UninitStageBoss(void);
void UpdateStageBoss(void);
void DrawStageBoss(void);

StageBoss*GetStageBoss(void);
void SetStageMapBoss(int Width, int Heidth, D3DXVECTOR3 pos);
#endif
