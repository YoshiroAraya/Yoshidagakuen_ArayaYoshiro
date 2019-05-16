//=============================================================================
//
// �G���� [enemy.cpp]
// Author : KishidaRei
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "particle.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "enemyarcher0.h"
#include "sound.h"
#include "enemyarchertext0.h"
#include "enemyarchermotion0.h"
#include "SencerCol.h"
#include "SencerLock.h"
#include "SencerEnemy.h"
#include "SencerAtk.h"
#include "SencerEnableAttack.h"
#include "Wall1.h"
#include "Wall2.h"
#include "WallBoss.h"
#include <math.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define JUMP_POWER (12.00f)	//�W�����v��
#define GRAVITY_E (0.8f)		//�d��
#define GRAVITY_E_MAX (150.0f)	//�d�͂̍ő��

#define DASHSPEED  (4.0f)
#define ROT_SPEED (0.05f)
#define ROT_SPEED2 (0.2f)

#define STAGE_LIMIT_MAX_X (1450.0f)
#define STAGE_LIMIT_MIN_X (-40.0f)
#define STAGE_LIMIT_MAX_Z (30.0f)
#define STAGE_LIMIT_MIN_Z (-3800.0f)

#define EFFECT_MAX (50)

#define MOVE_BULLET_Y (25.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

ENEMYARCHER_0 g_EnemyArcher_0[MAX_ENEMYARCHER_0];
ENEMYARCHERSTATUS_0 g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
ENEMYARCHERSTATUS_0 g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_NEUTRAL_0;

//STAGE g_aLimit[4];
//�e�L�X�g���擾

float fJump_A_0;	//�W�����v��
float fGRAVITY_E_A_0;	//�d��

int g_nCntSound_A_0 = 0;
int g_nCntEnemy_A0;

bool bLand_A_0; //���n����
 //=============================================================================
 // ����������
 //=============================================================================
void InitEnemyARCHER_0(void)
{
	

	EnemyArcherTex_0 *pEnemyText;
	pEnemyText = GetEnemyArcherTex_0();
	g_nCntEnemy_A0 = 3;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{
		for (int nCntIdx = 0; nCntIdx < pEnemyText->MAX_PARTS; nCntIdx++)
		{//�e��l�̑��
		 //�ǂݍ��ރ��f����
			g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].FileName[0] = pEnemyText->aModelTex[nCntIdx].FileName[0];

			//�e�q�֌W
			g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].nIdxModelParent = pEnemyText->aModelTex[nCntIdx].Index;

			//�ʒu
			g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].pos = D3DXVECTOR3(pEnemyText->aModelTex[nCntIdx].PosX, pEnemyText->aModelTex[nCntIdx].PosY, pEnemyText->aModelTex[nCntIdx].PosZ);

			//��]
			g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].rot = D3DXVECTOR3(pEnemyText->aModelTex[nCntIdx].RotX,
				pEnemyText->aModelTex[nCntIdx].RotY,
				pEnemyText->aModelTex[nCntIdx].RotZ);

			//���f���̐ݒ�
			D3DXLoadMeshFromX(&pEnemyText->aModelTex[nCntIdx].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].pBuffMat,
				NULL,
				&g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].nNumMat,
				&g_EnemyArcher_0[nCntEnemy].aModel[nCntIdx].pMesh);
		}
		g_EnemyArcher_0[nCntEnemy].Collision.bUse = false;
		g_EnemyArcher_0[nCntEnemy].Collision.nCntMotion = 0;
		g_EnemyArcher_0[nCntEnemy].Collision.StartFlame = 5;
		g_EnemyArcher_0[nCntEnemy].Collision.fRadius = 40.0f;
		g_EnemyArcher_0[nCntEnemy].Collision.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
		g_EnemyArcher_0[nCntEnemy].Collision.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyArcher_0[nCntEnemy].Collision.nIdxParent = 0;
		g_EnemyArcher_0[nCntEnemy].nCntCoolDown = 120;

		SetSencerAtk(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43 - 30.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43 - 20.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43 - 10.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43));


		//�W�����v�̏��
		g_EnemyArcher_0[nCntEnemy].bUseJump = false;
		//�v���C���[�̏��
		g_EnemyArcher_0[nCntEnemy].nCoolDown = 0;

		//���n���Ă��邩
		bLand_A_0 = false;

		//�v���C���[���g�p����Ă��邩
		g_EnemyArcher_0[nCntEnemy].bUse = false;

	}









	fJump_A_0 = JUMP_POWER;
	fGRAVITY_E_A_0 = GRAVITY_E;


	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{
		//���_�����擾
		nNumVtx = g_EnemyArcher_0[nCntEnemy].aModel[0].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyArcher_0[nCntEnemy].aModel[0].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_EnemyArcher_0[nCntEnemy].aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W

			if (Vtx.x < g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.x)
			{
				g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.y)
			{
				g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z < g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.z)
			{
				g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.z = Vtx.x;
			}


			if (Vtx.x > g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.x)
			{
				g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.x = Vtx.x + 20.0f;
			}

			if (Vtx.y > g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.y)
			{
				g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.y = Vtx.y + 30.0f;
			}

			if (Vtx.z > g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.z)
			{
				g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.z = Vtx.z + 20.0f;
			}
			pVtxBuff += sizeFVF;
		}

		g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.x = g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.x;
		g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.x = g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.x;

		g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.y = g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.y;
		g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.y = g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.y;

		g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.z = g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMinModel.z;
		g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.z = g_EnemyArcher_0[nCntEnemy].aModel[0].VtxMaxModel.z;

		g_EnemyArcher_0[nCntEnemy].fAngle = 0.0f;			//����

	}

	CAMERA *pCamera;
	pCamera = GetCamera();


}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyARCHER_0(void)
{
	

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{
		// ���b�V���̊J��
		if (g_EnemyArcher_0[nCntEnemy].aModel[0].pMesh != NULL)
		{
			g_EnemyArcher_0[nCntEnemy].aModel[0].pMesh->Release();
			g_EnemyArcher_0[nCntEnemy].aModel[0].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_EnemyArcher_0[nCntEnemy].aModel[0].pBuffMat != NULL)
		{
			g_EnemyArcher_0[nCntEnemy].aModel[0].pBuffMat->Release();
			g_EnemyArcher_0[nCntEnemy].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyARCHER_0(void)
{

	EnemyArcherMotion_0 *pE_Motion = GetEnemyArcherMotion_0();					//���[�V�����f�[�^�̏���
	EnemyArcherTex_0 *pE_Text = GetEnemyArcherTex_0();							//�t�@�C���f�[�^�̎擾

	EnemyArcherTex_0 *pEnemyText;
	pEnemyText = GetEnemyArcherTex_0();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾


#if 1




	//nCntUpdateRogic++;
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{




		g_EnemyArcher_0[nCntEnemy].nCntCoolDown++;
		g_EnemyArcher_0[nCntEnemy].posold = g_EnemyArcher_0[nCntEnemy].pos;

		CAMERA pCamera;
		pCamera = *GetCamera();
		PLAYER *pPlayer;
		//�v���C���[�̎擾
		pPlayer = GetPlayer();
		D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
		BulletMove.x = -30.0f;
		BulletMove.z = -30.0f;

		D3DXVECTOR3 BulletMove2(0.0f, 0.0f, 0.0f);
		BulletMove2.x = -7.0f;
		BulletMove2.z = -7.0f;

		D3DXVECTOR3 VecP;
		D3DXVECTOR3 VecLength;


		VecP.x = (pPlayer->pos.x - g_EnemyArcher_0[nCntEnemy].pos.x);
		VecP.y = pPlayer->pos.y - g_EnemyArcher_0[nCntEnemy].pos.y;
		VecP.z = (pPlayer->pos.z - g_EnemyArcher_0[nCntEnemy].pos.z) + 45.0f;
		D3DXVec3Normalize(&VecP, &VecP);

		VecLength = pPlayer->pos - g_EnemyArcher_0[nCntEnemy].pos;









		if (g_EnemyArcher_0[nCntEnemy].bUse == true)
		{
			switch (g_EnemyArcher_0[nCntEnemy].state2)
			{
			case ENEMYARCHERSTATE2_NORMAL_0:
				break;

			case ENEMYARCHERSTATE2_DAMAGE_0:
				g_EnemyArcher_0[nCntEnemy].nCntCoolDown--;
				if (g_EnemyArcher_0[nCntEnemy].nCntCoolDown <= 0)
				{
					g_EnemyArcher_0[nCntEnemy].state2 = ENEMYARCHERSTATE2_NORMAL_0;
				}
			}



			static float fAngle;
			//fAngle = atan2f(pPlayer->pos.x - g_EnemyArcher_0[nCntEnemy].pos.x, pPlayer->pos.z - g_EnemyArcher_0[nCntEnemy].pos.z);
			fAngle = atan2f(g_EnemyArcher_0[nCntEnemy].pos.x - pPlayer->pos.x, g_EnemyArcher_0[nCntEnemy].pos.z - pPlayer->pos.z);

			g_EnemyArcher_0[nCntEnemy].fLength = sqrtf((pPlayer->pos.x - g_EnemyArcher_0[nCntEnemy].pos.x) * (pPlayer->pos.x - g_EnemyArcher_0[nCntEnemy].pos.x) + (pPlayer->pos.z - g_EnemyArcher_0[nCntEnemy].pos.z) *(pPlayer->pos.z - g_EnemyArcher_0[nCntEnemy].pos.z));//����


			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}

			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}




			switch (g_EnemyArcher_0[nCntEnemy].state)
			{
			case ENEMYARCHERSTATE_NONE_0:

				if (CollisionSencer_Enemy(&pPlayer->pos, g_EnemyArcher_0[nCntEnemy].nIndexSencerEnemy) == true)
				{
					g_EnemyArcher_0[nCntEnemy].state = ENEMYARCHERSTATE_DISCOVERY_0;
				}
				else
				{
					g_EnemyArcher_0[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				break;

			case ENEMYARCHERSTATE_BACKHOME_0:

				g_EnemyArcher_0[nCntEnemy].DestHome = atan2f(g_EnemyArcher_0[nCntEnemy].HomePoint.x - g_EnemyArcher_0[nCntEnemy].pos.x,
					g_EnemyArcher_0[nCntEnemy].HomePoint.z - g_EnemyArcher_0[nCntEnemy].pos.z);

				g_EnemyArcher_0[nCntEnemy].move.x = g_EnemyArcher_0[nCntEnemy].DestHome * 1.2f;
				g_EnemyArcher_0[nCntEnemy].move.z = g_EnemyArcher_0[nCntEnemy].DestHome * 1.2f;

				if (g_EnemyArcher_0[nCntEnemy].pos.x <= g_EnemyArcher_0[nCntEnemy].HomePoint.x + 50.0f || g_EnemyArcher_0[nCntEnemy].pos.x >= g_EnemyArcher_0[nCntEnemy].HomePoint.x - 50.0f
					|| g_EnemyArcher_0[nCntEnemy].pos.z <= g_EnemyArcher_0[nCntEnemy].HomePoint.z + 50.0f || g_EnemyArcher_0[nCntEnemy].pos.z >= g_EnemyArcher_0[nCntEnemy].HomePoint.z - 50.0f)
				{
					g_EnemyArcher_0[nCntEnemy].state = ENEMYARCHERSTATE_NONE_0;
				}

				break;
			case ENEMYARCHERSTATE_DISCOVERY_0:
				g_EnemyArcher_0[nCntEnemy].move.x = VecP.x * 1.5f;
				g_EnemyArcher_0[nCntEnemy].move.z = VecP.z * 1.5f;
				fAngle = atan2f(g_EnemyArcher_0[nCntEnemy].pos.x - pPlayer->pos.x, g_EnemyArcher_0[nCntEnemy].pos.z - pPlayer->pos.z);
				if (fAngle > D3DX_PI)
				{
					fAngle -= D3DX_PI * 2;
				}

				if (fAngle < -D3DX_PI)
				{
					fAngle += D3DX_PI * 2;
				}
				if (CollisionSencer_Enemy(&pPlayer->pos,g_EnemyArcher_0[nCntEnemy].nIndexSencerEnemy) == false)
				{
					g_EnemyArcher_0[nCntEnemy].state = ENEMYARCHERSTATE_BACKHOME_0;
				}
				if (g_EnemyArcher_0StatusNow == ENEMYARCHERSTATUS_NEUTRAL_0)
				{//���[���ւ̈ڍs
					SetEnemyARCHERStatus_0(ENEMYARCHERSTATUS_MOVE_0, nCntEnemy);
				}
				if (CollisionSencer_Enable(&pPlayer->pos) == true)
				{
					if (g_EnemyArcher_0StatusNow == ENEMYARCHERSTATUS_NEUTRAL_0 || g_EnemyArcher_0StatusNow == ENEMYARCHERSTATUS_MOVE_0)
					{//���[���ւ̈ڍs
						pE_Motion->nCntFlame = 0;
						if (g_EnemyArcher_0[nCntEnemy].nCntCoolDown % 30 == 0)
						{
							SetEnemyARCHERStatus_0(ENEMYARCHERSTATUS_ATTACK_0, nCntEnemy);
						}
					}

					else if (g_EnemyArcher_0StatusNow == ENEMYARCHERSTATUS_ATTACK_0)
					{
						if (pE_Motion->nCntFlame % g_EnemyArcher_0[nCntEnemy].Collision.StartFlame == 0)
						{
							PlaySound(SOUND_LABEL_SE_SLASH);
						}
						if (pE_Motion->nCntFlame > g_EnemyArcher_0[nCntEnemy].Collision.StartFlame)
						{
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43 - 30.0f)
								, g_EnemyArcher_0[nCntEnemy].Collision.fRadius
								, g_EnemyArcher_0[nCntEnemy].nIndexSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43 - 20.0f)
								, g_EnemyArcher_0[nCntEnemy].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43 - 10.0f)
								, g_EnemyArcher_0[nCntEnemy].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._41, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._42, g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision._43)
								, g_EnemyArcher_0[nCntEnemy].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
						}
					}
					g_EnemyArcher_0[nCntEnemy].rot.y = fAngle;
				}
				break;
			}//switch��

			g_EnemyArcher_0[nCntEnemy].rot.y = fAngle;

#if 1

#endif			

			g_EnemyArcher_0[nCntEnemy].pos += g_EnemyArcher_0[nCntEnemy].move;

			g_EnemyArcher_0[nCntEnemy].move.y -= GRAVITY_E;
			if (g_EnemyArcher_0[nCntEnemy].move.y > GRAVITY_E_MAX)
			{
				g_EnemyArcher_0[nCntEnemy].move.y = GRAVITY_E_MAX;
			}
			if (g_EnemyArcher_0[nCntEnemy].pos.y <= 0.0)
			{

				g_EnemyArcher_0[nCntEnemy].pos.y = 0.0f;
				g_EnemyArcher_0[nCntEnemy].move.y = 0.0f;

			}



#endif
			SetPositionSencerCollision(g_EnemyArcher_0[nCntEnemy].nIndexSencer, g_EnemyArcher_0[nCntEnemy].pos);//�Z���T�[�̈ʒu
			SetPositionShadow(g_EnemyArcher_0[nCntEnemy].nIndexShadow, g_EnemyArcher_0[nCntEnemy].pos);
			SetPositionSencerEnemy(g_EnemyArcher_0[nCntEnemy].nIndexSencerEnemy,
				D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].pos.x, g_EnemyArcher_0[nCntEnemy].pos.y, g_EnemyArcher_0[nCntEnemy].pos.z));
			SetPositionSencerEnableAttack(g_EnemyArcher_0[nCntEnemy].nIndexSencerEnableAttack, g_EnemyArcher_0[nCntEnemy].pos);
			CollisionSencer_Lock(&g_EnemyArcher_0[nCntEnemy].pos);
			//g_EnemyArcher_0[nCntEnemy].rot.y += 0.01f;




			switch (g_EnemyArcher_0Status)
			{
			case ENEMYARCHERSTATUS_NEUTRAL_0:
				if (pE_Motion->KeyFlame == pE_Text->KEYFLAME[pE_Motion->nNumEnemymotion] - 1)
				{
					if (g_EnemyArcher_0StatusNow == ENEMYARCHERSTATUS_NEUTRAL_0)
					{

						SetEnemyArcherMotion_0(0);
					}
					else
					{
						pE_Motion->KeyFlame = 0;
						SetEnemyArcherMotion_0(0);
						g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_NEUTRAL_0;
						g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
					}
				}
				break;
			case ENEMYARCHERSTATUS_MOVE_0:
				g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_MOVE_0;
				g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
				SetEnemyArcherMotion_0(1);
				break;
			case ENEMYARCHERSTATUS_ATTACK_0:
				g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_ATTACK_0;
				g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
				SetEnemyArcherMotion_0(2);
				break;
			case ENEMYARCHERSTATUS_JUMP_0:
				g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_JUMP_0;
				g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
				SetEnemyArcherMotion_0(3);
				break;
			case ENEMYARCHERSTATUS_LANDING_0:
				g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_LANDING_0;
				g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
				SetEnemyArcherMotion_0(4);
				break;
			case ENEMYARCHERSTATUS_GUARD_0:
				g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_GUARD_0;
				g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
				SetEnemyArcherMotion_0(5);
				break;
			case ENEMYARCHERSTATUS_DAMAGE1_0:
				g_EnemyArcher_0StatusNow = ENEMYARCHERSTATUS_DAMAGE1_0;
				g_EnemyArcher_0Status = ENEMYARCHERSTATUS_NEUTRAL_0;
				SetEnemyArcherMotion_0(6);
				break;

			}//switch
		//if

			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWall2_WIDTHBack_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//��O�ǂ̂����蔻��
				CollisionWall2_WIDTHThisSide_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_RIGHT_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_LEFT_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_EnemyArcher_0[nCntEnemy].pos, &g_EnemyArcher_0[nCntEnemy].posold);
			}
		}//buse

	}//for
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyARCHER_0(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxrot, mtxtrans;

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	D3DXMATRIX mtxParent;
	D3DXMATRIX mtxParent2;

	//========================//
	//�v���C���[�̃C���f�b�N�X//
	//========================//
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EnemyArcher_0[nCntEnemy].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot,
			g_EnemyArcher_0[nCntEnemy].rot.y, g_EnemyArcher_0[nCntEnemy].rot.x, g_EnemyArcher_0[nCntEnemy].rot.z);

		D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].mtxWorld, &g_EnemyArcher_0[nCntEnemy].mtxWorld, &mtxrot);


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans,
			g_EnemyArcher_0[nCntEnemy].pos.x, g_EnemyArcher_0[nCntEnemy].pos.y, g_EnemyArcher_0[nCntEnemy].pos.z);
		D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].mtxWorld, &g_EnemyArcher_0[nCntEnemy].mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyArcher_0[nCntEnemy].mtxWorld);


		for (int nCntModelParts = 0; nCntModelParts < MAX_EARCHER_PARTS_0; nCntModelParts++)
		{
			if (g_EnemyArcher_0[nCntEnemy].bUse == true)
			{

				if (g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == -1)
				{//�v���C���[�̃}�g���b�N�X��
					mtxParent = g_EnemyArcher_0[nCntEnemy].mtxWorld;
				}
				else if (g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 0)
				{//�̂̃}�g���b�N�X��
					mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[0].mtxWorld;
				}
				else if (g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 1)
				{//���P��
					mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[1].mtxWorld;
				}
				else if (g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 2)
				{//���Q��
					mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[2].mtxWorld;
				}
				else if (g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 5)
				{//���Q��
					mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[5].mtxWorld;
				}
				else if (g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 8)
				{//���Q��
					mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[8].mtxWorld;
				}
				else
				{//���̑�
					mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts - 1].mtxWorld;
				}
				//=======================================================================//
				//						    �e���f���̃C���f�b�N�X						//
				//=====================================================================//
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxrot,
					g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].rot.y, g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].rot.x, g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].rot.z);
				D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld, &g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld, &mtxrot);


				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxtrans,
					g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].pos.x, g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].pos.y, g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].pos.z);
				D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld, &g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld, &mtxtrans);

				//�e�̃}�g���b�N�X���f
				D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld, &g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].mtxWorld);


				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//pDevice->SetTexture(0, g_EnemyArcher_0[nCntEnemy].aModel[0].pEnemyTexture);
					pDevice->SetTexture(0, 0);
					// ���f��(�p�[�c)�̕`��
					g_EnemyArcher_0[nCntEnemy].aModel[nCntModelParts].pMesh->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}

		/////////////////
		//�����蔻��p//
		///////////////
		if (g_EnemyArcher_0[nCntEnemy].Collision.nIdxParent == -1)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[16].mtxWorld;
		}
		if (g_EnemyArcher_0[nCntEnemy].Collision.nIdxParent == 0)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_EnemyArcher_0[nCntEnemy].aModel[15].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot, g_EnemyArcher_0[nCntEnemy].Collision.rot.y, g_EnemyArcher_0[nCntEnemy].Collision.rot.x, g_EnemyArcher_0[nCntEnemy].Collision.rot.z);
		D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision, &g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision, &mtxrot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans, g_EnemyArcher_0[nCntEnemy].Collision.pos.x, g_EnemyArcher_0[nCntEnemy].Collision.pos.y, g_EnemyArcher_0[nCntEnemy].Collision.pos.z);
		D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision, &g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision, &mtxtrans);

		//�e�̃}�g���b�N�X���f
		D3DXMatrixMultiply(&g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision, &g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision, &mtxParent);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyArcher_0[nCntEnemy].Collision.mtxWorldCollision);
	}
}
//=============================================================================
// �q�b�g����
//=============================================================================
void HitEnemyARCHER_0(int nDamage, int nCntEnemy)
{
	D3DXVECTOR3 VecP;
	
	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	if (g_EnemyArcher_0[nCntEnemy].bUse == true)
	{
		g_EnemyArcher_0[nCntEnemy].nLife += nDamage;

		VecP.x =   g_EnemyArcher_0[nCntEnemy].pos.x - pPlayer->pos.x;
		VecP.y = g_EnemyArcher_0[nCntEnemy].pos.y - pPlayer->pos.y;
		VecP.z = g_EnemyArcher_0[nCntEnemy].pos.z - pPlayer->pos.z * -1;


		D3DXVec3Normalize(&VecP, &VecP);
		//g_EnemyArcher_0[nCntEnemy].pos += VecP * 80.0f;

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			SetParticle(D3DXVECTOR3(g_EnemyArcher_0[nCntEnemy].pos.x, g_EnemyArcher_0[nCntEnemy].pos.y + 30.0f, g_EnemyArcher_0[nCntEnemy].pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f), PARTICLETYPE_EXPLOSION);
		}
		if (g_EnemyArcher_0[nCntEnemy].nLife <= 0)
		{

			g_EnemyArcher_0[nCntEnemy].bUse = false;
			DeletShadow(g_EnemyArcher_0[nCntEnemy].nIndexShadow);
			DeleteSencerCol(g_EnemyArcher_0[nCntEnemy].nIndexSencer);
			DeleteSencerEnemy(g_EnemyArcher_0[nCntEnemy].nIndexSencerEnemy);
			DeleteSencerEnableAttack(g_EnemyArcher_0[nCntEnemy].nIndexSencerEnableAttack);
		}

	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CollisionEnemyARCHER_0(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosold, D3DXVECTOR3 * VtxMax, D3DXVECTOR3 * VtxMin)
{
	bool bCollision = false; //���n������

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{
		if (g_EnemyArcher_0[nCntEnemy].bUse == true)
		{
			if (pPos->x + VtxMax->z >= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x && pPos->x - VtxMax->z <= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x
				&&pPos->y + VtxMax->y >= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y && pPos->y - VtxMax->y <= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y
				&&pPos->z + VtxMax->z >= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z && pPos->z - VtxMax->z <= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z)
			{
				if (pPosold->x + VtxMax->z <= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x  && pPos->x + VtxMax->z >= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x)
				{//�����炫���Ƃ�
					pPos->x = g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x - VtxMax->z;
					bCollision = true;
				}

				else if (pPosold->x - VtxMax->z >= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x  && pPos->x - VtxMax->z <= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x)
				{//�E���炫���Ƃ�
					pPos->x = g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.x + g_EnemyArcher_0[nCntEnemy].pos.x + VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z + VtxMax->z <= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z && pPos->z + VtxMax->z >= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z)
				{//��O���痈����
					pPos->z = g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z - VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z - VtxMax->z >= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z && pPos->z - VtxMax->z <= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z)
				{//�����痈����
					pPos->z = g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.z + g_EnemyArcher_0[nCntEnemy].pos.z + VtxMax->z;
					bCollision = true;

				}

				if (pPosold->y + VtxMax->y <= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y && pPos->y + VtxMax->y >= g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y)
				{//�ォ�痈����
					pPos->y = g_EnemyArcher_0[nCntEnemy].VtxMinEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y + VtxMin->y;
					bCollision = true;

				}
				if (pPosold->y - VtxMax->y >= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y && pPos->y - VtxMax->y <= g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y)
				{//�����痈����
					pPos->y = g_EnemyArcher_0[nCntEnemy].VtxMaxEnemy.y + g_EnemyArcher_0[nCntEnemy].pos.y + VtxMax->y;
					bCollision = true;

				}
			}

		}
	}
	return bCollision;
}

//////////////////////////////////////////////////////////////////////////
//////				�G�̐ݒu								  ////////////
//////////////////////////////////////////////////////////////////////////
int SetEnemyARCHER_0(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMYARCHER_0; nCntEnemy++)
	{
		if (g_EnemyArcher_0[nCntEnemy].bUse == false)
		{
			g_EnemyArcher_0[nCntEnemy].pos = pos;
			g_EnemyArcher_0[nCntEnemy].HomePoint = pos;
			g_EnemyArcher_0[nCntEnemy].rot = rot;
			g_EnemyArcher_0[nCntEnemy].nLife = nLife;
			g_EnemyArcher_0[nCntEnemy].nIndexSencer = SetSencerCollision(g_EnemyArcher_0[nCntEnemy].pos, g_EnemyArcher_0[nCntEnemy].rot, SENCERCOLTYPE_ENEMY);
			g_EnemyArcher_0[nCntEnemy].nIndexSencerEnemy = SetSencerEnemy(g_EnemyArcher_0[nCntEnemy].pos, g_EnemyArcher_0[nCntEnemy].rot);
			g_EnemyArcher_0[nCntEnemy].nIndexSencerEnableAttack = SetSencerEnableAttack(g_EnemyArcher_0[nCntEnemy].pos, g_EnemyArcher_0[nCntEnemy].rot);
			g_EnemyArcher_0[nCntEnemy].nIndexShadow = SetShadow(g_EnemyArcher_0[nCntEnemy].pos, g_EnemyArcher_0[nCntEnemy].rot);
			g_EnemyArcher_0[nCntEnemy].state2 = ENEMYARCHERSTATE2_NORMAL_0;
			g_EnemyArcher_0[nCntEnemy].bUse = true;
			break;
		}
	}
	return nCntEnemy;
}

//------------------------------------------------------------------------
// �G�l�~�[�̏�Ԃ̐ݒ�												      |
//------------------------------------------------------------------------
void SetEnemyARCHERStatus_0(ENEMYARCHERSTATUS_0 status, int nCntEnemy)
{
	g_EnemyArcher_0Status = status;
}

////////////////////////////////////////////////////////////
//				�G�̏���								  //
////////////////////////////////////////////////////////////
void DeleteEnemyARCHER_0(int nCntEnemy)
{
	g_EnemyArcher_0[nCntEnemy].bUse = false;
	DeletShadow(g_EnemyArcher_0[nCntEnemy].nIndexShadow);
	DeleteSencerCol(g_EnemyArcher_0[nCntEnemy].nIndexSencer);
	DeleteSencerEnemy(g_EnemyArcher_0[nCntEnemy].nIndexSencerEnemy);
	DeleteSencerEnableAttack(g_EnemyArcher_0[nCntEnemy].nIndexSencerEnableAttack);

}

////////////////////////////////////////////////////////////
//				�G�̎擾								  //
////////////////////////////////////////////////////////////
ENEMYARCHER_0 *GetEnemyARCHER_0(void)
{
	return &g_EnemyArcher_0[0];
}
///////////////////////////////////////////////////////////
//				�G��Ԃ̎擾							//
//////////////////////////////////////////////////////////
ENEMYARCHERSTATUS_0 *GetEnemyARCHERStatus_0(void)
{
	return &g_EnemyArcher_0[0].status;
}


