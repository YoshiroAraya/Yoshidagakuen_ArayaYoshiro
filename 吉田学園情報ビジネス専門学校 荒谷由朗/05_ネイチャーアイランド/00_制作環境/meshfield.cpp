//=============================================================================
//
// ���b�V���̏��� [mesh.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "meshfield.h"
#include "mesh.h"
#include "manager.h"
#include "scene.h"
#include "model.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MESHFIELD_0		"data\\TEXTURE\\sky.jpg"				// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MESHFIELD_1		"data\\TEXTURE\\green2.jpg"				// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MESHFIELD_2		"data\\TEXTURE\\field03.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MESHFIELD_3		"data\\TEXTURE\\rock_002.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MESHFIELD_4		"data\\TEXTURE\\soil.jpg"				// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture[MAX_MESH_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 CMeshField::m_pVtxBuff = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 CMeshField::m_pIdxBuff = NULL;					// �C���f�b�N�X�ւ̃|�C���^
//CMeshField::MeshField CMeshField::m_MeshField[MESH_DATA] = {};
//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CMeshField::CMeshField()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CMeshField::~CMeshField()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CMesh::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < MAX_MESH_TEXTURE; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}

	CMesh::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{
	CMesh::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�߂��̃��f���ȊO������
	if (m_pos.x + 3000.0f >= PlayerPos.x && m_pos.x - 3000.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		CMesh::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		CMesh::Draw();
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CMeshField * CMeshField::Create(D3DXVECTOR3 pos,int nMeshX, int nMeshZ,float fMeshWidth, float fMeshDepth, float fVtx0, float fVtxMeshX, float fVtxMeshZ, float fVtxMeshXMeshZ, int nTexType,int nMeshType)
{
	CMeshField *pMeshField = NULL;

	//NULL�`�F�b�N
	if (pMeshField == NULL)
	{//�������̓��I�m��

		pMeshField = new CMeshField;

		if (pMeshField != NULL)
		{
			//�ʒu��ϐ��ɑ��
			pMeshField->m_pos = pos;
			//�ʒu�̑��
			pMeshField->SetPosition(pos);
			//���b�V���̎��
			pMeshField->SetMeshType(nMeshType);
			//���b�V���̏���e�N���X�ɓn��
			pMeshField->SetMeshInfo(nMeshX, nMeshZ, fMeshDepth, fMeshWidth);
			//���b�V���̒��_�̍���
			pMeshField->SetVtx(fVtx0, fVtxMeshX, fVtxMeshZ, fVtxMeshXMeshZ);
			//�I�u�W�F�N�g�N���X�̐���
			pMeshField->Init();
			//�e�N�X�`���̐ݒ�
			pMeshField->BindTexture(m_pTexture[nTexType]);
		}
	}

	return pMeshField;
}
#if 0
//===============================================================================
//�@�N���G�C�g
//===============================================================================
void CMeshField::CreateMesh(void)
{
	//�g���������锠
	int nNumMaxMesh = 0;
	char read[200];

	//�t�@�C���̃|�C���^
	FILE *pFile;

	//�t�@�C���ݒ�
	pFile = fopen(MESHFILE_NAME, "r");

	//�G�̃e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//������tex�R�����g
		fscanf(pFile, "%s", &read[0]);

		//�R�����g�t��
		if (strcmp(&read[0], "#") == 0)
		{
			do
			{
				fscanf(pFile, "%c", &read[0]);
			}
			while (strcmp(&read[0], "\n") != 0);
		}

		//�g���G�̐�
		fscanf(pFile, "%d", &nNumMaxMesh);	//�ǂݍ���

		for (int nCntMesh = 0; nCntMesh < nNumMaxMesh; nCntMesh++)
		{
			//�G�̎�ނ̃R�����g
			for (int nCount = 0; nCount < 3; nCount++)
			{
				fscanf(pFile, "%s", &read[0]);

				if (strcmp(&read[0], "#") == 0)
				{
					do
					{
						fscanf(pFile, "%c", &read[0]);
					} while (strcmp(&read[0], "\n") != 0);
				}
			}

			//�����ʒu�̐ݒ�
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].InitPos.x);		//�ʒuX
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].InitPos.y);		//�ʒuY
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].InitPos.z);		//�ʒuZ

			//�������̐ݒ�
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nDivision_X);	//������X
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nDivision_Z);	//������Z

			//���b�V���̉����Ɖ��s�̐ݒ�
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].fWidth);			//����
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].fDepth);			//���s

			//�e�N�X�`���̐ݒ�
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nTexType);		//�e�N�X�`�����[0:��][1:���̒n��][2:��]

			//���b�V���V�����_�[���t�B�[���h��
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nMeshType);		//���b�V���̎��[0:�V�����_�[][1:�t�B�[���h]

			//�t�B�[���h�̐���
			CMeshField::Create
			(
				m_MeshField[nCntMesh].InitPos,		//�����ʒuD3DXVECTOR3�^
				m_MeshField[nCntMesh].nDivision_X,	//int�^�̕�����X����
				m_MeshField[nCntMesh].nDivision_Z,	//int�^�̕�����Z�����@�V�����_�[��Y�Ƃ��Ďg���F�t�B�[���h��Z�Ƃ��Ďg��
				m_MeshField[nCntMesh].fWidth,		//�����̃T�C�Y float�^
				m_MeshField[nCntMesh].fDepth,		//���s�̃T�C�Y float�^
				m_MeshField[nCntMesh].nTexType,		//�e�N�X�`���̎�� int�^ [0:��][1:���̒n��][2:��]
				m_MeshField[nCntMesh].nMeshType		//���b�V���t�B�[���h�̎�� [0:�V�����_�[][1:�t�B�[���h]
			);
		}

		fclose(pFile);	//�t�@�C�������
	}
	else
	{//�x����
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s!", "�x��", MB_ICONWARNING);
	}
}
#endif
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CMeshField::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_3, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_4, &m_pTexture[4]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CMeshField::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MESH_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

