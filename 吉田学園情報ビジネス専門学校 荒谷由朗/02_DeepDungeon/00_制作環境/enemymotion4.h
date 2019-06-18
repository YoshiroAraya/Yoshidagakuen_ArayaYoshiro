//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _ENEMYMOTION04_H_
#define _ENEMYMOTION04_H_

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
}EnemyPartsMotion_4;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemymotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyPartsMotion_4 aParts[256];
}EnemyMotion_4;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyMotion_4(void);
void UpdateEnemyMotion_4(void);
void SetEnemyMotion_4(int nNumEnemymotion);
EnemyMotion_4 *GetEnemyMotion_4(void);

#endif