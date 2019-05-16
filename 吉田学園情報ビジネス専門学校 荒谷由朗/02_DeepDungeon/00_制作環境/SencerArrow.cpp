//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �G�l�~�[�̒Ǐ]����Ƃ��̋���
// Author : KishidaRei 
//
//=============================================================================
#include "SencerArrow.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERENEMYARROW (5)
#define MAX_TEXTURE (2)

#define SENCERENEMYARROW_VERTEX (  (g_SencerEnemyArrow_h + 1) * (g_SencerEnemyArrow_v + 1)   )	//���_��
#define SENCERENEMYARROW_INDEX (   (g_SencerEnemyArrow_h * g_SencerEnemyArrow_v )* 2 + (4 * (g_SencerEnemyArrow_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERENEMYARROW_POLYGON ( (g_SencerEnemyArrow_h * g_SencerEnemyArrow_v) * 2 + (4 * (g_SencerEnemyArrow_v - 1)) )	//�|���S����

#define SENCERENEMYARROW_RADIUS (600.0f)
#define SENCERENEMYARROW_HEIGHT (8.0f)

#define MESH_H (20) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerEnemyArrow(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerEnemyArrow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerEnemyArrow = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerEnemyArrow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerEnemyArrow = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERARROW g_aSencerEnemyArow[MAX_SENCERENEMYARROW];

int g_SencerEnemyArrow_h, g_SencerEnemyArrow_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerEnemyArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerEnemyArrow_h = MESH_H;
	g_SencerEnemyArrow_v = MESH_V;


	MakeVertexSencerEnemyArrow(pDevice);
	MakeIndexSencerEnemyArrow(pDevice);

	for (int nCntSencerEnemyArrow = 0; nCntSencerEnemyArrow < MAX_SENCERENEMYARROW; nCntSencerEnemyArrow++)
	{
		g_aSencerEnemyArow[nCntSencerEnemyArrow].fRadius = SENCERENEMYARROW_RADIUS;
		g_aSencerEnemyArow[nCntSencerEnemyArrow].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerEnemyArrow(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerEnemyArrow != NULL)
	{
		g_pTextureSencerEnemyArrow->Release();
		g_pTextureSencerEnemyArrow = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerEnemyArrow != NULL)
	{
		g_pVtxBuffSencerEnemyArrow->Release();
		g_pVtxBuffSencerEnemyArrow = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerEnemyArrow != NULL)
	{
		g_pIdxBuffSencerEnemyArrow->Release();
		g_pIdxBuffSencerEnemyArrow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerEnemyArrow(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerEnemyArrow(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;



	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O



	for (int nCntSencerEnemyArrow = 0; nCntSencerEnemyArrow < MAX_SENCERENEMYARROW; nCntSencerEnemyArrow++)
	{
		if (g_aSencerEnemyArow[nCntSencerEnemyArrow].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerEnemyArow[nCntSencerEnemyArrow].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerEnemyArow[nCntSencerEnemyArrow].rot.y, g_aSencerEnemyArow[nCntSencerEnemyArrow].rot.x, g_aSencerEnemyArow[nCntSencerEnemyArrow].rot.z);

			D3DXMatrixMultiply(&g_aSencerEnemyArow[nCntSencerEnemyArrow].mtxWorld, &g_aSencerEnemyArow[nCntSencerEnemyArrow].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.x, g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.y, g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.z);

			D3DXMatrixMultiply(&g_aSencerEnemyArow[nCntSencerEnemyArrow].mtxWorld, &g_aSencerEnemyArow[nCntSencerEnemyArrow].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerEnemyArow[nCntSencerEnemyArrow].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerEnemyArrow, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerEnemyArrow);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERENEMYARROW_VERTEX, 0, SENCERENEMYARROW_POLYGON);

		}
	}


#endif
}

//=============================================================================
// �Z���T�[�̈ʒu�ݒ�
//=============================================================================
void SetPositionSencerEnemyArrow(int nIndexSencerEnemy, D3DXVECTOR3 pos)
{
	g_aSencerEnemyArow[nIndexSencerEnemy].pos.x = pos.x;
	g_aSencerEnemyArow[nIndexSencerEnemy].pos.y = pos.y + 30.0f;
	g_aSencerEnemyArow[nIndexSencerEnemy].pos.z = pos.z;

}
//=============================================================================
// �Z���T�[�̏���
//=============================================================================
void DeleteSencerEnemyArrow(int nIdxSencerEnemy)
{
	g_aSencerEnemyArow[nIdxSencerEnemy].bUse = false;
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerEnemyArrow(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERENEMYARROW_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerEnemyArrow,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerEnemyArrow->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerEnemyArrow_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerEnemyArrow_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerEnemyArrow_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerEnemyArrow_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERENEMYARROW_RADIUS;
			pVtx[nCntLife_V * (g_SencerEnemyArrow_h + 1) + nCntLife_H].pos.y = SENCERENEMYARROW_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerEnemyArrow_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERENEMYARROW_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerEnemyArrow_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerEnemyArrow_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerEnemyArrow_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerEnemyArrow_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerEnemyArrow->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerEnemyArrow(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERENEMYARROW_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerEnemyArrow,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerEnemyArrow->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerEnemyArrow_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerEnemyArrow_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerEnemyArrow_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerEnemyArrow_h && nCntIndex_V <= g_SencerEnemyArrow_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerEnemyArrow_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerEnemyArrow->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerEnemyArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSencerEnemyArrow;
	// ���_���̐ݒ�

	for (nCntSencerEnemyArrow = 0; nCntSencerEnemyArrow < MAX_SENCERENEMYARROW; nCntSencerEnemyArrow++)
	{
		if (g_aSencerEnemyArow[nCntSencerEnemyArrow].bUse == false)
		{
			g_aSencerEnemyArow[nCntSencerEnemyArrow].pos = pos;
			g_aSencerEnemyArow[nCntSencerEnemyArrow].rot = rot;
			g_aSencerEnemyArow[nCntSencerEnemyArrow].bUse = true;

			break;
		}
	}

	return nCntSencerEnemyArrow;
}


//=============================================================================
// �Z���T�[����(�v���C���[�Ƃ̓����蔻��)
//=============================================================================
bool CollisionSencer_EnemyArrow(D3DXVECTOR3 *pos, int nCntSencerEnemyArrow)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;



	fxpos = (g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.x - pos->x) * (g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.x - pos->x);
	fzpos = (g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.z - pos->z) * (g_aSencerEnemyArow[nCntSencerEnemyArrow].pos.z - pos->z);
	fRadius = SENCERENEMYARROW_RADIUS * SENCERENEMYARROW_RADIUS;


	if (g_aSencerEnemyArow[nCntSencerEnemyArrow].bUse == true)
	{
		if (fxpos + fzpos <= fRadius)
		{
			bCol = true;
		}

	}
	return bCol;
}

