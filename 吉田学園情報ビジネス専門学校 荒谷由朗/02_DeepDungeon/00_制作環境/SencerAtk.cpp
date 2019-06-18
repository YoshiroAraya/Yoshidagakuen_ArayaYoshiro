//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �U�����̓����蔻�肪�ǂ��ɂ������Ă�̂�
// Author : KishidaRei 
//
//=============================================================================
#include "SencerAtk.h"
#include "input.h"
#include "camera.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERATK (128)
#define MAX_TEXTURE (2)

#define SENCERATK_VERTEX (  (g_SencerAtk_h + 1) * (g_SencerAtk_v + 1)   )	//���_��
#define SENCERATK_INDEX (   (g_SencerAtk_h * g_SencerAtk_v )* 2 + (4 * (g_SencerAtk_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERATK_POLYGON ( (g_SencerAtk_h * g_SencerAtk_v) * 2 + (4 * (g_SencerAtk_v - 1)) )	//�|���S����

#define SENCERATK_RADIUS (8.0f)
#define SENCERATK_HEIGHT (3.0f)

#define MESH_H (20) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerAtk(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerAtk(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerAtk = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerAtk = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerAtk = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERATK g_aSencerAtk[MAX_SENCERATK];

int g_SencerAtk_h, g_SencerAtk_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerAtk(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerAtk_h = MESH_H;
	g_SencerAtk_v = MESH_V;


	MakeVertexSencerAtk(pDevice);
	MakeIndexSencerAtk(pDevice);

	for (int nCntSencerAtk = 0; nCntSencerAtk < MAX_SENCERATK; nCntSencerAtk++)
	{
		g_aSencerAtk[nCntSencerAtk].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSencerAtk[nCntSencerAtk].rot = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);
		g_aSencerAtk[nCntSencerAtk].fRadius = SENCERATK_RADIUS;
		g_aSencerAtk[nCntSencerAtk].nIdxParent = -1;
		g_aSencerAtk[nCntSencerAtk].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerAtk(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerAtk != NULL)
	{
		g_pTextureSencerAtk->Release();
		g_pTextureSencerAtk = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerAtk != NULL)
	{
		g_pVtxBuffSencerAtk->Release();
		g_pVtxBuffSencerAtk = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerAtk != NULL)
	{
		g_pIdxBuffSencerAtk->Release();
		g_pIdxBuffSencerAtk = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerAtk(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerAtk(void)
{
#if 1
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;
	D3DXMATRIX mtxParent;						// �e���f���̏��


	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O

	

	for (int nCntSencerAtk = 0; nCntSencerAtk < MAX_SENCERATK; nCntSencerAtk++)
	{
		if (g_aSencerAtk[nCntSencerAtk].bUse == true)
		{
			if (g_aSencerAtk[nCntSencerAtk].nIdxParent == -1)
			{
				mtxParent = pPlayer->aModel[16].mtxWorldPlayerModel;
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerAtk[nCntSencerAtk].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerAtk[nCntSencerAtk].rot.y, g_aSencerAtk[nCntSencerAtk].rot.x, g_aSencerAtk[nCntSencerAtk].rot.z);

			D3DXMatrixMultiply(&g_aSencerAtk[nCntSencerAtk].mtxWorld, &g_aSencerAtk[nCntSencerAtk].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerAtk[nCntSencerAtk].pos.x, g_aSencerAtk[nCntSencerAtk].pos.y, g_aSencerAtk[nCntSencerAtk].pos.z);

			D3DXMatrixMultiply(&g_aSencerAtk[nCntSencerAtk].mtxWorld, &g_aSencerAtk[nCntSencerAtk].mtxWorld, &mtxtrans);
			
			//�e�̃}�g���b�N�X���f
			D3DXMatrixMultiply(&g_aSencerAtk[nCntSencerAtk].mtxWorld, &g_aSencerAtk[nCntSencerAtk].mtxWorld, &mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerAtk[nCntSencerAtk].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerAtk, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerAtk);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERATK_VERTEX, 0, SENCERATK_POLYGON);

		}
	}


#endif
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerAtk(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERATK_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerAtk,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerAtk->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerAtk_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerAtk_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerAtk_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerAtk_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERATK_RADIUS;
			pVtx[nCntLife_V * (g_SencerAtk_h + 1) + nCntLife_H].pos.y = SENCERATK_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerAtk_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERATK_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerAtk_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerAtk_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerAtk_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerAtk_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerAtk->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerAtk(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERATK_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerAtk,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerAtk->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerAtk_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerAtk_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerAtk_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerAtk_h && nCntIndex_V <= g_SencerAtk_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerAtk_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerAtk->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
void SetSencerAtk(D3DXVECTOR3 pos)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerAtk->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSencerAtk = 0; nCntSencerAtk < MAX_SENCERATK; nCntSencerAtk++)
	{
		if (g_aSencerAtk[nCntSencerAtk].bUse == false)
		{
			g_aSencerAtk[nCntSencerAtk].pos = pos ;
			
			g_aSencerAtk[nCntSencerAtk].bUse = true;

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerAtk->Unlock();
}


//=============================================================================
// �����蔻��
//=============================================================================
bool CollisionSencerAtk(float *fRadius, D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadiusSum = 0.0f;

	for (int nCntSencerAtk = 0; nCntSencerAtk < MAX_SENCERATK; nCntSencerAtk++)
	{
		//fxpos = (g_aSencerAtk[nCntSencerAtk].pos.x - pos->x) * (g_aSencerAtk[nCntSencerAtk].pos.x - pos->x);
		//fzpos = (g_aSencerAtk[nCntSencerAtk].pos.z - pos->z) * (g_aSencerAtk[nCntSencerAtk].pos.z - pos->z);
		fxpos = (pos->x - g_aSencerAtk[nCntSencerAtk].pos.x) * (pos->x - g_aSencerAtk[nCntSencerAtk].pos.x);
		fzpos = (pos->z - g_aSencerAtk[nCntSencerAtk].pos.z) * (pos->z - g_aSencerAtk[nCntSencerAtk].pos.z);
		float fRadiusSum = (SENCERATK_RADIUS + *fRadius) * (SENCERATK_RADIUS + *fRadius);

		if (g_aSencerAtk[nCntSencerAtk].bUse == true)
		{
			if (fxpos + fzpos <= *fRadius)
			{
				bCol = true;
			}

		}
	}
	return bCol;
	
}
//=============================================================================
// �Z���T�[����
//=============================================================================
bool CollisionSencerAtk(D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencerAtk = 0; nCntSencerAtk < MAX_SENCERATK; nCntSencerAtk++)
	{
		//fxpos = powf((pos->x - g_aSencerAtk[nCntSencerAtk].pos.x), 2.0f);
		//fzpos = powf((pos->z - g_aSencerAtk[nCntSencerAtk].pos.z), 2.0f);
		//fpos = fxpos + fzpos;
		//fRadius = powf(SENCERATK_RADIUS, 2.0f);

		fxpos = (g_aSencerAtk[nCntSencerAtk].pos.x - pos->x) * (g_aSencerAtk[nCntSencerAtk].pos.x - pos->x);
		fzpos = (g_aSencerAtk[nCntSencerAtk].pos.z - pos->z) * (g_aSencerAtk[nCntSencerAtk].pos.z - pos->z);
		fRadius = SENCERATK_RADIUS * SENCERATK_RADIUS;


		//fxpos = (pos->x - g_aSencerAtk[nCntSencerAtk].pos.x);
		//fzpos = (pos->z - g_aSencerAtk[nCntSencerAtk].pos.z);
		//fpos = fxpos + fzpos;
		//fRadius = SENCERATK_RADIUS;
		if (g_aSencerAtk[nCntSencerAtk].bUse == true)
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
