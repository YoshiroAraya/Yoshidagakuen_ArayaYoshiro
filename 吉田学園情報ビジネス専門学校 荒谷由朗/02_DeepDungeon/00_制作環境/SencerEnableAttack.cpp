//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �G�l�~�[�̒Ǐ]����Ƃ��̋���
// Author : KishidaRei 
//
//=============================================================================
#include "SencerEnableAttack.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERENABLEATTCK (5)
#define MAX_TEXTURE (2)

#define SENCERENABLEATTACK_VERTEX (  (g_SencerEnableAttack_h + 1) * (g_SencerEnableAttack_v + 1)   )	//���_��
#define SENCERENABLEATTACK_INDEX (   (g_SencerEnableAttack_h * g_SencerEnableAttack_v )* 2 + (4 * (g_SencerEnableAttack_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERENABLEATTACK_POLYGON ( (g_SencerEnableAttack_h * g_SencerEnableAttack_v) * 2 + (4 * (g_SencerEnableAttack_v - 1)) )	//�|���S����

#define SENCERENABLEATTACK_RADIUS (50.0f)
#define SENCERENABLEATTACK_HEIGHT (8.0f)

#define MESH_H (20) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerEnableAttack(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerEnableAttack(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerEnableAttack = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerEnableAttack = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerEnableAttack = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERENABLEATTACK g_aSencerEnableAttack[MAX_SENCERENABLEATTCK];

int g_SencerEnableAttack_h, g_SencerEnableAttack_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerEnableAttack(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerEnableAttack_h = MESH_H;
	g_SencerEnableAttack_v = MESH_V;


	MakeVertexSencerEnableAttack(pDevice);
	MakeIndexSencerEnableAttack(pDevice);

	for (int nCntSencerEnableAttack = 0; nCntSencerEnableAttack < MAX_SENCERENABLEATTCK; nCntSencerEnableAttack++)
	{
		g_aSencerEnableAttack[nCntSencerEnableAttack].fRadius = SENCERENABLEATTACK_RADIUS;
		g_aSencerEnableAttack[nCntSencerEnableAttack].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerEnableAttack(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerEnableAttack != NULL)
	{
		g_pTextureSencerEnableAttack->Release();
		g_pTextureSencerEnableAttack = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerEnableAttack != NULL)
	{
		g_pVtxBuffSencerEnableAttack->Release();
		g_pVtxBuffSencerEnableAttack = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerEnableAttack != NULL)
	{
		g_pIdxBuffSencerEnableAttack->Release();
		g_pIdxBuffSencerEnableAttack = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerEnableAttack(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerEnableAttack(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;



	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O



	for (int nCntSencerEnableAttack = 0; nCntSencerEnableAttack < MAX_SENCERENABLEATTCK; nCntSencerEnableAttack++)
	{
		if (g_aSencerEnableAttack[nCntSencerEnableAttack].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerEnableAttack[nCntSencerEnableAttack].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerEnableAttack[nCntSencerEnableAttack].rot.y, g_aSencerEnableAttack[nCntSencerEnableAttack].rot.x, g_aSencerEnableAttack[nCntSencerEnableAttack].rot.z);

			D3DXMatrixMultiply(&g_aSencerEnableAttack[nCntSencerEnableAttack].mtxWorld, &g_aSencerEnableAttack[nCntSencerEnableAttack].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerEnableAttack[nCntSencerEnableAttack].pos.x, g_aSencerEnableAttack[nCntSencerEnableAttack].pos.y, g_aSencerEnableAttack[nCntSencerEnableAttack].pos.z);

			D3DXMatrixMultiply(&g_aSencerEnableAttack[nCntSencerEnableAttack].mtxWorld, &g_aSencerEnableAttack[nCntSencerEnableAttack].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerEnableAttack[nCntSencerEnableAttack].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerEnableAttack, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerEnableAttack);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERENABLEATTACK_VERTEX, 0, SENCERENABLEATTACK_POLYGON);

		}
	}


#endif
}

//=============================================================================
// �Z���T�[�̈ʒu�ݒ�
//=============================================================================
void SetPositionSencerEnableAttack(int nIndexSencerEnableAttack, D3DXVECTOR3 pos)
{
	g_aSencerEnableAttack[nIndexSencerEnableAttack].pos.x = pos.x;
	g_aSencerEnableAttack[nIndexSencerEnableAttack].pos.y = pos.y + 30.0f;
	g_aSencerEnableAttack[nIndexSencerEnableAttack].pos.z = pos.z;

}
//=============================================================================
// �Z���T�[�̏���
//=============================================================================
void DeleteSencerEnableAttack(int nIdxSencerEnableAttack)
{
	g_aSencerEnableAttack[nIdxSencerEnableAttack].bUse = false;
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerEnableAttack(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERENABLEATTACK_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerEnableAttack,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerEnableAttack->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerEnableAttack_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerEnableAttack_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerEnableAttack_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerEnableAttack_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERENABLEATTACK_RADIUS;
			pVtx[nCntLife_V * (g_SencerEnableAttack_h + 1) + nCntLife_H].pos.y = SENCERENABLEATTACK_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerEnableAttack_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERENABLEATTACK_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerEnableAttack_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerEnableAttack_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerEnableAttack_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerEnableAttack_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerEnableAttack->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerEnableAttack(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERENABLEATTACK_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerEnableAttack,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerEnableAttack->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerEnableAttack_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerEnableAttack_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerEnableAttack_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerEnableAttack_h && nCntIndex_V <= g_SencerEnableAttack_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerEnableAttack_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerEnableAttack->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerEnableAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSencerEnableAttack;
	// ���_���̐ݒ�

	for (nCntSencerEnableAttack = 0; nCntSencerEnableAttack < MAX_SENCERENABLEATTCK; nCntSencerEnableAttack++)
	{
		if (g_aSencerEnableAttack[nCntSencerEnableAttack].bUse == false)
		{
			g_aSencerEnableAttack[nCntSencerEnableAttack].pos = pos;
			g_aSencerEnableAttack[nCntSencerEnableAttack].rot = rot;
			g_aSencerEnableAttack[nCntSencerEnableAttack].bUse = true;

			break;
		}
	}

	return nCntSencerEnableAttack;
}


//=============================================================================
// �Z���T�[����(�v���C���[�Ƃ̓����蔻��)
//=============================================================================
bool CollisionSencer_Enable(D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencerEnableAttack = 0; nCntSencerEnableAttack < MAX_SENCERENABLEATTCK; nCntSencerEnableAttack++)
	{


		fxpos = (g_aSencerEnableAttack[nCntSencerEnableAttack].pos.x - pos->x) * (g_aSencerEnableAttack[nCntSencerEnableAttack].pos.x - pos->x);
		fzpos = (g_aSencerEnableAttack[nCntSencerEnableAttack].pos.z - pos->z) * (g_aSencerEnableAttack[nCntSencerEnableAttack].pos.z - pos->z);
		fRadius = SENCERENABLEATTACK_RADIUS * SENCERENABLEATTACK_RADIUS;


		if (g_aSencerEnableAttack[nCntSencerEnableAttack].bUse == true)
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

