//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �v���C���[�̏�Ԃ̎��
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
// �v���C���[�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// ���W
	D3DXVECTOR3 move;				// �ړ���
	PLAYERSTATE state;				// ���
	int			nCunterState;		// ��ԃJ�E���^
	int			nCunterAnim;		// �A�j���[�V�����J�E���^
	int			nLife;				// ���C�t
	bool		bUse;				// �g�p����Ă��邩�ǂ���
	bool		bDisp;				// ���S�t���O
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitPlayer		(void);
void	UninitPlayer	(void);
void	UpdatePlayer	(void);
void	DrawPlayer		(void);
void	HitPlayer		(int nDamage);
Player	*GetPlayer		(void);
#endif