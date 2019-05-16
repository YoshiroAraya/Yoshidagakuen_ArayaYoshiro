//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.cpp]
// Author : 
//
//=============================================================================
#include "enemytext.h"
//#include "char_select.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define ARMORTEXNAME "data/MOTION/motion_skelton.txt"				// ���[�h����t�@�C����
//------------------------------------------------------------------------
//�O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyTex g_EnemyTex;
EnemyComments g_EnemyComments;

//------------------------------------------------------------------------
// �e�L�X�g�f�[�^�̃��[�h����											  |
//------------------------------------------------------------------------
void LoadEnemyData(void)
{
	FILE *pFile = NULL;

	
	pFile = fopen(ARMORTEXNAME, "r");		// �t�@�C�����J��
	

	if (pFile != NULL)
	{   // �t�@�C�����J�����Ƃ�
		fscanf_s(pFile, "%d", &g_EnemyTex.MAX_PARTS);		// �p�[�c�̍ő吔�̓ǂݎ��
		for (int nCntFile = 0; nCntFile < g_EnemyTex.MAX_PARTS; nCntFile++)
		{// �t�@�C�����̓ǂݎ��
			fscanf_s(pFile, "%s", &g_EnemyTex.aModelTex[nCntFile].FileName, 256);
		}
		for (int nCntIdx = 0; nCntIdx < g_EnemyTex.MAX_PARTS; nCntIdx++)
		{// �e�q�֌W�̓ǂݎ��
			fscanf_s(pFile, "%f", &g_EnemyTex.aModelTex[nCntIdx].Index);
		}
		for (int nCntPos = 0; nCntPos < g_EnemyTex.MAX_PARTS; nCntPos++)
		{// �p�[�c�̍��W�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex.aModelTex[nCntPos].PosX, &g_EnemyTex.aModelTex[nCntPos].PosY, &g_EnemyTex.aModelTex[nCntPos].PosZ);
		}
		for (int nCntRot = 0; nCntRot < g_EnemyTex.MAX_PARTS; nCntRot++)
		{// �p�[�c�̉�]�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex.aModelTex[nCntRot].RotX, &g_EnemyTex.aModelTex[nCntRot].RotY, &g_EnemyTex.aModelTex[nCntRot].RotZ);
		}
		fscanf_s(pFile, "%d", &g_EnemyTex.MAX_MOTION);		// ���[�V�����̍ő吔�̓ǂݎ��
		for (int nCntMotionType = 0; nCntMotionType < g_EnemyTex.MAX_MOTION; nCntMotionType++)
		{
			fscanf_s(pFile, "%d", &g_EnemyTex.MOVEPARTS[nCntMotionType]);									// �������f���̐��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_EnemyTex.LOOP[nCntMotionType]);											// ���[�v�ԍ��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_EnemyTex.KEYFLAME[nCntMotionType]);										// �L�[�t���[�����̓ǂݍ���
			for (int nCntKey = 0; nCntKey < g_EnemyTex.KEYFLAME[nCntMotionType]; nCntKey++)
			{// �p�[�c�̈ʒu���̓ǂݎ��
				fscanf_s(pFile, "%d", &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME);			// �t���[�����̓ǂݎ��
				for (int nCntMotionPos = 0; nCntMotionPos < g_EnemyTex.MOVEPARTS[nCntMotionType]; nCntMotionPos++)
				{// �p�[�c�̈ʒu�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosX, &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosY, &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosZ);
				}
				for (int nCntMotionRot = 0; nCntMotionRot < g_EnemyTex.MOVEPARTS[nCntMotionType]; nCntMotionRot++)
				{// �p�[�c�̉�]�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotX, &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotY, &g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotZ);
				}
				g_EnemyTex.TOTALFLAME[nCntMotionType] += g_EnemyTex.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME;
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
EnemyTex *GetEnemyTex(void)
{
	return &g_EnemyTex;
}