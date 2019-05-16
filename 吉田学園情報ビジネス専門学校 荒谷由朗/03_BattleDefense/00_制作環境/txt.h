//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _TXT_H_
#define _TXT_H_
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

// ������̍\����
typedef struct
{
	char Comments[256];
	char *ret;
}Comments;

// ���f���̍\����
typedef struct
{
	char FileName[256];
	float Index;
	float PosX, PosY, PosZ;
	float RotX, RotY, RotZ;
}ModelTex;

// ���[�V�����̍\����
typedef struct
{
	int		MAX_FLAME;								// �t���[���̐�
	float   MotionPosX, MotionPosY, MotionPosZ;		// �ړI�̍��W�f�[�^
	float   MotionRotX, MotionRotY, MotionRotZ;		// �ړI�̍��W�f�[�^
}MotionTex;


// �t�@�C���̍\����
typedef struct
{

	int MAX_PARTS;						// �p�[�c�̍ő吔
	int MAX_MOTION;						// ���[�V�����̍ő吔
	int LOOP[25];						// ���[�V���������[�v���邩�ǂ���
	int KEYFLAME[25];					// �L�[�t���[���̐�
	int MOVEPARTS[25];					// ���[�V�������ɓ����p�[�c��
	ModelTex aModelTex[100];			// �p�[�c
	MotionTex aMotionTex[25][50][50];	// ���[�V����
}Tex;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void LoadData(void);    //�f�[�^�̃��[�h
Tex *GetTex(void);

#endif