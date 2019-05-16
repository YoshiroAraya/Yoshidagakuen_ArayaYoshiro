//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author :
//
//=============================================================================
#include "enemy_axe_motion2.h"
#include "enemy_axe_text2.h"
#include "enemy_axe2.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyAxeTex2 *g_aEnemyAxeTex2;					// �e�L�X�g�f�[�^�̎擾
ENEMYAXE2 *pEnemyAxe2;				// �G�l�~�[�f�[�^�̎擾
EnemyAxeMotion2 g_EnemyAxeMotion2;
int nNumEnemyAxeMotion2 = 0;
int g_CntEnemyAxeMotion2 = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitEnemyAxeMotion2(void)
{
	// �t�@�C���f�[�^�̎擾
	g_aEnemyAxeTex2 = GetEnemyAxeTex2();

	// �G�l�~�[�̎擾
	pEnemyAxe2 = GetEnemyAxe2();

	// �����ݒ�
	g_EnemyAxeMotion2.nNumEnemyAxeMotion = 0;
	g_EnemyAxeMotion2.nCntFlame = 0;
	g_EnemyAxeMotion2.KeyFlame = 0;
	g_EnemyAxeMotion2.MAX_FLAME = g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][0].MAX_FLAME;

	for (int nCntParts = 0; nCntParts > MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_EnemyAxeMotion2.aParts[nCntParts].Pos = D3DXVECTOR3(pEnemyAxe2->aModel[nCntParts].pos.x, pEnemyAxe2->aModel[nCntParts].pos.y, pEnemyAxe2->aModel[nCntParts].pos.z);
		g_EnemyAxeMotion2.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_EnemyAxeMotion2.aParts[nCntParts].Rot = D3DXVECTOR3(pEnemyAxe2->aModel[nCntParts].rot.x, pEnemyAxe2->aModel[nCntParts].rot.y, pEnemyAxe2->aModel[nCntParts].rot.z);
		g_EnemyAxeMotion2.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateEnemyAxeMotion2(void)
{
	g_CntEnemyAxeMotion2++;

	if (g_CntEnemyAxeMotion2 % 1 == 0)
	{
		// �G�l�~�[�̏�Ԃ��擾
		ENEMYAXESTATUS2 *pEnemyAxeState2;
		pEnemyAxeState2 = GetEnemyAxeStatus2();

		// �t�@�C���f�[�^�̎擾
		g_aEnemyAxeTex2 = GetEnemyAxeTex2();

		// �G�l�~�[�̎擾
		pEnemyAxe2 = GetEnemyAxe2();

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_EnemyAxeMotion2.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][nCntMotion].MotionRotX,
				g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][nCntMotion].MotionRotY,
				g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle = g_EnemyAxeMotion2.aParts[nCntMotion].RotDest - g_EnemyAxeMotion2.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pEnemyAxe2->aModel[nCntMotion].rot += g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle / (g_EnemyAxeMotion2.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyAxe2->aModel[nCntMotion].rot >= g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle)
			{
				pEnemyAxe2->aModel[nCntMotion].rot += g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle / (g_EnemyAxeMotion2.MAX_FLAME * 1.0f);
			}
			if (pEnemyAxe2->aModel[nCntMotion].rot <= g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle)
			{
				pEnemyAxe2->aModel[nCntMotion].rot += g_EnemyAxeMotion2.aParts[nCntMotion].fRotAngle / (g_EnemyAxeMotion2.MAX_FLAME * 1.0f);
			}

			g_EnemyAxeMotion2.aParts[nCntMotion].Rot = pEnemyAxe2->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_EnemyAxeMotion2.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][nCntMotion].MotionPosX,
				g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][nCntMotion].MotionPosY,
				g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.x = g_EnemyAxeMotion2.aParts[nCntMotion].PosDest.x - g_EnemyAxeMotion2.aParts[nCntMotion].Pos.x + g_aEnemyAxeTex2->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.y = g_EnemyAxeMotion2.aParts[nCntMotion].PosDest.y - g_EnemyAxeMotion2.aParts[nCntMotion].Pos.y + g_aEnemyAxeTex2->aModelTex[nCntMotion].PosY;
			g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.z = g_EnemyAxeMotion2.aParts[nCntMotion].PosDest.z - g_EnemyAxeMotion2.aParts[nCntMotion].Pos.z + g_aEnemyAxeTex2->aModelTex[nCntMotion].PosZ;

			if (g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.x > D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.x < -D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.y > D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.y < -D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.z > D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.z < -D3DX_PI)
			{
				g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle.z += D3DX_PI * 2;
			}

			pEnemyAxe2->aModel[nCntMotion].pos += g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle / (g_EnemyAxeMotion2.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyAxe2->aModel[nCntMotion].pos >= g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle)
			{
				pEnemyAxe2->aModel[nCntMotion].pos += g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle / (g_EnemyAxeMotion2.MAX_FLAME * 1.0f);
			}
			if (pEnemyAxe2->aModel[nCntMotion].pos <= g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle)
			{
				pEnemyAxe2->aModel[nCntMotion].pos += g_EnemyAxeMotion2.aParts[nCntMotion].fPosAngle / (g_EnemyAxeMotion2.MAX_FLAME * 1.0f);
			}

			g_EnemyAxeMotion2.aParts[nCntMotion].Pos = pEnemyAxe2->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_EnemyAxeMotion2.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_EnemyAxeMotion2.nCntFlame % g_EnemyAxeMotion2.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_EnemyAxeMotion2.KeyFlame == g_aEnemyAxeTex2->KEYFLAME[g_EnemyAxeMotion2.nNumEnemyAxeMotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_EnemyAxeMotion2.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_EnemyAxeMotion2.KeyFlame++;
					g_EnemyAxeMotion2.MAX_FLAME = g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][g_EnemyAxeMotion2.KeyFlame][0].MAX_FLAME;
				}
			}
		}

		// �t���[���̉��Z
		g_EnemyAxeMotion2.nCntFlame++;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetEnemyAxeMotion2(int nNumEnemyAxeMotion)
{
	// ���[�V�����̔ԍ�
	g_EnemyAxeMotion2.nNumEnemyAxeMotion = nNumEnemyAxeMotion;

	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_EnemyAxeMotion2.MAX_FLAME = g_aEnemyAxeTex2->aMotionTex[g_EnemyAxeMotion2.nNumEnemyAxeMotion][0][0].MAX_FLAME;

	if (nNumEnemyAxeMotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_EnemyAxeMotion2.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
EnemyAxeMotion2 *GetEnemyAxeMotion2(void)
{
	return &g_EnemyAxeMotion2;
}