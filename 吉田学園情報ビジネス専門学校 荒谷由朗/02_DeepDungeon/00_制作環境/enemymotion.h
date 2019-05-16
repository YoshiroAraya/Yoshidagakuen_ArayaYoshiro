//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYMOTION_H_
#define _ENEMYMOTION_H_

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
}EnemyPartsMotion;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemymotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyPartsMotion aParts[256];
}EnemyMotion;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyMotion(void);
void UpdateEnemyMotion(void);
void SetEnemyMotion(int nNumEnemymotion);
EnemyMotion *GetEnemyMotion(void);

#endif