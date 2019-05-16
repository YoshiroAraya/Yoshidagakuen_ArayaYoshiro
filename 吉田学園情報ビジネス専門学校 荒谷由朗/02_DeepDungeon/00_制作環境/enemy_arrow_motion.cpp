//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author :
//
//=============================================================================
#include "enemy_arrow_motion.h"
#include "enemy_arrow_text.h"
#include "enemy_arrow.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyArrowTex *g_aEnemyArrowex;					// �e�L�X�g�f�[�^�̎擾
ENEMYARROW *pEnemyArrow;				// �G�l�~�[�f�[�^�̎擾
EnemyArrowMotion g_EnemyArrowMotion;
int nNumEnemyArrowMotion = 0;
int g_CntEnemyArrowMotion = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitEnemyArrowMotion(void)
{
	// �t�@�C���f�[�^�̎擾
	g_aEnemyArrowex = GetEnemyArrowTex();

	// �G�l�~�[�̎擾
	pEnemyArrow = GetEnemyArrow();

	// �����ݒ�
	g_EnemyArrowMotion.nNumEnemyArrowMotion = 0;
	g_EnemyArrowMotion.nCntFlame = 0;
	g_EnemyArrowMotion.KeyFlame = 0;
	g_EnemyArrowMotion.MAX_FLAME = g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][0].MAX_FLAME;

	for (int nCntParts = 0; nCntParts > MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_EnemyArrowMotion.aParts[nCntParts].Pos = D3DXVECTOR3(pEnemyArrow->aModel[nCntParts].pos.x, pEnemyArrow->aModel[nCntParts].pos.y, pEnemyArrow->aModel[nCntParts].pos.z);
		g_EnemyArrowMotion.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_EnemyArrowMotion.aParts[nCntParts].Rot = D3DXVECTOR3(pEnemyArrow->aModel[nCntParts].rot.x, pEnemyArrow->aModel[nCntParts].rot.y, pEnemyArrow->aModel[nCntParts].rot.z);
		g_EnemyArrowMotion.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateEnemyArrowMotion(void)
{
	g_CntEnemyArrowMotion++;

	if (g_CntEnemyArrowMotion % 1 == 0)
	{
		// �G�l�~�[�̏�Ԃ��擾
		ENEMY_ARROW_STATUS *pEnemyArrowState;
		pEnemyArrowState = GetEnemyArrowStatus();

		// �t�@�C���f�[�^�̎擾
		g_aEnemyArrowex = GetEnemyArrowTex();

		// �G�l�~�[�̎擾
		pEnemyArrow = GetEnemyArrow();

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_EnemyArrowMotion.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][nCntMotion].MotionRotX,
				g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][nCntMotion].MotionRotY,
				g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle = g_EnemyArrowMotion.aParts[nCntMotion].RotDest - g_EnemyArrowMotion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pEnemyArrow->aModel[nCntMotion].rot += g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle / (g_EnemyArrowMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyArrow->aModel[nCntMotion].rot >= g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemyArrow->aModel[nCntMotion].rot += g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle / (g_EnemyArrowMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemyArrow->aModel[nCntMotion].rot <= g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemyArrow->aModel[nCntMotion].rot += g_EnemyArrowMotion.aParts[nCntMotion].fRotAngle / (g_EnemyArrowMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyArrowMotion.aParts[nCntMotion].Rot = pEnemyArrow->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_EnemyArrowMotion.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][nCntMotion].MotionPosX,
				g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][nCntMotion].MotionPosY,
				g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.x = g_EnemyArrowMotion.aParts[nCntMotion].PosDest.x - g_EnemyArrowMotion.aParts[nCntMotion].Pos.x + g_aEnemyArrowex->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.y = g_EnemyArrowMotion.aParts[nCntMotion].PosDest.y - g_EnemyArrowMotion.aParts[nCntMotion].Pos.y + g_aEnemyArrowex->aModelTex[nCntMotion].PosY;
			g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.z = g_EnemyArrowMotion.aParts[nCntMotion].PosDest.z - g_EnemyArrowMotion.aParts[nCntMotion].Pos.z + g_aEnemyArrowex->aModelTex[nCntMotion].PosZ;

			if (g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.x > D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.x < -D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.y > D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.y < -D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.z > D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.z < -D3DX_PI)
			{
				g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle.z += D3DX_PI * 2;
			}

			pEnemyArrow->aModel[nCntMotion].pos += g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle / (g_EnemyArrowMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyArrow->aModel[nCntMotion].pos >= g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemyArrow->aModel[nCntMotion].pos += g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle / (g_EnemyArrowMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemyArrow->aModel[nCntMotion].pos <= g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemyArrow->aModel[nCntMotion].pos += g_EnemyArrowMotion.aParts[nCntMotion].fPosAngle / (g_EnemyArrowMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyArrowMotion.aParts[nCntMotion].Pos = pEnemyArrow->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_EnemyArrowMotion.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_EnemyArrowMotion.nCntFlame % g_EnemyArrowMotion.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_EnemyArrowMotion.KeyFlame == g_aEnemyArrowex->KEYFLAME[g_EnemyArrowMotion.nNumEnemyArrowMotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_EnemyArrowMotion.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_EnemyArrowMotion.KeyFlame++;
					g_EnemyArrowMotion.MAX_FLAME = g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][g_EnemyArrowMotion.KeyFlame][0].MAX_FLAME;
				}
			}
		}

		// �t���[���̉��Z
		g_EnemyArrowMotion.nCntFlame++;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetEnemyArrowMotion(int nNumEnemyArrowMotion)
{
	// ���[�V�����̔ԍ�
	g_EnemyArrowMotion.nNumEnemyArrowMotion = nNumEnemyArrowMotion;

	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_EnemyArrowMotion.MAX_FLAME = g_aEnemyArrowex->aMotionTex[g_EnemyArrowMotion.nNumEnemyArrowMotion][0][0].MAX_FLAME;

	if (nNumEnemyArrowMotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_EnemyArrowMotion.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
EnemyArrowMotion *GetEnemyArrowMotion(void)
{
	return &g_EnemyArrowMotion;
}