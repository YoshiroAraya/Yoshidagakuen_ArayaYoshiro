//=============================================================================
//
// �G�l�~�[���� [Enemy1.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY8_H_
#define _ENEMY8_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_8 (2)

//#define MAX_PARTS (15)
#define MAX_E_PARTS_8 (17)
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
}PARTS_E_8;

typedef enum
{
	ENEMYSTATE_NONE_8 = 0,
	ENEMYSTATE_BACKHOME_8,
	ENEMYSTATE_DISCOVERY_8,
	ENEMYSTATE_MAX_8
}ENEMYSTATE_8;

typedef enum
{
	ENEMYSTATE2_NORMAL_8 = 0,
	ENEMYSTATE2_DAMAGE_8,
	ENEMYSTATE2_MAX_8
}ENEMYSTATE2_8;


typedef enum
{
	ENEMYSTATUS_NEUTRAL_8 = 0,
	ENEMYSTATUS_MOVE_8,
	ENEMYSTATUS_ATTACK_8,
	ENEMYSTATUS_JUMP_8,
	ENEMYSTATUS_LANDING_8,
	ENEMYSTATUS_GUARD_8,
	ENEMYSTATUS_DAMAGE1_8,
	ENEMYSTATUS_MAX_8
}ENEMYSTATUS_8;

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
}ENEMYCOLLISION_8;

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
	ENEMYSTATE_8 state;
	ENEMYSTATE2_8 state2;
	ENEMYSTATUS_8 status;
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
	ENEMYCOLLISION_8 Collision;
	PARTS_E_8 aModel[MAX_E_PARTS_8];
}ENEMY_8;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy_8(void);
void UninitEnemy_8(void);
void UpdateEnemy_8(void);
void DrawEnemy_8(void);

void HitEnemy_8(int nDamage, int nCntEnemy);

ENEMY_8 *GetEnemy_8(void);
ENEMYSTATUS_8 *GetEnemyStatus_8(void);

void HitEnemy_8(int nDamage, int nCntEnemy);

bool CollisionEnemy_8(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemy_8(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatus_8(ENEMYSTATUS_8 status, int nCntEnemy);
void DeleteEnemy_8(int nCntEnemy);
#endif
