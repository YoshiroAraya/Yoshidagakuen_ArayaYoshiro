//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMYARROWTXT_H_
#define _ENEMYTXTARROW_H_
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

//------------------------------------------------------------------------
// �R�����g�̍\����														  |
//------------------------------------------------------------------------
typedef struct
{
	char Comments[256];
	char *ret;
}EnemyArrowComments;

//------------------------------------------------------------------------
// ���f���̍\����														  |
//------------------------------------------------------------------------
typedef struct
{
	char FileName[256];								// �ǂݍ��ރe�N�X�`����
	float Index;									// �e�q�֌W
	float PosX, PosY, PosZ;							// ���W
	float RotX, RotY, RotZ;							// ��]
}EnemyArrowModelTex;

//------------------------------------------------------------------------
// ���[�V�����̍\����													  |
//------------------------------------------------------------------------
typedef struct
{
	int		MAX_FLAME;								// �t���[���̐�
	float   MotionPosX, MotionPosY, MotionPosZ;		// �ړI�̍��W�f�[�^
	float   MotionRotX, MotionRotY, MotionRotZ;		// �ړI�̉�]�f�[�^
}EnemyArrowMotionTex;

//------------------------------------------------------------------------
// �t�@�C���̍\����														  |
//------------------------------------------------------------------------
typedef struct
{
	int MAX_PARTS;						// �p�[�c�̍ő吔
	int MAX_MOTION;						// ���[�V�����̍ő吔
	int LOOP[25];						// ���[�V���������[�v���邩�ǂ���[���[�V�����̔ԍ�]
	int KEYFLAME[25];					// �L�[�t���[���̐�[���[�V�����̔ԍ�]
	int TOTALFLAME[25];					// �t���[���̍��v��[���[�V�����̔ԍ�]
	int MOVEPARTS[25];					// ���[�V�������ɓ����p�[�c��[���[�V�����̔ԍ�]
	EnemyArrowModelTex aModelTex[100];			// �p�[�c[�e�p�[�c�̔ԍ�]
	EnemyArrowMotionTex aMotionTex[25][50][50];	// ���[�V����[���[�V�����̔ԍ�][�L�[�t���[���̔ԍ�][�p�[�c�̔ԍ�]
}EnemyArrowTex;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void LoadEnemyArrowData(void);    // �e�L�X�g�̃��[�h
EnemyArrowTex *GetEnemyArrowTex(void);		// �e�L�X�g�f�[�^�̎擾

#endif