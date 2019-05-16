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
#include "boss.h"
#include "sound.h"
#include "bosstext.h"
#include "bossmotion.h"
#include "SencerCol.h"
#include "SencerLock.h"
#include "SencerEnemy.h"
#include "SencerAtk.h"
#include "SencerEnableBoss.h"
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

BOSS g_Boss;
BOSSSTATUS g_BossStatus = BOSSSTATUS_NEUTRAL;
BOSSSTATUS g_BossStatusNow = BOSSSTATUS_NEUTRAL;

//STAGE g_aLimit[4];
//�e�L�X�g���擾

float fGravity_Boss;	//�d��

int g_nCntBoss;

bool bLand_Boss; //���n����
//=============================================================================
// ����������
//=============================================================================
void InitBoss(void)
{


	BossTex *pBossText;
	pBossText = GetBossTex();
	g_nCntBoss = 3;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	
		for (int nCntIdx = 0; nCntIdx < pBossText->MAX_PARTS; nCntIdx++)
		{//�e��l�̑��
		 //�ǂݍ��ރ��f����
			g_Boss.aModel[nCntIdx].FileName[0] = pBossText->aModelTex[nCntIdx].FileName[0];

			//�e�q�֌W
			g_Boss.aModel[nCntIdx].nIdxModelParent = pBossText->aModelTex[nCntIdx].Index;

			//�ʒu
			g_Boss.aModel[nCntIdx].pos = D3DXVECTOR3(pBossText->aModelTex[nCntIdx].PosX, pBossText->aModelTex[nCntIdx].PosY, pBossText->aModelTex[nCntIdx].PosZ);

			//��]
			g_Boss.aModel[nCntIdx].rot = D3DXVECTOR3(pBossText->aModelTex[nCntIdx].RotX,
				pBossText->aModelTex[nCntIdx].RotY,
				pBossText->aModelTex[nCntIdx].RotZ);

			//���f���̐ݒ�
			D3DXLoadMeshFromX(&pBossText->aModelTex[nCntIdx].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Boss.aModel[nCntIdx].pBuffMat,
				NULL,
				&g_Boss.aModel[nCntIdx].nNumMat,
				&g_Boss.aModel[nCntIdx].pMesh);
		}
		g_Boss.Collision.bUse = false;
		g_Boss.Collision.nCntMotion = 0;
		g_Boss.Collision.StartFlame = 5;
		g_Boss.Collision.fRadius = 40.0f;
		g_Boss.Collision.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
		g_Boss.Collision.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Boss.Collision.nIdxParent = 0;
		g_Boss.nCntCoolDown = 120;

		SetSencerAtk(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 50.0f));
		SetSencerAtk(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 40.0f));
		SetSencerAtk(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 30.0f));
		SetSencerAtk(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 20.0f));
		SetSencerAtk(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 10.0f));
		SetSencerAtk(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43));


		
		//�{�X�̏��
		g_Boss.nCoolDown = 0;

		//���n���Ă��邩
		bLand_Boss = false;

		//�{�X���g�p����Ă��邩
		g_Boss.bUse = false;

	



	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	
		//���_�����擾
		nNumVtx = g_Boss.aModel[0].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Boss.aModel[0].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_Boss.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W

			if (Vtx.x < g_Boss.aModel[0].VtxMinModel.x)
			{
				g_Boss.aModel[0].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_Boss.aModel[0].VtxMinModel.y)
			{
				g_Boss.aModel[0].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z < g_Boss.aModel[0].VtxMinModel.z)
			{
				g_Boss.aModel[0].VtxMinModel.z = Vtx.x;
			}


			if (Vtx.x > g_Boss.aModel[0].VtxMaxModel.x)
			{
				g_Boss.aModel[0].VtxMaxModel.x = Vtx.x + 20.0f;
			}

			if (Vtx.y > g_Boss.aModel[0].VtxMaxModel.y)
			{
				g_Boss.aModel[0].VtxMaxModel.y = Vtx.y + 30.0f;
			}

			if (Vtx.z > g_Boss.aModel[0].VtxMaxModel.z)
			{
				g_Boss.aModel[0].VtxMaxModel.z = Vtx.z + 20.0f;
			}
			pVtxBuff += sizeFVF;
		}

		g_Boss.VtxMinBoss.x = g_Boss.aModel[0].VtxMinModel.x;
		g_Boss.VtxMaxBoss.x = g_Boss.aModel[0].VtxMaxModel.x;

		g_Boss.VtxMinBoss.y = g_Boss.aModel[0].VtxMinModel.y;
		g_Boss.VtxMaxBoss.y = g_Boss.aModel[0].VtxMaxModel.y;

		g_Boss.VtxMinBoss.z = g_Boss.aModel[0].VtxMinModel.z;
		g_Boss.VtxMaxBoss.z = g_Boss.aModel[0].VtxMaxModel.z;

		g_Boss.fAngle = 0.0f;			//����



	CAMERA *pCamera;
	pCamera = GetCamera();


}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{


	
		// ���b�V���̊J��
		if (g_Boss.aModel[0].pMesh != NULL)
		{
			g_Boss.aModel[0].pMesh->Release();
			g_Boss.aModel[0].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_Boss.aModel[0].pBuffMat != NULL)
		{
			g_Boss.aModel[0].pBuffMat->Release();
			g_Boss.aModel[0].pBuffMat = NULL;
		}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{

	BossMotion *pBoss_Motion = GetBossMotion();					//���[�V�����f�[�^�̏���
	BossTex *pBoss_Text = GetBossTex();							//�t�@�C���f�[�^�̎擾

	BossTex *pBossText;
	pBossText = GetBossTex();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾


#if 1


		g_Boss.nCntCoolDown++;
		g_Boss.posold = g_Boss.pos;

		CAMERA pCamera;
		pCamera = *GetCamera();
		PLAYER *pPlayer;
		//�{�X�̎擾
		pPlayer = GetPlayer();
		D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
		BulletMove.x = -30.0f;
		BulletMove.z = -30.0f;

		D3DXVECTOR3 BulletMove2(0.0f, 0.0f, 0.0f);
		BulletMove2.x = -7.0f;
		BulletMove2.z = -7.0f;

		D3DXVECTOR3 VecP;
		D3DXVECTOR3 VecLength;


		VecP.x = (pPlayer->pos.x - g_Boss.pos.x);
		VecP.y = pPlayer->pos.y - g_Boss.pos.y;
		VecP.z = (pPlayer->pos.z - g_Boss.pos.z) + 45.0f;
		D3DXVec3Normalize(&VecP, &VecP);

		VecLength = pPlayer->pos - g_Boss.pos;









		if (g_Boss.bUse == true)
		{
			switch (g_Boss.state)
			{
			case BOSSSTATE_NORMAL:
				break;

			case BOSSSTATE_DAMAGE:
				g_Boss.nCntCoolDown--;
				if (g_Boss.nCntCoolDown <= 0)
				{
					g_Boss.state = BOSSSTATE_NORMAL;
				}
			}



			static float fAngle;
			//fAngle = atan2f(pPlayer->pos.x - g_Boss.pos.x, pPlayer->pos.z - g_Boss.pos.z);
			fAngle = atan2f(g_Boss.pos.x - pPlayer->pos.x, g_Boss.pos.z - pPlayer->pos.z);

			g_Boss.fLength = sqrtf((pPlayer->pos.x - g_Boss.pos.x) * (pPlayer->pos.x - g_Boss.pos.x) + (pPlayer->pos.z - g_Boss.pos.z) *(pPlayer->pos.z - g_Boss.pos.z));//����


			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}

			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}


				g_Boss.move.x = VecP.x * 2.0f;
				g_Boss.move.z = VecP.z * 2.0f;

				if (g_BossStatusNow == BOSSSTATUS_NEUTRAL)
				{//���[���ւ̈ڍs
					SetBossStatus(BOSSSTATUS_MOVE);
				}
				if (CollisionSencer_EnableBoss(&pPlayer->pos) == true)
				{
					if (g_BossStatusNow == BOSSSTATUS_NEUTRAL || g_BossStatusNow == BOSSSTATUS_MOVE)
					{//���[���ւ̈ڍs
						pBoss_Motion->nCntFlame = 0;
						if (g_Boss.nCntCoolDown % 30 == 0)
						{
							SetBossStatus(BOSSSTATUS_ATTACK);
						}
					}

					else if (g_BossStatusNow == BOSSSTATUS_ATTACK)
					{
						if (pBoss_Motion->nCntFlame % g_Boss.Collision.StartFlame == 0)
						{
							PlaySound(SOUND_LABEL_SE_SLASH);
						}
						if (pBoss_Motion->nCntFlame > g_Boss.Collision.StartFlame)
						{
							CollisionAttackBoss(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 50.0f)
								, g_Boss.Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY_BOSS);
							CollisionAttackBoss(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 40.0f)
								, g_Boss.Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY_BOSS);
							CollisionAttackBoss(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 30.0f)
								, g_Boss.Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY_BOSS);
							CollisionAttackBoss(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 20.0f)
								, g_Boss.Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY_BOSS);
							CollisionAttackBoss(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43 - 10.0f)
								, g_Boss.Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY_BOSS);
							CollisionAttackBoss(D3DXVECTOR3(g_Boss.Collision.mtxWorldCollision._41, g_Boss.Collision.mtxWorldCollision._42, g_Boss.Collision.mtxWorldCollision._43)
								, g_Boss.Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY_BOSS);

							//CollisionAttackEnemy(D3DXVECTOR3(g_Enemy[nCntEnemy].Collision.mtxWorldCollision._41, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._42, g_Enemy[nCntEnemy].Collision.mtxWorldCollision._43)
							//	, g_Enemy[nCntEnemy].Collision.fRadius
							//	, pPlayer->nIdxSencer
							//	, SENCERCOLTYPE_ENEMY);
						}
					}
				}
				g_Boss.rot.y = fAngle;

			g_Boss.pos += g_Boss.move;

			g_Boss.move.y -= GRAVITY_E;
			if (g_Boss.move.y > GRAVITY_E_MAX)
			{
				g_Boss.move.y = GRAVITY_E_MAX;
			}
			if (g_Boss.pos.y <= 0.0)
			{

				g_Boss.pos.y = 0.0f;
				g_Boss.move.y = 0.0f;

			}



			SetPositionSencerCollision(g_Boss.nIndexSencer, g_Boss.pos);//�Z���T�[�̈ʒu
			SetPositionShadow(g_Boss.nIndexShadow, g_Boss.pos);
			SetPositionSencerEnemy(g_Boss.nIndexSencerBoss,D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y, g_Boss.pos.z));
			SetPositionSencerEnableBoss(g_Boss.nIndexSencerEnableAttack, g_Boss.pos);
			CollisionSencer_Lock(&g_Boss.pos);




			switch (g_BossStatus)
			{
			case BOSSSTATUS_NEUTRAL:
				if (pBoss_Motion->KeyFlame == pBoss_Text->KEYFLAME[pBoss_Motion->nNumBossMotion] - 1)
				{
					if (g_BossStatusNow == BOSSSTATUS_NEUTRAL)
					{

						SetBossMotion(0);
					}
					else
					{
						pBoss_Motion->KeyFlame = 0;
						SetBossMotion(0);
						g_BossStatusNow = BOSSSTATUS_NEUTRAL;
						g_BossStatus = BOSSSTATUS_NEUTRAL;
					}
				}
				break;
			case BOSSSTATUS_MOVE:
				g_BossStatusNow = BOSSSTATUS_MOVE;
				g_BossStatus = BOSSSTATUS_NEUTRAL;
				SetBossMotion(1);
				break;
			case BOSSSTATUS_ATTACK:
				g_BossStatusNow = BOSSSTATUS_ATTACK;
				g_BossStatus = BOSSSTATUS_NEUTRAL;
				SetBossMotion(2);
				break;
			case BOSSSTATUS_JUMP:
				g_BossStatusNow = BOSSSTATUS_JUMP;
				g_BossStatus = BOSSSTATUS_NEUTRAL;
				SetBossMotion(3);
				break;
			case BOSSSTATUS_LANDING:
				g_BossStatusNow = BOSSSTATUS_LANDING;
				g_BossStatus = BOSSSTATUS_NEUTRAL;
				SetBossMotion(4);
				break;
			case BOSSSTATUS_GUARD:
				g_BossStatusNow = BOSSSTATUS_GUARD;
				g_BossStatus = BOSSSTATUS_NEUTRAL;
				SetBossMotion(5);
				break;
			case BOSSSTATUS_DAMAGE1:
				g_BossStatusNow = BOSSSTATUS_DAMAGE1;
				g_BossStatus = BOSSSTATUS_NEUTRAL;
				SetBossMotion(6);
				break;

			}//switch
			

			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Ene(&g_Boss.pos, &g_Boss.posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Ene(&g_Boss.pos, &g_Boss.posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Ene(&g_Boss.pos, &g_Boss.posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Ene(&g_Boss.pos, &g_Boss.posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWall2_WIDTHBack_Ene(&g_Boss.pos, &g_Boss.posold);

				//��O�ǂ̂����蔻��
				CollisionWall2_WIDTHThisSide_Ene(&g_Boss.pos, &g_Boss.posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_RIGHT_Ene(&g_Boss.pos, &g_Boss.posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_LEFT_Ene(&g_Boss.pos, &g_Boss.posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_Boss.pos, &g_Boss.posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_Boss.pos, &g_Boss.posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_Boss.pos, &g_Boss.posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_Boss.pos, &g_Boss.posold);
			}
		}//buse
#endif

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
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
	//�{�X�̃C���f�b�N�X//
	//========================//
	
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Boss.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot,
			g_Boss.rot.y, g_Boss.rot.x, g_Boss.rot.z);

		D3DXMatrixMultiply(&g_Boss.mtxWorld, &g_Boss.mtxWorld, &mtxrot);


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans,
			g_Boss.pos.x, g_Boss.pos.y, g_Boss.pos.z);
		D3DXMatrixMultiply(&g_Boss.mtxWorld, &g_Boss.mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Boss.mtxWorld);


		for (int nCntModelParts = 0; nCntModelParts < MAX_BOSS_PARTS; nCntModelParts++)
		{
			if (g_Boss.bUse == true)
			{

				if (g_Boss.aModel[nCntModelParts].nIdxModelParent == -1)
				{//�{�X�̃}�g���b�N�X��
					mtxParent = g_Boss.mtxWorld;
				}
				else if (g_Boss.aModel[nCntModelParts].nIdxModelParent == 0)
				{//�̂̃}�g���b�N�X��
					mtxParent = g_Boss.aModel[0].mtxWorld;
				}
				else if (g_Boss.aModel[nCntModelParts].nIdxModelParent == 1)
				{//���P��
					mtxParent = g_Boss.aModel[1].mtxWorld;
				}
				else if (g_Boss.aModel[nCntModelParts].nIdxModelParent == 2)
				{//���Q��
					mtxParent = g_Boss.aModel[2].mtxWorld;
				}
				else if (g_Boss.aModel[nCntModelParts].nIdxModelParent == 5)
				{//���Q��
					mtxParent = g_Boss.aModel[5].mtxWorld;
				}
				else if (g_Boss.aModel[nCntModelParts].nIdxModelParent == 8)
				{//���Q��
					mtxParent = g_Boss.aModel[8].mtxWorld;
				}
				else
				{//���̑�
					mtxParent = g_Boss.aModel[nCntModelParts - 1].mtxWorld;
				}
				//=======================================================================//
				//						    �e���f���̃C���f�b�N�X						//
				//=====================================================================//
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Boss.aModel[nCntModelParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxrot,
					g_Boss.aModel[nCntModelParts].rot.y, g_Boss.aModel[nCntModelParts].rot.x, g_Boss.aModel[nCntModelParts].rot.z);
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModelParts].mtxWorld, &g_Boss.aModel[nCntModelParts].mtxWorld, &mtxrot);


				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxtrans,
					g_Boss.aModel[nCntModelParts].pos.x, g_Boss.aModel[nCntModelParts].pos.y, g_Boss.aModel[nCntModelParts].pos.z);
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModelParts].mtxWorld, &g_Boss.aModel[nCntModelParts].mtxWorld, &mtxtrans);

				//�e�̃}�g���b�N�X���f
				D3DXMatrixMultiply(&g_Boss.aModel[nCntModelParts].mtxWorld, &g_Boss.aModel[nCntModelParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Boss.aModel[nCntModelParts].mtxWorld);


				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Boss.aModel[nCntModelParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_Boss.aModel[nCntModelParts].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//pDevice->SetTexture(0, g_Boss.aModel[0].pBossTexture);
					pDevice->SetTexture(0, 0);
					// ���f��(�p�[�c)�̕`��
					g_Boss.aModel[nCntModelParts].pMesh->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}

		/////////////////
		//�����蔻��p//
		///////////////
		
		if (g_Boss.Collision.nIdxParent == 0)
		{// �̂̎��A�{�X�̃}�g���b�N�X�ɓ����
			mtxParent = g_Boss.aModel[15].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Boss.Collision.mtxWorldCollision);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot, g_Boss.Collision.rot.y, g_Boss.Collision.rot.x, g_Boss.Collision.rot.z);
		D3DXMatrixMultiply(&g_Boss.Collision.mtxWorldCollision, &g_Boss.Collision.mtxWorldCollision, &mtxrot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans, g_Boss.Collision.pos.x, g_Boss.Collision.pos.y, g_Boss.Collision.pos.z);
		D3DXMatrixMultiply(&g_Boss.Collision.mtxWorldCollision, &g_Boss.Collision.mtxWorldCollision, &mtxtrans);

		//�e�̃}�g���b�N�X���f
		D3DXMatrixMultiply(&g_Boss.Collision.mtxWorldCollision, &g_Boss.Collision.mtxWorldCollision, &mtxParent);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Boss.Collision.mtxWorldCollision);

	}

//=============================================================================
// �q�b�g����
//=============================================================================
void HitBoss(int nDamage)
{
	D3DXVECTOR3 VecP;
	
	PLAYER *pPlayer;

	

	//�{�X�̎擾
	pPlayer = GetPlayer();

	if (g_Boss.bUse == true)
	{
		g_Boss.nLife += nDamage;

		VecP.x = g_Boss.pos.x - pPlayer->pos.x;
		VecP.y = g_Boss.pos.y - pPlayer->pos.y;
		VecP.z = g_Boss.pos.z - pPlayer->pos.z * -1;


		D3DXVec3Normalize(&VecP, &VecP);
		//g_Boss.pos += VecP * 80.0f;

		

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			SetParticle(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 30.0f, g_Boss.pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f), PARTICLETYPE_EXPLOSION);
		}
		if (g_Boss.nLife <= 0)
		{
			DecreaseBrazen(-30);
			g_Boss.bUse = false;
			DeletShadow(g_Boss.nIndexShadow);
			DeleteSencerCol(g_Boss.nIndexSencer);
			DeleteSencerEnemy(g_Boss.nIndexSencerBoss);
			DeleteSencerEnableBoss(g_Boss.nIndexSencerEnableAttack);

			int pBrazen;
			pBrazen = GetBrazen();

			if (pBrazen >= 75)
			{
				SetGameState(GAMESTATE_CLEAR_75);
			}
			if (pBrazen >= 50 && pBrazen <= 74)
			{
				SetGameState(GAMESTATE_CLEAR_50);
			}
			if (pBrazen >= 1 && pBrazen <= 49)
			{
				SetGameState(GAMESTATE_CLEAR_50);
			}
			if (pBrazen <= 0)
			{
				SetGameState(GAMESTATE_CLEAR_TRUE);
			}
		}

	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CollisionBoss(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosold, D3DXVECTOR3 * VtxMax, D3DXVECTOR3 * VtxMin)
{
	bool bCollision = false; //���n������

	
		if (g_Boss.bUse == true)
		{
			if (pPos->x + VtxMax->z >= g_Boss.VtxMinBoss.x + g_Boss.pos.x && pPos->x - VtxMax->z <= g_Boss.VtxMaxBoss.x + g_Boss.pos.x
				&&pPos->y + VtxMax->y >= g_Boss.VtxMinBoss.y + g_Boss.pos.y && pPos->y - VtxMax->y <= g_Boss.VtxMaxBoss.y + g_Boss.pos.y
				&&pPos->z + VtxMax->z >= g_Boss.VtxMinBoss.z + g_Boss.pos.z && pPos->z - VtxMax->z <= g_Boss.VtxMaxBoss.z + g_Boss.pos.z)
			{
				if (pPosold->x + VtxMax->z <= g_Boss.VtxMinBoss.x + g_Boss.pos.x  && pPos->x + VtxMax->z >= g_Boss.VtxMinBoss.x + g_Boss.pos.x)
				{//�����炫���Ƃ�
					pPos->x = g_Boss.VtxMinBoss.x + g_Boss.pos.x - VtxMax->z;
					bCollision = true;
				}

				else if (pPosold->x - VtxMax->z >= g_Boss.VtxMaxBoss.x + g_Boss.pos.x  && pPos->x - VtxMax->z <= g_Boss.VtxMaxBoss.x + g_Boss.pos.x)
				{//�E���炫���Ƃ�
					pPos->x = g_Boss.VtxMaxBoss.x + g_Boss.pos.x + VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z + VtxMax->z <= g_Boss.VtxMinBoss.z + g_Boss.pos.z && pPos->z + VtxMax->z >= g_Boss.VtxMinBoss.z + g_Boss.pos.z)
				{//��O���痈����
					pPos->z = g_Boss.VtxMinBoss.z + g_Boss.pos.z - VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z - VtxMax->z >= g_Boss.VtxMaxBoss.z + g_Boss.pos.z && pPos->z - VtxMax->z <= g_Boss.VtxMaxBoss.z + g_Boss.pos.z)
				{//�����痈����
					pPos->z = g_Boss.VtxMaxBoss.z + g_Boss.pos.z + VtxMax->z;
					bCollision = true;

				}

				if (pPosold->y + VtxMax->y <= g_Boss.VtxMinBoss.y + g_Boss.pos.y && pPos->y + VtxMax->y >= g_Boss.VtxMinBoss.y + g_Boss.pos.y)
				{//�ォ�痈����
					pPos->y = g_Boss.VtxMinBoss.y + g_Boss.pos.y + VtxMin->y;
					bCollision = true;

				}
				if (pPosold->y - VtxMax->y >= g_Boss.VtxMaxBoss.y + g_Boss.pos.y && pPos->y - VtxMax->y <= g_Boss.VtxMaxBoss.y + g_Boss.pos.y)
				{//�����痈����
					pPos->y = g_Boss.VtxMaxBoss.y + g_Boss.pos.y + VtxMax->y;
					bCollision = true;

				}
			}

		}
	
	return bCollision;
}

//////////////////////////////////////////////////////////////////////////
//////				�G�̐ݒu								  ////////////
//////////////////////////////////////////////////////////////////////////
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
		if (g_Boss.bUse == false)
		{
			g_Boss.pos = pos;
			g_Boss.rot = rot;
			g_Boss.nLife = nLife;
			g_Boss.nIndexSencer = SetSencerCollision(g_Boss.pos, g_Boss.rot, SENCERCOLTYPE_ENEMY_BOSS);
			g_Boss.nIndexSencerBoss = SetSencerEnemy(g_Boss.pos, g_Boss.rot);
			g_Boss.nIndexSencerEnableAttack = SetSencerEnableBoss(g_Boss.pos, g_Boss.rot);
			g_Boss.nIndexShadow = SetShadow(g_Boss.pos, g_Boss.rot);
			g_Boss.bUse = true;
		}
	
}

//------------------------------------------------------------------------
// �G�l�~�[�̏�Ԃ̐ݒ�												      |
//------------------------------------------------------------------------
void SetBossStatus(BOSSSTATUS status)
{
	g_BossStatus = status;
}

////////////////////////////////////////////////////////////
//				�G�̏���								  //
////////////////////////////////////////////////////////////
void DeleteBoss(int nCntEnemy)
{
	g_Boss.bUse = false;
	DeletShadow(g_Boss.nIndexShadow);
	DeleteSencerCol(g_Boss.nIndexSencer);
	DeleteSencerEnemy(g_Boss.nIndexSencerBoss);
	DeleteSencerEnableBoss(g_Boss.nIndexSencerEnableAttack);

}

////////////////////////////////////////////////////////////
//				�G�̎擾								  //
////////////////////////////////////////////////////////////
BOSS *GetBoss(void)
{
	return &g_Boss;
}
///////////////////////////////////////////////////////////
//				�G��Ԃ̎擾							//
//////////////////////////////////////////////////////////
BOSSSTATUS *GetBossStatus(void)
{
	return &g_Boss.status;
}


