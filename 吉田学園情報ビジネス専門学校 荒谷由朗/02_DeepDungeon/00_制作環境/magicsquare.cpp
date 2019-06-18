//=============================================================================
//
// �e���ˏ��� [MagicSquare.cpp]
// Author : 
//
//=============================================================================
#include "magicsquare.h"
#include "input.h"
#include "player.h"
#include "brazen.h"
#include "sencer.h"
#include "life.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAGICSQUARE_TEXTURENAME	"data/TEXTURE/magicsquare.jpg"	// �t�@�C����
#define MAX_MAGICSQUARE			(10)							// ���@�w�̍ő吔
#define MAGICAQUARE_WIDTH		(120.0f)							// ���@�w�̕�
#define MAGICSQUARE_DEPTH		(120.0f)							// ���@�w�̉��s


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMagicSquare(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMagicSquare = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagicSquare = NULL;	//���_�o�b�t�@�ւ̃|�C���^

MAGICSQUARE g_aMagicSquare[MAX_MAGICSQUARE];

float fDestCol;
float fCol;
//=============================================================================
// ����������
//=============================================================================
void InitMagicSquare(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntMagicSquare = 0; nCntMagicSquare < MAX_MAGICSQUARE; nCntMagicSquare++)
	{
		g_aMagicSquare[nCntMagicSquare].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagicSquare[nCntMagicSquare].col = D3DXCOLOR(1.0f, 0.0f, 0.9f, 1.0f);
		g_aMagicSquare[nCntMagicSquare].bUse = false;
	}

	MakeVertexMagicSquare(pDevice);






}

//=============================================================================
// �I������
//=============================================================================
void UninitMagicSquare(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMagicSquare != NULL)
	{
		g_pTextureMagicSquare->Release();
		g_pTextureMagicSquare = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMagicSquare != NULL)
	{
		g_pVtxBuffMagicSquare->Release();
		g_pVtxBuffMagicSquare = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMagicSquare(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;


	//���_�o�b�t�@�����b�N
	g_pVtxBuffMagicSquare->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntMagicSquare = 0; nCntMagicSquare < MAX_MAGICSQUARE; nCntMagicSquare++)
	{
		g_aMagicSquare[nCntMagicSquare].rot.y += 0.015f;

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, g_aMagicSquare[nCntMagicSquare].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, g_aMagicSquare[nCntMagicSquare].fRadius);
		pVtx[2].pos = D3DXVECTOR3(-g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, -g_aMagicSquare[nCntMagicSquare].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, -g_aMagicSquare[nCntMagicSquare].fRadius);


		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMagicSquare->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMagicSquare(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X


	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	for (int nCntMagicSquare = 0; nCntMagicSquare < MAX_MAGICSQUARE; nCntMagicSquare++)
	{
		if (g_aMagicSquare[nCntMagicSquare].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMagicSquare[nCntMagicSquare].mtxWorldMagicSquare);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMagicSquare[nCntMagicSquare].rot.y, g_aMagicSquare[nCntMagicSquare].rot.x, g_aMagicSquare[nCntMagicSquare].rot.z);
			D3DXMatrixMultiply(&g_aMagicSquare[nCntMagicSquare].mtxWorldMagicSquare, &g_aMagicSquare[nCntMagicSquare].mtxWorldMagicSquare, &mtxRot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aMagicSquare[nCntMagicSquare].pos.x, g_aMagicSquare[nCntMagicSquare].pos.y, g_aMagicSquare[nCntMagicSquare].pos.z);

			D3DXMatrixMultiply(&g_aMagicSquare[nCntMagicSquare].mtxWorldMagicSquare, &g_aMagicSquare[nCntMagicSquare].mtxWorldMagicSquare, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMagicSquare[nCntMagicSquare].mtxWorldMagicSquare);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMagicSquare, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, g_pTextureMagicSquare);


			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMagicSquare * 4, 2);
		}
	}


	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMagicSquare(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/magicsquare.jpg", &g_pTextureMagicSquare);


	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MAGICSQUARE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMagicSquare,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMagicSquare->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntMagicSquare = 0; nCntMagicSquare < MAX_MAGICSQUARE; nCntMagicSquare++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, g_aMagicSquare[nCntMagicSquare].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, g_aMagicSquare[nCntMagicSquare].fRadius);
		pVtx[2].pos = D3DXVECTOR3(-g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, -g_aMagicSquare[nCntMagicSquare].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_aMagicSquare[nCntMagicSquare].fRadius, 0.0f, -g_aMagicSquare[nCntMagicSquare].fRadius);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.9f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.9f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.9f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.9f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMagicSquare->Unlock();
}

//=============================================================================
// ���@�w�̐ݒu
//=============================================================================

int SetMagicSquare(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	int nCntMagicSquare;
	//���_�o�b�t�@�����b�N
	g_pVtxBuffMagicSquare->Lock(0, 0, (void**)&pVtx, 0);
	for ( nCntMagicSquare = 0; nCntMagicSquare < MAX_MAGICSQUARE; nCntMagicSquare++)
	{
		if (g_aMagicSquare[nCntMagicSquare].bUse == false)
		{

			g_aMagicSquare[nCntMagicSquare].pos = pos;
			g_aMagicSquare[nCntMagicSquare].rot = rot;
			g_aMagicSquare[nCntMagicSquare].fRadius = fRadius;
			g_aMagicSquare[nCntMagicSquare].col = D3DXCOLOR(1.0f, 0.0f, 0.9f, 1.0f);
			g_aMagicSquare[nCntMagicSquare].nIdxSencer = SetSencer(pos, rot, SENCERTYPE_COLLISION);
			g_aMagicSquare[nCntMagicSquare].bUse = true;

		

			break;

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMagicSquare->Unlock();
	return nCntMagicSquare;
}
//=============================================================================
// ���@�w�̏���
//=============================================================================
void DeleteMagicSquare(int nIdxMagicSquare)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	

	

		fDestCol = 0.0f;
		fCol = fDestCol - g_aMagicSquare[nIdxMagicSquare].col.a;
		if (g_aMagicSquare[nIdxMagicSquare].bUse == true)
		{

			g_aMagicSquare[nIdxMagicSquare].col.a -=  0.013f;
			HitDamage(+2);


			if (g_aMagicSquare[nIdxMagicSquare].col.a <= 0.0f)
			{
				g_aMagicSquare[nIdxMagicSquare].col.a = 0.0f;
				g_aMagicSquare[nIdxMagicSquare].bUse = false;
				DeleteSencer(g_aMagicSquare[nIdxMagicSquare].nIdxSencer);
				DecreaseBrazen(-25);
			}
		}



		//���_�o�b�t�@�����b�N
		g_pVtxBuffMagicSquare->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntMagicSquare = 0; nCntMagicSquare < MAX_MAGICSQUARE; nCntMagicSquare++)
		{
			g_aMagicSquare[nCntMagicSquare].rot.y += 0.015f;

			//���_���W
			pVtx[0].col = g_aMagicSquare[nCntMagicSquare].col;
			pVtx[1].col = g_aMagicSquare[nCntMagicSquare].col;
			pVtx[2].col = g_aMagicSquare[nCntMagicSquare].col;
			pVtx[3].col = g_aMagicSquare[nCntMagicSquare].col;


			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffMagicSquare->Unlock();
	
}
//=============================================================================
// ���@�w�̏���
//=============================================================================
void DeleteOnlyMagicSquare(int nCntMagicsquare)
{
	if (g_aMagicSquare[nCntMagicsquare].bUse == true)
	{
		g_aMagicSquare[nCntMagicsquare].bUse = false;
		DeleteSencer(g_aMagicSquare[nCntMagicsquare].nIdxSencer);
	}
}


MAGICSQUARE *GetMagicSquare(void)
{
	return &g_aMagicSquare[0];
}
