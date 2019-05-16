//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author :
//
//=============================================================================
#include "enemy_axe_motion.h"
#include "enemy_axe_text.h"
#include "enemy_axe.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
EnemyAxeTex *g_aEnemyAxeTex;					// �e�L�X�g�f�[�^�̎擾
ENEMYAXE *pEnemyAxe;				// �G�l�~�[�f�[�^�̎擾
EnemyAxeMotion g_EnemyAxeMotion;
int nNumEnemyAxeMotion = 0;
int g_CntEnemyAxeMotion = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitEnemyAxeMotion(void)
{
	// �t�@�C���f�[�^�̎擾
	g_aEnemyAxeTex = GetEnemyAxeTex();

	// �G�l�~�[�̎擾
	pEnemyAxe = GetEnemyAxe();

	// �����ݒ�
	g_EnemyAxeMotion.nNumEnemyAxeMotion = 0;
	g_EnemyAxeMotion.nCntFlame = 0;
	g_EnemyAxeMotion.KeyFlame = 0;
	g_EnemyAxeMotion.MAX_FLAME = g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][0].MAX_FLAME;

	for (int nCntParts = 0; nCntParts > MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_EnemyAxeMotion.aParts[nCntParts].Pos = D3DXVECTOR3(pEnemyAxe->aModel[nCntParts].pos.x, pEnemyAxe->aModel[nCntParts].pos.y, pEnemyAxe->aModel[nCntParts].pos.z);
		g_EnemyAxeMotion.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_EnemyAxeMotion.aParts[nCntParts].Rot = D3DXVECTOR3(pEnemyAxe->aModel[nCntParts].rot.x, pEnemyAxe->aModel[nCntParts].rot.y, pEnemyAxe->aModel[nCntParts].rot.z);
		g_EnemyAxeMotion.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateEnemyAxeMotion(void)
{
	g_CntEnemyAxeMotion++;

	if (g_CntEnemyAxeMotion % 1 == 0)
	{
		// �G�l�~�[�̏�Ԃ��擾
		ENEMYAXESTATUS *pEnemyAxeState;
		pEnemyAxeState = GetEnemyAxeStatus();

		// �t�@�C���f�[�^�̎擾
		g_aEnemyAxeTex = GetEnemyAxeTex();

		// �G�l�~�[�̎擾
		pEnemyAxe = GetEnemyAxe();

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_EnemyAxeMotion.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][nCntMotion].MotionRotX,
				g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][nCntMotion].MotionRotY,
				g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle = g_EnemyAxeMotion.aParts[nCntMotion].RotDest - g_EnemyAxeMotion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pEnemyAxe->aModel[nCntMotion].rot += g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle / (g_EnemyAxeMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyAxe->aModel[nCntMotion].rot >= g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemyAxe->aModel[nCntMotion].rot += g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle / (g_EnemyAxeMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemyAxe->aModel[nCntMotion].rot <= g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle)
			{
				pEnemyAxe->aModel[nCntMotion].rot += g_EnemyAxeMotion.aParts[nCntMotion].fRotAngle / (g_EnemyAxeMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyAxeMotion.aParts[nCntMotion].Rot = pEnemyAxe->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_EnemyAxeMotion.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][nCntMotion].MotionPosX,
				g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][nCntMotion].MotionPosY,
				g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.x = g_EnemyAxeMotion.aParts[nCntMotion].PosDest.x - g_EnemyAxeMotion.aParts[nCntMotion].Pos.x + g_aEnemyAxeTex->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.y = g_EnemyAxeMotion.aParts[nCntMotion].PosDest.y - g_EnemyAxeMotion.aParts[nCntMotion].Pos.y + g_aEnemyAxeTex->aModelTex[nCntMotion].PosY;
			g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.z = g_EnemyAxeMotion.aParts[nCntMotion].PosDest.z - g_EnemyAxeMotion.aParts[nCntMotion].Pos.z + g_aEnemyAxeTex->aModelTex[nCntMotion].PosZ;

			if (g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.x > D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.x -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.x < -D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.x += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.y > D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.y -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.y < -D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.y += D3DX_PI * 2;
			}

			if (g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.z > D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.z -= D3DX_PI * 2;
			}
			if (g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.z < -D3DX_PI)
			{
				g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle.z += D3DX_PI * 2;
			}

			pEnemyAxe->aModel[nCntMotion].pos += g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle / (g_EnemyAxeMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pEnemyAxe->aModel[nCntMotion].pos >= g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemyAxe->aModel[nCntMotion].pos += g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle / (g_EnemyAxeMotion.MAX_FLAME * 1.0f);
			}
			if (pEnemyAxe->aModel[nCntMotion].pos <= g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle)
			{
				pEnemyAxe->aModel[nCntMotion].pos += g_EnemyAxeMotion.aParts[nCntMotion].fPosAngle / (g_EnemyAxeMotion.MAX_FLAME * 1.0f);
			}

			g_EnemyAxeMotion.aParts[nCntMotion].Pos = pEnemyAxe->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_EnemyAxeMotion.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_EnemyAxeMotion.nCntFlame % g_EnemyAxeMotion.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_EnemyAxeMotion.KeyFlame == g_aEnemyAxeTex->KEYFLAME[g_EnemyAxeMotion.nNumEnemyAxeMotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_EnemyAxeMotion.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_EnemyAxeMotion.KeyFlame++;
					g_EnemyAxeMotion.MAX_FLAME = g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][g_EnemyAxeMotion.KeyFlame][0].MAX_FLAME;
				}
			}
		}

		// �t���[���̉��Z
		g_EnemyAxeMotion.nCntFlame++;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetEnemyAxeMotion(int nNumEnemyAxeMotion)
{
	// ���[�V�����̔ԍ�
	g_EnemyAxeMotion.nNumEnemyAxeMotion = nNumEnemyAxeMotion;

	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_EnemyAxeMotion.MAX_FLAME = g_aEnemyAxeTex->aMotionTex[g_EnemyAxeMotion.nNumEnemyAxeMotion][0][0].MAX_FLAME;

	if (nNumEnemyAxeMotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_EnemyAxeMotion.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
EnemyAxeMotion *GetEnemyAxeMotion(void)
{
	return &g_EnemyAxeMotion;
}