//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "enemymotion3.h"
#include "enemytext3.h"
#include "enemy3.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyTex_3 *g_aEnemyTex;					// �e�L�X�g�f�[�^�̎擾
ENEMY_3 *pEnemy;				// �G�l�~�[�f�[�^�̎擾
EnemyMotion_3 g_EnemyMotion;
int g_CntEnemyMotion_3 = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitEnemyMotion_3(void)
{
	int nNumEnemyMotion = 0;

	// �t�@�C���f�[�^�̎擾
	g_aEnemyTex = GetEnemyTex_3();

	// �G�l�~�[�̎擾
	pEnemy = GetEnemy_3();

	// �����ݒ�
	g_EnemyMotion.nNumEnemymotion = 0;
	g_EnemyMotion.nCntFlame = 0;
	g_EnemyMotion.KeyFlame = 0;
	g_EnemyMotion.MAX_FLAME = g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][0].MAX_FLAME;

	for (int nCntParts = 0; nCntParts > MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_EnemyMotion.aParts[nCntParts].Pos = D3DXVECTOR3(pEnemy->aModel[nCntParts].pos.x, pEnemy->aModel[nCntParts].pos.y, pEnemy->aModel[nCntParts].pos.z);
		g_EnemyMotion.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_EnemyMotion.aParts[nCntParts].Rot = D3DXVECTOR3(pEnemy->aModel[nCntParts].rot.x, pEnemy->aModel[nCntParts].rot.y, pEnemy->aModel[nCntParts].rot.z);
		g_EnemyMotion.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateEnemyMotion_3(void)
{
	g_CntEnemyMotion_3++;

	if (g_CntEnemyMotion_3 % 1 == 0)
	{
		// �G�l�~�[�̏�Ԃ��擾
		ENEMYSTATUS_3 *pEnemyState;
		pEnemyState = GetEnemyStatus_3();

		// �t�@�C���f�[�^�̎擾
		g_aEnemyTex = GetEnemyTex_3();

		// �G�l�~�[�̎擾
		pEnemy = GetEnemy_3();

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_EnemyMotion.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][nCntMotion].MotionRotX,
				g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][nCntMotion].MotionRotY,
				g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_EnemyMotion.aParts[nCntMotion].fRotAngle = g_EnemyMotion.aParts[nCntMotion].RotDest - g_EnemyMotion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_EnemyMotion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyMotion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyMotion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyMotion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyMotion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyMotion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pEnemy->aModel[nCntMotion].rot += g_EnemyMotion.aParts[nCntMotion].fRotAngle / (g_EnemyMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemy->aModel[nCntMotion].rot >= g_EnemyMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemy->aModel[nCntMotion].rot += g_EnemyMotion.aParts[nCntMotion].fRotAngle / (g_EnemyMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemy->aModel[nCntMotion].rot <= g_EnemyMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemy->aModel[nCntMotion].rot += g_EnemyMotion.aParts[nCntMotion].fRotAngle / (g_EnemyMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyMotion.aParts[nCntMotion].Rot = pEnemy->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_EnemyMotion.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][nCntMotion].MotionPosX,
				g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][nCntMotion].MotionPosY,
				g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_EnemyMotion.aParts[nCntMotion].fPosAngle.x = g_EnemyMotion.aParts[nCntMotion].PosDest.x - g_EnemyMotion.aParts[nCntMotion].Pos.x + g_aEnemyTex->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_EnemyMotion.aParts[nCntMotion].fPosAngle.y = g_EnemyMotion.aParts[nCntMotion].PosDest.y - g_EnemyMotion.aParts[nCntMotion].Pos.y + g_aEnemyTex->aModelTex[nCntMotion].PosY;
			g_EnemyMotion.aParts[nCntMotion].fPosAngle.z = g_EnemyMotion.aParts[nCntMotion].PosDest.z - g_EnemyMotion.aParts[nCntMotion].Pos.z + g_aEnemyTex->aModelTex[nCntMotion].PosZ;

			if (g_EnemyMotion.aParts[nCntMotion].fPosAngle.x > D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fPosAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyMotion.aParts[nCntMotion].fPosAngle.x < -D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fPosAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyMotion.aParts[nCntMotion].fPosAngle.y > D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fPosAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyMotion.aParts[nCntMotion].fPosAngle.y < -D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fPosAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyMotion.aParts[nCntMotion].fPosAngle.z > D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fPosAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyMotion.aParts[nCntMotion].fPosAngle.z < -D3DX_PI)
			{
				g_EnemyMotion.aParts[nCntMotion].fPosAngle.z += D3DX_PI * 2;
			}

			pEnemy->aModel[nCntMotion].pos += g_EnemyMotion.aParts[nCntMotion].fPosAngle / (g_EnemyMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemy->aModel[nCntMotion].pos >= g_EnemyMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemy->aModel[nCntMotion].pos += g_EnemyMotion.aParts[nCntMotion].fPosAngle / (g_EnemyMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemy->aModel[nCntMotion].pos <= g_EnemyMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemy->aModel[nCntMotion].pos += g_EnemyMotion.aParts[nCntMotion].fPosAngle / (g_EnemyMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyMotion.aParts[nCntMotion].Pos = pEnemy->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_EnemyMotion.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_EnemyMotion.nCntFlame % g_EnemyMotion.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_EnemyMotion.KeyFlame == g_aEnemyTex->KEYFLAME[g_EnemyMotion.nNumEnemymotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_EnemyMotion.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_EnemyMotion.KeyFlame++;
					g_EnemyMotion.MAX_FLAME = g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][g_EnemyMotion.KeyFlame][0].MAX_FLAME;
				}
			}
		}

		// �t���[���̉��Z
		g_EnemyMotion.nCntFlame++;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetEnemyMotion_3(int nNumEnemymotion)
{
	// ���[�V�����̔ԍ�
	g_EnemyMotion.nNumEnemymotion = nNumEnemymotion;

	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_EnemyMotion.MAX_FLAME = g_aEnemyTex->aMotionTex[g_EnemyMotion.nNumEnemymotion][0][0].MAX_FLAME;

	if (nNumEnemymotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_EnemyMotion.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
EnemyMotion_3 *GetEnemyMotion_3(void)
{
	return &g_EnemyMotion;
}