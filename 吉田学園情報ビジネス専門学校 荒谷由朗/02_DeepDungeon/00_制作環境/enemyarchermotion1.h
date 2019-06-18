//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _ENEMYARCHERMOTION01_H_
#define _ENEMYARCHERMOTION01_H_

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
}EnemyArcherPartsMotion_1;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemymotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyArcherPartsMotion_1 aParts[256];
}EnemyArcherMotion_1;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyArcherMotion_1(void);
void UpdateEnemyArcherMotion_1(void);
void SetEnemyArcherMotion_1(int nNumEnemymotion);
EnemyArcherMotion_1 *GetEnemyArcherMotion_1(void);

#endif