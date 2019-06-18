//=============================================================================
//
// �t�@�C���ǂݍ��݂̏��� [txt.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "bosstext.h"
//#include "char_select.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define ARMORTEXNAME "data/MOTION/motion_skeltonmaster.txt"				// ���[�h����t�@�C����
//------------------------------------------------------------------------
//�O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
BossTex g_BossTex;
BossComments g_BossComments;

//------------------------------------------------------------------------
// �e�L�X�g�f�[�^�̃��[�h����											  |
//------------------------------------------------------------------------
void LoadBossData(void)
{
	FILE *pFile = NULL;


	pFile = fopen(ARMORTEXNAME, "r");		// �t�@�C�����J��


	if (pFile != NULL)
	{   // �t�@�C�����J�����Ƃ�
		fscanf_s(pFile, "%d", &g_BossTex.MAX_PARTS);		// �p�[�c�̍ő吔�̓ǂݎ��
		for (int nCntFile = 0; nCntFile < g_BossTex.MAX_PARTS; nCntFile++)
		{// �t�@�C�����̓ǂݎ��
			fscanf_s(pFile, "%s", &g_BossTex.aModelTex[nCntFile].FileName, 256);
		}
		for (int nCntIdx = 0; nCntIdx < g_BossTex.MAX_PARTS; nCntIdx++)
		{// �e�q�֌W�̓ǂݎ��
			fscanf_s(pFile, "%f", &g_BossTex.aModelTex[nCntIdx].Index);
		}
		for (int nCntPos = 0; nCntPos < g_BossTex.MAX_PARTS; nCntPos++)
		{// �p�[�c�̍��W�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_BossTex.aModelTex[nCntPos].PosX, &g_BossTex.aModelTex[nCntPos].PosY, &g_BossTex.aModelTex[nCntPos].PosZ);
		}
		for (int nCntRot = 0; nCntRot < g_BossTex.MAX_PARTS; nCntRot++)
		{// �p�[�c�̉�]�̓ǂݎ��
			fscanf_s(pFile, "%f , %f , %f", &g_BossTex.aModelTex[nCntRot].RotX, &g_BossTex.aModelTex[nCntRot].RotY, &g_BossTex.aModelTex[nCntRot].RotZ);
		}
		fscanf_s(pFile, "%d", &g_BossTex.MAX_MOTION);		// ���[�V�����̍ő吔�̓ǂݎ��
		for (int nCntMotionType = 0; nCntMotionType < g_BossTex.MAX_MOTION; nCntMotionType++)
		{
			fscanf_s(pFile, "%d", &g_BossTex.MOVEPARTS[nCntMotionType]);									// �������f���̐��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_BossTex.LOOP[nCntMotionType]);											// ���[�v�ԍ��̓ǂݎ��
			fscanf_s(pFile, "%d", &g_BossTex.KEYFLAME[nCntMotionType]);										// �L�[�t���[�����̓ǂݍ���
			for (int nCntKey = 0; nCntKey < g_BossTex.KEYFLAME[nCntMotionType]; nCntKey++)
			{// �p�[�c�̈ʒu���̓ǂݎ��
				fscanf_s(pFile, "%d", &g_BossTex.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME);			// �t���[�����̓ǂݎ��
				for (int nCntMotionPos = 0; nCntMotionPos < g_BossTex.MOVEPARTS[nCntMotionType]; nCntMotionPos++)
				{// �p�[�c�̈ʒu�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_BossTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosX, &g_BossTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosY, &g_BossTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionPos].MotionPosZ);
				}
				for (int nCntMotionRot = 0; nCntMotionRot < g_BossTex.MOVEPARTS[nCntMotionType]; nCntMotionRot++)
				{// �p�[�c�̉�]�̓ǂݎ��
					fscanf_s(pFile, "%f , %f , %f", &g_BossTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotX, &g_BossTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotY, &g_BossTex.aMotionTex[nCntMotionType][nCntKey][nCntMotionRot].MotionRotZ);
				}
				g_BossTex.TOTALFLAME[nCntMotionType] += g_BossTex.aMotionTex[nCntMotionType][nCntKey][0].MAX_FLAME;
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
BossTex *GetBossTex(void)
{
	return &g_BossTex;
}