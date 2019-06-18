//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "meshField.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MESHFIELD_TEXTURE	"data/TEXTURE/see.png"			// �ǂݍ��ރe�N�X�`��
#define MAX_POS				(9)								// ���_�̍ő吔
#define MAX_MESH			(14)							// ���b�V���̍ő吔
#define MESH_Z				(2)								// ���b�V���̏c
#define MESH_X				(2)								// ���b�V���̉�

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pldxBuffMeshField = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_posMeshField;				// �ʒu
D3DXVECTOR3				g_rotMeshField;				// ����
D3DXMATRIX				g_mtxWorldMeshField;		// ���[���h�}�g���b�N�X
int						g_nNumVertexMeshField;		// ���_��
int						g_nNumIndexMeshField;		// �C���f�b�N�X��
int						g_nNumPolygonMeshField;		// �|���S����

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_3D*pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE, &g_pTextureMeshField);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_MESH,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshField,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMeshFiled = 0; nCntMeshFiled < MESH_Z; nCntMeshFiled++)
	{	// �c��
		for (int nCntMeshField1 = 0; nCntMeshField1 < MESH_X + 1; nCntMeshField1++)
		{	// ����
			// ���_���W�̐ݒ�
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f) + 1000.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f));
			// �@���̐ݒ�
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`���ݒ�
			pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(1.0f, 0.0f);

			if (nCntMeshField1 == MESH_X - 1)
			{
				// ���_���W�̐ݒ�
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f) + 1000.0f);
				pVtx[nCntMeshField1 + MESH_X + 2 + (nCntMeshFiled * 3)].pos = D3DXVECTOR3((nCntMeshField1 * 1000.0f) - 1000.0f, 0.0f, (nCntMeshFiled * -1000.0f));
				// �@���̐ݒ�
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// ���_�J���[�̐ݒ�
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				// �e�N�X�`���ݒ�
				pVtx[nCntMeshField1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[nCntMeshField1 + MESH_X + 1 + (nCntMeshFiled * 3)].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
		}
	}

	// �e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);

	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);

	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	int nCntIndex = 0;

	WORD*pldx;		// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pldxBuffMeshField->Lock(0, 0, (void**)&pldx, 0);
	// �C���f�b�N�X�̐ݒ�
	for (int nCntIndex_V = 0; nCntIndex_V < MESH_Z; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= MESH_X; nCntIndex_H++, nCntIndex++)
		{
			pldx[0] = (MESH_X + 1) + nCntIndex;
			pldx[1] = nCntIndex;

			pldx += 2;

			if (nCntIndex == MESH_X && nCntIndex_V <= MESH_Z)
			{
				pldx[0] = nCntIndex;
				pldx[1] = (MESH_X + 1) + nCntIndex + 1;

				pldx += 2;
			}
		}
	}
	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pldxBuffMeshField->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pldxBuffMeshField != NULL)
	{
		g_pldxBuffMeshField->Release();
		g_pldxBuffMeshField = NULL;
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
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pldxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_POS, 0, MAX_MESH);
}