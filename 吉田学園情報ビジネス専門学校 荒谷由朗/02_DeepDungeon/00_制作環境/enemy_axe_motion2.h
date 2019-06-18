//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _ENEMYAXEMOTION2_H_
#define _ENEMYAXEMOTION2_H_

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
}EnemyAxePartsMotion2;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemyAxeMotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyAxePartsMotion2 aParts[256];
}EnemyAxeMotion2;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyAxeMotion2(void);
void UpdateEnemyAxeMotion2(void);
void SetEnemyAxeMotion2(int nNumEnemyAxemotion);
EnemyAxeMotion2 *GetEnemyAxeMotion2(void);

#endif