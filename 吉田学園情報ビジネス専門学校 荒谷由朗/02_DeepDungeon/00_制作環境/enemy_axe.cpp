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
#include "enemy_axe.h"
#include "enemy_axe_text.h"
#include "enemy_axe_motion.h"
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

ENEMYAXE g_EnemyAxe[MAX_ENEMYAXE];
ENEMYAXESTATUS g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
ENEMYAXESTATUS g_EnemyAxeStatusNow = ENEMYAXESTATUS_NEUTRAL;

//STAGE g_aLimit[4];
//�e�L�X�g���擾

float fJump_Axe;	//�W�����v��
float fGRAVITY_Axe;	//�d��

int g_nCntSound_Axe = 0;
int g_nCntEnemyAxeAxe;

bool bLand_Axe; //���n����
//=============================================================================
// ����������
 //=============================================================================
void InitEnemyAxe(void)
{


	EnemyAxeTex *pEnemyAxeText;
	pEnemyAxeText = GetEnemyAxeTex();
	g_nCntEnemyAxeAxe = 3;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		for (int nCntIdx = 0; nCntIdx < pEnemyAxeText->MAX_PARTS; nCntIdx++)
		{//�e��l�̑��
		 //�ǂݍ��ރ��f����
			g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].FileName[0] = pEnemyAxeText->aModelTex[nCntIdx].FileName[0];

			//�e�q�֌W
			g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].nIdxModelParent = pEnemyAxeText->aModelTex[nCntIdx].Index;

			//�ʒu
			g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].pos = D3DXVECTOR3(pEnemyAxeText->aModelTex[nCntIdx].PosX, pEnemyAxeText->aModelTex[nCntIdx].PosY, pEnemyAxeText->aModelTex[nCntIdx].PosZ);

			//��]
			g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].rot = D3DXVECTOR3(pEnemyAxeText->aModelTex[nCntIdx].RotX,
				pEnemyAxeText->aModelTex[nCntIdx].RotY,
				pEnemyAxeText->aModelTex[nCntIdx].RotZ);

			//���f���̐ݒ�
			D3DXLoadMeshFromX(&pEnemyAxeText->aModelTex[nCntIdx].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].pBuffMat,
				NULL,
				&g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].nNumMat,
				&g_EnemyAxe[nCntEnemyAxe].aModel[nCntIdx].pMesh);
		}
		g_EnemyAxe[nCntEnemyAxe].Collision.bUse = false;
		g_EnemyAxe[nCntEnemyAxe].Collision.nCntMotion = 0;
		g_EnemyAxe[nCntEnemyAxe].Collision.StartFlame = 5;
		g_EnemyAxe[nCntEnemyAxe].Collision.fRadius = 40.0f;
		g_EnemyAxe[nCntEnemyAxe].Collision.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
		g_EnemyAxe[nCntEnemyAxe].Collision.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EnemyAxe[nCntEnemyAxe].Collision.nIdxParent = 0;
		g_EnemyAxe[nCntEnemyAxe].nCntCoolDown = 120;

		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 30.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 20.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 10.0f));
		SetSencerAtk(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43));


		//�W�����v�̏��
		g_EnemyAxe[nCntEnemyAxe].bUseJump = false;
		//�v���C���[�̏��
		g_EnemyAxe[nCntEnemyAxe].nCoolDown = 0;

		//���n���Ă��邩
		bLand_Axe = false;

		//�v���C���[���g�p����Ă��邩
		g_EnemyAxe[nCntEnemyAxe].bUse = false;

	}









	fJump_Axe = JUMP_POWER;
	fGRAVITY_Axe = GRAVITY_E;


	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		//���_�����擾
		nNumVtx = g_EnemyAxe[nCntEnemyAxe].aModel[0].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyAxe[nCntEnemyAxe].aModel[0].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_EnemyAxe[nCntEnemyAxe].aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W

			if (Vtx.x < g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.x)
			{
				g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.y)
			{
				g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z < g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.z)
			{
				g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.z = Vtx.x;
			}


			if (Vtx.x > g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.x)
			{
				g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.x = Vtx.x + 20.0f;
			}

			if (Vtx.y > g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.y)
			{
				g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.y = Vtx.y + 30.0f;
			}

			if (Vtx.z > g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.z)
			{
				g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.z = Vtx.z + 20.0f;
			}
			pVtxBuff += sizeFVF;
		}

		g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.x = g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.x;
		g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.x = g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.x;

		g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.y = g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.y;
		g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.y = g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.y;

		g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.z = g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMinModel.z;
		g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.z = g_EnemyAxe[nCntEnemyAxe].aModel[0].VtxMaxModel.z;

		g_EnemyAxe[nCntEnemyAxe].fAngle = 0.0f;			//����

	}

	CAMERA *pCamera;
	pCamera = GetCamera();


}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyAxe(void)
{


	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		// ���b�V���̊J��
		if (g_EnemyAxe[nCntEnemyAxe].aModel[0].pMesh != NULL)
		{
			g_EnemyAxe[nCntEnemyAxe].aModel[0].pMesh->Release();
			g_EnemyAxe[nCntEnemyAxe].aModel[0].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_EnemyAxe[nCntEnemyAxe].aModel[0].pBuffMat != NULL)
		{
			g_EnemyAxe[nCntEnemyAxe].aModel[0].pBuffMat->Release();
			g_EnemyAxe[nCntEnemyAxe].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyAxe(void)
{

	EnemyAxeMotion *pAxe_Motion = GetEnemyAxeMotion();					//���[�V�����f�[�^�̏���
	EnemyAxeTex *pAxe_Text = GetEnemyAxeTex();							//�t�@�C���f�[�^�̎擾

	EnemyAxeTex *pEnemyAxeText;
	pEnemyAxeText = GetEnemyAxeTex();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾


#if 1




													//nCntUpdateRogic++;
	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{




		g_EnemyAxe[nCntEnemyAxe].nCntCoolDown++;
		g_EnemyAxe[nCntEnemyAxe].posold = g_EnemyAxe[nCntEnemyAxe].pos;

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


		VecP.x = (pPlayer->pos.x - g_EnemyAxe[nCntEnemyAxe].pos.x);
		VecP.y = pPlayer->pos.y - g_EnemyAxe[nCntEnemyAxe].pos.y;
		VecP.z = (pPlayer->pos.z - g_EnemyAxe[nCntEnemyAxe].pos.z) + 45.0f;
		D3DXVec3Normalize(&VecP, &VecP);

		VecLength = pPlayer->pos - g_EnemyAxe[nCntEnemyAxe].pos;









		if (g_EnemyAxe[nCntEnemyAxe].bUse == true)
		{
			switch (g_EnemyAxe[nCntEnemyAxe].state2)
			{
			case ENEMYAXESTATE2_NORMAL:
				break;

			case ENEMYAXESTATE2_DAMAGE:
				g_EnemyAxe[nCntEnemyAxe].nCntCoolDown--;
				if (g_EnemyAxe[nCntEnemyAxe].nCntCoolDown <= 0)
				{
					g_EnemyAxe[nCntEnemyAxe].state2 = ENEMYAXESTATE2_NORMAL;
				}
			}



			static float fAngle;
			//fAngle = atan2f(pPlayer->pos.x - g_EnemyAxe[nCntEnemyAxe].pos.x, pPlayer->pos.z - g_EnemyAxe[nCntEnemyAxe].pos.z);
			fAngle = atan2f(g_EnemyAxe[nCntEnemyAxe].pos.x - pPlayer->pos.x, g_EnemyAxe[nCntEnemyAxe].pos.z - pPlayer->pos.z);

			g_EnemyAxe[nCntEnemyAxe].fLength = sqrtf((pPlayer->pos.x - g_EnemyAxe[nCntEnemyAxe].pos.x) * (pPlayer->pos.x - g_EnemyAxe[nCntEnemyAxe].pos.x) + (pPlayer->pos.z - g_EnemyAxe[nCntEnemyAxe].pos.z) *(pPlayer->pos.z - g_EnemyAxe[nCntEnemyAxe].pos.z));//����


			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}

			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}




			switch (g_EnemyAxe[nCntEnemyAxe].state)
			{
			case ENEMYAXESTATE_NONE:

				if (CollisionSencer_Enemy(&pPlayer->pos, g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnemy) == true)
				{
					g_EnemyAxe[nCntEnemyAxe].state = ENEMYAXESTATE_DISCOVERY;
				}
				else
				{
					g_EnemyAxe[nCntEnemyAxe].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				break;

			case ENEMYAXESTATE_BACKHOME:

				g_EnemyAxe[nCntEnemyAxe].DestHome = atan2f(g_EnemyAxe[nCntEnemyAxe].HomePoint.x - g_EnemyAxe[nCntEnemyAxe].pos.x,
					g_EnemyAxe[nCntEnemyAxe].HomePoint.z - g_EnemyAxe[nCntEnemyAxe].pos.z);

				g_EnemyAxe[nCntEnemyAxe].move.x = g_EnemyAxe[nCntEnemyAxe].DestHome * 1.2f;
				g_EnemyAxe[nCntEnemyAxe].move.z = g_EnemyAxe[nCntEnemyAxe].DestHome * 1.2f;

				if (g_EnemyAxe[nCntEnemyAxe].pos.x <= g_EnemyAxe[nCntEnemyAxe].HomePoint.x + 50.0f || g_EnemyAxe[nCntEnemyAxe].pos.x >= g_EnemyAxe[nCntEnemyAxe].HomePoint.x - 50.0f
					|| g_EnemyAxe[nCntEnemyAxe].pos.z <= g_EnemyAxe[nCntEnemyAxe].HomePoint.z + 50.0f || g_EnemyAxe[nCntEnemyAxe].pos.z >= g_EnemyAxe[nCntEnemyAxe].HomePoint.z - 50.0f)
				{
					g_EnemyAxe[nCntEnemyAxe].state = ENEMYAXESTATE_NONE;
				}

				break;
			case ENEMYAXESTATE_DISCOVERY:
				g_EnemyAxe[nCntEnemyAxe].move.x = VecP.x * 1.4f;
				g_EnemyAxe[nCntEnemyAxe].move.z = VecP.z * 1.4f;
				fAngle = atan2f(g_EnemyAxe[nCntEnemyAxe].pos.x - pPlayer->pos.x, g_EnemyAxe[nCntEnemyAxe].pos.z - pPlayer->pos.z);
				if (fAngle > D3DX_PI)
				{
					fAngle -= D3DX_PI * 2;
				}

				if (fAngle < -D3DX_PI)
				{
					fAngle += D3DX_PI * 2;
				}
				if (CollisionSencer_Enemy(&pPlayer->pos, g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnemy) == false)
				{
					g_EnemyAxe[nCntEnemyAxe].state = ENEMYAXESTATE_BACKHOME;
				}
				if (g_EnemyAxeStatusNow == ENEMYAXESTATUS_NEUTRAL)
				{//���[���ւ̈ڍs
					SetEnemyAxeStatus(ENEMYAXESTATUS_MOVE, nCntEnemyAxe);
				}
				if (CollisionSencer_Enable(&pPlayer->pos) == true)
				{
					if (g_EnemyAxeStatusNow == ENEMYAXESTATUS_NEUTRAL || g_EnemyAxeStatusNow == ENEMYAXESTATUS_MOVE)
					{//���[���ւ̈ڍs
						pAxe_Motion->nCntFlame = 0;
						if (g_EnemyAxe[nCntEnemyAxe].nCntCoolDown % 30 == 0)
						{
							SetEnemyAxeStatus(ENEMYAXESTATUS_ATTACK, nCntEnemyAxe);
						}
					}

					else if (g_EnemyAxeStatusNow == ENEMYAXESTATUS_ATTACK)
					{
						if (pAxe_Motion->nCntFlame % g_EnemyAxe[nCntEnemyAxe].Collision.StartFlame == 0)
						{
							PlaySound(SOUND_LABEL_SE_SLASH);
						}
						if (pAxe_Motion->nCntFlame > g_EnemyAxe[nCntEnemyAxe].Collision.StartFlame)
						{
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 30.0f)
								, g_EnemyAxe[nCntEnemyAxe].Collision.fRadius
								, g_EnemyAxe[nCntEnemyAxe].nIndexSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 20.0f)
								, g_EnemyAxe[nCntEnemyAxe].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43 - 10.0f)
								, g_EnemyAxe[nCntEnemyAxe].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
							CollisionAttackEnemy(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._41, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._42, g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision._43)
								, g_EnemyAxe[nCntEnemyAxe].Collision.fRadius
								, pPlayer->nIdxSencer
								, SENCERCOLTYPE_ENEMY);
						}
					}
					g_EnemyAxe[nCntEnemyAxe].rot.y = fAngle;
				}
				break;
			}//switch��

			g_EnemyAxe[nCntEnemyAxe].rot.y = fAngle;

#if 1

#endif			

			g_EnemyAxe[nCntEnemyAxe].pos += g_EnemyAxe[nCntEnemyAxe].move;

			g_EnemyAxe[nCntEnemyAxe].move.y -= GRAVITY_E;
			if (g_EnemyAxe[nCntEnemyAxe].move.y > GRAVITY_E_MAX)
			{
				g_EnemyAxe[nCntEnemyAxe].move.y = GRAVITY_E_MAX;
			}
			if (g_EnemyAxe[nCntEnemyAxe].pos.y <= 0.0)
			{

				g_EnemyAxe[nCntEnemyAxe].pos.y = 0.0f;
				g_EnemyAxe[nCntEnemyAxe].move.y = 0.0f;

			}



#endif
			SetPositionSencerCollision(g_EnemyAxe[nCntEnemyAxe].nIndexSencer, g_EnemyAxe[nCntEnemyAxe].pos);//�Z���T�[�̈ʒu
			SetPositionShadow(g_EnemyAxe[nCntEnemyAxe].nIndexShadow, g_EnemyAxe[nCntEnemyAxe].pos);
			SetPositionSencerEnemy(g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnemy,
				D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].pos.x, g_EnemyAxe[nCntEnemyAxe].pos.y, g_EnemyAxe[nCntEnemyAxe].pos.z));
			SetPositionSencerEnableAttack(g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnableAttack, g_EnemyAxe[nCntEnemyAxe].pos);
			CollisionSencer_Lock(&g_EnemyAxe[nCntEnemyAxe].pos);
			//g_EnemyAxe[nCntEnemyAxe].rot.y += 0.01f;




			switch (g_EnemyAxeStatus)
			{
			case ENEMYAXESTATUS_NEUTRAL:
				if (pAxe_Motion->KeyFlame == pAxe_Text->KEYFLAME[pAxe_Motion->nNumEnemyAxeMotion] - 1)
				{
					if (g_EnemyAxeStatusNow == ENEMYAXESTATUS_NEUTRAL)
					{

						SetEnemyAxeMotion(0);
					}
					else
					{
						pAxe_Motion->KeyFlame = 0;
						SetEnemyAxeMotion(0);
						g_EnemyAxeStatusNow = ENEMYAXESTATUS_NEUTRAL;
						g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
					}
				}
				break;
			case ENEMYAXESTATUS_MOVE:
				g_EnemyAxeStatusNow = ENEMYAXESTATUS_MOVE;
				g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
				SetEnemyAxeMotion(1);
				break;
			case ENEMYAXESTATUS_ATTACK:
				g_EnemyAxeStatusNow = ENEMYAXESTATUS_ATTACK;
				g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
				SetEnemyAxeMotion(2);
				break;
			case ENEMYAXESTATUS_JUMP:
				g_EnemyAxeStatusNow = ENEMYAXESTATUS_JUMP;
				g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
				SetEnemyAxeMotion(3);
				break;
			case ENEMYAXESTATUS_LANDING:
				g_EnemyAxeStatusNow = ENEMYAXESTATUS_LANDING;
				g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
				SetEnemyAxeMotion(4);
				break;
			case ENEMYAXESTATUS_GUARD:
				g_EnemyAxeStatusNow = ENEMYAXESTATUS_GUARD;
				g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
				SetEnemyAxeMotion(5);
				break;
			case ENEMYAXESTATUS_DAMAGE1:
				g_EnemyAxeStatusNow = ENEMYAXESTATUS_DAMAGE1;
				g_EnemyAxeStatus = ENEMYAXESTATUS_NEUTRAL;
				SetEnemyAxeMotion(6);
				break;

			}//switch
			 //if

			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWall2_WIDTHBack_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//��O�ǂ̂����蔻��
				CollisionWall2_WIDTHThisSide_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_RIGHT_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_LEFT_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_EnemyAxe[nCntEnemyAxe].pos, &g_EnemyAxe[nCntEnemyAxe].posold);
			}
		}//buse

	}//for
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyAxe(void)
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
		D3DXMatrixIdentity(&g_EnemyAxe[nCntEnemyAxe].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot,
			g_EnemyAxe[nCntEnemyAxe].rot.y, g_EnemyAxe[nCntEnemyAxe].rot.x, g_EnemyAxe[nCntEnemyAxe].rot.z);

		D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].mtxWorld, &g_EnemyAxe[nCntEnemyAxe].mtxWorld, &mtxrot);


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans,
			g_EnemyAxe[nCntEnemyAxe].pos.x, g_EnemyAxe[nCntEnemyAxe].pos.y, g_EnemyAxe[nCntEnemyAxe].pos.z);
		D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].mtxWorld, &g_EnemyAxe[nCntEnemyAxe].mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyAxe[nCntEnemyAxe].mtxWorld);


		for (int nCntModelParts = 0; nCntModelParts < MAX_AXE_PARTS; nCntModelParts++)
		{
			if (g_EnemyAxe[nCntEnemyAxe].bUse == true)
			{

				if (g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == -1)
				{//�v���C���[�̃}�g���b�N�X��
					mtxParent = g_EnemyAxe[nCntEnemyAxe].mtxWorld;
				}
				else if (g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 0)
				{//�̂̃}�g���b�N�X��
					mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[0].mtxWorld;
				}
				else if (g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 1)
				{//���P��
					mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[1].mtxWorld;
				}
				else if (g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 2)
				{//���Q��
					mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[2].mtxWorld;
				}
				else if (g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 5)
				{//���Q��
					mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[5].mtxWorld;
				}
				else if (g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nIdxModelParent == 8)
				{//���Q��
					mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[8].mtxWorld;
				}
				else
				{//���̑�
					mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts - 1].mtxWorld;
				}
				//=======================================================================//
				//						    �e���f���̃C���f�b�N�X						//
				//=====================================================================//
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxrot,
					g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].rot.y, g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].rot.x, g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].rot.z);
				D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &mtxrot);


				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxtrans,
					g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].pos.x, g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].pos.y, g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].pos.z);
				D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &mtxtrans);

				//�e�̃}�g���b�N�X���f
				D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].mtxWorld);


				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//pDevice->SetTexture(0, g_EnemyAxe[nCntEnemyAxe].aModel[0].pEnemyAxeTexture);
					pDevice->SetTexture(0, 0);
					// ���f��(�p�[�c)�̕`��
					g_EnemyAxe[nCntEnemyAxe].aModel[nCntModelParts].pMesh->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}

		/////////////////
		//�����蔻��p//
		///////////////
		if (g_EnemyAxe[nCntEnemyAxe].Collision.nIdxParent == -1)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[16].mtxWorld;
		}
		if (g_EnemyAxe[nCntEnemyAxe].Collision.nIdxParent == 0)
		{// �̂̎��A�v���C���[�̃}�g���b�N�X�ɓ����
			mtxParent = g_EnemyAxe[nCntEnemyAxe].aModel[15].mtxWorld;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot, g_EnemyAxe[nCntEnemyAxe].Collision.rot.y, g_EnemyAxe[nCntEnemyAxe].Collision.rot.x, g_EnemyAxe[nCntEnemyAxe].Collision.rot.z);
		D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision, &g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision, &mtxrot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans, g_EnemyAxe[nCntEnemyAxe].Collision.pos.x, g_EnemyAxe[nCntEnemyAxe].Collision.pos.y, g_EnemyAxe[nCntEnemyAxe].Collision.pos.z);
		D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision, &g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision, &mtxtrans);

		//�e�̃}�g���b�N�X���f
		D3DXMatrixMultiply(&g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision, &g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision, &mtxParent);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyAxe[nCntEnemyAxe].Collision.mtxWorldCollision);
	}
}
//=============================================================================
// �q�b�g����
//=============================================================================
void HitEnemyAxe(int nDamage, int nCntEnemyAxe)
{
	D3DXVECTOR3 VecP;

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	if (g_EnemyAxe[nCntEnemyAxe].bUse == true)
	{
		g_EnemyAxe[nCntEnemyAxe].nLife += nDamage;

		VecP.x = g_EnemyAxe[nCntEnemyAxe].pos.x - pPlayer->pos.x;
		VecP.y = g_EnemyAxe[nCntEnemyAxe].pos.y - pPlayer->pos.y;
		VecP.z = g_EnemyAxe[nCntEnemyAxe].pos.z - pPlayer->pos.z * -1;


		D3DXVec3Normalize(&VecP, &VecP);
		//g_EnemyAxe[nCntEnemyAxe].pos += VecP * 80.0f;

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			SetParticle(D3DXVECTOR3(g_EnemyAxe[nCntEnemyAxe].pos.x, g_EnemyAxe[nCntEnemyAxe].pos.y + 30.0f, g_EnemyAxe[nCntEnemyAxe].pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f), PARTICLETYPE_EXPLOSION);
		}
		if (g_EnemyAxe[nCntEnemyAxe].nLife <= 0)
		{

			g_EnemyAxe[nCntEnemyAxe].bUse = false;
			DeletShadow(g_EnemyAxe[nCntEnemyAxe].nIndexShadow);
			DeleteSencerCol(g_EnemyAxe[nCntEnemyAxe].nIndexSencer);
			DeleteSencerEnemy(g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnemy);
			DeleteSencerEnableAttack(g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnableAttack);
			DecreaseBrazen(-2);

		}

	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CollisionEnemyAxe(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosold, D3DXVECTOR3 * VtxMax, D3DXVECTOR3 * VtxMin)
{
	bool bCollision = false; //���n������

	for (int nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		if (g_EnemyAxe[nCntEnemyAxe].bUse == true)
		{
			if (pPos->x + VtxMax->z >= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x && pPos->x - VtxMax->z <= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x
				&&pPos->y + VtxMax->y >= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y && pPos->y - VtxMax->y <= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y
				&&pPos->z + VtxMax->z >= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z && pPos->z - VtxMax->z <= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z)
			{
				if (pPosold->x + VtxMax->z <= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x  && pPos->x + VtxMax->z >= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x)
				{//�����炫���Ƃ�
					pPos->x = g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x - VtxMax->z;
					bCollision = true;
				}

				else if (pPosold->x - VtxMax->z >= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x  && pPos->x - VtxMax->z <= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x)
				{//�E���炫���Ƃ�
					pPos->x = g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.x + g_EnemyAxe[nCntEnemyAxe].pos.x + VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z + VtxMax->z <= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z && pPos->z + VtxMax->z >= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z)
				{//��O���痈����
					pPos->z = g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z - VtxMax->z;
					bCollision = true;

				}
				else if (pPosold->z - VtxMax->z >= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z && pPos->z - VtxMax->z <= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z)
				{//�����痈����
					pPos->z = g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.z + g_EnemyAxe[nCntEnemyAxe].pos.z + VtxMax->z;
					bCollision = true;

				}

				if (pPosold->y + VtxMax->y <= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y && pPos->y + VtxMax->y >= g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y)
				{//�ォ�痈����
					pPos->y = g_EnemyAxe[nCntEnemyAxe].VtxMinEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y + VtxMin->y;
					bCollision = true;

				}
				if (pPosold->y - VtxMax->y >= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y && pPos->y - VtxMax->y <= g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y)
				{//�����痈����
					pPos->y = g_EnemyAxe[nCntEnemyAxe].VtxMaxEnemyAxe.y + g_EnemyAxe[nCntEnemyAxe].pos.y + VtxMax->y;
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
int SetEnemyAxe(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntEnemyAxe;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemyAxe = 0; nCntEnemyAxe < MAX_ENEMYAXE; nCntEnemyAxe++)
	{
		if (g_EnemyAxe[nCntEnemyAxe].bUse == false)
		{
			g_EnemyAxe[nCntEnemyAxe].pos = pos;
			g_EnemyAxe[nCntEnemyAxe].HomePoint = pos;
			g_EnemyAxe[nCntEnemyAxe].rot = rot;
			g_EnemyAxe[nCntEnemyAxe].nLife = nLife;
			g_EnemyAxe[nCntEnemyAxe].nIndexSencer = SetSencerCollision(g_EnemyAxe[nCntEnemyAxe].pos, g_EnemyAxe[nCntEnemyAxe].rot, SENCERCOLTYPE_ENEMY_AXE);
			g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnemy = SetSencerEnemy(g_EnemyAxe[nCntEnemyAxe].pos, g_EnemyAxe[nCntEnemyAxe].rot);
			g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnableAttack = SetSencerEnableAttack(g_EnemyAxe[nCntEnemyAxe].pos, g_EnemyAxe[nCntEnemyAxe].rot);
			g_EnemyAxe[nCntEnemyAxe].nIndexShadow = SetShadow(g_EnemyAxe[nCntEnemyAxe].pos, g_EnemyAxe[nCntEnemyAxe].rot);
			g_EnemyAxe[nCntEnemyAxe].state2 = ENEMYAXESTATE2_NORMAL;
			g_EnemyAxe[nCntEnemyAxe].bUse = true;
			break;
		}
	}
	return nCntEnemyAxe;
}

//------------------------------------------------------------------------
// �G�l�~�[�̏�Ԃ̐ݒ�												      |
//------------------------------------------------------------------------
void SetEnemyAxeStatus(ENEMYAXESTATUS status, int nCntEnemyAxe)
{
	g_EnemyAxeStatus = status;
}

////////////////////////////////////////////////////////////
//				�G�̏���								  //
////////////////////////////////////////////////////////////
void DeleteEnemyAxe(int nCntEnemyAxe)
{
	g_EnemyAxe[nCntEnemyAxe].bUse = false;
	DeletShadow(g_EnemyAxe[nCntEnemyAxe].nIndexShadow);
	DeleteSencerCol(g_EnemyAxe[nCntEnemyAxe].nIndexSencer);
	DeleteSencerEnemy(g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnemy);
	DeleteSencerEnableAttack(g_EnemyAxe[nCntEnemyAxe].nIndexSencerEnableAttack);

}

////////////////////////////////////////////////////////////
//				�G�̎擾								  //
////////////////////////////////////////////////////////////
ENEMYAXE *GetEnemyAxe(void)
{
	return &g_EnemyAxe[0];
}
///////////////////////////////////////////////////////////
//				�G��Ԃ̎擾							//
//////////////////////////////////////////////////////////
ENEMYAXESTATUS *GetEnemyAxeStatus(void)
{
	return &g_EnemyAxe[0].status;
}


