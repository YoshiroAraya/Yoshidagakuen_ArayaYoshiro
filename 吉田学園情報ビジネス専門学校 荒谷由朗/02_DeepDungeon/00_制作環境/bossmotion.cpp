//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "bossmotion.h"
#include "bosstext.h"
#include "boss.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
BossTex *pBossText;					// �e�L�X�g�f�[�^�̎擾
BOSS *pBoss;				// �G�l�~�[�f�[�^�̎擾
BossMotion g_BossMotion;
int nNumBossMotion = 0;
int g_CntBossMotion = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitBossMotion(void)
{
	// �t�@�C���f�[�^�̎擾
	pBossText = GetBossTex();

	// �G�l�~�[�̎擾
	pBoss = GetBoss();

	// �����ݒ�
	g_BossMotion.nNumBossMotion = 0;
	g_BossMotion.nCntFlame = 0;
	g_BossMotion.KeyFlame = 0;
	g_BossMotion.MAX_FLAME = pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][0].MAX_FLAME;

	for (int nCntParts = 0; nCntParts > MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_BossMotion.aParts[nCntParts].Pos = D3DXVECTOR3(pBoss->aModel[nCntParts].pos.x, pBoss->aModel[nCntParts].pos.y, pBoss->aModel[nCntParts].pos.z);
		g_BossMotion.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_BossMotion.aParts[nCntParts].Rot = D3DXVECTOR3(pBoss->aModel[nCntParts].rot.x, pBoss->aModel[nCntParts].rot.y, pBoss->aModel[nCntParts].rot.z);
		g_BossMotion.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateBossMotion(void)
{
	g_CntBossMotion++;

	if (g_CntBossMotion % 1 == 0)
	{
		// �G�l�~�[�̏�Ԃ��擾
		BOSSSTATUS *pBossState;
		pBossState = GetBossStatus();

		// �t�@�C���f�[�^�̎擾
		pBossText = GetBossTex();

		// �G�l�~�[�̎擾
		pBoss = GetBoss();

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_BossMotion.aParts[nCntMotion].RotDest = D3DXVECTOR3(pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][nCntMotion].MotionRotX,
				pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][nCntMotion].MotionRotY,
				pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_BossMotion.aParts[nCntMotion].fRotAngle = g_BossMotion.aParts[nCntMotion].RotDest - g_BossMotion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_BossMotion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_BossMotion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_BossMotion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_BossMotion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_BossMotion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_BossMotion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pBoss->aModel[nCntMotion].rot += g_BossMotion.aParts[nCntMotion].fRotAngle / (g_BossMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pBoss->aModel[nCntMotion].rot >= g_BossMotion.aParts[nCntMotion].fRotAngle)
			{
				pBoss->aModel[nCntMotion].rot += g_BossMotion.aParts[nCntMotion].fRotAngle / (g_BossMotion.MAX_FLAME * 1.0f);
			}
			if (pBoss->aModel[nCntMotion].rot <= g_BossMotion.aParts[nCntMotion].fRotAngle)
			{
				pBoss->aModel[nCntMotion].rot += g_BossMotion.aParts[nCntMotion].fRotAngle / (g_BossMotion.MAX_FLAME * 1.0f);
			}

			g_BossMotion.aParts[nCntMotion].Rot = pBoss->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_BossMotion.aParts[nCntMotion].PosDest = D3DXVECTOR3(pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][nCntMotion].MotionPosX,
				pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][nCntMotion].MotionPosY,
				pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_BossMotion.aParts[nCntMotion].fPosAngle.x = g_BossMotion.aParts[nCntMotion].PosDest.x - g_BossMotion.aParts[nCntMotion].Pos.x + pBossText->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_BossMotion.aParts[nCntMotion].fPosAngle.y = g_BossMotion.aParts[nCntMotion].PosDest.y - g_BossMotion.aParts[nCntMotion].Pos.y + pBossText->aModelTex[nCntMotion].PosY;
			g_BossMotion.aParts[nCntMotion].fPosAngle.z = g_BossMotion.aParts[nCntMotion].PosDest.z - g_BossMotion.aParts[nCntMotion].Pos.z + pBossText->aModelTex[nCntMotion].PosZ;

			if (g_BossMotion.aParts[nCntMotion].fPosAngle.x > D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fPosAngle.x -= D3DX_PI * 2;
			}
			if (g_BossMotion.aParts[nCntMotion].fPosAngle.x < -D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fPosAngle.x += D3DX_PI * 2;
			}

			if (g_BossMotion.aParts[nCntMotion].fPosAngle.y > D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fPosAngle.y -= D3DX_PI * 2;
			}
			if (g_BossMotion.aParts[nCntMotion].fPosAngle.y < -D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fPosAngle.y += D3DX_PI * 2;
			}

			if (g_BossMotion.aParts[nCntMotion].fPosAngle.z > D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fPosAngle.z -= D3DX_PI * 2;
			}
			if (g_BossMotion.aParts[nCntMotion].fPosAngle.z < -D3DX_PI)
			{
				g_BossMotion.aParts[nCntMotion].fPosAngle.z += D3DX_PI * 2;
			}

			pBoss->aModel[nCntMotion].pos += g_BossMotion.aParts[nCntMotion].fPosAngle / (g_BossMotion.MAX_FLAME * 1.0f);

			// �X�V
			if (pBoss->aModel[nCntMotion].pos >= g_BossMotion.aParts[nCntMotion].fPosAngle)
			{
				pBoss->aModel[nCntMotion].pos += g_BossMotion.aParts[nCntMotion].fPosAngle / (g_BossMotion.MAX_FLAME * 1.0f);
			}
			if (pBoss->aModel[nCntMotion].pos <= g_BossMotion.aParts[nCntMotion].fPosAngle)
			{
				pBoss->aModel[nCntMotion].pos += g_BossMotion.aParts[nCntMotion].fPosAngle / (g_BossMotion.MAX_FLAME * 1.0f);
			}

			g_BossMotion.aParts[nCntMotion].Pos = pBoss->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_BossMotion.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_BossMotion.nCntFlame % g_BossMotion.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_BossMotion.KeyFlame == pBossText->KEYFLAME[g_BossMotion.nNumBossMotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_BossMotion.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_BossMotion.KeyFlame++;
					g_BossMotion.MAX_FLAME = pBossText->aMotionTex[g_BossMotion.nNumBossMotion][g_BossMotion.KeyFlame][0].MAX_FLAME;
				}
			}
		}

		// �t���[���̉��Z
		g_BossMotion.nCntFlame++;
	}
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetBossMotion(int nNumBossMotion)
{
	// ���[�V�����̔ԍ�
	g_BossMotion.nNumBossMotion = nNumBossMotion;

	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_BossMotion.MAX_FLAME = pBossText->aMotionTex[g_BossMotion.nNumBossMotion][0][0].MAX_FLAME;

	if (nNumBossMotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_BossMotion.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
BossMotion *GetBossMotion(void)
{
	return &g_BossMotion;
}