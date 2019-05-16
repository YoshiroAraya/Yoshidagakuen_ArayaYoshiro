//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// �\����
//=============================================================================
typedef enum
{
	BULLETTYPE_NONE = 0,
	BULLETTYPE_PLAYER,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 posOld;				// �ʒu
	//D3DXVECTOR3 posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 posAngle;			// �����̈ʒu
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 rotDest;			// �ړI�̈ʒu
	D3DXVECTOR3 rotAngle;			// �����̈ʒu
	D3DXVECTOR3 move;				// �ړ�
	D3DXMATRIX  mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;				// �r���[�}�g���b�N�X
	D3DXVECTOR3 vtxMin;		// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;		// ���f���̍ő�l
	int nIdyShadow;					// �e�̔ԍ�
	int nLife;						// ����
	bool bUse;						// �g�p���Ă��邩�ǂ���
	BULLETTYPE type;
}Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,int nLife, BULLETTYPE type);
bool CollisionEnemyBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax);
bool CollisionPlayerBULLET(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax, int nNumEnemy);

#endif
