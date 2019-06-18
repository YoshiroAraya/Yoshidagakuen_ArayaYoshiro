//=============================================================================
//
// �G�l�~�[���� [Enemy1.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY4_H_
#define _ENEMY4_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_4 (2)

//#define MAX_PARTS (15)
#define MAX_E_PARTS_4 (17)
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
}PARTS_E_4;

typedef enum
{
	ENEMYSTATE_NONE_4 = 0,
	ENEMYSTATE_BACKHOME_4,
	ENEMYSTATE_DISCOVERY_4,
	ENEMYSTATE_MAX_4
}ENEMYSTATE_4;

typedef enum
{
	ENEMYSTATE2_NORMAL_4 = 0,
	ENEMYSTATE2_DAMAGE_4,
	ENEMYSTATE2_MAX_4
}ENEMYSTATE2_4;


typedef enum
{
	ENEMYSTATUS_NEUTRAL_4 = 0,
	ENEMYSTATUS_MOVE_4,
	ENEMYSTATUS_ATTACK_4,
	ENEMYSTATUS_JUMP_4,
	ENEMYSTATUS_LANDING_4,
	ENEMYSTATUS_GUARD_4,
	ENEMYSTATUS_DAMAGE1_4,
	ENEMYSTATUS_MAX_4
}ENEMYSTATUS_4;

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
}ENEMYCOLLISION_4;

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
	ENEMYSTATE_4 state;
	ENEMYSTATE2_4 state2;
	ENEMYSTATUS_4 status;
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
	ENEMYCOLLISION_4 Collision;
	PARTS_E_4 aModel[MAX_E_PARTS_4];
}ENEMY_4;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy_4(void);
void UninitEnemy_4(void);
void UpdateEnemy_4(void);
void DrawEnemy_4(void);

void HitEnemy_4(int nDamage, int nCntEnemy);

ENEMY_4 *GetEnemy_4(void);
ENEMYSTATUS_4 *GetEnemyStatus_4(void);

void HitEnemy_4(int nDamage, int nCntEnemy);

bool CollisionEnemy_4(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemy_4(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatus_4(ENEMYSTATUS_4 status, int nCntEnemy);
void DeleteEnemy_4(int nCntEnemy);
#endif
