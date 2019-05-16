//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYMOTION07_H_
#define _ENEMYMOTION07_H_

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
}EnemyPartsMotion_7;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemymotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyPartsMotion_7 aParts[256];
}EnemyMotion_7;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyMotion_7(void);
void UpdateEnemyMotion_7(void);
void SetEnemyMotion_7(int nNumEnemymotion);
EnemyMotion_7 *GetEnemyMotion_7(void);

#endif