//=============================================================================
//
// �A�j���[�V�����̏��� [motion.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

typedef enum
{
	MOTIONSTATE_NEUTRAL = 0,
	MOTIONSTATE_MOVE,
	MOTIONSTATE_STOP,
	MOTIONSTATE_MAX
}MOTIONSTATE;

// ���f���̍\����
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
	PartsMotion aParts[256];
	MOTIONSTATE state;
}Motion;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void InitMotion(void);
void UninitMotion(void);
void UpdateMotion(void);
void DrawMotion(void);
void SetMotion_STATE(MOTIONSTATE state);
void SetMotion(int nNumPlayermotion);
Motion *GetMotion(void);

#endif