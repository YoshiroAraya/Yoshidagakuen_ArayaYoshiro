//=============================================================================
//
// �|���S������ [MeshFild.h]
// Author : ��Ո�
//
//=============================================================================
#ifndef WALLNOSS_H_
#define WALLNOSS_H_

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
	int VertexStage;			//�o�[�e�b�N�X
	int IndexStage;				//�C���f�b�N�X
	int PolygonStage;			//�|���S����
	D3DXVECTOR3 aPos[4];		//�x�N�g��
	D3DXVECTOR3 VecA;
	D3DXVECTOR3 VecC;

}WallBoss;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWallBoss(void);
void UninitWallBoss(void);
void UpdateWallBoss(void);
void DrawWallBoss(void);

WallBoss*GetWallBoss(void);
void SetWallBoss(int Width, int Heidth, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void CollisionWallBoss_WIDTHBack_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//���ʂ����蔻��
void CollisionWallBoss_WIDTHThisSide_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//��O�ǂ����蔻��
void CollisionWallBoss_RIGHT_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//�E�ǂ����蔻��
void CollisionWallBoss_LEFT_PL(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//���ǂ����蔻��
void CollisionWallBoss_WIDTHBack_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//���ʂ����蔻��
void CollisionWallBoss_WIDTHThisSide_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//��O�ǂ����蔻��
void CollisionWallBoss_RIGHT_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//�E�ǂ����蔻��
void CollisionWallBoss_LEFT_Ene(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld);//���ǂ����蔻��


#endif
