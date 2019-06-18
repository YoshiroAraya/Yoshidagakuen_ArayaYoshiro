//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PARTICLE (2800)

//=============================================================================
// �ǂ̍\����
//=============================================================================
typedef enum
{
	PARTICLETYPE_SHOWER = 0, //�V�����[
	PARTICLETYPE_EXPLOSION,	//����
	PARTICLETYPE_SMOKE,		//��
	PARTICLETYPE_BULLET,
	PARTICLETYPE_MAX
}PARTICLETYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu(���S���W)
	D3DXVECTOR3 posold;		//�O��̈ʒu(���S���W)
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//��]
	D3DXCOLOR col;			//�F
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nLife;				//���C�t
	bool bUse;				//�g�p���Ă��邩
	float fRadius;			//���a
	PARTICLETYPE type;		//�p�[�e�B�N���̎��
}PARTICLE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitParticle(void);		//�p�[�e�B�N��������
void UninitParticle(void);		//�p�[�e�B�N���I��
void UpdateParticle(void);		//�p�[�e�B�N���X�V
void DrawParticle(void);		//�p�[�e�B�N���`��

void SetParticle(D3DXVECTOR3 pos, int nLife, D3DXCOLOR col, PARTICLETYPE type);
#endif
