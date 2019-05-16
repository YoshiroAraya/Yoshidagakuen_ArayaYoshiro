//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �G�l�~�[�̒Ǐ]����Ƃ��̋���
// Author : KishidaRei 
//
//=============================================================================
#include "SencerEnableBoss.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERENABLEBOSS (5)
#define MAX_TEXTURE (2)

#define SENCERENABLEBOSS_VERTEX (  (g_SencerEnableBoss_h + 1) * (g_SencerEnableBoss_v + 1)   )	//���_��
#define SENCERENABLEBOSS_INDEX (   (g_SencerEnableBoss_h * g_SencerEnableBoss_v )* 2 + (4 * (g_SencerEnableBoss_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERENABLEBOSS_POLYGON ( (g_SencerEnableBoss_h * g_SencerEnableBoss_v) * 2 + (4 * (g_SencerEnableBoss_v - 1)) )	//�|���S����

#define SENCERENABLEBOSS_RADIUS (90.0f)
#define SENCERENABLEBOSS_HEIGHT (8.0f)

#define MESH_H (20) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerEnableBoss(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerEnableBoss(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerEnableBoss = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerEnableBoss = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerEnableBoss = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERENABLEBOSS g_aSencerEnableBoss[MAX_SENCERENABLEBOSS];

int g_SencerEnableBoss_h, g_SencerEnableBoss_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerEnableBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerEnableBoss_h = MESH_H;
	g_SencerEnableBoss_v = MESH_V;


	MakeVertexSencerEnableBoss(pDevice);
	MakeIndexSencerEnableBoss(pDevice);

	for (int nCntSencerEnableBoss = 0; nCntSencerEnableBoss < MAX_SENCERENABLEBOSS; nCntSencerEnableBoss++)
	{
		g_aSencerEnableBoss[nCntSencerEnableBoss].fRadius = SENCERENABLEBOSS_RADIUS;
		g_aSencerEnableBoss[nCntSencerEnableBoss].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerEnableBoss(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerEnableBoss != NULL)
	{
		g_pTextureSencerEnableBoss->Release();
		g_pTextureSencerEnableBoss = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerEnableBoss != NULL)
	{
		g_pVtxBuffSencerEnableBoss->Release();
		g_pVtxBuffSencerEnableBoss = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerEnableBoss != NULL)
	{
		g_pIdxBuffSencerEnableBoss->Release();
		g_pIdxBuffSencerEnableBoss = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerEnableBoss(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerEnableBoss(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;



	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O



	for (int nCntSencerEnableBoss = 0; nCntSencerEnableBoss < MAX_SENCERENABLEBOSS; nCntSencerEnableBoss++)
	{
		if (g_aSencerEnableBoss[nCntSencerEnableBoss].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerEnableBoss[nCntSencerEnableBoss].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerEnableBoss[nCntSencerEnableBoss].rot.y, g_aSencerEnableBoss[nCntSencerEnableBoss].rot.x, g_aSencerEnableBoss[nCntSencerEnableBoss].rot.z);

			D3DXMatrixMultiply(&g_aSencerEnableBoss[nCntSencerEnableBoss].mtxWorld, &g_aSencerEnableBoss[nCntSencerEnableBoss].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerEnableBoss[nCntSencerEnableBoss].pos.x, g_aSencerEnableBoss[nCntSencerEnableBoss].pos.y, g_aSencerEnableBoss[nCntSencerEnableBoss].pos.z);

			D3DXMatrixMultiply(&g_aSencerEnableBoss[nCntSencerEnableBoss].mtxWorld, &g_aSencerEnableBoss[nCntSencerEnableBoss].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerEnableBoss[nCntSencerEnableBoss].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerEnableBoss, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerEnableBoss);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERENABLEBOSS_VERTEX, 0, SENCERENABLEBOSS_POLYGON);

		}
	}


#endif
}

//=============================================================================
// �Z���T�[�̈ʒu�ݒ�
//=============================================================================
void SetPositionSencerEnableBoss(int nIndexSencerEnableBoss, D3DXVECTOR3 pos)
{
	g_aSencerEnableBoss[nIndexSencerEnableBoss].pos.x = pos.x;
	g_aSencerEnableBoss[nIndexSencerEnableBoss].pos.y = pos.y + 30.0f;
	g_aSencerEnableBoss[nIndexSencerEnableBoss].pos.z = pos.z;

}
//=============================================================================
// �Z���T�[�̏���
//=============================================================================
void DeleteSencerEnableBoss(int nIdxSencerEnableBoss)
{
	g_aSencerEnableBoss[nIdxSencerEnableBoss].bUse = false;
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerEnableBoss(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERENABLEBOSS_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerEnableBoss,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerEnableBoss->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerEnableBoss_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerEnableBoss_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerEnableBoss_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerEnableBoss_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERENABLEBOSS_RADIUS;
			pVtx[nCntLife_V * (g_SencerEnableBoss_h + 1) + nCntLife_H].pos.y = SENCERENABLEBOSS_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerEnableBoss_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERENABLEBOSS_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerEnableBoss_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerEnableBoss_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerEnableBoss_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerEnableBoss_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerEnableBoss->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerEnableBoss(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERENABLEBOSS_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerEnableBoss,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerEnableBoss->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerEnableBoss_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerEnableBoss_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerEnableBoss_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerEnableBoss_h && nCntIndex_V <= g_SencerEnableBoss_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerEnableBoss_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerEnableBoss->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerEnableBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSencerEnableBoss;
	// ���_���̐ݒ�

	for (nCntSencerEnableBoss = 0; nCntSencerEnableBoss < MAX_SENCERENABLEBOSS; nCntSencerEnableBoss++)
	{
		if (g_aSencerEnableBoss[nCntSencerEnableBoss].bUse == false)
		{
			g_aSencerEnableBoss[nCntSencerEnableBoss].pos = pos;
			g_aSencerEnableBoss[nCntSencerEnableBoss].rot = rot;
			g_aSencerEnableBoss[nCntSencerEnableBoss].bUse = true;

			break;
		}
	}

	return nCntSencerEnableBoss;
}


//=============================================================================
// �Z���T�[����(�v���C���[�Ƃ̓����蔻��)
//=============================================================================
bool CollisionSencer_EnableBoss(D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencerEnableBoss = 0; nCntSencerEnableBoss < MAX_SENCERENABLEBOSS; nCntSencerEnableBoss++)
	{


		fxpos = (g_aSencerEnableBoss[nCntSencerEnableBoss].pos.x - pos->x) * (g_aSencerEnableBoss[nCntSencerEnableBoss].pos.x - pos->x);
		fzpos = (g_aSencerEnableBoss[nCntSencerEnableBoss].pos.z - pos->z) * (g_aSencerEnableBoss[nCntSencerEnableBoss].pos.z - pos->z);
		fRadius = SENCERENABLEBOSS_RADIUS * SENCERENABLEBOSS_RADIUS;


		if (g_aSencerEnableBoss[nCntSencerEnableBoss].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				bCol = true;
			}

		}
	}
#if  0
#endif
	return bCol;
}

