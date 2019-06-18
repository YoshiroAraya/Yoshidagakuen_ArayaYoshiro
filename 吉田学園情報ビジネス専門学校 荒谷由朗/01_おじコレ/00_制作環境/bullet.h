//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// �e�̎��
//=============================================================================
typedef enum
{
	BULLETTYPE_ENEMY,		// �G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �e�̈ʒu(����)
	D3DXVECTOR3 posOld;		// �e�̈ʒu(�ߋ�)
	D3DXVECTOR3 move;		// �e�̈ړ���
	D3DXCOLOR	col;		// �F
	BULLETTYPE	type;		// �e�̎��
	int			nType;		// ���
	int			nLife;		// ����
	bool		bUse;		// �g�p���Ă��邩�ǂ���
}Bullet;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void	InitBullet	(void);
void	UninitBullet(void);
void	UpdateBullet(void);
void	DrawBullet	(void);
void	SetBullet	(D3DXVECTOR3 pos,
					D3DXVECTOR3 move,
					BULLETTYPE type,
					int nType);
Bullet	*GetBullet	(void);
#endif