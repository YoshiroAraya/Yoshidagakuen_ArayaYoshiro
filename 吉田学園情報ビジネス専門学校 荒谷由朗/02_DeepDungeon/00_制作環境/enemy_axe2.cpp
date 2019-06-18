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
#include "sound.h"
#include "enemy_axe2.h"
#include "enemy_axe_text2.h"
#include "enemy_axe_motion2.h"
#include "SencerCol.h"
#include "SencerLock.h"
#include "SencerEnemy.h"
#include "SencerAtk.h"
#include "SencerEnableAttack.h"
#include "Wall1.h"
#include "Wall2.h"
#include "WallBoss.h"
#include <math.h>
#include "brazen.h"
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

ENEMYAXE2 g_EnemyAxe2[MAX_ENEMYAXE];
ENEMYAXESTATUS2 g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
ENEMYAXESTATUS2 g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_NEUTRAL;

//STAGE g_aLimit[4];
//�e�L�X�g���擾

float fJump_Axe2;	//�W�����v��
float fGRAVITY_Axe2;	//�d��

int g_nCntSound_Axe2 = 0;
int g_nCntEnemyAxeAxe2;

bool bLand_Axe2; //���n����
//=============================================================================
// ����������
//=============================================================================
void InitEnemyAxe2(void)
{


	EnemyAxeTex2 *pEnemyAxeText2;
	pEnemyAxeText2 = GetEnemyAxeTex2();
	g_nCntEnemyAxeAxe2 = 3;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		for (int nCntIdx = 0; nCntIdx < pEnemyAxeText2->MAX_PARTS; nCntIdx++)
		{//�e��l�̑��
		 //�ǂݍ��ރ��f����
			g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].FileName[0] = pEnemyAxeText2->aModelTex[nCntIdx].FileName[0];

			//�e�q�֌W
			g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].nIdxModelParent = pEnemyAxeText2->aModelTex[nCntIdx].Index;

			//�ʒu
			g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].pos = D3DXVECTOR3(pEnemyAxeText2->aModelTex[nCntIdx].PosX, pEnemyAxeText2->aModelTex[nCntIdx].PosY, pEnemyAxeText2->aModelTex[nCntIdx].PosZ);

			//��]
			g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].rot = D3DXVECTOR3(pEnemyAxeText2->aModelTex[nCntIdx].RotX,
				pEnemyAxeText2->aModelTex[nCntIdx].RotY,
				pEnemyAxeText2->aModelTex[nCntIdx].RotZ);

			//���f���̐ݒ�
			D3DXLoadMeshFromX(&pEnemyAxeText2->aModelTex[nCntIdx].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].pBuffMat,
				NULL,
				&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].nNumMat,
				&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntIdx].pMesh);
		}
		g_EnemyAxe2[nCntEnemyAxe].Collision.bUse = false;
		g_EnemyAxe2[nCntEnemyAxe].Collision.nCntMotion = 0;
		g_EnemyAxe2[nCntEnemyAxe].Collision.StartFlame = 5;
		g_EnemyAxe2[nCntEnemyAxe].Collision.fRadius = 40.0f;
		g_EnemyAxe2[nCntEnemyAxe].Collision.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
		g_EnemyAxe2[nCntEnemyAxe].Collision.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyAxe2[nCntEnemyAxe].Collision.nIdxParent = 0;
		g_EnemyAxe2[nCntEnemyAxe].nCntCoolDown = 120;

		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 30.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 20.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 10.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43));


		//�W�����v�̏��
		g_EnemyAxe2[nCntEnemyAxe].bUseJump = false;
		//�v���C���[�̏��
		g_EnemyAxe2[nCntEnemyAxe].nCoolDown = 0;

		//���n���Ă��邩
		bLand_Axe2 = false;

		//�v���C���[���g�p����Ă��邩
		g_EnemyAxe2[nCntEnemyAxe].bUse = false;

	}









	fJump_Axe2 = JUMP_POWER;
	fGRAVITY_Axe2 = GRAVITY_E;


	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		//���_�����擾
		nNumVtx = g_EnemyAxe2[nCntEnemyAxe].aModel[0].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyAxe2[nCntEnemyAxe].aModel[0].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_EnemyAxe2[nCntEnemyAxe].aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W

			if (Vtx.x < g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.x)
			{
				g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.y)
			{
				g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z < g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.z)
			{
				g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.z = Vtx.x;
			}


			if (Vtx.x > g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.x)
			{
				g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.x = Vtx.x + 20.0f;
			}

			if (Vtx.y > g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.y)
			{
				g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.y = Vtx.y + 30.0f;
			}

			if (Vtx.z > g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.z)
			{
				g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.z = Vtx.z + 20.0f;
			}
			pVtxBuff += sizeFVF;
		}

		g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.x = g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.x;
		g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.x = g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.x;

		g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.y = g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.y;
		g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.y = g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.y;

		g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.z = g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMinModel.z;
		g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.z = g_EnemyAxe2[nCntEnemyAxe].aModel[0].VtxMaxModel.z;

		g_EnemyAxe2[nCntEnemyAxe].fAngle = 0.0f;			//����

	}

	CAMERA *pCamera;
	pCamera = GetCamera();


}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyAxe2(void)
{


	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		// ���b�V���̊J��
		if (g_EnemyAxe2[nCntEnemyAxe].aModel[0].pMesh != NULL)
		{
			g_EnemyAxe2[nCntEnemyAxe].aModel[0].pMesh->Release();
			g_EnemyAxe2[nCntEnemyAxe].aModel[0].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_EnemyAxe2[nCntEnemyAxe].aModel[0].pBuffMat != NULL)
		{
			g_EnemyAxe2[nCntEnemyAxe].aModel[0].pBuffMat->Release();
			g_EnemyAxe2[nCntEnemyAxe].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyAxe2(void)
{

	EnemyAxeMotion2 *pAxe_Motion = GetEnemyAxeMotion2();					//���[�V�����f�[�^�̏���
	EnemyAxeTex2 *pAxe_Text = GetEnemyAxeTex2();							//�t�@�C���f�[�^�̎擾

	EnemyAxeTex2 *pEnemyAxeText2;
	pEnemyAxeText2 = GetEnemyAxeTex2();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾


#if 1




													//nCntUpdateRogic++;
	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{




		g_EnemyAxe2[nCntEnemyAxe].nCntCoolDown++;
		g_EnemyAxe2[nCntEnemyAxe].posold = g_EnemyAxe2[nCntEnemyAxe].pos;

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


		VecP.x = (pPlayer->pos.x - g_EnemyAxe2[nCntEnemyAxe].pos.x);
		VecP.y = pPlayer->pos.y - g_EnemyAxe2[nCntEnemyAxe].pos.y;
		VecP.z = (pPlayer->pos.z - g_EnemyAxe2[nCntEnemyAxe].pos.z) + 45.0f;
		D3DXVec3Normalize(&VecP, &VecP);

		VecLength = pPlayer->pos - g_EnemyAxe2[nCntEnemyAxe].pos;









		if (g_EnemyAxe2[nCntEnemyAxe].bUse == true)
		{
			switch (g_EnemyAxe2[nCntEnemyAxe].state22)
			{
			case ENEMYAXESTATE22_NORMAL:
				break;

			case ENEMYAXESTATE22_DAMAGE:
				g_EnemyAxe2[nCntEnemyAxe].nCntCoolDown--;
				if (g_EnemyAxe2[nCntEnemyAxe].nCntCoolDown <= 0)
				{
					g_EnemyAxe2[nCntEnemyAxe].state22 = ENEMYAXESTATE22_NORMAL;
				}
			}



			static float fAngle;
			//fAngle = atan2f(pPlayer->pos.x - g_EnemyAxe2[nCntEnemyAxe].pos.x, pPlayer->pos.z - g_EnemyAxe2[nCntEnemyAxe].pos.z);
			fAngle = atan2f(g_EnemyAxe2[nCntEnemyAxe].pos.x - pPlayer->pos.x, g_EnemyAxe2[nCntEnemyAxe].pos.z - pPlayer->pos.z);

			g_EnemyAxe2[nCntEnemyAxe].fLength = sqrtf((pPlayer->pos.x - g_EnemyAxe2[nCntEnemyAxe].pos.x) * (pPlayer->pos.x - g_EnemyAxe2[nCntEnemyAxe].pos.x) + (pPlayer->pos.z - g_EnemyAxe2[nCntEnemyAxe].pos.z) *(pPlayer->pos.z - g_EnemyAxe2[nCntEnemyAxe].pos.z));//����


			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}

			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}




			switch (g_EnemyAxe2[nCntEnemyAxe].state)
			{
			case ENEMYAXESTATE21_NONE:

				if (CollisionSencer_Enemy(&pPlayer->pos, g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnemy) == true)
				{
					g_EnemyAxe2[nCntEnemyAxe].state = ENEMYAXESTATE21_DISCOVERY;
				}
				else
				{
					g_EnemyAxe2[nCntEnemyAxe].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				break;

			case ENEMYAXESTATE21_BACKHOME:

				g_EnemyAxe2[nCntEnemyAxe].DestHome = atan2f(g_EnemyAxe2[nCntEnemyAxe].HomePoint.x - g_EnemyAxe2[nCntEnemyAxe].pos.x,
					g_EnemyAxe2[nCntEnemyAxe].HomePoint.z - g_EnemyAxe2[nCntEnemyAxe].pos.z);

				g_EnemyAxe2[nCntEnemyAxe].move.x = g_EnemyAxe2[nCntEnemyAxe].DestHome * 1.2f;
				g_EnemyAxe2[nCntEnemyAxe].move.z = g_EnemyAxe2[nCntEnemyAxe].DestHome * 1.2f;

				if (g_EnemyAxe2[nCntEnemyAxe].pos.x <= g_EnemyAxe2[nCntEnemyAxe].HomePoint.x + 50.0f || g_EnemyAxe2[nCntEnemyAxe].pos.x >= g_EnemyAxe2[nCntEnemyAxe].HomePoint.x - 50.0f
					|| g_EnemyAxe2[nCntEnemyAxe].pos.z <= g_EnemyAxe2[nCntEnemyAxe].HomePoint.z + 50.0f || g_EnemyAxe2[nCntEnemyAxe].pos.z >= g_EnemyAxe2[nCntEnemyAxe].HomePoint.z - 50.0f)
				{
					g_EnemyAxe2[nCntEnemyAxe].state = ENEMYAXESTATE21_NONE;
				}

				break;
			case ENEMYAXESTATE21_DISCOVERY:
				g_EnemyAxe2[nCntEnemyAxe].move.x = VecP.x * 1.4f;
				g_EnemyAxe2[nCntEnemyAxe].move.z = VecP.z * 1.4f;
				fAngle = atan2f(g_EnemyAxe2[nCntEnemyAxe].pos.x - pPlayer->pos.x, g_EnemyAxe2[nCntEnemyAxe].pos.z - pPlayer->pos.z);
				if (fAngle > D3DX_PI)
				{
					fAngle -= D3DX_PI * 2;
				}

				if (fAngle < -D3DX_PI)
				{
					fAngle += D3DX_PI * 2;
				}
				if (CollisionSencer_Enemy(&pPlayer->pos, g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnemy) == false)
				{
					g_EnemyAxe2[nCntEnemyAxe].state = ENEMYAXESTATE21_BACKHOME;
				}
				if (g_EnemyAxe2StatusNow == ENEMYAXESTATUS2_NEUTRAL)
				{//���[���ւ̈ڍs
					SetEnemyAxeStatus2(ENEMYAXESTATUS2_MOVE, nCntEnemyAxe);
				}
				if (CollisionSencer_Enable(&pPlayer->pos) == true)
				{
					if (g_EnemyAxe2StatusNow == ENEMYAXESTATUS2_NEUTRAL || g_EnemyAxe2StatusNow == ENEMYAXESTATUS2_MOVE)
					{//���[���ւ̈ڍs
						pAxe_Motion->nCntFlame = 0;
						if (g_EnemyAxe2[nCntEnemyAxe].nCntCoolDown % 30 == 0)
						{
							SetEnemyAxeStatus2(ENEMYAXESTATUS2_ATTACK, nCntEnemyAxe);
						}
					}

					else if (g_EnemyAxe2StatusNow == ENEMYAXESTATUS2_ATTACK)
					{
						if (pAxe_Motion->nCntFlame % g_EnemyAxe2[nCntEnemyAxe].Collision.StartFlame == 0)
						{
							PlaySound(SOUND_LABEL_SE_SLASH);
						}
						if (pAxe_Motion->nCntFlame > g_EnemyAxe2[nCntEnemyAxe].Collision.StartFlame)
						{
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 30.0f)
								, g_EnemyAxe2[nCntEnemyAxe].Collision.fRadius
								, g_EnemyAxe2[nCntEnemyAxe].nIndexSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 20.0f)
								, g_EnemyAxe2[nCntEnemyAxe].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 10.0f)
								, g_EnemyAxe2[nCntEnemyAxe].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision._43)
								, g_EnemyAxe2[nCntEnemyAxe].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
						}
					}
					g_EnemyAxe2[nCntEnemyAxe].rot.y = fAngle;
				}
				break;
			}//switch��

			g_EnemyAxe2[nCntEnemyAxe].rot.y = fAngle;

#if 1

#endif			

			g_EnemyAxe2[nCntEnemyAxe].pos += g_EnemyAxe2[nCntEnemyAxe].move;

			g_EnemyAxe2[nCntEnemyAxe].move.y -= GRAVITY_E;
			if (g_EnemyAxe2[nCntEnemyAxe].move.y > GRAVITY_E_MAX)
			{
				g_EnemyAxe2[nCntEnemyAxe].move.y = GRAVITY_E_MAX;
			}
			if (g_EnemyAxe2[nCntEnemyAxe].pos.y <= 0.0)
			{

				g_EnemyAxe2[nCntEnemyAxe].pos.y = 0.0f;
				g_EnemyAxe2[nCntEnemyAxe].move.y = 0.0f;

			}



#endif
			SetPositionSencerCollision(g_EnemyAxe2[nCntEnemyAxe].nIndexSencer, g_EnemyAxe2[nCntEnemyAxe].pos);//�Z���T�[�̈ʒu
			SetPositionShadow(g_EnemyAxe2[nCntEnemyAxe].nIndexShadow, g_EnemyAxe2[nCntEnemyAxe].pos);
			SetPositionSencerEnemy(g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnemy,
				D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].pos.x, g_EnemyAxe2[nCntEnemyAxe].pos.y, g_EnemyAxe2[nCntEnemyAxe].pos.z));
			SetPositionSencerEnableAttack(g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnableAttack, g_EnemyAxe2[nCntEnemyAxe].pos);
			CollisionSencer_Lock(&g_EnemyAxe2[nCntEnemyAxe].pos);
			//g_EnemyAxe2[nCntEnemyAxe].rot.y += 0.01f;




			switch (g_EnemyAxe2Status)
			{
			case ENEMYAXESTATUS2_NEUTRAL:
				if (pAxe_Motion->KeyFlame == pAxe_Text->KEYFLAME[pAxe_Motion->nNumEnemyAxeMotion] - 1)
				{
					if (g_EnemyAxe2StatusNow == ENEMYAXESTATUS2_NEUTRAL)
					{

						SetEnemyAxeMotion2(0);
					}
					else
					{
						pAxe_Motion->KeyFlame = 0;
						SetEnemyAxeMotion2(0);
						g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_NEUTRAL;
						g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
					}
				}
				break;
			case ENEMYAXESTATUS2_MOVE:
				g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_MOVE;
				g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
				SetEnemyAxeMotion2(1);
				break;
			case ENEMYAXESTATUS2_ATTACK:
				g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_ATTACK;
				g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
				SetEnemyAxeMotion2(2);
				break;
			case ENEMYAXESTATUS2_JUMP:
				g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_JUMP;
				g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
				SetEnemyAxeMotion2(3);
				break;
			case ENEMYAXESTATUS2_LANDING:
				g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_LANDING;
				g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
				SetEnemyAxeMotion2(4);
				break;
			case ENEMYAXESTATUS2_GUARD:
				g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_GUARD;
				g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
				SetEnemyAxeMotion2(5);
				break;
			case ENEMYAXESTATUS2_DAMAGE1:
				g_EnemyAxe2StatusNow = ENEMYAXESTATUS2_DAMAGE1;
				g_EnemyAxe2Status = ENEMYAXESTATUS2_NEUTRAL;
				SetEnemyAxeMotion2(6);
				break;

			}//switch
			 //if

			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWall2_WIDTHBack_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//��O�ǂ̂����蔻��
				CollisionWall2_WIDTHThisSide_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_RIGHT_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_LEFT_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_EnemyAxe2[nCntEnemyAxe].pos, &g_EnemyAxe2[nCntEnemyAxe].posold);
			}
		}//buse

	}//for
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyAxe2(void)
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
	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EnemyAxe2[nCntEnemyAxe].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot,
			g_EnemyAxe2[nCntEnemyAxe].rot.y, g_EnemyAxe2[nCntEnemyAxe].rot.x, g_EnemyAxe2[nCntEnemyAxe].rot.z);

		D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].mtxWorld, &g_EnemyAxe2[nCntEnemyAxe].mtxWorld, &mtxrot);


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans,
			g_EnemyAxe2[nCntEnemyAxe].pos.x, g_EnemyAxe2[nCntEnemyAxe].pos.y, g_EnemyAxe2[nCntEnemyAxe].pos.z);
		D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].mtxWorld, &g_EnemyAxe2[nCntEnemyAxe].mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyAxe2[nCntEnemyAxe].mtxWorld);


		for (int nCntModelParts = 0; nCntModelParts < MAX_AXE_PARTS; nCntModelParts++)
		{
			if (g_EnemyAxe2[nCntEnemyAxe].bUse == true)
			{

				if (g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == -1)
				{//�v���C���[�̃}�g���b�N�X��
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].mtxWorld;
				}
				else if (g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 0)
				{//�̂̃}�g���b�N�X��
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[0].mtxWorld;
				}
				else if (g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 1)
				{//���P��
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[1].mtxWorld;
				}
				else if (g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 2)
				{//���Q��
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[2].mtxWorld;
				}
				else if (g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 5)
				{//���Q��
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[5].mtxWorld;
				}
				else if (g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 8)
				{//���Q��
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[8].mtxWorld;
				}
				else
				{//���̑�
					mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts - 1].mtxWorld;
				}
				//=======================================================================//
				//						    �e���f���̃C���f�b�N�X						//
				//=====================================================================//
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxrot,
					g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].rot.y, g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].rot.x, g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].rot.z);
				D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &mtxrot);


				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxtrans,
					g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].pos.x, g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].pos.y, g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].pos.z);
				D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &mtxtrans);

				//�e�̃}�g���b�N�X���f
				D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld);


				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//pDevice->SetTexture(0, g_EnemyAxe2[nCntEnemyAxe].aModel[0].pEnemyAxeText2ure);
					pDevice->SetTexture(0, 0);
					// ���f��(�p�[�c)�̕`��
					g_EnemyAxe2[nCntEnemyAxe].aModel[nCntModelParts].pMesh->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}

		/////////////////
		//�����蔻��p//
		///////////////
		if (g_EnemyAxe2[nCntEnemyAxe].Collision.nIdxParent == -1)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[16].mtxWorld;
		}
		if (g_EnemyAxe2[nCntEnemyAxe].Collision.nIdxParent == 0)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_EnemyAxe2[nCntEnemyAxe].aModel[15].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot, g_EnemyAxe2[nCntEnemyAxe].Collision.rot.y, g_EnemyAxe2[nCntEnemyAxe].Collision.rot.x, g_EnemyAxe2[nCntEnemyAxe].Collision.rot.z);
		D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision, &g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision, &mtxrot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans, g_EnemyAxe2[nCntEnemyAxe].Collision.pos.x, g_EnemyAxe2[nCntEnemyAxe].Collision.pos.y, g_EnemyAxe2[nCntEnemyAxe].Collision.pos.z);
		D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision, &g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision, &mtxtrans);

		//�e�̃}�g���b�N�X���f
		D3DXMatrixMultiply(&g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision, &g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision, &mtxParent);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyAxe2[nCntEnemyAxe].Collision.mtxWorldCollision);
	}
}
//=============================================================================
// �q�b�g����
//=============================================================================
void HitEnemyAxe2(int nDamage, int nCntEnemyAxe)
{
	D3DXVECTOR3 VecP;

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	if (g_EnemyAxe2[nCntEnemyAxe].bUse == true)
	{
		g_EnemyAxe2[nCntEnemyAxe].nLife += nDamage;

		VecP.x = g_EnemyAxe2[nCntEnemyAxe].pos.x - pPlayer->pos.x;
		VecP.y = g_EnemyAxe2[nCntEnemyAxe].pos.y - pPlayer->pos.y;
		VecP.z = g_EnemyAxe2[nCntEnemyAxe].pos.z - pPlayer->pos.z * -1;


		D3DXVec3Normalize(&VecP, &VecP);
		//g_EnemyAxe2[nCntEnemyAxe].pos += VecP * 80.0f;

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			SetParticle(D3DXVECTOR3(g_EnemyAxe2[nCntEnemyAxe].pos.x, g_EnemyAxe2[nCntEnemyAxe].pos.y + 30.0f, g_EnemyAxe2[nCntEnemyAxe].pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f), PARTICLETYPE_EXPLOSION);
		}
		if (g_EnemyAxe2[nCntEnemyAxe].nLife <= 0)
		{

			g_EnemyAxe2[nCntEnemyAxe].bUse = false;
			DeletShadow(g_EnemyAxe2[nCntEnemyAxe].nIndexShadow);
			DeleteSencerCol(g_EnemyAxe2[nCntEnemyAxe].nIndexSencer);
			DeleteSencerEnemy(g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnemy);
			DeleteSencerEnableAttack(g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnableAttack);
			DecreaseBrazen(-2);

		}

	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CollisionEnemyAxe2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosold, D3DXVECTOR3 * VtxMax, D3DXVECTOR3 * VtxMin)
{
	bool bCollision = false; //���n������

	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		if (g_EnemyAxe2[nCntEnemyAxe].bUse == true)
		{
			if (pPos->x + VtxMax->z >= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x && pPos->x - VtxMax->z <= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x
				&&pPos->y + VtxMax->y >= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y && pPos->y - VtxMax->y <= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y
				&&pPos->z + VtxMax->z >= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z && pPos->z - VtxMax->z <= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z)
			{
				if (pPosold->x + VtxMax->z <= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x  && pPos->x + VtxMax->z >= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x)
				{//�����炫���Ƃ�
					pPos->x = g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x - VtxMax->z;
					bCollision = true;
				}

				else if (pPosold->x - VtxMax->z >= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x  && pPos->x - VtxMax->z <= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x)
				{//�E���炫���Ƃ�
					pPos->x = g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe2[nCntEnemyAxe].pos.x + VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z + VtxMax->z <= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z && pPos->z + VtxMax->z >= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z)
				{//��O���痈����
					pPos->z = g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z - VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z - VtxMax->z >= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z && pPos->z - VtxMax->z <= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z)
				{//�����痈����
					pPos->z = g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe2[nCntEnemyAxe].pos.z + VtxMax->z;
					bCollision = true;

				}

				if (pPosold->y + VtxMax->y <= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y && pPos->y + VtxMax->y >= g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y)
				{//�ォ�痈����
					pPos->y = g_EnemyAxe2[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y + VtxMin->y;
					bCollision = true;

				}
				if (pPosold->y - VtxMax->y >= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y && pPos->y - VtxMax->y <= g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y)
				{//�����痈����
					pPos->y = g_EnemyAxe2[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe2[nCntEnemyAxe].pos.y + VtxMax->y;
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
int SetEnemyAxe2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntEnemyAxe;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		if (g_EnemyAxe2[nCntEnemyAxe].bUse == false)
		{
			g_EnemyAxe2[nCntEnemyAxe].pos = pos;
			g_EnemyAxe2[nCntEnemyAxe].HomePoint = pos;
			g_EnemyAxe2[nCntEnemyAxe].rot = rot;
			g_EnemyAxe2[nCntEnemyAxe].nLife = nLife;
			g_EnemyAxe2[nCntEnemyAxe].nIndexSencer = SetSencerCollision(g_EnemyAxe2[nCntEnemyAxe].pos, g_EnemyAxe2[nCntEnemyAxe].rot, SENCERCOLTYPE_ENEMY_AXE2);
			g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnemy = SetSencerEnemy(g_EnemyAxe2[nCntEnemyAxe].pos, g_EnemyAxe2[nCntEnemyAxe].rot);
			g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnableAttack = SetSencerEnableAttack(g_EnemyAxe2[nCntEnemyAxe].pos, g_EnemyAxe2[nCntEnemyAxe].rot);
			g_EnemyAxe2[nCntEnemyAxe].nIndexShadow = SetShadow(g_EnemyAxe2[nCntEnemyAxe].pos, g_EnemyAxe2[nCntEnemyAxe].rot);
			g_EnemyAxe2[nCntEnemyAxe].state22 = ENEMYAXESTATE22_NORMAL;
			g_EnemyAxe2[nCntEnemyAxe].bUse = true;
			break;
		}
	}
	return nCntEnemyAxe;
}

//------------------------------------------------------------------------
// �G�l�~�[�̏�Ԃ̐ݒ�												      |
//------------------------------------------------------------------------
void SetEnemyAxeStatus2(ENEMYAXESTATUS2 status, int nCntEnemyAxe)
{
	g_EnemyAxe2Status = status;
}

////////////////////////////////////////////////////////////
//				�G�̏���								  //
////////////////////////////////////////////////////////////
void DeleteEnemyAxe2(int nCntEnemyAxe)
{
	g_EnemyAxe2[nCntEnemyAxe].bUse = false;
	DeletShadow(g_EnemyAxe2[nCntEnemyAxe].nIndexShadow);
	DeleteSencerCol(g_EnemyAxe2[nCntEnemyAxe].nIndexSencer);
	DeleteSencerEnemy(g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnemy);
	DeleteSencerEnableAttack(g_EnemyAxe2[nCntEnemyAxe].nIndexSencerEnableAttack);

}

////////////////////////////////////////////////////////////
//				�G�̎擾								  //
////////////////////////////////////////////////////////////
ENEMYAXE2 *GetEnemyAxe2(void)
{
	return &g_EnemyAxe2[0];
}
///////////////////////////////////////////////////////////
//				�G��Ԃ̎擾							//
//////////////////////////////////////////////////////////
ENEMYAXESTATUS2 *GetEnemyAxeStatus2(void)
{
	return &g_EnemyAxe2[0].status;
}


