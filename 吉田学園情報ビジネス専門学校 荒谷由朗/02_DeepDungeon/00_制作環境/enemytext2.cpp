//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.cpp]
// Author : 
//
//=============================================================================
#include "enemytext2.h"
//#include "char_select.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define ARMORTEXNAME "data/MOTION/motion_skelton.txt"				// ���[�h����t�@�C����
//------------------------------------------------------------------------
//�O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyTex_2 g_EnemyTex_2;
EnemyComments_2 g_EnemyComments_2;

//------------------------------------------------------------------------
// �e�L�X�g�f�[�^�̃��[�h����											  |
//------------------------------------------------------------------------
void LoadEnemyData_2(void)
{
	FILE *pFile = NULL;

	
	pFile = fopen(ARMORTEXNAME, "r");		// �t�@�C�����J��
	

	if (pFile != NULL)
	{   // �t�@�C�����J�����Ƃ�
		fscanf_s(pFile, "%d", &g_EnemyTex_2.MAX_PARTS);		// �p�[�c�̍ő吔�̓ǂݎ��
		for (int nCntFile = 0; nCntFile < g_EnemyTex_2.MAX_PARTS; nCntFile++)
		{// �t�@�C�����̓ǂݎ��
			fscanf_s(pFile, "%s", &g_EnemyTex_2.aModelTex[nCntFile].FileName, 256);
		}
		for (int nCntIdx = 0; nCntIdx < g_EnemyTex_2.MAX_PARTS; nCntIdx++)
		{// �e�q�֌W�̓ǂݎ��
			fscanf_s(pFile, "%f", &g_EnemyTex_2.aModelTex[nCntIdx].Index);
		}
		for (int nCntPos = 0; nCntPos < g_EnemyTex_2.MAX_PARTS; nCntPos++)
		{// �p�[�c�̍��W�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_2.aModelTex[nCntPos].PosX, &g_EnemyTex_2.aModelTex[nCntPos].PosY, &g_EnemyTex_2.aModelTex[nCntPos].PosZ);
		}
		for (int nCntRot = 0; nCntRot < g_EnemyTex_2.MAX_PARTS; nCntRot++)
		{// �p�[�c�̉�]�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_2.aModelTex[nCntRot].RotX, &g_EnemyTex_2.aModelTex[nCntRot].RotY, &g_EnemyTex_2.aModelTex[nCntRot].RotZ);
		}
		fscanf_s(pFile, "%d", &g_EnemyTex_2.MAX_MOTION);		// ���[�V�����̍ő吔�̓ǂݎ��
		for (int nCntMotionType = 0; nCntMotionType < g_EnemyTex_2.MAX_MOTION; nCntMotionType++)
		{
			fscanf_s(pFile, "%d", &g_EnemyTex_2.MOVEPARTS[nCntMotionType]);									// �������f���̐��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_EnemyTex_2.LOOP[nCntMotionType]);											// ���[�v�ԍ��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_EnemyTex_2.KEYFLAME[nCntMotionType]);										// �L�[�t���[�����̓ǂݍ���
			for (int nCntKey = 0; nCntKey < g_EnemyTex_2.KEYFLAME[nCntMotionType]; nCntKey++)
			{// �p�[�c�̈ʒu���̓ǂݎ��
				fscanf_s(pFile, "%d", &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME);			// �t���[�����̓ǂݎ��
				for (int nCntMotionPos = 0; nCntMotionPos < g_EnemyTex_2.MOVEPARTS[nCntMotionType]; nCntMotionPos++)
				{// �p�[�c�̈ʒu�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosX, &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosY, &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosZ);
				}
				for (int nCntMotionRot = 0; nCntMotionRot < g_EnemyTex_2.MOVEPARTS[nCntMotionType]; nCntMotionRot++)
				{// �p�[�c�̉�]�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotX, &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotY, &g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotZ);
				}
				g_EnemyTex_2.TOTALFLAME[nCntMotionType] += g_EnemyTex_2.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME;
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
EnemyTex_2 *GetEnemyTex_2(void)
{
	return &g_EnemyTex_2;
}