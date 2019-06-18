//=============================================================================
//
// �G�l�~�[���� [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYAXE_H_
#define _ENEMYAXE_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMYAXE (2)

//#define MAX_PARTS (15)
#define MAX_AXE_PARTS (16)
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
}PARTS_AXE;

typedef enum
{
	ENEMYAXESTATE_NONE = 0,
	ENEMYAXESTATE_BACKHOME,
	ENEMYAXESTATE_DISCOVERY,
	ENEMYAXESTATE_MAX
}ENEMYAXESTATE;

typedef enum
{
	ENEMYAXESTATE2_NORMAL = 0,
	ENEMYAXESTATE2_DAMAGE,
	ENEMYAXESTATE2_MAX
}ENEMYAXESTATE2;


typedef enum
{
	ENEMYAXESTATUS_NEUTRAL = 0,
	ENEMYAXESTATUS_MOVE,
	ENEMYAXESTATUS_ATTACK,
	ENEMYAXESTATUS_JUMP,
	ENEMYAXESTATUS_LANDING,
	ENEMYAXESTATUS_GUARD,
	ENEMYAXESTATUS_DAMAGE1,
	ENEMYAXESTATUS_MAX
}ENEMYAXESTATUS;

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
}ENEMYAXECOLLISION;

typedef struct
{
	DWORD nNumMatEnemy = 0;	//�}�e���A���̏��̐�
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 move;	//����
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 VtxMinEnemyAxe = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	D3DXVECTOR3 VtxMaxEnemyAxe = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	D3DXVECTOR3 HomePoint;
	float DestHome;
	ENEMYAXESTATE state;
	ENEMYAXESTATE2 state2;
	ENEMYAXESTATUS status;
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
	int nCntCoolDown;
	int nCoolDown = 200;
	ENEMYAXECOLLISION Collision;
	PARTS_AXE aModel[MAX_AXE_PARTS];
}ENEMYAXE;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemyAxe(void);
void UninitEnemyAxe(void);
void UpdateEnemyAxe(void);
void DrawEnemyAxe(void);

void HitEnemyAxe(int nDamage, int nCntEnemy);

ENEMYAXE *GetEnemyAxe(void);
ENEMYAXESTATUS *GetEnemyAxeStatus(void);


bool CollisionEnemyAxe(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
int SetEnemyAxe(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyAxeStatus(ENEMYAXESTATUS status, int nCntEnemy);
void DeleteEnemyAxe(int nCntEnemy);
#endif
