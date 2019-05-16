//=============================================================================
//
// �|���S������ [player.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�v���C���[�̏�Ԃ̎��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX
}PLAYERSTATE;
//*****************************************************************************
//�v���C���[�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;
	int nCunterState;
	int nCunterAnim;
	int nLife;
	bool bUse;				//�g�p����Ă��邩�ǂ���
	bool bDisp;
}Player;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif