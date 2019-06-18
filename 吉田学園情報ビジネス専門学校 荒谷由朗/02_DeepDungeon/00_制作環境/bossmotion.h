//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _BOSSMOTION_H_
#define _BOSSMOTION_H_

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
}BossPartsMotion;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumBossMotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	BossPartsMotion aParts[256];
}BossMotion;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitBossMotion(void);
void UpdateBossMotion(void);
void SetBossMotion(int nNumMotion);
BossMotion *GetBossMotion(void);

#endif