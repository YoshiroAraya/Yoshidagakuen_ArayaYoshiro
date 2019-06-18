//=============================================================================
//
// �G�l�~�[���� [Enemy1.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY7_H_
#define _ENEMY7_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_7 (2)

//#define MAX_PARTS (15)
#define MAX_E_PARTS_7 (17)
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
}PARTS_E_7;

typedef enum
{
	ENEMYSTATE_NONE_7 = 0,
	ENEMYSTATE_BACKHOME_7,
	ENEMYSTATE_DISCOVERY_7,
	ENEMYSTATE_MAX_7
}ENEMYSTATE_7;

typedef enum
{
	ENEMYSTATE2_NORMAL_7 = 0,
	ENEMYSTATE2_DAMAGE_7,
	ENEMYSTATE2_MAX_7
}ENEMYSTATE2_7;


typedef enum
{
	ENEMYSTATUS_NEUTRAL_7 = 0,
	ENEMYSTATUS_MOVE_7,
	ENEMYSTATUS_ATTACK_7,
	ENEMYSTATUS_JUMP_7,
	ENEMYSTATUS_LANDING_7,
	ENEMYSTATUS_GUARD_7,
	ENEMYSTATUS_DAMAGE1_7,
	ENEMYSTATUS_MAX_7
}ENEMYSTATUS_7;

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
}ENEMYCOLLISION_7;

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
	ENEMYSTATE_7 state;
	ENEMYSTATE2_7 state2;
	ENEMYSTATUS_7 status;
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
	ENEMYCOLLISION_7 Collision;
	PARTS_E_7 aModel[MAX_E_PARTS_7];
}ENEMY_7;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy_7(void);
void UninitEnemy_7(void);
void UpdateEnemy_7(void);
void DrawEnemy_7(void);

void HitEnemy_7(int nDamage, int nCntEnemy);

ENEMY_7 *GetEnemy_7(void);
ENEMYSTATUS_7 *GetEnemyStatus_7(void);

void HitEnemy_7(int nDamage, int nCntEnemy);

bool CollisionEnemy_7(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemy_7(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatus_7(ENEMYSTATUS_7 status, int nCntEnemy);
void DeleteEnemy_7(int nCntEnemy);
#endif
