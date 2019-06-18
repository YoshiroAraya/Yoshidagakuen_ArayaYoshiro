//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : komatsu keisuke
//
//=============================================================================
#include "meshfield.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MESHFIELD_TEXTURENAME	"data/TEXTURE/Field.jpg"	//�\������t�@�C���̖��O
#define HORIZONTAL_MESHFIELD	(2)							//���̕�����	
#define VERTICAL_MESHFIELD		(2)							//�c�̕�����
#define MESHFIELD_DEPTH			(500.0f)					//���s��
#define MESHFIELD_WIDTH			(500.0f)					//��
#define ALL_VERTEX	((HORIZONTAL_MESHFIELD + 1) * (VERTICAL_MESHFIELD + 1))		//�S���_
#define ALL_POLYGON	((HORIZONTAL_MESHFIELD * VERTICAL_MESHFIELD) * 2 + (VERTICAL_MESHFIELD - 1) * 4)	//�S�|���S��
#define ALL_INDEX	(ALL_POLYGON + 2)						//�S�C���f�b�N�X

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshField g_MeshField;									//���b�V���t�B�[���h�̏��

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_3D *pVtx;
	WORD *pIdx;

	//�|���S���̏�����
	g_MeshField.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshField.fWidth = MESHFIELD_WIDTH;
	g_MeshField.fDepth = MESHFIELD_DEPTH;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURENAME, &g_pTextureMeshField);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ALL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ALL_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�̃��b�N

	//���_���
	for (int nCntVertical = 0; nCntVertical < (VERTICAL_MESHFIELD + 1) * 2; nCntVertical += (VERTICAL_MESHFIELD + 1))
	{//�c��
		for (int nCntHorizontal = 0; nCntHorizontal <= HORIZONTAL_MESHFIELD; nCntHorizontal++)
		{//����
			pVtx[nCntVertical + nCntHorizontal].pos = D3DXVECTOR3(-g_MeshField.fWidth + (nCntHorizontal) * g_MeshField.fWidth, 0.0f, g_MeshField.fDepth - (nCntVertical / (HORIZONTAL_MESHFIELD + 1) * g_MeshField.fDepth));
			pVtx[nCntVertical + nCntHorizontal + (HORIZONTAL_MESHFIELD + 1)].pos = D3DXVECTOR3(-g_MeshField.fWidth + (nCntHorizontal * g_MeshField.fWidth), 0.0f, 0.0f - (nCntVertical / (HORIZONTAL_MESHFIELD + 1) * g_MeshField.fDepth));
		}
	}

	for (int nCntMF = 0; nCntMF < ALL_VERTEX; nCntMF++)
	{
		//�@���x�N�g���̐ݒ�
		pVtx[nCntMF].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[nCntMF].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);

	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffMeshField->Unlock();	//���_�o�b�t�@�̃A�����b�N

	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);	//�C���f�b�N�X�o�b�t�@�̃��b�N

	int nCntIndex = 0;

	for (int nCntVertical = 0; nCntVertical < VERTICAL_MESHFIELD; nCntVertical++)
	{//�c��
		for (int nCntHorizontal = 0; nCntHorizontal <= HORIZONTAL_MESHFIELD; nCntHorizontal++, nCntIndex++)
		{//����
			pIdx[0] = (HORIZONTAL_MESHFIELD + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			if (nCntHorizontal == HORIZONTAL_MESHFIELD && nCntVertical < VERTICAL_MESHFIELD - 1)
			{
				pIdx += 2;
				pIdx[0] = nCntIndex;
				pIdx[1] = (HORIZONTAL_MESHFIELD + 1) + nCntIndex + (VERTICAL_MESHFIELD - 1);
			}
			pIdx += 2;
		}
	}
	
	 //pIdx[0] = 3; //pIdx[1] = 0;
	 //pIdx[2] = 4; //pIdx[3] = 1;
	 //pIdx[4] = 5; //pIdx[5] = 2;
	 //pIdx[6] = 2; //pIdx[7] = 6;
	 //pIdx[8] = 6; //pIdx[9] = 3;
	//pIdx[10] = 7;//pIdx[11] = 4;
	//pIdx[12] = 8;//pIdx[13] = 5;

	g_pIdxBuffMeshField->Unlock();	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshField.mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorldMeshField, &g_MeshField.mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.rot.x, g_MeshField.rot.y, g_MeshField.rot.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorldMeshField, &g_MeshField.mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorldMeshField);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, ALL_VERTEX, 0, ALL_POLYGON);
}