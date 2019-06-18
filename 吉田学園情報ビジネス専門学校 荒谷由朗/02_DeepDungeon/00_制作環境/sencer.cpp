//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: ���@�w�Ƃ̓����蔻��p
// Author : KishidaRei 
//
//=============================================================================
#include "sencer.h"
#include "input.h"
#include "camera.h"
#include "SencerAtk.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCER (50)
#define MAX_TEXTURE (2)
	
#define SENCER_VERTEX (  (g_Sencer_h + 1) * (g_Sencer_v + 1)   )	//���_��
#define SENCER_INDEX (   (g_Sencer_h * g_Sencer_v )* 2 + (4 * (g_Sencer_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCER_POLYGON ( (g_Sencer_h * g_Sencer_v) * 2 + (4 * (g_Sencer_v - 1)) )	//�|���S����

#define SENCER_RADIUS (120.0f)
#define SENCER_HEIGHT (90.0f)

#define MESH_H (50) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencer(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencer = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCER g_aSencer[MAX_SENCER];

int g_Sencer_h, g_Sencer_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_Sencer_h = MESH_H;
	g_Sencer_v = MESH_V;


	MakeVertexSencer(pDevice);
	MakeIndexSencer(pDevice);

	for (int nCntSencer = 0; nCntSencer < MAX_SENCER; nCntSencer++)
	{
		g_aSencer[nCntSencer].fRadius = SENCER_RADIUS;
		g_aSencer[nCntSencer].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencer(void)
{
	
		//�e�N�X�`���̔j��
		if (g_pTextureSencer != NULL)
		{
			g_pTextureSencer->Release();
			g_pTextureSencer = NULL;
		}
	
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencer != NULL)
	{
		g_pVtxBuffSencer->Release();
		g_pVtxBuffSencer = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencer != NULL)
	{
		g_pIdxBuffSencer->Release();
		g_pIdxBuffSencer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencer(void)
{
	
	for (int nCntSencer = 0; nCntSencer < MAX_SENCER; nCntSencer++)
	{
		CollisionSencerAtk(&g_aSencer[nCntSencer].fRadius, &g_aSencer[nCntSencer].pos);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencer(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;


	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O

	

	for (int nCntSencer = 0; nCntSencer < MAX_SENCER; nCntSencer++)
	{
		if (g_aSencer[nCntSencer].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencer[nCntSencer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencer[nCntSencer].rot.y, g_aSencer[nCntSencer].rot.x, g_aSencer[nCntSencer].rot.z);

			D3DXMatrixMultiply(&g_aSencer[nCntSencer].mtxWorld, &g_aSencer[nCntSencer].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencer[nCntSencer].pos.x, g_aSencer[nCntSencer].pos.y, g_aSencer[nCntSencer].pos.z);

			D3DXMatrixMultiply(&g_aSencer[nCntSencer].mtxWorld, &g_aSencer[nCntSencer].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencer[nCntSencer].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencer, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencer);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCER_VERTEX, 0, SENCER_POLYGON);

		}
	}

#endif	
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencer(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencer,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencer->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_Sencer_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_Sencer_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_Sencer_h + 1; nCntLife_H++)
		{
			
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_Sencer_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCER_RADIUS;
				pVtx[nCntLife_V * (g_Sencer_h + 1) + nCntLife_H].pos.y = SENCER_HEIGHT * nCntLife_V;				
				pVtx[nCntLife_V * (g_Sencer_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCER_RADIUS;
				//�@���̐ݒ�
				pVtx[nCntLife_V * (g_Sencer_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[
				pVtx[nCntLife_V * (g_Sencer_h + 1) + nCntLife_H].col = D3DXCOLOR(1.0f, 0.0f, 0.8f, 0.1f);
				
				//�e�N�X�`�����W
				pVtx[nCntLife_V * (g_Sencer_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_Sencer_h / 2)), nCntLife_V * -1.0f);

				fDestAngle += fAngle;
			}
			
		
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencer->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencer(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencer,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencer->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_Sencer_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_Sencer_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_Sencer_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_Sencer_h && nCntIndex_V <= g_Sencer_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_Sencer_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencer->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SENCERTYPE type)
{
	// ���_���̐ݒ�
	//VERTEX_3D *pVtx;
	int nCntSencer;
	
	for ( nCntSencer = 0; nCntSencer < MAX_SENCER; nCntSencer++)
	{
		if (g_aSencer[nCntSencer].bUse == false)
		{
			g_aSencer[nCntSencer].pos = pos;
			g_aSencer[nCntSencer].rot = rot;
			g_aSencer[nCntSencer].type = type;
			g_aSencer[nCntSencer].bUse = true;

			break;
		}
	}

	return nCntSencer;
}
//=============================================================================
// �Z���T�[����(�v���C���[�ƃZ���T�[�̂̔���)
//=============================================================================
bool CollisionSencer(D3DXVECTOR3 *pos)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCER; nCntSencer++)
	{
		

		fxpos = (g_aSencer[nCntSencer].pos.x - pos->x) * (g_aSencer[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencer[nCntSencer].pos.z - pos->z) * (g_aSencer[nCntSencer].pos.z - pos->z);
		fRadius = SENCER_RADIUS * SENCER_RADIUS;


		
		if (g_aSencer[nCntSencer].bUse == true)
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
//=============================================================================
// �Z���T�[����(nCnt��Ԃ�)
//=============================================================================
int CollisionSencerReturnCnt(D3DXVECTOR3 * pos)
{
	int nCntSencer = 0;

	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for ( int Sencer = 0; Sencer < MAX_SENCER; Sencer++)
	{
		if (g_aSencer[Sencer].bUse == true)
		{

			fxpos = (g_aSencer[Sencer].pos.x - pos->x) * (g_aSencer[Sencer].pos.x - pos->x);
			fzpos = (g_aSencer[Sencer].pos.z - pos->z) * (g_aSencer[Sencer].pos.z - pos->z);
			fRadius = SENCER_RADIUS * SENCER_RADIUS;

			if (fxpos + fzpos <= fRadius)
			{
				nCntSencer = Sencer;

			}


		}
	}
	return nCntSencer;
}
//=============================================================================
// �Z���T�[������
//=============================================================================
void DeleteSencer(int nIdxSencer)
{
	g_aSencer[nIdxSencer].bUse = false;
}


