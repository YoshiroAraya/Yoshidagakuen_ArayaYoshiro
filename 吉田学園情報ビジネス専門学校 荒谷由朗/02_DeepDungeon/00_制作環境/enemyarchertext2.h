//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [Archertxt.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _ENEMYARCHERTXT2_H_
#define _ENEMYARCHERTXT2_H_
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
}EnemyArcherComments_2;

//------------------------------------------------------------------------
// ���f���̍\����														  |
//------------------------------------------------------------------------
typedef struct
{
	char FileName[256];								// �ǂݍ��ރe�N�X�`����
	float Index;									// �e�q�֌W
	float PosX, PosY, PosZ;							// ���W
	float RotX, RotY, RotZ;							// ��]
}EnemyArcherModelTex_2;

//------------------------------------------------------------------------
// ���[�V�����̍\����													  |
//------------------------------------------------------------------------
typedef struct
{
	int		MAX_FLAME;								// �t���[���̐�
	float   MotionPosX, MotionPosY, MotionPosZ;		// �ړI�̍��W�f�[�^
	float   MotionRotX, MotionRotY, MotionRotZ;		// �ړI�̉�]�f�[�^
}EnemyArcherMotionTex_2;

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
	EnemyArcherModelTex_2 aModelTex[100];			// �p�[�c[�e�p�[�c�̔ԍ�]
	EnemyArcherMotionTex_2 aMotionTex[25][50][50];	// ���[�V����[���[�V�����̔ԍ�][�L�[�t���[���̔ԍ�][�p�[�c�̔ԍ�]
}EnemyArcherTex_2;

//------------------------------------------------------------------------
// �v���g�^�C�v�錾														  |
//------------------------------------------------------------------------
void LoadEnemyArcherData_2(void);    // �e�L�X�g�̃��[�h
EnemyArcherTex_2 *GetEnemyArcherTex_2(void);		// �e�L�X�g�f�[�^�̎擾

#endif