//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// �v���C���[�̏��
//=============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �v���C���[�̈ʒu(����)
	D3DXVECTOR3 posOld;				// �v���C���[�̈ʒu(�ߋ�)
	D3DXVECTOR3 move;				// �v���C���[�̈ړ���
	PLAYERSTATE state;
	float		fWidth;				// ��
	float		fHeight;			// ����
	int			nCounterJump;		// �W�����v�J�E���^�[
	int			nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int			nPatternAnim;		// �A�j���[�V�����p�^�[��No��������
	int			nLife;				// �v���C���[�̗̑�
	int			nCounterState;		// ��ԊǗ��̃J�E���^
	int			nDirectionMove;		// 0->�E�������Ă���A1->���������Ă���
	bool		bUse;				// �g�p����Ă��邩�ǂ���
	bool		bDisp;				// �\�����Ă��邩�ǂ���
	bool		bJump;				// �W�����v���Ă��邩�ǂ���
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitPlayer	(void);
void	UninitPlayer(void);
void	UpdatePlayer(void);
void	DrawPlayer	(void);
void	HitPlayer	(int nDamage);
Player	*GetPlayer	(void);
#endif