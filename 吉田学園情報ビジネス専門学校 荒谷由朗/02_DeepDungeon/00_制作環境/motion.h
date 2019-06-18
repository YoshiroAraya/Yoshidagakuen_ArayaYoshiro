//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

// ���f���̍\����

typedef enum
{
	MOTIONSTATE_NEUTRAL = 0,
	MOTIONSTATE_MOVE,
	MOTIONSTATE_STOP,
	MOTIONSTATE_MAX
}MOTIONSTATE;

typedef struct
{
	D3DXVECTOR3 Rot;			// ���݂̌���
	D3DXVECTOR3 RotDest;		// �ڕW�̌���
	D3DXVECTOR3 fRotAngle;		// �����̍���
	
	D3DXVECTOR3 Pos;			// ���݂̍��W
	D3DXVECTOR3 PosDest;		// �ڕW�̍��W
	D3DXVECTOR3 fPosAngle;		// ���W�̍���
}PartsMotion;

typedef struct
{
	int			MAX_FLAME;			// �t���[����
	int			KeyFlame;			// �L�[�t���[��
	bool		Loop;				// ���[�v���邩�ǂ���
	int			nNumPlayermotion;	// ���[�V�����̔ԍ�
	int			nCntFlame;			// �t���[���J�E���^�[
	MOTIONSTATE  state;
	PartsMotion aParts[256];
}Motion;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitMotion(void);
void UpdateMotion(void);
void SetMotion(int nNumPlayermotion);
void SetMotion_STATE(MOTIONSTATE state);
Motion *GetMotion(void);

#endif