//=============================================================================
//
// ��� [arrow.cpp]
// Author : KishidaRei
//
//=============================================================================
#include "arrow.h"
#include "player.h"
#include "particle.h"
#include "camera.h"
#include "SencerCol.h"
#include "Wall1.h"
#include "Wall2.h"
#include "WallBoss.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ARROW (50)
#define MODEL_ARROW			"data/MODEL/arrow.x"
#define ARROW_MOVR		(1.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH			g_pMeshArrow = NULL;				//���b�V�����i���_���j�̃|�C���^
LPD3DXBUFFER		g_pBuffMatArrow = NULL;				//�}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatArrow = 0;					//�}�e���A�����̐�
LPDIRECT3DTEXTURE9	g_pTextureArrow = NULL;				//�e�N�X�`���ւ̃|�C���^
ARROW				g_Arrow[MAX_ARROW];							//���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//���_��
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;						//���_�o�b�t�@�̃|�C���^

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		g_Arrow[nCntArrow].vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		g_Arrow[nCntArrow].vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		// �ʒu�E�����E�F�̏����ݒ�
		
		g_Arrow[nCntArrow].bUse = false;
	}
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_ARROW,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatArrow,
			NULL,
			&g_nNumMatArrow,
			&g_pMeshArrow);


		for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
		{
			//���_���̎擾
			nNumVtx = g_pMeshArrow->GetNumVertices();
			sizeFVF = D3DXGetFVFVertexSize(g_pMeshArrow->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_pMeshArrow->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				if (g_Arrow[0].vtxMin.x > vtx.x)
				{//X�̍ŏ��l�̏�������
					g_Arrow[0].vtxMin.x = vtx.x;
				}
				if (g_Arrow[0].vtxMin.z > vtx.z)
				{//X�̍ŏ��l�̏�������
					g_Arrow[0].vtxMin.z = vtx.z;
				}
				if (g_Arrow[0].vtxMax.x < vtx.x)
				{//X�̍ŏ��l�̏�������
					g_Arrow[0].vtxMax.x = vtx.x;
				}
				if (g_Arrow[0].vtxMax.z < vtx.z)
				{//X�̍ŏ��l�̏�������
					g_Arrow[0].vtxMax.z = vtx.z;
				}

				pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
			}
			//���_�o�b�t�@�̃A�����b�N
			g_pMeshArrow->UnlockVertexBuffer();


		}
}

//=============================================================================
// �I������
//=============================================================================
void UninitArrow(void)
{
	// ���b�V���̊J��
	if (g_pMeshArrow != NULL)
	{
		g_pMeshArrow->Release();
		g_pMeshArrow = NULL;
	}
	// �}�e���A���̊J��
	if (g_pBuffMatArrow != NULL)
	{
		g_pBuffMatArrow->Release();
		g_pBuffMatArrow = NULL;
	}

	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateArrow(void)
{
	CAMERA pCamera;
	pCamera = *GetCamera();
	PLAYER *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();
	STAGEMODE g_Stage = GetStageMode();				//���݂̃X�e�[�W�ԍ����擾


	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{//�e���ړ�������
		if (g_Arrow[nCntArrow].bUse == true)
		{
			g_Arrow[nCntArrow].posold = g_Arrow[nCntArrow].pos;
			g_Arrow[nCntArrow].nLife--;

			/*static float fAngle;
			fAngle = atan2f(g_Arrow[nCntArrow].pos.x - pPlayer->pos.x, g_Arrow[nCntArrow].pos.z - pPlayer->pos.z);*/


			if (CollisionAttackEnemyArrow(&g_Arrow[nCntArrow].pos) == true)
			{
				g_Arrow[nCntArrow].bUse = false;

			}
			//g_Arrow[nCntArrow].rot.y = fAngle;

			SetParticle(g_Arrow[nCntArrow].pos, 20, D3DXCOLOR(1.0f, 0.0f, 0.9f, 0.6f), PARTICLETYPE_BULLET);
			
			if (g_Arrow[nCntArrow].nLife < 0)
			{
				g_Arrow[nCntArrow].bUse = false;
			}

			g_Arrow[nCntArrow].pos += g_Arrow[nCntArrow].move;




			if (g_Stage == STAGEMODE_STAGE1)
			{//���݂̃X�e�[�W���X�e�[�W1
			 //���ǂ̂����蔻��
				CollisionWall1_WIDTHBack_Arrow(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				//��O�ǂ̂����蔻��
				CollisionWall1_WIDTHThisSide_Arrow(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_RIGHT_Arrow(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWall1_LEFT_Arrow(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE2)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				//CollisionWall2_WIDTHBack_Arrow(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				////��O�ǂ̂����蔻��
				//CollisionWall2_WIDTHThisSide_Arrow(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				////�E�ǂ̂����蔻��
				//CollisionWall2_RIGHT_Ene(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				////�E�ǂ̂����蔻��
				//CollisionWall2_LEFT_Ene(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);
			}
			else if (g_Stage == STAGEMODE_STAGE3)
			{//���݂̃X�e�[�W���X�e�[�W2
			 //���ǂ̂����蔻��
				CollisionWallBoss_WIDTHBack_Ene(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				//��O�ǂ̂����蔻��
				CollisionWallBoss_WIDTHThisSide_Ene(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_RIGHT_Ene(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);

				//�E�ǂ̂����蔻��
				CollisionWallBoss_LEFT_Ene(&g_Arrow[nCntArrow].pos, &g_Arrow[nCntArrow].posold);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawArrow(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Arrow[nCntArrow].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Arrow[nCntArrow].rot.y, g_Arrow[nCntArrow].rot.x, g_Arrow[nCntArrow].rot.z);
			D3DXMatrixMultiply(&g_Arrow[nCntArrow].mtxWorld, &g_Arrow[nCntArrow].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Arrow[nCntArrow].pos.x, g_Arrow[nCntArrow].pos.y, g_Arrow[nCntArrow].pos.z);
			D3DXMatrixMultiply(&g_Arrow[nCntArrow].mtxWorld, &g_Arrow[nCntArrow].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Arrow[nCntArrow].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatArrow->GetBufferPointer();

			for (int nCntMat = 0; nCntMat <= (int)g_nNumMatArrow; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureArrow);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// ���f��(�p�[�c)�̕`��
				g_pMeshArrow->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
#endif
}
//=============================================================================
// ���f���̎擾
//=============================================================================
ARROW *GetArrow(void)
{
	return &g_Arrow[0];
}

void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife)
{
	BYTE *pVtxBuff;	//���_�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�̃��b�N
	g_pMeshArrow->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == false)
		{
			g_Arrow[nCntArrow].pos = pos;
			g_Arrow[nCntArrow].rot = rot;
			g_Arrow[nCntArrow].move = move;
			g_Arrow[nCntArrow].nLife = nLife;
			g_Arrow[nCntArrow].bUse = true;

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshArrow->UnlockVertexBuffer();
}
