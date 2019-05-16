//=============================================================================
//
// �G�l�~�[���� [Boss.h]
// Author : KishidaRei 
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//#define MAX_PARTS (15)
#define MAX_BOSS_PARTS (16)
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
}PARTS_BOSS;


typedef enum
{
	BOSSSTATE_NORMAL = 0,
	BOSSSTATE_DAMAGE,
	BOSSSTATE_DEAD,
	BOSSSTATE_MAX
}BOSSSTATE;


typedef enum
{
	BOSSSTATUS_NEUTRAL = 0,
	BOSSSTATUS_MOVE,
	BOSSSTATUS_ATTACK,
	BOSSSTATUS_JUMP,
	BOSSSTATUS_LANDING,
	BOSSSTATUS_GUARD,
	BOSSSTATUS_DAMAGE1,
	BOSSSTATUS_MAX
}BOSSSTATUS;

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
}BOSSCOLLISION;

typedef struct
{
	DWORD nNumMatBoss = 0;	//�}�e���A���̏��̐�
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 move;	//����
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 VtxMinBoss = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	D3DXVECTOR3 VtxMaxBoss = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	BOSSSTATE state;
	BOSSSTATUS status;
	float fDestAngle;					//�ړI�̊p�x
	float fAngle;						//����
	float fLength;
	int nIndexShadow;					//�e�̔ԍ�
	int nIndexSencer;					//�Z���T�[(�����蔻��p)�̔ԍ�
	int nIndexSencerBoss;				//�Z���T�[(AI�p)�̔ԍ�
	int nIndexSencerEnableAttack;		//�Z���T�[(�U���\����)�̔ԍ�
	int nLife;
	bool bUse;
	bool bHit;
	int nCntCoolDown;
	int nCoolDown = 200;
	BOSSCOLLISION Collision;
	PARTS_BOSS aModel[MAX_BOSS_PARTS];
}BOSS;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);

void HitBoss(int nDamage);

BOSS *GetBoss(void);
BOSSSTATUS *GetBossStatus(void);


bool CollisionBoss(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin);
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetBossStatus(BOSSSTATUS status);
#endif
