//=============================================================================
//
// ��Q���̏��� [obstacle.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"

// �I�u�W�F�N�g�̏��
typedef enum
{
	OBJECTSTATE_NORMAL = 0,
	OBJECTSTATE_DAMAGE,
	OBJECTSTATE_DEATH,
	OBJECTSTATE_MAX
}OBJECTSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 posOld;		// �ߋ��̈ʒu
	D3DXVECTOR3 move;		// �ړ�
	D3DXVECTOR3	rot;		// ����
	D3DXVECTOR3 vtxMin;		// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;		// ���f���̍ő�l
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	int nLife;				// ���C�t
	int nLifeMAX;				// ���C�t
	float nCunterState;
	int		nIdyShadow;		// �e�̔ԍ�
	bool bUse;						//�g�p���Ă��邩�ǂ���
	bool bDisp;
	OBJECTSTATE ObjectState;
}OBSTACLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObstaclel(void);
void UninitObstaclel(void);
void UpdateObstaclel(void);
void DrawObstaclel(void);
bool CollisionObstaclel_Player(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
bool CollisionObstaclel_Enemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy);
void HitObstaclel(int nDamage);
OBSTACLE *GetObstaclel(void);

#endif
