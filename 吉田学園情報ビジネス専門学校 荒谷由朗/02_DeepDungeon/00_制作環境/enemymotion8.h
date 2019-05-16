//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYMOTION08_H_
#define _ENEMYMOTION08_H_

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
}EnemyPartsMotion_8;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumEnemymotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	EnemyPartsMotion_8 aParts[256];
}EnemyMotion_8;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitEnemyMotion_8(void);
void UpdateEnemyMotion_8(void);
void SetEnemyMotion_8(int nNumEnemymotion);
EnemyMotion_8 *GetEnemyMotion_8(void);

#endif