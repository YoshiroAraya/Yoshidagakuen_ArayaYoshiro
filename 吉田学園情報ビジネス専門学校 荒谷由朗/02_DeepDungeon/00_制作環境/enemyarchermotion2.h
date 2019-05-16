//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYARCHERMOTION02_H_
#define _ENEMYARCHERMOTION02_H_

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
}EnemyArcherPartsMotion_2;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemymotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyArcherPartsMotion_2 aParts[256];
}EnemyArcherMotion_2;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyArcherMotion_2(void);
void UpdateEnemyArcherMotion_2(void);
void SetEnemyArcherMotion_2(int nNumEnemymotion);
EnemyArcherMotion_2 *GetEnemyArcherMotion_2(void);

#endif