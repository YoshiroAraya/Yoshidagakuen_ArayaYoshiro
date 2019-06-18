//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �G�l�~�[�̒Ǐ]����Ƃ��̋���
// Author : KishidaRei 
//
//=============================================================================
#include "SencerEnemy.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERENEMY (5)
#define MAX_TEXTURE (2)

#define SENCERENEMY_VERTEX (  (g_SencerEnemy_h + 1) * (g_SencerEnemy_v + 1)   )	//���_��
#define SENCERENEMY_INDEX (   (g_SencerEnemy_h * g_SencerEnemy_v )* 2 + (4 * (g_SencerEnemy_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERENEMY_POLYGON ( (g_SencerEnemy_h * g_SencerEnemy_v) * 2 + (4 * (g_SencerEnemy_v - 1)) )	//�|���S����

#define SENCERENEMY_RADIUS (300.0f)
#define SENCERENEMY_HEIGHT (8.0f)

#define MESH_H (20) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerEnemy(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerEnemy(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerEnemy = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerEnemy = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerEnemy = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERENEMY g_aSencerEnemy[MAX_SENCERENEMY];

int g_SencerEnemy_h, g_SencerEnemy_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerEnemy_h = MESH_H;
	g_SencerEnemy_v = MESH_V;


	MakeVertexSencerEnemy(pDevice);
	MakeIndexSencerEnemy(pDevice);

	for (int nCntSencerEnemy = 0; nCntSencerEnemy < MAX_SENCERENEMY; nCntSencerEnemy++)
	{
		g_aSencerEnemy[nCntSencerEnemy].fRadius = SENCERENEMY_RADIUS;
		g_aSencerEnemy[nCntSencerEnemy].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerEnemy(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerEnemy != NULL)
	{
		g_pTextureSencerEnemy->Release();
		g_pTextureSencerEnemy = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerEnemy != NULL)
	{
		g_pVtxBuffSencerEnemy->Release();
		g_pVtxBuffSencerEnemy = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerEnemy != NULL)
	{
		g_pIdxBuffSencerEnemy->Release();
		g_pIdxBuffSencerEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerEnemy(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerEnemy(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;



	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O



	for (int nCntSencerEnemy = 0; nCntSencerEnemy < MAX_SENCERENEMY; nCntSencerEnemy++)
	{
		if (g_aSencerEnemy[nCntSencerEnemy].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerEnemy[nCntSencerEnemy].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerEnemy[nCntSencerEnemy].rot.y, g_aSencerEnemy[nCntSencerEnemy].rot.x, g_aSencerEnemy[nCntSencerEnemy].rot.z);

			D3DXMatrixMultiply(&g_aSencerEnemy[nCntSencerEnemy].mtxWorld, &g_aSencerEnemy[nCntSencerEnemy].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerEnemy[nCntSencerEnemy].pos.x, g_aSencerEnemy[nCntSencerEnemy].pos.y, g_aSencerEnemy[nCntSencerEnemy].pos.z);

			D3DXMatrixMultiply(&g_aSencerEnemy[nCntSencerEnemy].mtxWorld, &g_aSencerEnemy[nCntSencerEnemy].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerEnemy[nCntSencerEnemy].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerEnemy, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerEnemy);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERENEMY_VERTEX, 0, SENCERENEMY_POLYGON);

		}
	}


#endif
}

//=============================================================================
// �Z���T�[�̈ʒu�ݒ�
//=============================================================================
void SetPositionSencerEnemy(int nIndexSencerEnemy, D3DXVECTOR3 pos)
{
	g_aSencerEnemy[nIndexSencerEnemy].pos.x = pos.x;
	g_aSencerEnemy[nIndexSencerEnemy].pos.y = pos.y + 30.0f;
	g_aSencerEnemy[nIndexSencerEnemy].pos.z = pos.z;

}
//=============================================================================
// �Z���T�[�̏���
//=============================================================================
void DeleteSencerEnemy(int nIdxSencerEnemy)
{
	g_aSencerEnemy[nIdxSencerEnemy].bUse = false;
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERENEMY_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerEnemy,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerEnemy->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerEnemy_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerEnemy_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerEnemy_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerEnemy_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERENEMY_RADIUS;
			pVtx[nCntLife_V * (g_SencerEnemy_h + 1) + nCntLife_H].pos.y = SENCERENEMY_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerEnemy_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERENEMY_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerEnemy_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerEnemy_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerEnemy_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerEnemy_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerEnemy->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERENEMY_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerEnemy,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerEnemy->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerEnemy_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerEnemy_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerEnemy_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerEnemy_h && nCntIndex_V <= g_SencerEnemy_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerEnemy_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerEnemy->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSencerEnemy;
	// ���_���̐ݒ�

	for (nCntSencerEnemy = 0; nCntSencerEnemy < MAX_SENCERENEMY; nCntSencerEnemy++)
	{
		if (g_aSencerEnemy[nCntSencerEnemy].bUse == false)
		{
			g_aSencerEnemy[nCntSencerEnemy].pos = pos;
			g_aSencerEnemy[nCntSencerEnemy].rot = rot;
			g_aSencerEnemy[nCntSencerEnemy].bUse = true;

			break;
		}
	}

	return nCntSencerEnemy;
}


//=============================================================================
// �Z���T�[����(�v���C���[�Ƃ̓����蔻��)
//=============================================================================
bool CollisionSencer_Enemy(D3DXVECTOR3 *pos, int nCntSencerEnemy)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	


		fxpos = (g_aSencerEnemy[nCntSencerEnemy].pos.x - pos->x) * (g_aSencerEnemy[nCntSencerEnemy].pos.x - pos->x);
		fzpos = (g_aSencerEnemy[nCntSencerEnemy].pos.z - pos->z) * (g_aSencerEnemy[nCntSencerEnemy].pos.z - pos->z);
		fRadius = SENCERENEMY_RADIUS * SENCERENEMY_RADIUS;


		if (g_aSencerEnemy[nCntSencerEnemy].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				bCol = true;
			}

		}
	return bCol;
}

