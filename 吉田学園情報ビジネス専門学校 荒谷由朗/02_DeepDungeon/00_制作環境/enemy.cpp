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
#include "enemy.h"
#include "sound.h"
#include "enemytext.h"
#include "enemymotion.h"
#include "SencerCol.h"
#include "SencerLock.h"
#include "SencerEnemy.h"
#include "SencerAtk.h"
#include "SencerEnableAttack.h"
#include "Wall1.h"
#include "Wall2.h"
#include "WallBoss.h"
#include "brazen.h"

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

ENEMY g_Enemy[MAX_ENEMY];
ENEMYSTATUS g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
ENEMYSTATUS g_EnemyStatusNow = ENEMYSTATUS_NEUTRAL;

//STAGE g_aLimit[4];
//�e�L�X�g���擾

float fJump_E;	//�W�����v��
float fGRAVITY_E_E;	//�d��

int g_nCntSound_E = 0;
int g_nCntEnemy;

bool bLand_E; //���n����
 //=============================================================================
 // ����������
 //=============================================================================
void InitEnemy(void)
{
	

	EnemyTex *pEnemyText;
	pEnemyText = GetEnemyTex();
	g_nCntEnemy = 3;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		for (int nCntIdx = 0; nCntIdx < pEnemyText->MAX_PARTS; nCntIdx++)
		{//�e��l�̑��
		 //�ǂݍ��ރ��f����
			g_Enemy[nCntEnemy].aModel[nCntIdx].FileName[0] = pEnemyText->aModelTex[nCntIdx].FileName[0];

			//�e�q�֌W
			g_Enemy[nCntEnemy].aModel[nCntIdx].nIdxModelParent = pEnemyText->aModelTex[nCntIdx].Index;

			//�ʒu
			g_Enemy[nCntEnemy].aModel[nCntIdx].pos = D3DXVECTOR3(pEnemyText->aModelTex[nCntIdx].PosX, pEnemyText->aModelTex[nCntIdx].PosY, pEnemyText->aModelTex[nCntIdx].PosZ);

			//��]
			g_Enemy[nCntEnemy].aModel[nCntIdx].rot = D3DXVECTOR3(pEnemyText->aModelTex[nCntIdx].RotX,
				pEnemyText->aModelTex[nCntIdx].RotY,
				pEnemyText->aModelTex[nCntIdx].RotZ);

			//���f���̐ݒ�
			D3DXLoadMeshFromX(&pEnemyText->aModelTex[nCntIdx].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCntEnemy].aModel[nCntIdx].pBuffMat,
				NULL,
				&g_Enemy[nCntEnemy].aModel[nCntIdx].nNumMat,
				&g_Enemy[nCntEnemy].aModel[nCntIdx].pMesh);
		}
		g_Enemy[nCntEnemy].Collision.bUse = false;
		g_Enemy[nCntEnemy].Collision.nCntMotion = 0;
		g_Enemy[nCntEnemy].Collision.StartFlame = 5;
		g_Enemy[nCntEnemy].Collision.fRadius = 40.0f;
		g_Enemy[nCntEnemy].Collision.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
		g_Enemy[nCntEnemy].Collision.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].Collision.nIdxParent = 0;
		g_Enemy[nCntEnemy].nCntCoolDown = 120;

		SetSencerAtk(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43 - 30.0f));
		SetSencerAtk(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43 - 20.0f));
		SetSencerAtk(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43 - 10.0f));
		SetSencerAtk(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43));


		//�W�����v�̏��
		g_Enemy[nCntEnemy].bUseJump = false;
		//�v���C���[�̏��
		g_Enemy[nCntEnemy].nCoolDown = 0;

		//���n���Ă��邩
		bLand_E = false;

		//�v���C���[���g�p����Ă��邩
		g_Enemy[nCntEnemy].bUse = false;

	}









	fJump_E = JUMP_POWER;
	fGRAVITY_E_E = GRAVITY_E;


	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_�����擾
		nNumVtx = g_Enemy[nCntEnemy].aModel[0].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCntEnemy].aModel[0].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_Enemy[nCntEnemy].aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W

			if (Vtx.x < g_Enemy[nCntEnemy].aModel[0].VtxMinModel.x)
			{
				g_Enemy[nCntEnemy].aModel[0].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_Enemy[nCntEnemy].aModel[0].VtxMinModel.y)
			{
				g_Enemy[nCntEnemy].aModel[0].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z < g_Enemy[nCntEnemy].aModel[0].VtxMinModel.z)
			{
				g_Enemy[nCntEnemy].aModel[0].VtxMinModel.z = Vtx.x;
			}


			if (Vtx.x > g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.x)
			{
				g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.x = Vtx.x + 20.0f;
			}

			if (Vtx.y > g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.y)
			{
				g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.y = Vtx.y + 30.0f;
			}

			if (Vtx.z > g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.z)
			{
				g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.z = Vtx.z + 20.0f;
			}
			pVtxBuff += sizeFVF;
		}

		g_Enemy[nCntEnemy].VtxMinEnemy.x = g_Enemy[nCntEnemy].aModel[0].VtxMinModel.x;
		g_Enemy[nCntEnemy].VtxMaxEnemy.x = g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.x;

		g_Enemy[nCntEnemy].VtxMinEnemy.y = g_Enemy[nCntEnemy].aModel[0].VtxMinModel.y;
		g_Enemy[nCntEnemy].VtxMaxEnemy.y = g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.y;

		g_Enemy[nCntEnemy].VtxMinEnemy.z = g_Enemy[nCntEnemy].aModel[0].VtxMinModel.z;
		g_Enemy[nCntEnemy].VtxMaxEnemy.z = g_Enemy[nCntEnemy].aModel[0].VtxMaxModel.z;

		g_Enemy[nCntEnemy].fAngle = 0.0f;			//����

	}

	CAMERA *pCamera;
	pCamera = GetCamera();


}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// ���b�V���̊J��
		if (g_Enemy[nCntEnemy].aModel[0].pMesh != NULL)
		{
			g_Enemy[nCntEnemy].aModel[0].pMesh->Release();
			g_Enemy[nCntEnemy].aModel[0].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_Enemy[nCntEnemy].aModel[0].pBuffMat != NULL)
		{
			g_Enemy[nCntEnemy].aModel[0].pBuffMat->Release();
			g_Enemy[nCntEnemy].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{

	EnemyMotion *pE_Motion = GetEnemyMotion();					//���[�V�����f�[�^�̏���
	EnemyTex *pE_Text = GetEnemyTex();							//�t�@�C���f�[�^�̎擾

	EnemyTex *pEnemyText;
	pEnemyText = GetEnemyTex();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾


#if 1




	//nCntUpdateRogic++;
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{




		g_Enemy[nCntEnemy].nCntCoolDown++;
		g_Enemy[nCntEnemy].posold = g_Enemy[nCntEnemy].pos;

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


		VecP.x = (pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x);
		VecP.y = pPlayer->pos.y - g_Enemy[nCntEnemy].pos.y;
		VecP.z = (pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z) + 45.0f;
		D3DXVec3Normalize(&VecP, &VecP);

		VecLength = pPlayer->pos - g_Enemy[nCntEnemy].pos;









		if (g_Enemy[nCntEnemy].bUse == true)
		{
			switch (g_Enemy[nCntEnemy].state2)
			{
			case ENEMYSTATE2_NORMAL:
				break;

			case ENEMYSTATE2_DAMAGE:
				g_Enemy[nCntEnemy].nCntCoolDown--;
				if (g_Enemy[nCntEnemy].nCntCoolDown <= 0)
				{
					g_Enemy[nCntEnemy].state2 = ENEMYSTATE2_NORMAL;
				}
			}



			static float fAngle;
			//fAngle = atan2f(pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x, pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z);
			fAngle = atan2f(g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x, g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z);

			g_Enemy[nCntEnemy].fLength = sqrtf((pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x) * (pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x) + (pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z) *(pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z));//����


			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}

			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}




			switch (g_Enemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NONE:

				if (CollisionSencer_Enemy(&pPlayer->pos, g_Enemy[nCntEnemy].nIndexSencerEnemy) == true)
				{
					g_Enemy[nCntEnemy].state = ENEMYSTATE_DISCOVERY;
				}
				else
				{
					g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				break;

			case ENEMYSTATE_BACKHOME:

				g_Enemy[nCntEnemy].DestHome = atan2f(g_Enemy[nCntEnemy].HomePoint.x - g_Enemy[nCntEnemy].pos.x,
					g_Enemy[nCntEnemy].HomePoint.z - g_Enemy[nCntEnemy].pos.z);

				g_Enemy[nCntEnemy].move.x = g_Enemy[nCntEnemy].DestHome * 1.2f;
				g_Enemy[nCntEnemy].move.z = g_Enemy[nCntEnemy].DestHome * 1.2f;

				if (g_Enemy[nCntEnemy].pos.x <= g_Enemy[nCntEnemy].HomePoint.x + 50.0f || g_Enemy[nCntEnemy].pos.x >= g_Enemy[nCntEnemy].HomePoint.x - 50.0f
					|| g_Enemy[nCntEnemy].pos.z <= g_Enemy[nCntEnemy].HomePoint.z + 50.0f || g_Enemy[nCntEnemy].pos.z >= g_Enemy[nCntEnemy].HomePoint.z - 50.0f)
				{
					g_Enemy[nCntEnemy].state = ENEMYSTATE_NONE;
				}

				break;
			case ENEMYSTATE_DISCOVERY:
				g_Enemy[nCntEnemy].move.x = VecP.x * 1.8f;
				g_Enemy[nCntEnemy].move.z = VecP.z * 1.8f;
				fAngle = atan2f(g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x, g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z);
				if (fAngle > D3DX_PI)
				{
					fAngle -= D3DX_PI * 2;
				}

				if (fAngle < -D3DX_PI)
				{
					fAngle += D3DX_PI * 2;
				}
				if (CollisionSencer_Enemy(&pPlayer->pos, g_Enemy[nCntEnemy].nIndexSencerEnemy) == false)
				{
					g_Enemy[nCntEnemy].state = ENEMYSTATE_BACKHOME;
				}
				if (g_EnemyStatusNow == ENEMYSTATUS_NEUTRAL)
				{//���[���ւ̈ڍs
					SetEnemyStatus(ENEMYSTATUS_MOVE, nCntEnemy);
				}
				if (CollisionSencer_Enable(&pPlayer->pos) == true)
				{
					if (g_EnemyStatusNow == ENEMYSTATUS_NEUTRAL || g_EnemyStatusNow == ENEMYSTATUS_MOVE)
					{//���[���ւ̈ڍs
						pE_Motion->nCntFlame = 0;
						if (g_Enemy[nCntEnemy].nCntCoolDown % 40 == 0)
						{
							SetEnemyStatus(ENEMYSTATUS_ATTACK, nCntEnemy);
						}
					}

					else if (g_EnemyStatusNow == ENEMYSTATUS_ATTACK)
					{
						if (pE_Motion->nCntFlame % g_Enemy[nCntEnemy].Collision.StartFlame == 0)
						{
							PlaySound(SOUND_LABEL_SE_SLASH);
						}
						if (pE_Motion->nCntFlame > g_Enemy[nCntEnemy].Collision.StartFlame)
						{
							CollisionAttackEnemy(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43 - 30.0f)
								, g_Enemy[nCntEnemy].Collision.fRadius
								, g_Enemy[nCntEnemy].nIndexSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43 - 20.0f)
								, g_Enemy[nCntEnemy].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43 - 10.0f)
								, g_Enemy[nCntEnemy].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43)
								, g_Enemy[nCntEnemy].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
						}
					}
					g_Enemy[nCntEnemy].rot.y = fAngle;
				}
				break;
			}//switch��

			g_Enemy[nCntEnemy].rot.y = fAngle;

#if 1

#endif			

			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move;

			g_Enemy[nCntEnemy].move.y -= GRAVITY_E;
			if (g_Enemy[nCntEnemy].move.y > GRAVITY_E_MAX)
			{
				g_Enemy[nCntEnemy].move.y = GRAVITY_E_MAX;
			}
			if (g_Enemy[nCntEnemy].pos.y <= 0.0)
			{

				g_Enemy[nCntEnemy].pos.y = 0.0f;
				g_Enemy[nCntEnemy].move.y = 0.0f;

			}



#endif
			SetPositionSencerCollision(g_Enemy[nCntEnemy].nIndexSencer, g_Enemy[nCntEnemy].pos);//�Z���T�[�̈ʒu
			SetPositionShadow(g_Enemy[nCntEnemy].nIndexShadow, g_Enemy[nCntEnemy].pos);
			SetPositionSencerEnemy(g_Enemy[nCntEnemy].nIndexSencerEnemy,
				D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z));
			SetPositionSencerEnableAttack(g_Enemy[nCntEnemy].nIndexSencerEnableAttack, g_Enemy[nCntEnemy].pos);
			CollisionSencer_Lock(&g_Enemy[nCntEnemy].pos);
			//g_Enemy[nCntEnemy].rot.y += 0.01f;




			switch (g_EnemyStatus)
			{
			case ENEMYSTATUS_NEUTRAL:
				if (pE_Motion->KeyFlame == pE_Text->KEYFLAME[pE_Motion->nNumEnemymotion] - 1)
				{
					if (g_EnemyStatusNow == ENEMYSTATUS_NEUTRAL)
					{

						SetEnemyMotion(0);
					}
					else
					{
						pE_Motion->KeyFlame = 0;
						SetEnemyMotion(0);
						g_EnemyStatusNow = ENEMYSTATUS_NEUTRAL;
						g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
					}
				}
				break;
			case ENEMYSTATUS_MOVE:
				g_EnemyStatusNow = ENEMYSTATUS_MOVE;
				g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
				SetEnemyMotion(1);
				break;
			case ENEMYSTATUS_ATTACK:
				g_EnemyStatusNow = ENEMYSTATUS_ATTACK;
				g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
				SetEnemyMotion(2);
				break;
			case ENEMYSTATUS_JUMP:
				g_EnemyStatusNow = ENEMYSTATUS_JUMP;
				g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
				SetEnemyMotion(3);
				break;
			case ENEMYSTATUS_LANDING:
				g_EnemyStatusNow = ENEMYSTATUS_LANDING;
				g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
				SetEnemyMotion(4);
				break;
			case ENEMYSTATUS_GUARD:
				g_EnemyStatusNow = ENEMYSTATUS_GUARD;
				g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
				SetEnemyMotion(5);
				break;
			case ENEMYSTATUS_DAMAGE1:
				g_EnemyStatusNow = ENEMYSTATUS_DAMAGE1;
				g_EnemyStatus = ENEMYSTATUS_NEUTRAL;
				SetEnemyMotion(6);
				break;

			}//switch
		//if

			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWall2_WIDTHBack_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//��O�ǂ̂����蔻��
				CollisionWall2_WIDTHThisSide_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_RIGHT_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_LEFT_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posold);
			}
		}//buse

	}//for
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
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
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot,
			g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);

		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxrot);


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans,
			g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);


		for (int nCntModelParts = 0; nCntModelParts < MAX_E_PARTS; nCntModelParts++)
		{
			if (g_Enemy[nCntEnemy].bUse == true)
			{

				if (g_Enemy[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == -1)
				{//�v���C���[�̃}�g���b�N�X��
					mtxParent = g_Enemy[nCntEnemy].mtxWorld;
				}
				else if (g_Enemy[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 0)
				{//�̂̃}�g���b�N�X��
					mtxParent = g_Enemy[nCntEnemy].aModel[0].mtxWorld;
				}
				else if (g_Enemy[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 1)
				{//���P��
					mtxParent = g_Enemy[nCntEnemy].aModel[1].mtxWorld;
				}
				else if (g_Enemy[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 2)
				{//���Q��
					mtxParent = g_Enemy[nCntEnemy].aModel[2].mtxWorld;
				}
				else if (g_Enemy[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 5)
				{//���Q��
					mtxParent = g_Enemy[nCntEnemy].aModel[5].mtxWorld;
				}
				else if (g_Enemy[nCntEnemy].aModel[nCntModelParts].nIdxModelParent == 8)
				{//���Q��
					mtxParent = g_Enemy[nCntEnemy].aModel[8].mtxWorld;
				}
				else
				{//���̑�
					mtxParent = g_Enemy[nCntEnemy].aModel[nCntModelParts - 1].mtxWorld;
				}
				//=======================================================================//
				//						    �e���f���̃C���f�b�N�X						//
				//=====================================================================//
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxrot,
					g_Enemy[nCntEnemy].aModel[nCntModelParts].rot.y, g_Enemy[nCntEnemy].aModel[nCntModelParts].rot.x, g_Enemy[nCntEnemy].aModel[nCntModelParts].rot.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld, &mtxrot);


				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxtrans,
					g_Enemy[nCntEnemy].aModel[nCntModelParts].pos.x, g_Enemy[nCntEnemy].aModel[nCntModelParts].pos.y, g_Enemy[nCntEnemy].aModel[nCntModelParts].pos.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld, &mtxtrans);

				//�e�̃}�g���b�N�X���f
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].aModel[nCntModelParts].mtxWorld);


				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel[nCntModelParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntEnemy].aModel[nCntModelParts].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//pDevice->SetTexture(0, g_Enemy[nCntEnemy].aModel[0].pEnemyTexture);
					pDevice->SetTexture(0, 0);
					// ���f��(�p�[�c)�̕`��
					g_Enemy[nCntEnemy].aModel[nCntModelParts].pMesh->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}

		/////////////////
		//�����蔻��p//
		///////////////
		if (g_Enemy[nCntEnemy].Collision.nIdxParent == -1)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_Enemy[nCntEnemy].aModel[16].mtxWorld;
		}
		if (g_Enemy[nCntEnemy].Collision.nIdxParent == 0)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_Enemy[nCntEnemy].aModel[15].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[nCntEnemy].Collision.mtxWorldCollision);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot, g_Enemy[nCntEnemy].Collision.rot.y, g_Enemy[nCntEnemy].Collision.rot.x, g_Enemy[nCntEnemy].Collision.rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].Collision.mtxWorldCollision, &g_Enemy[nCntEnemy].Collision.mtxWorldCollision, &mtxrot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans, g_Enemy[nCntEnemy].Collision.pos.x, g_Enemy[nCntEnemy].Collision.pos.y, g_Enemy[nCntEnemy].Collision.pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].Collision.mtxWorldCollision, &g_Enemy[nCntEnemy].Collision.mtxWorldCollision, &mtxtrans);

		//�e�̃}�g���b�N�X���f
		D3DXMatrixMultiply(&g_Enemy[nCntEnemy].Collision.mtxWorldCollision, &g_Enemy[nCntEnemy].Collision.mtxWorldCollision, &mtxParent);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].Collision.mtxWorldCollision);
	}
}
//=============================================================================
// �q�b�g����
//=============================================================================
void HitEnemy(int nDamage, int nCntEnemy)
{
	D3DXVECTOR3 VecP;
	
	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	if (g_Enemy[nCntEnemy].bUse == true)
	{
		g_Enemy[nCntEnemy].nLife += nDamage;

		VecP.x =   g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x;
		VecP.y = g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y;
		VecP.z = g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z * -1;


		D3DXVec3Normalize(&VecP, &VecP);
		//g_Enemy[nCntEnemy].pos += VecP * 80.0f;

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			SetParticle(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y + 30.0f, g_Enemy[nCntEnemy].pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f), PARTICLETYPE_EXPLOSION);
		}
		if (g_Enemy[nCntEnemy].nLife <= 0)
		{

			g_Enemy[nCntEnemy].bUse = false;
			DeletShadow(g_Enemy[nCntEnemy].nIndexShadow);
			DeleteSencerCol(g_Enemy[nCntEnemy].nIndexSencer);
			DeleteSencerEnemy(g_Enemy[nCntEnemy].nIndexSencerEnemy);
			DeleteSencerEnableAttack(g_Enemy[nCntEnemy].nIndexSencerEnableAttack);
			DecreaseBrazen(-2);

		}

	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosold, D3DXVECTOR3 * VtxMax, D3DXVECTOR3 * VtxMin)
{
	bool bCollision = false; //���n������

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			if (pPos->x + VtxMax->z >= g_Enemy[nCntEnemy].VtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x && pPos->x - VtxMax->z <= g_Enemy[nCntEnemy].VtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x
				&&pPos->y + VtxMax->y >= g_Enemy[nCntEnemy].VtxMinEnemy.y + g_Enemy[nCntEnemy].pos.y && pPos->y - VtxMax->y <= g_Enemy[nCntEnemy].VtxMaxEnemy.y + g_Enemy[nCntEnemy].pos.y
				&&pPos->z + VtxMax->z >= g_Enemy[nCntEnemy].VtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z && pPos->z - VtxMax->z <= g_Enemy[nCntEnemy].VtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z)
			{
				if (pPosold->x + VtxMax->z <= g_Enemy[nCntEnemy].VtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x  && pPos->x + VtxMax->z >= g_Enemy[nCntEnemy].VtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x)
				{//�����炫���Ƃ�
					pPos->x = g_Enemy[nCntEnemy].VtxMinEnemy.x + g_Enemy[nCntEnemy].pos.x - VtxMax->z;
					bCollision = true;
				}

				else if (pPosold->x - VtxMax->z >= g_Enemy[nCntEnemy].VtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x  && pPos->x - VtxMax->z <= g_Enemy[nCntEnemy].VtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x)
				{//�E���炫���Ƃ�
					pPos->x = g_Enemy[nCntEnemy].VtxMaxEnemy.x + g_Enemy[nCntEnemy].pos.x + VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z + VtxMax->z <= g_Enemy[nCntEnemy].VtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z && pPos->z + VtxMax->z >= g_Enemy[nCntEnemy].VtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z)
				{//��O���痈����
					pPos->z = g_Enemy[nCntEnemy].VtxMinEnemy.z + g_Enemy[nCntEnemy].pos.z - VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z - VtxMax->z >= g_Enemy[nCntEnemy].VtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z && pPos->z - VtxMax->z <= g_Enemy[nCntEnemy].VtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z)
				{//�����痈����
					pPos->z = g_Enemy[nCntEnemy].VtxMaxEnemy.z + g_Enemy[nCntEnemy].pos.z + VtxMax->z;
					bCollision = true;

				}

				if (pPosold->y + VtxMax->y <= g_Enemy[nCntEnemy].VtxMinEnemy.y + g_Enemy[nCntEnemy].pos.y && pPos->y + VtxMax->y >= g_Enemy[nCntEnemy].VtxMinEnemy.y + g_Enemy[nCntEnemy].pos.y)
				{//�ォ�痈����
					pPos->y = g_Enemy[nCntEnemy].VtxMinEnemy.y + g_Enemy[nCntEnemy].pos.y + VtxMin->y;
					bCollision = true;

				}
				if (pPosold->y - VtxMax->y >= g_Enemy[nCntEnemy].VtxMaxEnemy.y + g_Enemy[nCntEnemy].pos.y && pPos->y - VtxMax->y <= g_Enemy[nCntEnemy].VtxMaxEnemy.y + g_Enemy[nCntEnemy].pos.y)
				{//�����痈����
					pPos->y = g_Enemy[nCntEnemy].VtxMaxEnemy.y + g_Enemy[nCntEnemy].pos.y + VtxMax->y;
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
int SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].HomePoint = pos;
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].nLife = nLife;
			g_Enemy[nCntEnemy].nIndexSencer = SetSencerCollision(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot, SENCERCOLTYPE_ENEMY);
			g_Enemy[nCntEnemy].nIndexSencerEnemy = SetSencerEnemy(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);
			g_Enemy[nCntEnemy].nIndexSencerEnableAttack = SetSencerEnableAttack(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);
			g_Enemy[nCntEnemy].nIndexShadow = SetShadow(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);
			g_Enemy[nCntEnemy].state2 = ENEMYSTATE2_NORMAL;
			g_Enemy[nCntEnemy].bUse = true;
			break;
		}
	}
	return nCntEnemy;
}

//------------------------------------------------------------------------
// �G�l�~�[�̏�Ԃ̐ݒ�												      |
//------------------------------------------------------------------------
void SetEnemyStatus(ENEMYSTATUS status, int nCntEnemy)
{
	g_EnemyStatus = status;
}

////////////////////////////////////////////////////////////
//				�G�̏���								  //
////////////////////////////////////////////////////////////
void DeleteEnemy(int nCntEnemy)
{
	g_Enemy[nCntEnemy].bUse = false;
	DeletShadow(g_Enemy[nCntEnemy].nIndexShadow);
	DeleteSencerCol(g_Enemy[nCntEnemy].nIndexSencer);
	DeleteSencerEnemy(g_Enemy[nCntEnemy].nIndexSencerEnemy);
	DeleteSencerEnableAttack(g_Enemy[nCntEnemy].nIndexSencerEnableAttack);

}

////////////////////////////////////////////////////////////
//				�G�̎擾								  //
////////////////////////////////////////////////////////////
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}
///////////////////////////////////////////////////////////
//				�G��Ԃ̎擾							//
//////////////////////////////////////////////////////////
ENEMYSTATUS *GetEnemyStatus(void)
{
	return &g_Enemy[0].status;
}


