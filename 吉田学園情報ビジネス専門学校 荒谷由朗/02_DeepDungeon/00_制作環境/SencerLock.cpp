//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �v���C���[�̃��b�N�I���ł��鋗��
// Author : KishidaRei 
//
//=============================================================================
#include "SencerLock.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERLOCK (5)
#define MAX_TEXTURE (2)

#define SENCERLOCK_VERTEX (  (g_SencerLock_h + 1) * (g_SencerLock_v + 1)   )	//���_��
#define SENCERLOCK_INDEX (   (g_SencerLock_h * g_SencerLock_v )* 2 + (4 * (g_SencerLock_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERLOCK_POLYGON ( (g_SencerLock_h * g_SencerLock_v) * 2 + (4 * (g_SencerLock_v - 1)) )	//�|���S����

#define SENCERLOCK_RADIUS (200.0f)
#define SENCERLOCK_HEIGHT (8.0f)

#define MESH_H (30) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerLock(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerLock(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerLock = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerLock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerLock = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERLOCK g_aSencerLock[MAX_SENCERLOCK];

int g_SencerLock_h, g_SencerLock_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerLock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerLock_h = MESH_H;
	g_SencerLock_v = MESH_V;


	MakeVertexSencerLock(pDevice);
	MakeIndexSencerLock(pDevice);

	for (int nCntSencerLock = 0; nCntSencerLock < MAX_SENCERLOCK; nCntSencerLock++)
	{
		g_aSencerLock[nCntSencerLock].fRadius = SENCERLOCK_RADIUS;
		g_aSencerLock[nCntSencerLock].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerLock(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerLock != NULL)
	{
		g_pTextureSencerLock->Release();
		g_pTextureSencerLock = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerLock != NULL)
	{
		g_pVtxBuffSencerLock->Release();
		g_pVtxBuffSencerLock = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerLock != NULL)
	{
		g_pIdxBuffSencerLock->Release();
		g_pIdxBuffSencerLock = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerLock(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerLock(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;



	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O



	for (int nCntSencerLock = 0; nCntSencerLock < MAX_SENCERLOCK; nCntSencerLock++)
	{
		if (g_aSencerLock[nCntSencerLock].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerLock[nCntSencerLock].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerLock[nCntSencerLock].rot.y, g_aSencerLock[nCntSencerLock].rot.x, g_aSencerLock[nCntSencerLock].rot.z);

			D3DXMatrixMultiply(&g_aSencerLock[nCntSencerLock].mtxWorld, &g_aSencerLock[nCntSencerLock].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerLock[nCntSencerLock].pos.x, g_aSencerLock[nCntSencerLock].pos.y, g_aSencerLock[nCntSencerLock].pos.z);

			D3DXMatrixMultiply(&g_aSencerLock[nCntSencerLock].mtxWorld, &g_aSencerLock[nCntSencerLock].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerLock[nCntSencerLock].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerLock, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerLock);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERLOCK_VERTEX, 0, SENCERLOCK_POLYGON);

		}
	}


#endif
}

//=============================================================================
// �Z���T�[�̈ʒu�ݒ�
//=============================================================================
void SetPositionSencerLock(int nIdxSencer, D3DXVECTOR3 pos)
{
	g_aSencerLock[nIdxSencer].pos.x = pos.x;
	g_aSencerLock[nIdxSencer].pos.y = pos.y;

	g_aSencerLock[nIdxSencer].pos.z = pos.z;

}
//=============================================================================
// �Z���T�[�̏���
//=============================================================================
void DeleteSencerLock(int nIdxSencerLock)
{
	g_aSencerLock[nIdxSencerLock].bUse = false;
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerLock(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERLOCK_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerLock,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerLock->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerLock_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerLock_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerLock_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerLock_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERLOCK_RADIUS;
			pVtx[nCntLife_V * (g_SencerLock_h + 1) + nCntLife_H].pos.y = SENCERLOCK_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerLock_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERLOCK_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerLock_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerLock_h + 1) + nCntLife_H].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerLock_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerLock_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerLock->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerLock(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERLOCK_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerLock,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerLock->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerLock_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerLock_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerLock_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerLock_h && nCntIndex_V <= g_SencerLock_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerLock_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerLock->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerLock(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSencerLock;
	// ���_���̐ݒ�

	for (nCntSencerLock = 0; nCntSencerLock < MAX_SENCERLOCK; nCntSencerLock++)
	{
		if (g_aSencerLock[nCntSencerLock].bUse == false)
		{
			g_aSencerLock[nCntSencerLock].pos = pos;
			g_aSencerLock[nCntSencerLock].rot = rot;
			g_aSencerLock[nCntSencerLock].bUse = true;

			break;
		}
	}

	return nCntSencerLock;
}

//=============================================================================
// �Z���T�[����i�ǂ̃G�l�~�[���̐�����Ԃ��j
//=============================================================================
int CollisionSencer_Lock_ReturnEnemy(D3DXVECTOR3 * pos, int nCntEnemy)
{
	bool bCol = false;
	int nCnt = 0;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencerLock = 0; nCntSencerLock < MAX_SENCERLOCK; nCntSencerLock++)
	{


		fxpos = (g_aSencerLock[nCntSencerLock].pos.x - pos->x) * (g_aSencerLock[nCntSencerLock].pos.x - pos->x);
		fzpos = (g_aSencerLock[nCntSencerLock].pos.z - pos->z) * (g_aSencerLock[nCntSencerLock].pos.z - pos->z);
		fRadius = SENCERLOCK_RADIUS * SENCERLOCK_RADIUS;


		if (g_aSencerLock[nCntSencerLock].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				bCol = true;
				nCnt = nCntEnemy;
			}

		}
	}
	return nCnt;

}

//=============================================================================
// �Z���T�[����(�G�Ƃ̓����蔻��)
//=============================================================================
bool CollisionSencer_Lock(D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencerLock = 0; nCntSencerLock < MAX_SENCERLOCK; nCntSencerLock++)
	{


		fxpos = (g_aSencerLock[nCntSencerLock].pos.x - pos->x) * (g_aSencerLock[nCntSencerLock].pos.x - pos->x);
		fzpos = (g_aSencerLock[nCntSencerLock].pos.z - pos->z) * (g_aSencerLock[nCntSencerLock].pos.z - pos->z);
		fRadius = SENCERLOCK_RADIUS * SENCERLOCK_RADIUS;


		if (g_aSencerLock[nCntSencerLock].bUse == true)
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

