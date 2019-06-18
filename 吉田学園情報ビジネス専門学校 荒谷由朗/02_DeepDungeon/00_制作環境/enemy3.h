//=============================================================================
//
// �G�l�~�[���� [Enemy1.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY3_H_
#define _ENEMY3_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_3 (2)

//#define MAX_PARTS (15)
#define MAX_E_PARTS_3 (17)
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
}PARTS_E_3;

typedef enum
{
	ENEMYSTATE_NONE_3 = 0,
	ENEMYSTATE_BACKHOME_3,
	ENEMYSTATE_DISCOVERY_3,
	ENEMYSTATE_MAX_3
}ENEMYSTATE_3;

typedef enum
{
	ENEMYSTATE2_NORMAL_3 = 0,
	ENEMYSTATE2_DAMAGE_3,
	ENEMYSTATE2_MAX_3
}ENEMYSTATE2_3;


typedef enum
{
	ENEMYSTATUS_NEUTRAL_3 = 0,
	ENEMYSTATUS_MOVE_3,
	ENEMYSTATUS_ATTACK_3,
	ENEMYSTATUS_JUMP_3,
	ENEMYSTATUS_LANDING_3,
	ENEMYSTATUS_GUARD_3,
	ENEMYSTATUS_DAMAGE1_3,
	ENEMYSTATUS_MAX_3
}ENEMYSTATUS_3;

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
}ENEMYCOLLISION_3;

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
	ENEMYSTATE_3 state;
	ENEMYSTATE2_3 state2;
	ENEMYSTATUS_3 status;
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
	ENEMYCOLLISION_3 Collision;
	PARTS_E_3 aModel[MAX_E_PARTS_3];
}ENEMY_3;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy_3(void);
void UninitEnemy_3(void);
void UpdateEnemy_3(void);
void DrawEnemy_3(void);

void HitEnemy_3(int nDamage, int nCntEnemy);

ENEMY_3 *GetEnemy_3(void);
ENEMYSTATUS_3 *GetEnemyStatus_3(void);

void HitEnemy_3(int nDamage, int nCntEnemy);

bool CollisionEnemy_3(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemy_3(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatus_3(ENEMYSTATUS_3 status, int nCntEnemy);
void DeleteEnemy_3(int nCntEnemy);
#endif
