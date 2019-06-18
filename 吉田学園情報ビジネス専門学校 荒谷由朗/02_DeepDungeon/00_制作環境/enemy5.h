//=============================================================================
//
// �G�l�~�[���� [Enemy1.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY5_H_
#define _ENEMY5_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_5 (2)

//#define MAX_PARTS (15)
#define MAX_E_PARTS_5 (17)
//*****************************************************************************
// �G�l�~�[�̍\����
//*****************************************************************************
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH pMesh = NULL;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;	//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;			//�}�e���A�����̐�
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 VtxMinModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	D3DXVECTOR3 VtxMaxModel = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 VecShot;	//�V���b�g�p�x�N�g��
	float fDestAngle;		//�ړI�̊p�x
	D3DXVECTOR3 fDestAngle_Axis;		//�ړI�̊p�x
	D3DXVECTOR3 fAngle_Axis;		//�ړI�̊p�x
	float fAngle;			//����
	float nIdxModelParent = -1;	//�e���f���̃C���f�b�N�X
	char FileName[256];
}PARTS_E_5;

typedef enum
{
	ENEMYSTATE_NONE_5 = 0,
	ENEMYSTATE_BACKHOME_5,
	ENEMYSTATE_DISCOVERY_5,
	ENEMYSTATE_MAX_5
}ENEMYSTATE_5;

typedef enum
{
	ENEMYSTATE2_NORMAL_5 = 0,
	ENEMYSTATE2_DAMAGE_5,
	ENEMYSTATE2_MAX_5
}ENEMYSTATE2_5;


typedef enum
{
	ENEMYSTATUS_NEUTRAL_5 = 0,
	ENEMYSTATUS_MOVE_5,
	ENEMYSTATUS_ATTACK_5,
	ENEMYSTATUS_JUMP_5,
	ENEMYSTATUS_LANDING_5,
	ENEMYSTATUS_GUARD_5,
	ENEMYSTATUS_DAMAGE1_5,
	ENEMYSTATUS_MAX_5
}ENEMYSTATUS_5;

//------------------------------------------------------------------------
// �����蔻��̍\����													 |
//------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorldCollision;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fRadius;
	int StartFlame;
	int EndFlame;
	bool bUse;
	int nCntMotion;
	int nIdxMotion;
	int nIdxParent;
}ENEMYCOLLISION_5;

typedef struct
{
	DWORD nNumMatEnemy = 0;	//�}�e���A���̏��̐�
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 move;	//����
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 VtxMinEnemy = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	D3DXVECTOR3 VtxMaxEnemy = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 HomePoint;
	float DestHome;
	ENEMYSTATE_5 state;
	ENEMYSTATE2_5 state2;
	ENEMYSTATUS_5 status;
	bool bUseJump;
	float fDestAngle;					//�ړI�̊p�x
	float fAngle;						//����
	float fLength;
	int nIndexShadow;					//�e�̔ԍ�
	int nIndexSencer;					//�Z���T�[(�����蔻��p)�̔ԍ�
	int nIndexSencerEnemy;				//�Z���T�[(AI�p)�̔ԍ�
	int nIndexSencerEnableAttack;		//�Z���T�[(�U���\����)�̔ԍ�
	int nLife;
	bool bUse;
	bool bHit;
	int nCntCoolDown ;
	int nCoolDown = 200;
	ENEMYCOLLISION_5 Collision;
	PARTS_E_5 aModel[MAX_E_PARTS_5];
}ENEMY_5;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy_5(void);
void UninitEnemy_5(void);
void UpdateEnemy_5(void);
void DrawEnemy_5(void);

void HitEnemy_5(int nDamage, int nCntEnemy);

ENEMY_5 *GetEnemy_5(void);
ENEMYSTATUS_5 *GetEnemyStatus_5(void);

void HitEnemy_5(int nDamage, int nCntEnemy);

bool CollisionEnemy_5(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemy_5(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatus_5(ENEMYSTATUS_5 status, int nCntEnemy);
void DeleteEnemy_5(int nCntEnemy);
#endif
