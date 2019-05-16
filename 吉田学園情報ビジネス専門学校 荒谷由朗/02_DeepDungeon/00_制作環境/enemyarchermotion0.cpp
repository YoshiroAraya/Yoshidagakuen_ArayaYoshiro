//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author :
//
//=============================================================================
#include "enemyarchermotion0.h"
#include "enemyarchertext0.h"
#include "enemyarcher0.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyArcherTex_0 *g_aEnemyArcherTex;					// �e�L�X�g�f�[�^�̎擾
ENEMYARCHER_0 *pEnemyArcher;				// �G�l�~�[�f�[�^�̎擾
EnemyArcherMotion_0 g_EnemyArcherMotion;
int g_CntEnemyArcherMotion_0 = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitEnemyArcherMotion_0(void)
{
	int nNumEnemyMotion = 0;

	// �t�@�C���f�[�^�̎擾
	g_aEnemyArcherTex = GetEnemyArcherTex_0();

	// �G�l�~�[�̎擾
	pEnemyArcher = GetEnemyARCHER_0();

	// �����ݒ�
	g_EnemyArcherMotion.nNumEnemymotion = 0;
	g_EnemyArcherMotion.nCntFlame = 0;
	g_EnemyArcherMotion.KeyFlame = 0;
	g_EnemyArcherMotion.MAX_FLAME = g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][0].MAX_FLAME;

	for (int nCntParts = 0; nCntParts > MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_EnemyArcherMotion.aParts[nCntParts].Pos = D3DXVECTOR3(pEnemyArcher->aModel[nCntParts].pos.x, pEnemyArcher->aModel[nCntParts].pos.y, pEnemyArcher->aModel[nCntParts].pos.z);
		g_EnemyArcherMotion.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_EnemyArcherMotion.aParts[nCntParts].Rot = D3DXVECTOR3(pEnemyArcher->aModel[nCntParts].rot.x, pEnemyArcher->aModel[nCntParts].rot.y, pEnemyArcher->aModel[nCntParts].rot.z);
		g_EnemyArcherMotion.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateEnemyArcherMotion_0(void)
{
	g_CntEnemyArcherMotion_0++;

	if (g_CntEnemyArcherMotion_0 % 1 == 0)
	{
		// �G�l�~�[�̏�Ԃ��擾
		ENEMYARCHERSTATUS_0 *pEnemyArcherState;
		pEnemyArcherState = GetEnemyARCHERStatus_0();

		// �t�@�C���f�[�^�̎擾
		g_aEnemyArcherTex = GetEnemyArcherTex_0();

		// �G�l�~�[�̎擾
		pEnemyArcher = GetEnemyARCHER_0();

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_EnemyArcherMotion.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][nCntMotion].MotionRotX,
				g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][nCntMotion].MotionRotY,
				g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle = g_EnemyArcherMotion.aParts[nCntMotion].RotDest - g_EnemyArcherMotion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pEnemyArcher->aModel[nCntMotion].rot += g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle / (g_EnemyArcherMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyArcher->aModel[nCntMotion].rot >= g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemyArcher->aModel[nCntMotion].rot += g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle / (g_EnemyArcherMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemyArcher->aModel[nCntMotion].rot <= g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemyArcher->aModel[nCntMotion].rot += g_EnemyArcherMotion.aParts[nCntMotion].fRotAngle / (g_EnemyArcherMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyArcherMotion.aParts[nCntMotion].Rot = pEnemyArcher->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_EnemyArcherMotion.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][nCntMotion].MotionPosX,
				g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][nCntMotion].MotionPosY,
				g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.x = g_EnemyArcherMotion.aParts[nCntMotion].PosDest.x - g_EnemyArcherMotion.aParts[nCntMotion].Pos.x + g_aEnemyArcherTex->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.y = g_EnemyArcherMotion.aParts[nCntMotion].PosDest.y - g_EnemyArcherMotion.aParts[nCntMotion].Pos.y + g_aEnemyArcherTex->aModelTex[nCntMotion].PosY;
			g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.z = g_EnemyArcherMotion.aParts[nCntMotion].PosDest.z - g_EnemyArcherMotion.aParts[nCntMotion].Pos.z + g_aEnemyArcherTex->aModelTex[nCntMotion].PosZ;

			if (g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.x > D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.x < -D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.y > D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.y < -D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.z > D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.z < -D3DX_PI)
			{
				g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle.z += D3DX_PI * 2;
			}

			pEnemyArcher->aModel[nCntMotion].pos += g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle / (g_EnemyArcherMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyArcher->aModel[nCntMotion].pos >= g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemyArcher->aModel[nCntMotion].pos += g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle / (g_EnemyArcherMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemyArcher->aModel[nCntMotion].pos <= g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemyArcher->aModel[nCntMotion].pos += g_EnemyArcherMotion.aParts[nCntMotion].fPosAngle / (g_EnemyArcherMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyArcherMotion.aParts[nCntMotion].Pos = pEnemyArcher->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_EnemyArcherMotion.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_EnemyArcherMotion.nCntFlame % g_EnemyArcherMotion.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_EnemyArcherMotion.KeyFlame == g_aEnemyArcherTex->KEYFLAME[g_EnemyArcherMotion.nNumEnemymotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_EnemyArcherMotion.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_EnemyArcherMotion.KeyFlame++;
					g_EnemyArcherMotion.MAX_FLAME = g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][g_EnemyArcherMotion.KeyFlame][0].MAX_FLAME;
				}
			}
		}

		// �t���[���̉��Z
		g_EnemyArcherMotion.nCntFlame++;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetEnemyArcherMotion_0(int nNumEnemymotion)
{
	// ���[�V�����̔ԍ�
	g_EnemyArcherMotion.nNumEnemymotion = nNumEnemymotion;

	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_EnemyArcherMotion.MAX_FLAME = g_aEnemyArcherTex->aMotionTex[g_EnemyArcherMotion.nNumEnemymotion][0][0].MAX_FLAME;

	if (nNumEnemymotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_EnemyArcherMotion.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
EnemyArcherMotion_0 *GetEnemyArcherMotion_0(void)
{
	return &g_EnemyArcherMotion;
}