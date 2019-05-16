//=============================================================================
//
// �A�j���[�V�����̏��� [motion.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "motion.h"
#include "txt.h"
#include "player.h"

//------------------------------------------------------------------------
// �}�N����`															  |
//------------------------------------------------------------------------
#define MOVE_PARTS (15)			// �A�j���[�V�����œ����p�[�c��

//------------------------------------------------------------------------
// �O���[�o���ϐ��錾                                                      |
//------------------------------------------------------------------------
Tex *g_aTex;					// �e�L�X�g�f�[�^�̎擾
Player *pPlayer;				// �v���C���[�f�[�^�̎擾
Motion g_Motion;
int nNumMotion = 0;

//------------------------------------------------------------------------
// ����������															  |
//------------------------------------------------------------------------
void InitMotion(void)
{
	// �t�@�C���f�[�^�̎擾
	g_aTex = GetTex();

	// �v���C���[�̎擾
	pPlayer = GetPlayer();

	// �����ݒ�
	g_Motion.nNumPlayermotion = 0;
	g_Motion.nCntFlame = 0;
	g_Motion.KeyFlame = 0;
	g_Motion.MAX_FLAME = g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][0].MAX_FLAME;
	g_Motion.state = MOTIONSTATE_MOVE;

	for (int nCntParts = 0; nCntParts < MOVE_PARTS; nCntParts++)
	{// �A�j���[�V��������p�[�c�̏����擾
		g_Motion.aParts[nCntParts].Pos = D3DXVECTOR3(pPlayer->aModel[nCntParts].pos.x, pPlayer->aModel[nCntParts].pos.y, pPlayer->aModel[nCntParts].pos.z);
		g_Motion.aParts[nCntParts].fPosAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Motion.aParts[nCntParts].Rot = D3DXVECTOR3(pPlayer->aModel[nCntParts].rot.x, pPlayer->aModel[nCntParts].rot.y, pPlayer->aModel[nCntParts].rot.z);
		g_Motion.aParts[nCntParts].fRotAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//------------------------------------------------------------------------
// �I������																  |
//------------------------------------------------------------------------
void UninitMotion(void)
{// ����Ȃ�
}
//------------------------------------------------------------------------
// �X�V����																  |
//------------------------------------------------------------------------
void UpdateMotion(void)
{
	// �t�@�C���f�[�^�̎擾
	g_aTex = GetTex();

	// �v���C���[�̎擾
	pPlayer = GetPlayer();

	if (g_Motion.state == MOTIONSTATE_MOVE)
	{
		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
			// �e�L�X�g�f�[�^�����]�����擾����
			g_Motion.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionRotX,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionRotY,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_Motion.aParts[nCntMotion].fRotAngle = g_Motion.aParts[nCntMotion].RotDest - g_Motion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_Motion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_Motion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_Motion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_Motion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_Motion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_Motion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pPlayer->aModel[nCntMotion].rot += g_Motion.aParts[nCntMotion].fRotAngle / (g_Motion.MAX_FLAME * 1.0f);

			// �X�V
			if (pPlayer->aModel[nCntMotion].rot >= g_Motion.aParts[nCntMotion].fRotAngle)
			{
				pPlayer->aModel[nCntMotion].rot += g_Motion.aParts[nCntMotion].fRotAngle / (g_Motion.MAX_FLAME * 1.0f);
			}
			if (pPlayer->aModel[nCntMotion].rot <= g_Motion.aParts[nCntMotion].fRotAngle)
			{
				pPlayer->aModel[nCntMotion].rot += g_Motion.aParts[nCntMotion].fRotAngle / (g_Motion.MAX_FLAME * 1.0f);
			}

			g_Motion.aParts[nCntMotion].Rot = pPlayer->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
			// �e�L�X�g�f�[�^������W�����擾����
			g_Motion.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionPosX,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionPosY,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_Motion.aParts[nCntMotion].fPosAngle.x = g_Motion.aParts[nCntMotion].PosDest.x - g_Motion.aParts[nCntMotion].Pos.x + g_aTex->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_Motion.aParts[nCntMotion].fPosAngle.y = g_Motion.aParts[nCntMotion].PosDest.y - g_Motion.aParts[nCntMotion].Pos.y + g_aTex->aModelTex[nCntMotion].PosY;
			g_Motion.aParts[nCntMotion].fPosAngle.z = g_Motion.aParts[nCntMotion].PosDest.z - g_Motion.aParts[nCntMotion].Pos.z + g_aTex->aModelTex[nCntMotion].PosZ;

			pPlayer->aModel[nCntMotion].pos += g_Motion.aParts[nCntMotion].fPosAngle / (g_Motion.MAX_FLAME * 1.0f);

			// �X�V
			if (pPlayer->aModel[nCntMotion].pos >= g_Motion.aParts[nCntMotion].fPosAngle)
			{
				pPlayer->aModel[nCntMotion].pos += g_Motion.aParts[nCntMotion].fPosAngle / (g_Motion.MAX_FLAME * 1.0f);
			}
			if (pPlayer->aModel[nCntMotion].pos <= g_Motion.aParts[nCntMotion].fPosAngle)
			{
				pPlayer->aModel[nCntMotion].pos += g_Motion.aParts[nCntMotion].fPosAngle / (g_Motion.MAX_FLAME * 1.0f);
			}

			g_Motion.aParts[nCntMotion].Pos = pPlayer->aModel[nCntMotion].pos;		// ���݂̍X�V
		}

		// �L�[�t���[���̍X�V
		if (g_Motion.MAX_FLAME > 0)
		{// !!!	�������������G���[�ŗ����܂�	!!!
			if (g_Motion.nCntFlame % g_Motion.MAX_FLAME == 0)
			{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
				if (g_Motion.KeyFlame == g_aTex->KEYFLAME[g_Motion.nNumPlayermotion] - 1)
				{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
					g_Motion.KeyFlame = 0;
				}
				else
				{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
					g_Motion.KeyFlame++;
					g_Motion.MAX_FLAME = g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][0].MAX_FLAME;
				}
			}
		}
	}
	else if(g_Motion.state == MOTIONSTATE_STOP)
	{
		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ��]�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^�����]�����擾����
			g_Motion.aParts[nCntMotion].RotDest = D3DXVECTOR3(g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionRotX,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionRotY,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionRotZ);
			// �������v�Z����
			g_Motion.aParts[nCntMotion].fRotAngle = g_Motion.aParts[nCntMotion].RotDest - g_Motion.aParts[nCntMotion].Rot;		// ���� = �ړI - ����

			if (g_Motion.aParts[nCntMotion].fRotAngle.x > D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.x -= D3DX_PI * 2;
			}
			if (g_Motion.aParts[nCntMotion].fRotAngle.x < -D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.x += D3DX_PI * 2;
			}

			if (g_Motion.aParts[nCntMotion].fRotAngle.y > D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.y -= D3DX_PI * 2;
			}
			if (g_Motion.aParts[nCntMotion].fRotAngle.y < -D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.y += D3DX_PI * 2;
			}

			if (g_Motion.aParts[nCntMotion].fRotAngle.z > D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.z -= D3DX_PI * 2;
			}
			if (g_Motion.aParts[nCntMotion].fRotAngle.z < -D3DX_PI)
			{
				g_Motion.aParts[nCntMotion].fRotAngle.z += D3DX_PI * 2;
			}

			pPlayer->aModel[nCntMotion].rot += g_Motion.aParts[nCntMotion].fRotAngle / (g_Motion.MAX_FLAME * 1.0f);

			// �X�V
			if (pPlayer->aModel[nCntMotion].rot >= g_Motion.aParts[nCntMotion].fRotAngle)
			{
				pPlayer->aModel[nCntMotion].rot += g_Motion.aParts[nCntMotion].fRotAngle / (g_Motion.MAX_FLAME * 1.0f);
			}
			if (pPlayer->aModel[nCntMotion].rot <= g_Motion.aParts[nCntMotion].fRotAngle)
			{
				pPlayer->aModel[nCntMotion].rot += g_Motion.aParts[nCntMotion].fRotAngle / (g_Motion.MAX_FLAME * 1.0f);
			}

			g_Motion.aParts[nCntMotion].Rot = pPlayer->aModel[nCntMotion].rot;		// ���݂̍X�V
		}

		for (int nCntMotion = 0; nCntMotion < MOVE_PARTS; nCntMotion++)
		{// ���W�̍����������Ĉړ�����
		 // �e�L�X�g�f�[�^������W�����擾����
			g_Motion.aParts[nCntMotion].PosDest = D3DXVECTOR3(g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionPosX,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionPosY,
				g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][nCntMotion].MotionPosZ);
			// �������v�Z����
			g_Motion.aParts[nCntMotion].fPosAngle.x = g_Motion.aParts[nCntMotion].PosDest.x - g_Motion.aParts[nCntMotion].Pos.x + g_aTex->aModelTex[nCntMotion].PosX;		// ���� = �ړI - ����
			g_Motion.aParts[nCntMotion].fPosAngle.y = g_Motion.aParts[nCntMotion].PosDest.y - g_Motion.aParts[nCntMotion].Pos.y + g_aTex->aModelTex[nCntMotion].PosY;
			g_Motion.aParts[nCntMotion].fPosAngle.z = g_Motion.aParts[nCntMotion].PosDest.z - g_Motion.aParts[nCntMotion].Pos.z + g_aTex->aModelTex[nCntMotion].PosZ;

			pPlayer->aModel[nCntMotion].pos += g_Motion.aParts[nCntMotion].fPosAngle / (g_Motion.MAX_FLAME * 1.0f);

			// �X�V
			if (pPlayer->aModel[nCntMotion].pos >= g_Motion.aParts[nCntMotion].fPosAngle)
			{
				pPlayer->aModel[nCntMotion].pos += g_Motion.aParts[nCntMotion].fPosAngle / (g_Motion.MAX_FLAME * 1.0f);
			}
			if (pPlayer->aModel[nCntMotion].pos <= g_Motion.aParts[nCntMotion].fPosAngle)
			{
				pPlayer->aModel[nCntMotion].pos += g_Motion.aParts[nCntMotion].fPosAngle / (g_Motion.MAX_FLAME * 1.0f);
			}

			g_Motion.aParts[nCntMotion].Pos = pPlayer->aModel[nCntMotion].pos;		// ���݂̍X�V

			// �L�[�t���[���̍X�V
			if (g_Motion.MAX_FLAME > 0)
			{// !!!	�������������G���[�ŗ����܂�	!!!
				if (g_Motion.nCntFlame % g_Motion.MAX_FLAME == 0)
				{// �t���[�����w�肵�����A�i�񂾂�L�[�t���[�������ɐi�߂�
					if (g_Motion.KeyFlame == g_aTex->KEYFLAME[g_Motion.nNumPlayermotion] - 1)
					{// �Ō�̃L�[�ɂȂ�����0�ɖ߂�
						g_Motion.KeyFlame = g_aTex->KEYFLAME[g_Motion.nNumPlayermotion] - 1;
						//g_Motion.MAX_FLAME = g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][0].MAX_FLAME;
					}
					else
					{// �L�[�����ɐi�߂ăe�L�X�g�f�[�^���玟�̃t���[�����擾����
						g_Motion.KeyFlame++;
						g_Motion.MAX_FLAME = g_aTex->aMotionTex[g_Motion.nNumPlayermotion][g_Motion.KeyFlame][0].MAX_FLAME;
					}
				}
			}
		}
	}
	// �t���[���̉��Z
	g_Motion.nCntFlame++;

	switch (g_Motion.state)
	{
	case MOTIONSTATE_NEUTRAL:
		break;
	case MOTIONSTATE_MOVE:
		break;
	case MOTIONSTATE_STOP:
		break;
	}
}

//=============================================================================
// �`�揈��																	   |
//=============================================================================
void DrawMotion(void)
{// ����Ȃ�
}

void SetMotion_STATE(MOTIONSTATE state)
{
	g_Motion.state = state;
}

//=============================================================================
// ���[�V�����̐ݒ�															   |
//=============================================================================
void SetMotion(int nNumPlayermotion)
{
	// ���[�V�����̔ԍ�
	g_Motion.nNumPlayermotion = nNumPlayermotion;
	// �e�L�X�g�f�[�^���玟�̃t���[�����擾����
	g_Motion.MAX_FLAME = g_aTex->aMotionTex[g_Motion.nNumPlayermotion][0][0].MAX_FLAME;

	if (nNumPlayermotion > 0)
	{// 0�ȊO��������L�[�t���[��������������
		g_Motion.KeyFlame = 0;
	}
}

//=============================================================================
// ���[�V�����̏��̎擾													   |
//=============================================================================
Motion *GetMotion(void)
{
	return &g_Motion;
}