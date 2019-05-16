//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYAXEMOTION_H_
#define _ENEMYAXEMOTION_H_

#include "main.h"

// ���f���̍\����
typedef struct
{
	D3DXVECTOR3 Rot;			// ���݂̌���
	D3DXVECTOR3 RotDest;		// �ڕW�̌���
	D3DXVECTOR3 fRotAngle;		// �����̍���

	D3DXVECTOR3 Pos;			// ���݂̍��W
	D3DXVECTOR3 PosDest;		// �ڕW�̍��W
	D3DXVECTOR3 fPosAngle;		// ���W�̍���
}EnemyAxePartsMotion;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemyAxeMotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyAxePartsMotion aParts[256];
}EnemyAxeMotion;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyAxeMotion(void);
void UpdateEnemyAxeMotion(void);
void SetEnemyAxeMotion(int nNumEnemyAxemotion);
EnemyAxeMotion *GetEnemyAxeMotion(void);

#endif