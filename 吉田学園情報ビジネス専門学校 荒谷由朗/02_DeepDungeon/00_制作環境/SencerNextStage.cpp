//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: ���@�w�Ƃ̓����蔻��p
// Author : KishidaRei 
//
//=============================================================================
#include "SencerNextStage.h"
#include "input.h"
#include "camera.h"
#include "SencerAtk.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERNEXT (50)
#define MAX_TEXTURE (2)

#define SENCERNEXT_VERTEX (  (g_SencerNext_h + 1) * (g_SencerNext_v + 1)   )	//���_��
#define SENCERNEXT_INDEX (   (g_SencerNext_h * g_SencerNext_v )* 2 + (4 * (g_SencerNext_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERNEXT_POLYGON ( (g_SencerNext_h * g_SencerNext_v) * 2 + (4 * (g_SencerNext_v - 1)) )	//�|���S����

#define SENCERNEXT_RADIUS (100.0f)
#define SENCERNEXT_HEIGHT (30.0f)

#define MESH_H (50) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerNext(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerNext(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerNext = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerNext = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerNext = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERNEXT g_aSencerNext[MAX_SENCERNEXT];

int g_SencerNext_h, g_SencerNext_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerNext(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerNext_h = MESH_H;
	g_SencerNext_v = MESH_V;


	MakeVertexSencerNext(pDevice);
	MakeIndexSencerNext(pDevice);

	for (int nCntSencer = 0; nCntSencer < MAX_SENCERNEXT; nCntSencer++)
	{
		g_aSencerNext[nCntSencer].fRadius = SENCERNEXT_RADIUS;
		g_aSencerNext[nCntSencer].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerNext(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerNext != NULL)
	{
		g_pTextureSencerNext->Release();
		g_pTextureSencerNext = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerNext != NULL)
	{
		g_pVtxBuffSencerNext->Release();
		g_pVtxBuffSencerNext = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerNext != NULL)
	{
		g_pIdxBuffSencerNext->Release();
		g_pIdxBuffSencerNext = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerNext(void)
{

	for (int nCntSencer = 0; nCntSencer < MAX_SENCERNEXT; nCntSencer++)
	{
		CollisionSencerAtk(&g_aSencerNext[nCntSencer].fRadius, &g_aSencerNext[nCntSencer].pos);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerNext(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;



	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O



	for (int nCntSencer = 0; nCntSencer < MAX_SENCERNEXT; nCntSencer++)
	{
		if (g_aSencerNext[nCntSencer].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerNext[nCntSencer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerNext[nCntSencer].rot.y, g_aSencerNext[nCntSencer].rot.x, g_aSencerNext[nCntSencer].rot.z);

			D3DXMatrixMultiply(&g_aSencerNext[nCntSencer].mtxWorld, &g_aSencerNext[nCntSencer].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerNext[nCntSencer].pos.x, g_aSencerNext[nCntSencer].pos.y, g_aSencerNext[nCntSencer].pos.z);

			D3DXMatrixMultiply(&g_aSencerNext[nCntSencer].mtxWorld, &g_aSencerNext[nCntSencer].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerNext[nCntSencer].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerNext, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerNext);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERNEXT_VERTEX, 0, SENCERNEXT_POLYGON);

		}
	}

#endif	
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerNext(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERNEXT_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerNext,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerNext->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerNext_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerNext_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerNext_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerNext_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERNEXT_RADIUS;
			pVtx[nCntLife_V * (g_SencerNext_h + 1) + nCntLife_H].pos.y = SENCERNEXT_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerNext_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERNEXT_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerNext_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerNext_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerNext_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerNext_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerNext->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerNext(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERNEXT_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerNext,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerNext->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerNext_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerNext_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerNext_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerNext_h && nCntIndex_V <= g_SencerNext_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerNext_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerNext->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerNext(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���_���̐ݒ�
	//VERTEX_3D *pVtx;
	int nCntSencer;

	for (nCntSencer = 0; nCntSencer < MAX_SENCERNEXT; nCntSencer++)
	{
		if (g_aSencerNext[nCntSencer].bUse == false)
		{
			g_aSencerNext[nCntSencer].pos = pos;
			g_aSencerNext[nCntSencer].rot = rot;
			g_aSencerNext[nCntSencer].bUse = true;

			break;
		}
	}

	return nCntSencer;
}
//=============================================================================
// �Z���T�[����(�v���C���[�ƃZ���T�[�̂̔���)
//=============================================================================
bool CollisionSencerNext(D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERNEXT; nCntSencer++)
	{


		fxpos = (g_aSencerNext[nCntSencer].pos.x - pos->x) * (g_aSencerNext[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerNext[nCntSencer].pos.z - pos->z) * (g_aSencerNext[nCntSencer].pos.z - pos->z);
		fRadius = SENCERNEXT_RADIUS * SENCERNEXT_RADIUS;



		if (g_aSencerNext[nCntSencer].bUse == true)
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

void DeleteSencerNext(int nCnt)
{
	g_aSencerNext[nCnt].bUse = false;
}
