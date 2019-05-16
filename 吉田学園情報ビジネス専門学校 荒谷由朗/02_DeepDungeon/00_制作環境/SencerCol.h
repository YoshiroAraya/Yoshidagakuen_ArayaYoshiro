//=============================================================================
//
// �e��Z���T�[�������� [sencer.h]
// Author : KishidaRei
//
//=============================================================================
#ifndef _SENCERCOL_H_
#define _SENCERCOL_H_

#include "main.h"


//*****************************************************************************
// �Z���T�[�̍\����
//*****************************************************************************
typedef enum
{
	SENCERCOLTYPE_PLAYER = 0,
	SENCERCOLTYPE_ENEMY,
	SENCERCOLTYPE_ENEMY0,
	SENCERCOLTYPE_ENEMY1,
	SENCERCOLTYPE_ENEMY2,
	SENCERCOLTYPE_ENEMY3,
	SENCERCOLTYPE_ENEMY4,
	SENCERCOLTYPE_ENEMY5,
	SENCERCOLTYPE_ENEMY6,
	SENCERCOLTYPE_ENEMY7,

	SENCERCOLTYPE_ENEMY_AXE,
	SENCERCOLTYPE_ENEMY_AXE2,
	SENCERCOLTYPE_ENEMY_ARROW,
	SENCERCOLTYPE_ENEMY_ARROW0,
	SENCERCOLTYPE_ENEMY_ARROW1,
	SENCERCOLTYPE_ENEMY_ARROW2,

	SENCERCOLTYPE_ENEMY_BOSS,
	SENCERCOLTYPE_MAX
}SENCERCOLTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	SENCERCOLTYPE type;
	bool bUse;
	float fRadius;
}SENCERCOLLISION;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSencerCollision(void);		//�Z���T�[������
void UninitSencerCollision(void);	//�Z���T�[�I��
void UpdateSencerCollision(void);	//�Z���T�[�X�V
void DrawSencerCollision(void);		//�Z���T�[�`��

void SetPositionSencerCollision(int nIdxSencer, D3DXVECTOR3 pos);
void DeleteSencerCol(int nIdxSencerCol);

int SetSencerCollision(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SENCERCOLTYPE type);


//�ʏ�U��(player->enemy)
bool CollisionAttackPlayer(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemy);//player -> enemy�ւ̓����蔻��
bool CollisionAttackPvA(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyArrow);//player -> enemy(Arrow)�ւ̓����蔻��
bool CollisionAttackAxe(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyAxe);//player -> enemy(axe)�ւ̓����蔻��
bool CollisionAttackPvB(D3DXVECTOR3 pos, float fRadius, int nCntSencer);//player -> boss�ւ̓����蔻��

//�U��(Enemy->player)
bool CollisionAttackEnemy(D3DXVECTOR3 pos, float fRadius, int nCntSencer, SENCERCOLTYPE Type);//enemy -> player�ւ̓����蔻��
bool CollisionAttackBoss(D3DXVECTOR3 pos, float fRadius, int nCntSencer, SENCERCOLTYPE Type);//enemy -> player�ւ̓����蔻��

//Ꮜ�
bool Collision_L_AttackPlayer(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemy);//player -> enemy�ւ̓����蔻��
bool Collision_L_AttackPvB(D3DXVECTOR3 pos, float fRadius, int nCntSencer);//player -> boss�ւ̓����蔻��
bool Collision_L_AttackPvA(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyArrow);//player -> enemy(Arrow)�ւ̓����蔻��
bool Collision_L_AttackAxe(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyArrow);//player -> enemy(Arrow)�ւ̓����蔻��


bool CollisionSencer_Col(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold);

//���@�U��
bool CollisionSencer_Magic(D3DXVECTOR3 *pos, int nCntEnemy);

bool CollisionSencer_Magic_Boss(D3DXVECTOR3 *pos);

//�G�|�U��
bool CollisionAttackEnemyArrow(D3DXVECTOR3 *pos);//enemy -> player�ւ̓����蔻��(��)

																								   
//�Ռ����@�U��
bool CollisionSencer_L_Magic(D3DXVECTOR3 *pos, int nCntEnemy);
bool CollisionSencer_L_Magic_Boss(D3DXVECTOR3 *pos);


#endif
