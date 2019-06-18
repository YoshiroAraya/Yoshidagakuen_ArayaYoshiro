//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ENEMY	(256)	// �G�̍ő吔

//=============================================================================
//�G�̃^�C�v
//=============================================================================
typedef enum
{
	EnemyType_NORMAL = 0,
	EnemyType_MAX
}EnemyType;

//=============================================================================
// �G�̏��
//=============================================================================
typedef enum
{
	ENEMEYSTATE_NEUTRAL = 0,
	ENEMEYSTATE_DEATH,
	ENEMEYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

//=============================================================================
// ���f���̍\����
//=============================================================================
typedef struct
{
	LPD3DXMESH				pMash		= NULL;
	LPD3DXBUFFER			pBuffMat	= NULL;
	DWORD					nNumMat;
	D3DXMATRIX				mtxWorld;
	LPDIRECT3DTEXTURE9		pTexture;
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	float					nIdxModelParent = -1;	// �e���f���̃C���f�b�N�X
	char					FileName[256];
}EnemyModel;

//=============================================================================
// �G�̍\����
//=============================================================================
typedef struct
{
	D3DXMATRIX	mtxWorld;
	D3DXVECTOR3 Pos;			// ���݂̈ʒu
	D3DXVECTOR3 PosOld;			// �ʒu
	D3DXVECTOR3 PosDest;		// �ڕW�̍��W
	D3DXVECTOR3 fPosAngle;		// ���W�̍���
	D3DXVECTOR3 Rot;			// ���݂̌���
	D3DXVECTOR3 RotDest;		// �ڕW�̌���
	D3DXVECTOR3 fRotAngle;		// �����̍���
	D3DXVECTOR3 move;			// �ړ�
	D3DXVECTOR3 vtxMin;			// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;			// ���f���̍ő�l
	int	nNumParts = 0;			// �p�[�c�̔ԍ�
	int MAX_PARTS;				// �p�[�c�̍ő吔
	int nCntPlayermotion;		// ���[�V�����̔ԍ�
	int nLife;					// ����
	float		fAngle;			// ����
	float nSpped;				// �G�̈ړ����x
	bool bUse;					// �g�p���Ă��邩�ǂ���
	EnemyModel aModel[256];		// �p�[�c
	EnemyType type;				// ���
	ENEMYSTATE EnemyState;		// �G�l�~�[�̏��
}Enemy;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void		InitEnemy			(void);
void		UninitEnemy			(void);
void		UpdateEnemy			(void);
void		DrawEnemy			(void);
void		SetEnemy			(D3DXVECTOR3 pos);
void		SetEnemyState		(ENEMYSTATE state);
void		HitEnemy			(int nNumEnemy,int nDamage, int typ);
ENEMYSTATE	GetEnemyStateNow	(void);
Enemy		*GetEnemy			(void);
#endif