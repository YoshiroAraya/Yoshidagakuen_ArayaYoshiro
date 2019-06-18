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
#include "enemy_arrow.h"
#include "sound.h"
#include "enemy_arrow_text.h"
#include "enemy_arrow_motion.h"
#include "SencerCol.h"
#include "SencerLock.h"
#include "SencerAtk.h"
#include "SencerEnableAttack.h"
#include "Wall1.h"
#include "Wall2.h"
#include "WallBoss.h"
#include "arrow.h"
#include "magic.h"
#include "sencerArrow.h"
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

ENEMYARROW g_EnemyArrow[MAX_ENEMY_ARROW];
ENEMY_ARROW_STATUS g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
ENEMY_ARROW_STATUS g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_NEUTRAL;

//STAGE g_aLimit[4];
//�e�L�X�g���擾


int g_nCntSound_Arrow = 0;
int g_nCntEnemyArrowArrow;

//=============================================================================
// ����������
//=============================================================================
void InitEnemyArrow(void)
{


	EnemyArrowTex *pEnemyArrowText;
	pEnemyArrowText = GetEnemyArrowTex();
	g_nCntEnemyArrowArrow = 3;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemyArrow = 0; nCntEnemyArrow < MAX_ENEMY_ARROW; nCntEnemyArrow++)
	{
		for (int nCntIdx = 0; nCntIdx < pEnemyArrowText->MAX_PARTS; nCntIdx++)
		{//�e��l�̑��
		 //�ǂݍ��ރ��f����
			g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].FileName[0] = pEnemyArrowText->aModelTex[nCntIdx].FileName[0];

			//�e�q�֌W
			g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].nIdxModelParent = pEnemyArrowText->aModelTex[nCntIdx].Index;

			//�ʒu
			g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].pos = D3DXVECTOR3(pEnemyArrowText->aModelTex[nCntIdx].PosX, pEnemyArrowText->aModelTex[nCntIdx].PosY, pEnemyArrowText->aModelTex[nCntIdx].PosZ);

			//��]
			g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].rot = D3DXVECTOR3(pEnemyArrowText->aModelTex[nCntIdx].RotX,
				pEnemyArrowText->aModelTex[nCntIdx].RotY,
				pEnemyArrowText->aModelTex[nCntIdx].RotZ);

			//���f���̐ݒ�
			D3DXLoadMeshFromX(&pEnemyArrowText->aModelTex[nCntIdx].FileName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].pBuffMat,
				NULL,
				&g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].nNumMat,
				&g_EnemyArrow[nCntEnemyArrow].aModel[nCntIdx].pMesh);
		}
		


		//�W�����v�̏��
		g_EnemyArrow[nCntEnemyArrow].bUseJump = false;
		//�v���C���[�̏��
		g_EnemyArrow[nCntEnemyArrow].nCoolDown = 0;

		//�v���C���[���g�p����Ă��邩
		g_EnemyArrow[nCntEnemyArrow].bUse = false;

	}









	


	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	for (int nCntEnemyArrow = 0; nCntEnemyArrow < MAX_ENEMY_ARROW; nCntEnemyArrow++)
	{
		//���_�����擾
		nNumVtx = g_EnemyArrow[nCntEnemyArrow].aModel[0].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyArrow[nCntEnemyArrow].aModel[0].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_EnemyArrow[nCntEnemyArrow].aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W

			if (Vtx.x < g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.x)
			{
				g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.y)
			{
				g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z < g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.z)
			{
				g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.z = Vtx.x;
			}


			if (Vtx.x > g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.x)
			{
				g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.x = Vtx.x + 20.0f;
			}

			if (Vtx.y > g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.y)
			{
				g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.y = Vtx.y + 30.0f;
			}

			if (Vtx.z > g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.z)
			{
				g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.z = Vtx.z + 20.0f;
			}
			pVtxBuff += sizeFVF;
		}

		g_EnemyArrow[nCntEnemyArrow].VtxMinEnemy.x = g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.x;
		g_EnemyArrow[nCntEnemyArrow].VtxMaxEnemy.x = g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.x;

		g_EnemyArrow[nCntEnemyArrow].VtxMinEnemy.y = g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.y;
		g_EnemyArrow[nCntEnemyArrow].VtxMaxEnemy.y = g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.y;

		g_EnemyArrow[nCntEnemyArrow].VtxMinEnemy.z = g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMinModel.z;
		g_EnemyArrow[nCntEnemyArrow].VtxMaxEnemy.z = g_EnemyArrow[nCntEnemyArrow].aModel[0].VtxMaxModel.z;

		g_EnemyArrow[nCntEnemyArrow].fAngle = 0.0f;			//����

	}

	CAMERA *pCamera;
	pCamera = GetCamera();


}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyArrow(void)
{


	for (int nCntEnemyArrow = 0; nCntEnemyArrow < MAX_ENEMY_ARROW; nCntEnemyArrow++)
	{
		// ���b�V���̊J��
		if (g_EnemyArrow[nCntEnemyArrow].aModel[0].pMesh != NULL)
		{
			g_EnemyArrow[nCntEnemyArrow].aModel[0].pMesh->Release();
			g_EnemyArrow[nCntEnemyArrow].aModel[0].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_EnemyArrow[nCntEnemyArrow].aModel[0].pBuffMat != NULL)
		{
			g_EnemyArrow[nCntEnemyArrow].aModel[0].pBuffMat->Release();
			g_EnemyArrow[nCntEnemyArrow].aModel[0].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyArrow(void)
{

	EnemyArrowMotion *pArrow_Motion = GetEnemyArrowMotion();					//���[�V�����f�[�^�̏���
	EnemyArrowTex *pArrow_Text = GetEnemyArrowTex();							//�t�@�C���f�[�^�̎擾

	EnemyArrowTex *pEnemyArrowText;
	pEnemyArrowText = GetEnemyArrowTex();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾






													//nCntUpdateRogic++;
	for (int nCntEnemyArrow = 0; nCntEnemyArrow < MAX_ENEMY_ARROW; nCntEnemyArrow++)
	{

		if (g_EnemyArrow[nCntEnemyArrow].bUse == true)

		{
			g_EnemyArrow[nCntEnemyArrow].nCntCoolDown++;
			g_EnemyArrow[nCntEnemyArrow].posold = g_EnemyArrow[nCntEnemyArrow].pos;

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


			VecP.x = (pPlayer->pos.x - g_EnemyArrow[nCntEnemyArrow].pos.x);
			VecP.y = pPlayer->pos.y - g_EnemyArrow[nCntEnemyArrow].pos.y;
			VecP.z = (pPlayer->pos.z - g_EnemyArrow[nCntEnemyArrow].pos.z) + 45.0f;
			D3DXVec3Normalize(&VecP, &VecP);

			VecLength = pPlayer->pos - g_EnemyArrow[nCntEnemyArrow].pos;



			D3DXVECTOR3 ArrowMove;








			static float fAngle;
			//fAngle = atan2f(pPlayer->pos.x - g_EnemyArrow[nCntEnemyArrow].pos.x, pPlayer->pos.z - g_EnemyArrow[nCntEnemyArrow].pos.z);
			fAngle = atan2f(g_EnemyArrow[nCntEnemyArrow].pos.x - pPlayer->pos.x, g_EnemyArrow[nCntEnemyArrow].pos.z - pPlayer->pos.z);

			g_EnemyArrow[nCntEnemyArrow].fLength = sqrtf((pPlayer->pos.x - g_EnemyArrow[nCntEnemyArrow].pos.x) * (pPlayer->pos.x - g_EnemyArrow[nCntEnemyArrow].pos.x) + (pPlayer->pos.z - g_EnemyArrow[nCntEnemyArrow].pos.z) *(pPlayer->pos.z - g_EnemyArrow[nCntEnemyArrow].pos.z));//����


			if (fAngle > D3DX_PI)
			{
				fAngle -= D3DX_PI * 2;
			}

			if (fAngle < -D3DX_PI)
			{
				fAngle += D3DX_PI * 2;
			}




			switch (g_EnemyArrow[nCntEnemyArrow].state)
			{
			case ENEMY_ARROW_STATE_NONE:

				if (CollisionSencer_EnemyArrow(&pPlayer->pos, g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnemyaArrow) == true)
				{
					g_EnemyArrow[nCntEnemyArrow].state = ENEMY_ARROW_STATE_DISCOVERY;
				}
				else
				{
					g_EnemyArrow[nCntEnemyArrow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}

				break;

			case ENEMY_ARROW_STATE_BACKHOME:

				g_EnemyArrow[nCntEnemyArrow].DestHome = atan2f(g_EnemyArrow[nCntEnemyArrow].HomePoint.x - g_EnemyArrow[nCntEnemyArrow].pos.x,
					g_EnemyArrow[nCntEnemyArrow].HomePoint.z - g_EnemyArrow[nCntEnemyArrow].pos.z);

				g_EnemyArrow[nCntEnemyArrow].move.x = g_EnemyArrow[nCntEnemyArrow].DestHome * 1.2f;
				g_EnemyArrow[nCntEnemyArrow].move.z = g_EnemyArrow[nCntEnemyArrow].DestHome * 1.2f;

				if (g_EnemyArrow[nCntEnemyArrow].pos.x <= g_EnemyArrow[nCntEnemyArrow].HomePoint.x + 50.0f || g_EnemyArrow[nCntEnemyArrow].pos.x >= g_EnemyArrow[nCntEnemyArrow].HomePoint.x - 50.0f
					|| g_EnemyArrow[nCntEnemyArrow].pos.z <= g_EnemyArrow[nCntEnemyArrow].HomePoint.z + 50.0f || g_EnemyArrow[nCntEnemyArrow].pos.z >= g_EnemyArrow[nCntEnemyArrow].HomePoint.z - 50.0f)
				{
					g_EnemyArrow[nCntEnemyArrow].state = ENEMY_ARROW_STATE_NONE;
				}

				break;
			case ENEMY_ARROW_STATE_DISCOVERY:
				/*g_EnemyArrow[nCntEnemyArrow].move.x = VecP.x * 1.5f;
				g_EnemyArrow[nCntEnemyArrow].move.z = VecP.z * 1.5f;*/
				fAngle = atan2f(g_EnemyArrow[nCntEnemyArrow].pos.x - pPlayer->pos.x, g_EnemyArrow[nCntEnemyArrow].pos.z - pPlayer->pos.z);
				if (fAngle > D3DX_PI)
				{
					fAngle -= D3DX_PI * 2;
				}

				if (fAngle < -D3DX_PI)
				{
					fAngle += D3DX_PI * 2;
				}
				if (CollisionSencer_EnemyArrow(&pPlayer->pos, g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnemyaArrow) == false)
				{
					g_EnemyArrow[nCntEnemyArrow].state = ENEMY_ARROW_STATE_BACKHOME;
				}


				if (g_EnemyArrowStatusNow == ENEMY_ARROW_STATUS_NEUTRAL || g_EnemyArrowStatusNow == ENEMY_ARROW_STATUS_MOVE)
				{//���[���ւ̈ڍs
					pArrow_Motion->nCntFlame = 0;
					if (g_EnemyArrow[nCntEnemyArrow].nCntCoolDown % 70 == 0)
					{
						SetEnemyStatusArrow(ENEMY_ARROW_STATUS_ATTACK, nCntEnemyArrow);
						SetArrow(D3DXVECTOR3(g_EnemyArrow[nCntEnemyArrow].pos.x, g_EnemyArrow[nCntEnemyArrow].pos.y + 60.0f, g_EnemyArrow[nCntEnemyArrow].pos.z),
							D3DXVECTOR3(g_EnemyArrow[nCntEnemyArrow].rot.x, g_EnemyArrow[nCntEnemyArrow].rot.y, g_EnemyArrow[nCntEnemyArrow].rot.z),
							D3DXVECTOR3(sinf(g_EnemyArrow[nCntEnemyArrow].rot.y + (-1.0f * D3DX_PI)) * 15.0f, 0.0f, cosf(g_EnemyArrow[nCntEnemyArrow].rot.y + (-1.0f * D3DX_PI)) * 15.0f),
							90);

						

					}
				}


				g_EnemyArrow[nCntEnemyArrow].rot.y = fAngle;

				break;
			}//switch��

			g_EnemyArrow[nCntEnemyArrow].rot.y = fAngle;

			g_EnemyArrow[nCntEnemyArrow].pos += g_EnemyArrow[nCntEnemyArrow].move;

			g_EnemyArrow[nCntEnemyArrow].move.y -= GRAVITY_E;
			if (g_EnemyArrow[nCntEnemyArrow].move.y > GRAVITY_E_MAX)
			{
				g_EnemyArrow[nCntEnemyArrow].move.y = GRAVITY_E_MAX;
			}
			if (g_EnemyArrow[nCntEnemyArrow].pos.y <= 0.0)
			{

				g_EnemyArrow[nCntEnemyArrow].pos.y = 0.0f;
				g_EnemyArrow[nCntEnemyArrow].move.y = 0.0f;

			}



			SetPositionSencerCollision(g_EnemyArrow[nCntEnemyArrow].nIndexSencer, g_EnemyArrow[nCntEnemyArrow].pos);//�Z���T�[�̈ʒu
			SetPositionShadow(g_EnemyArrow[nCntEnemyArrow].nIndexShadow, g_EnemyArrow[nCntEnemyArrow].pos);
			SetPositionSencerEnemyArrow(g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnemyaArrow,
				D3DXVECTOR3(g_EnemyArrow[nCntEnemyArrow].pos.x, g_EnemyArrow[nCntEnemyArrow].pos.y, g_EnemyArrow[nCntEnemyArrow].pos.z));
			SetPositionSencerEnableAttack(g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnableAttack, g_EnemyArrow[nCntEnemyArrow].pos);
			CollisionSencer_Lock(&g_EnemyArrow[nCntEnemyArrow].pos);
			//g_EnemyArrow[nCntEnemyArrow].rot.y += 0.01f;




			switch (g_EnemyArrowStatus)
			{
			case ENEMY_ARROW_STATUS_NEUTRAL:
				if (pArrow_Motion->KeyFlame == pArrow_Text->KEYFLAME[pArrow_Motion->nNumEnemyArrowMotion] - 1)
				{
					if (g_EnemyArrowStatusNow == ENEMY_ARROW_STATUS_NEUTRAL)
					{

						SetEnemyArrowMotion(0);
					}
					else
					{
						pArrow_Motion->KeyFlame = 0;
						SetEnemyArrowMotion(0);
						g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_NEUTRAL;
						g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
					}
				}
				break;
			case ENEMY_ARROW_STATUS_MOVE:
				g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_MOVE;
				g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
				SetEnemyArrowMotion(1);
				break;
			case ENEMY_ARROW_STATUS_ATTACK:
				g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_ATTACK;
				g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
				SetEnemyArrowMotion(2);
				break;
			case ENEMY_ARROW_STATUS_JUMP:
				g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_JUMP;
				g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
				SetEnemyArrowMotion(3);
				break;
			case ENEMY_ARROW_STATUS_LANDING:
				g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_LANDING;
				g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
				SetEnemyArrowMotion(4);
				break;
			case ENEMY_ARROW_STATUS_GUARD:
				g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_GUARD;
				g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
				SetEnemyArrowMotion(5);
				break;
			case ENEMY_ARROW_STATUS_DAMAGE1:
				g_EnemyArrowStatusNow = ENEMY_ARROW_STATUS_DAMAGE1;
				g_EnemyArrowStatus = ENEMY_ARROW_STATUS_NEUTRAL;
				SetEnemyArrowMotion(6);
				break;

			}//switch
			 //if

			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWall2_WIDTHBack_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//��O�ǂ̂����蔻��
				CollisionWall2_WIDTHThisSide_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_RIGHT_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWall2_LEFT_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_EnemyArrow[nCntEnemyArrow].pos, &g_EnemyArrow[nCntEnemyArrow].posold);
			}
		}//buse
	}
}//for

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyArrow(void)
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
	for (int nCntEnemyArrow = 0; nCntEnemyArrow < MAX_ENEMY_ARROW; nCntEnemyArrow++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EnemyArrow[nCntEnemyArrow].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxrot,
			g_EnemyArrow[nCntEnemyArrow].rot.y, g_EnemyArrow[nCntEnemyArrow].rot.x, g_EnemyArrow[nCntEnemyArrow].rot.z);

		D3DXMatrixMultiply(&g_EnemyArrow[nCntEnemyArrow].mtxWorld, &g_EnemyArrow[nCntEnemyArrow].mtxWorld, &mtxrot);


		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxtrans,
			g_EnemyArrow[nCntEnemyArrow].pos.x, g_EnemyArrow[nCntEnemyArrow].pos.y, g_EnemyArrow[nCntEnemyArrow].pos.z);
		D3DXMatrixMultiply(&g_EnemyArrow[nCntEnemyArrow].mtxWorld, &g_EnemyArrow[nCntEnemyArrow].mtxWorld, &mtxtrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EnemyArrow[nCntEnemyArrow].mtxWorld);


		for (int nCntModelParts = 0; nCntModelParts < MAX_ARROW_PARTS; nCntModelParts++)
		{
			if (g_EnemyArrow[nCntEnemyArrow].bUse == true)
			{

				if (g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nIdxModelParent == -1)
				{//�v���C���[�̃}�g���b�N�X��
					mtxParent = g_EnemyArrow[nCntEnemyArrow].mtxWorld;
				}
				else if (g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nIdxModelParent == 0)
				{//�̂̃}�g���b�N�X��
					mtxParent = g_EnemyArrow[nCntEnemyArrow].aModel[0].mtxWorld;
				}
				else if (g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nIdxModelParent == 1)
				{//���P��
					mtxParent = g_EnemyArrow[nCntEnemyArrow].aModel[1].mtxWorld;
				}
				else if (g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nIdxModelParent == 2)
				{//���Q��
					mtxParent = g_EnemyArrow[nCntEnemyArrow].aModel[2].mtxWorld;
				}
				else if (g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nIdxModelParent == 5)
				{//���Q��
					mtxParent = g_EnemyArrow[nCntEnemyArrow].aModel[5].mtxWorld;
				}
				else if (g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nIdxModelParent == 8)
				{//���Q��
					mtxParent = g_EnemyArrow[nCntEnemyArrow].aModel[8].mtxWorld;
				}
				else
				{//���̑�
					mtxParent = g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts - 1].mtxWorld;
				}
				//=======================================================================//
				//						    �e���f���̃C���f�b�N�X						//
				//=====================================================================//
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxrot,
					g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].rot.y, g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].rot.x, g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].rot.z);
				D3DXMatrixMultiply(&g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld, &g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld, &mtxrot);


				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxtrans,
					g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].pos.x, g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].pos.y, g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].pos.z);
				D3DXMatrixMultiply(&g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld, &g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld, &mtxtrans);

				//�e�̃}�g���b�N�X���f
				D3DXMatrixMultiply(&g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld, &g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].mtxWorld);


				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].nNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//pDevice->SetTexture(0, g_EnemyArrow[nCntEnemyArrow].aModel[0].pEnemyArrowTexture);
					pDevice->SetTexture(0, 0);
					// ���f��(�p�[�c)�̕`��
					g_EnemyArrow[nCntEnemyArrow].aModel[nCntModelParts].pMesh->DrawSubset(nCntMat);
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}

		
	}
}
//=============================================================================
// �q�b�g����
//=============================================================================
void HitEnemyArrow(int nDamage, int nCntEnemyArrow)
{
	D3DXVECTOR3 VecP;

	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	if (g_EnemyArrow[nCntEnemyArrow].bUse == true)
	{
		g_EnemyArrow[nCntEnemyArrow].nLife += nDamage;

		VecP.x = g_EnemyArrow[nCntEnemyArrow].pos.x - pPlayer->pos.x;
		VecP.y = g_EnemyArrow[nCntEnemyArrow].pos.y - pPlayer->pos.y;
		VecP.z = g_EnemyArrow[nCntEnemyArrow].pos.z - pPlayer->pos.z * -1;


		D3DXVec3Normalize(&VecP, &VecP);
		//g_EnemyArrow[nCntEnemyArrow].pos += VecP * 80.0f;

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			SetParticle(D3DXVECTOR3(g_EnemyArrow[nCntEnemyArrow].pos.x, g_EnemyArrow[nCntEnemyArrow].pos.y + 30.0f, g_EnemyArrow[nCntEnemyArrow].pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.8f, 1.0f), PARTICLETYPE_EXPLOSION);
		}
		if (g_EnemyArrow[nCntEnemyArrow].nLife <= 0)
		{

			g_EnemyArrow[nCntEnemyArrow].bUse = false;
			DeletShadow(g_EnemyArrow[nCntEnemyArrow].nIndexShadow);
			DeleteSencerCol(g_EnemyArrow[nCntEnemyArrow].nIndexSencer);
			DeleteSencerEnemyArrow(g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnemyaArrow);
			DeleteSencerEnableAttack(g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnableAttack);
			DecreaseBrazen(-2);
		}

	}
}


//////////////////////////////////////////////////////////////////////////
//////				�G�̐ݒu								  ////////////
//////////////////////////////////////////////////////////////////////////
int SetEnemyArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntEnemyArrow;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntEnemyArrow = 0; nCntEnemyArrow < MAX_ENEMY_ARROW; nCntEnemyArrow++)
	{
		if (g_EnemyArrow[nCntEnemyArrow].bUse == false)
		{
			g_EnemyArrow[nCntEnemyArrow].pos = pos;
			g_EnemyArrow[nCntEnemyArrow].HomePoint = pos;
			g_EnemyArrow[nCntEnemyArrow].rot = rot;
			g_EnemyArrow[nCntEnemyArrow].nLife = nLife;
			g_EnemyArrow[nCntEnemyArrow].nIndexSencer = SetSencerCollision(g_EnemyArrow[nCntEnemyArrow].pos, g_EnemyArrow[nCntEnemyArrow].rot, SENCERCOLTYPE_ENEMY_ARROW);
			g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnemyaArrow = SetSencerEnemyArrow(g_EnemyArrow[nCntEnemyArrow].pos, g_EnemyArrow[nCntEnemyArrow].rot);
			g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnableAttack = SetSencerEnableAttack(g_EnemyArrow[nCntEnemyArrow].pos, g_EnemyArrow[nCntEnemyArrow].rot);
			g_EnemyArrow[nCntEnemyArrow].nIndexShadow = SetShadow(g_EnemyArrow[nCntEnemyArrow].pos, g_EnemyArrow[nCntEnemyArrow].rot);
			g_EnemyArrow[nCntEnemyArrow].state2 = ENEMY_ARROW_STATE2_NORMAL;
			g_EnemyArrow[nCntEnemyArrow].bUse = true;
			break;
		}
	}
	return nCntEnemyArrow;
}

//------------------------------------------------------------------------
// �G�l�~�[�̏�Ԃ̐ݒ�												      |
//------------------------------------------------------------------------
void SetEnemyStatusArrow(ENEMY_ARROW_STATUS status, int nCntEnemyArrow)
{
	g_EnemyArrowStatus = status;
}

////////////////////////////////////////////////////////////
//				�G�̏���								  //
////////////////////////////////////////////////////////////
void DeleteEnemyArrow(int nCntEnemyArrow)
{
	g_EnemyArrow[nCntEnemyArrow].bUse = false;
	DeletShadow(g_EnemyArrow[nCntEnemyArrow].nIndexShadow);
	DeleteSencerCol(g_EnemyArrow[nCntEnemyArrow].nIndexSencer);
	DeleteSencerEnemyArrow(g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnemyaArrow);
	DeleteSencerEnableAttack(g_EnemyArrow[nCntEnemyArrow].nIndexSencerEnableAttack);

}

////////////////////////////////////////////////////////////
//				�G�̎擾								  //
////////////////////////////////////////////////////////////
ENEMYARROW *GetEnemyArrow(void)
{
	return &g_EnemyArrow[0];
}
///////////////////////////////////////////////////////////
//				�G��Ԃ̎擾							//
//////////////////////////////////////////////////////////
ENEMY_ARROW_STATUS *GetEnemyArrowStatus(void)
{
	return &g_EnemyArrow[0].status;
}


