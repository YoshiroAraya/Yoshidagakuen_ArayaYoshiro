//=============================================================================
//
// �G�l�~�[���� [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYARROW_H_
#define _ENEMYARROW_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_ARROW (2)

//#define MAX_PARTS (15)
#define MAX_ARROW_PARTS (16)
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
}PARTS_ARROW;

typedef enum
{
	ENEMY_ARROW_STATE_NONE = 0,
	ENEMY_ARROW_STATE_BACKHOME,
	ENEMY_ARROW_STATE_DISCOVERY,
	ENEMY_ARROW_STATE_MAX
}ENEMY_ARROW_STATE;

typedef enum
{
	ENEMY_ARROW_STATE2_NORMAL = 0,
	ENEMY_ARROW_STATE2_DAMAGE,
	ENEMY_ARROW_STATE2_MAX
}ENEMY_ARROW_STATE2;


typedef enum
{
	ENEMY_ARROW_STATUS_NEUTRAL = 0,
	ENEMY_ARROW_STATUS_MOVE,
	ENEMY_ARROW_STATUS_ATTACK,
	ENEMY_ARROW_STATUS_JUMP,
	ENEMY_ARROW_STATUS_LANDING,
	ENEMY_ARROW_STATUS_GUARD,
	ENEMY_ARROW_STATUS_DAMAGE1,
	ENEMY_ARROW_STATUS_MAX
}ENEMY_ARROW_STATUS;

//------------------------------------------------------------------------
// �����蔻��̍\����													 |
//------------------------------------------------------------------------
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
	ENEMY_ARROW_STATE state;
	ENEMY_ARROW_STATE2 state2;
	ENEMY_ARROW_STATUS status;
	bool bUseJump;
	float fDestAngle;					//�ړI�̊p�x
	float fAngle;						//����
	float fLength;
	int nIndexShadow;					//�e�̔ԍ�
	int nIndexSencer;					//�Z���T�[(�����蔻��p)�̔ԍ�
	int nIndexSencerEnemyaArrow;				//�Z���T�[(AI�p)�̔ԍ�
	int nIndexSencerEnableAttack;		//�Z���T�[(�U���\����)�̔ԍ�
	int nLife;
	bool bUse;
	bool bHit;
	int nCntCoolDown;
	int nCoolDown = 200;
	int StartFlame;
	PARTS_ARROW aModel[MAX_ARROW_PARTS];
}ENEMYARROW;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemyArrow(void);
void UninitEnemyArrow(void);
void UpdateEnemyArrow(void);
void DrawEnemyArrow(void);

void HitEnemyArrow(int nDamage, int nCntEnemy);

ENEMYARROW *GetEnemyArrow(void);
ENEMY_ARROW_STATUS *GetEnemyArrowStatus(void);


int SetEnemyArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
void SetEnemyStatusArrow(ENEMY_ARROW_STATUS status, int nCntEnemy);
void DeleteEnemyArrow(int nCntEnemy);
#endif
