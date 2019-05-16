//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.cpp]
// Author : 
//
//=============================================================================
#include "enemytext4.h"
//#include "char_select.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define ARMORTEXNAME "data/MOTION/motion_skelton.txt"				// ���[�h����t�@�C����
//------------------------------------------------------------------------
//�O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyTex_4 g_EnemyTex_4;
EnemyComments_4 g_EnemyComments_4;

//------------------------------------------------------------------------
// �e�L�X�g�f�[�^�̃��[�h����											  |
//------------------------------------------------------------------------
void LoadEnemyData_4(void)
{
	FILE *pFile = NULL;

	
	pFile = fopen(ARMORTEXNAME, "r");		// �t�@�C�����J��
	

	if (pFile != NULL)
	{   // �t�@�C�����J�����Ƃ�
		fscanf_s(pFile, "%d", &g_EnemyTex_4.MAX_PARTS);		// �p�[�c�̍ő吔�̓ǂݎ��
		for (int nCntFile = 0; nCntFile < g_EnemyTex_4.MAX_PARTS; nCntFile++)
		{// �t�@�C�����̓ǂݎ��
			fscanf_s(pFile, "%s", &g_EnemyTex_4.aModelTex[nCntFile].FileName, 256);
		}
		for (int nCntIdx = 0; nCntIdx < g_EnemyTex_4.MAX_PARTS; nCntIdx++)
		{// �e�q�֌W�̓ǂݎ��
			fscanf_s(pFile, "%f", &g_EnemyTex_4.aModelTex[nCntIdx].Index);
		}
		for (int nCntPos = 0; nCntPos < g_EnemyTex_4.MAX_PARTS; nCntPos++)
		{// �p�[�c�̍��W�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_4.aModelTex[nCntPos].PosX, &g_EnemyTex_4.aModelTex[nCntPos].PosY, &g_EnemyTex_4.aModelTex[nCntPos].PosZ);
		}
		for (int nCntRot = 0; nCntRot < g_EnemyTex_4.MAX_PARTS; nCntRot++)
		{// �p�[�c�̉�]�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_4.aModelTex[nCntRot].RotX, &g_EnemyTex_4.aModelTex[nCntRot].RotY, &g_EnemyTex_4.aModelTex[nCntRot].RotZ);
		}
		fscanf_s(pFile, "%d", &g_EnemyTex_4.MAX_MOTION);		// ���[�V�����̍ő吔�̓ǂݎ��
		for (int nCntMotionType = 0; nCntMotionType < g_EnemyTex_4.MAX_MOTION; nCntMotionType++)
		{
			fscanf_s(pFile, "%d", &g_EnemyTex_4.MOVEPARTS[nCntMotionType]);									// �������f���̐��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_EnemyTex_4.LOOP[nCntMotionType]);											// ���[�v�ԍ��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_EnemyTex_4.KEYFLAME[nCntMotionType]);										// �L�[�t���[�����̓ǂݍ���
			for (int nCntKey = 0; nCntKey < g_EnemyTex_4.KEYFLAME[nCntMotionType]; nCntKey++)
			{// �p�[�c�̈ʒu���̓ǂݎ��
				fscanf_s(pFile, "%d", &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME);			// �t���[�����̓ǂݎ��
				for (int nCntMotionPos = 0; nCntMotionPos < g_EnemyTex_4.MOVEPARTS[nCntMotionType]; nCntMotionPos++)
				{// �p�[�c�̈ʒu�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosX, &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosY, &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosZ);
				}
				for (int nCntMotionRot = 0; nCntMotionRot < g_EnemyTex_4.MOVEPARTS[nCntMotionType]; nCntMotionRot++)
				{// �p�[�c�̉�]�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotX, &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotY, &g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotZ);
				}
				g_EnemyTex_4.TOTALFLAME[nCntMotionType] += g_EnemyTex_4.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME;
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
EnemyTex_4 *GetEnemyTex_4(void)
{
	return &g_EnemyTex_4;
}