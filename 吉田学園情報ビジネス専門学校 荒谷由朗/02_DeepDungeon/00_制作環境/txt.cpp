//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.cpp]
// Author : �r�J�R�N
//
//=============================================================================
#include "txt.h"
#include "char_select.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define SEVEFILENAME "data/MOTION/motion0.txt"					// ���[�h����t�@�C����
#define ARMORTEXNAME "data/MOTION/motion_armor.txt"				// ���[�h����t�@�C����
#define ARMORTEXNAME0 "data/MOTION/motion_armor0.txt"			// ���[�h����t�@�C����
#define ARMORTEXNAME1 "data/MOTION/motion_armor1.txt"			// ���[�h����t�@�C����
#define WARRIOR_TEXT	"data/MOTION/motion_warrior.txt"
#define SORCERER_TEXT	"data/MOTION/magi_motion.txt"
//------------------------------------------------------------------------
//�O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
Tex g_Tex;
Comments g_Comments;

//------------------------------------------------------------------------
// �e�L�X�g�f�[�^�̃��[�h����											  |
//------------------------------------------------------------------------
void LoadData(void)
{
	CHARACTER_TYPE pCharaType = GetCharaType();		// �I���L�����N�^�[���̎擾
	FILE *pFile = NULL;

	if (pCharaType == CHARACTER_TYPE_SOLDIER)
	{
		pFile = fopen(ARMORTEXNAME0, "r");		// �t�@�C�����J��
	}
	else if (pCharaType == CHARACTER_TYPE_WARRIOR)
	{
		pFile = fopen(WARRIOR_TEXT, "r");		// �t�@�C�����J��
	}
	else if (pCharaType == CHARACTER_TYPE_SORCERER)
	{
		pFile = fopen(SORCERER_TEXT, "r");		// �t�@�C�����J��
	}

	if (pFile != NULL)
	{   // �t�@�C�����J�����Ƃ�
		fscanf_s(pFile, "%d", &g_Tex.MAX_PARTS);		// �p�[�c�̍ő吔�̓ǂݎ��
		for (int nCntFile = 0; nCntFile < g_Tex.MAX_PARTS; nCntFile++)
		{// �t�@�C�����̓ǂݎ��
			fscanf_s(pFile, "%s", &g_Tex.aModelTex[nCntFile].FileName,256);
		}
		for (int nCntIdx = 0; nCntIdx < g_Tex.MAX_PARTS; nCntIdx++)
		{// �e�q�֌W�̓ǂݎ��
			fscanf_s(pFile, "%f", &g_Tex.aModelTex[nCntIdx].Index);
		}
		for (int nCntPos = 0; nCntPos < g_Tex.MAX_PARTS; nCntPos++)
		{// �p�[�c�̍��W�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_Tex.aModelTex[nCntPos].PosX, &g_Tex.aModelTex[nCntPos].PosY, &g_Tex.aModelTex[nCntPos].PosZ);
		}
		for (int nCntRot = 0; nCntRot < g_Tex.MAX_PARTS; nCntRot++)
		{// �p�[�c�̉�]�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_Tex.aModelTex[nCntRot].RotX, &g_Tex.aModelTex[nCntRot].RotY, &g_Tex.aModelTex[nCntRot].RotZ);
		}
		fscanf_s(pFile, "%d", &g_Tex.MAX_MOTION);		// ���[�V�����̍ő吔�̓ǂݎ��
		for (int nCntMotionType = 0; nCntMotionType < g_Tex.MAX_MOTION; nCntMotionType++)
		{
			fscanf_s(pFile, "%d", &g_Tex.MOVEPARTS[nCntMotionType]);									// �������f���̐��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_Tex.LOOP[nCntMotionType]);											// ���[�v�ԍ��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_Tex.KEYFLAME[nCntMotionType]);										// �L�[�t���[�����̓ǂݍ���
			for (int nCntKey = 0; nCntKey < g_Tex.KEYFLAME[nCntMotionType]; nCntKey++)
			{// �p�[�c�̈ʒu���̓ǂݎ��
				fscanf_s(pFile, "%d", &g_Tex.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME);			// �t���[�����̓ǂݎ��
				for (int nCntMotionPos = 0; nCntMotionPos < g_Tex.MOVEPARTS[nCntMotionType]; nCntMotionPos++)
				{// �p�[�c�̈ʒu�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_Tex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosX, &g_Tex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosY, &g_Tex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosZ);
				}
				for (int nCntMotionRot = 0; nCntMotionRot < g_Tex.MOVEPARTS[nCntMotionType]; nCntMotionRot++)
				{// �p�[�c�̉�]�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_Tex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotX, &g_Tex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotY, &g_Tex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotZ);
				}
				g_Tex.TOTALFLAME[nCntMotionType] += g_Tex.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME;
			}
		}
		fclose(pFile);   //�t�@�C�������
		_getch();
	}
	else
	{   // �t�@�C�����J���Ȃ������Ƃ�
		MessageBox(NULL, "�G���[", NULL, MB_YESNO);
	}
}

//------------------------------------------------------------------------
// �e�L�X�g�f�[�^�̎擾													  |
//------------------------------------------------------------------------
Tex *GetTex(void)
{
	return &g_Tex;
}