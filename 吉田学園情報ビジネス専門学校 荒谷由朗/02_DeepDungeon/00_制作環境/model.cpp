//=============================================================================
//
// ���f��(�K�i����̂���)���� [model.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "model.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MODEL_TEXTUER	"data/TEXTURE/step.jpg"
#define MODEL_1			"data/MODEL/door.x"
#define MODEL_MOVR		(1.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH			g_pMeshModel = NULL;				//���b�V�����i���_���j�̃|�C���^
LPD3DXBUFFER		g_pBuffMatModel = NULL;				//�}�e���A�����ւ̃|�C���^
DWORD				g_nNumMatModel = 0;					//�}�e���A�����̐�
LPDIRECT3DTEXTURE9	g_pTextureModel = NULL;				//�e�N�X�`���ւ̃|�C���^
Model				g_Model;							//���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;						//���_��
	DWORD sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;						//���_�o�b�t�@�̃|�C���^
	g_Model.vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	g_Model.vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	//���_���̎擾
	nNumVtx = g_pMeshModel->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		
		if (g_Model.vtxMin.x > vtx.x)
		{//X�̍ŏ��l�̏�������
			g_Model.vtxMin.x = vtx.x;
		}
		if (g_Model.vtxMin.z > vtx.z)
		{//X�̍ŏ��l�̏�������
			g_Model.vtxMin.z = vtx.z;
		}
		if (g_Model.vtxMax.x < vtx.x)
		{//X�̍ŏ��l�̏�������
			g_Model.vtxMax.x = vtx.x;
		}
		if (g_Model.vtxMax.z < vtx.z)
		{//X�̍ŏ��l�̏�������
			g_Model.vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;//�T�C�Y���|�C���^��i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pMeshModel->UnlockVertexBuffer();
	
	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, MODEL_TEXTUER, &g_pTextureModel);

	// �ʒu�E�����E�F�̏����ݒ�
	g_Model.pos = D3DXVECTOR3(120.0f, 0.0f, -350.0f);
	g_Model.rot = D3DXVECTOR3(0.0f, D3DX_PI *-0.5, 0.0f);
	g_Model.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Model.bUse = true;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	// ���b�V���̊J��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
	// �}�e���A���̊J��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
	
	if (g_pTextureModel != NULL)
	{
		g_pTextureModel->Release();
		g_pTextureModel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Model.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat <= (int)g_nNumMatModel;nCntMat++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureModel);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// ���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
#endif
}
//=============================================================================
// ���f���̎擾
//=============================================================================
Model*GetModel(void)
{
	return &g_Model;
}

//=============================================================================
// ���f���ƃv���C���[�̂����蔻��
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld)
{
	bool bLand = false;
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if (g_Model.bUse == true)
	{//���f���̎g�p��
		bLand = false;
		//���ǂ����蔻��------------------------------
		if (posOld->x + pPlayer->vtxMaxModel.x < g_Model.pos.x + g_Model.vtxMin.x
			&&posOld->z + pPlayer->vtxMaxModel.z < g_Model.pos.z + g_Model.vtxMax.z
			&&posOld->z + pPlayer->vtxMaxModel.z > g_Model.pos.z + g_Model.vtxMin.z)
		{//�O��̈ʒu�����f�����������ɂ���

			if (pos->x + pPlayer->vtxMaxModel.x < g_Model.pos.x + g_Model.vtxMax.x
				&&pos->z + pPlayer->vtxMaxModel.z < g_Model.pos.x + g_Model.vtxMax.z
				&&pos->x + pPlayer->vtxMaxModel.x > g_Model.pos.x + g_Model.vtxMin.x
				&&pos->z + pPlayer->vtxMaxModel.z > g_Model.pos.z + g_Model.vtxMin.z)
			{//���̕ǂɂ߂荞��
				bLand = true;
				pos->x = posOld->x;
			}
		}
		//���ǂ����蔻��------------------------------
		if (posOld->z + pPlayer->vtxMinModel.z > g_Model.pos.z + g_Model.vtxMax.z
			&&posOld->x + pPlayer->vtxMinModel.x > g_Model.pos.x + g_Model.vtxMin.x
			&&posOld->x + pPlayer->vtxMinModel.x < g_Model.pos.x + g_Model.vtxMax.x)
		{//�O��̈ʒu�����f�����������ɂ���
			if (pos->x + pPlayer->vtxMinModel.x > g_Model.pos.x + g_Model.vtxMin.x
				&&pos->z + pPlayer->vtxMinModel.z > g_Model.pos.z + g_Model.vtxMin.z
				&&pos->x + pPlayer->vtxMinModel.x < g_Model.pos.x + g_Model.vtxMax.x
				&&pos->z + pPlayer->vtxMinModel.z < g_Model.pos.z + g_Model.vtxMax.z)
			{//���ǂɂ߂荞��
				bLand = true;
				pos->z = posOld->z;
			}
		}

		//�E�ǂ����蔻��------------------------------
		if (posOld->x + pPlayer->vtxMinModel.x > g_Model.pos.x + g_Model.vtxMax.x
			&&posOld->z + pPlayer->vtxMinModel.z > g_Model.pos.z + g_Model.vtxMin.z
			&&posOld->z + pPlayer->vtxMinModel.z < g_Model.pos.z + g_Model.vtxMax.z)
		{//�O��̈ʒu�����f�������E���ɂ���
			if (pos->x + pPlayer->vtxMinModel.x < g_Model.pos.x + g_Model.vtxMax.x
				&&pos->z + pPlayer->vtxMinModel.z < g_Model.pos.x + g_Model.vtxMax.z
				&&pos->x + pPlayer->vtxMinModel.x > g_Model.pos.x + g_Model.vtxMin.x
				&&pos->z + pPlayer->vtxMinModel.z > g_Model.pos.z + g_Model.vtxMin.z)
			{//�E�̕ǂɂ߂荞��
				bLand = true;
				pos->x = posOld->x;
			}
		}

		//��O�ǂ����蔻��------------------------------
		if (posOld->z + pPlayer->vtxMaxModel.z < g_Model.pos.z + g_Model.vtxMin.z
			&&posOld->x + pPlayer->vtxMaxModel.x < g_Model.pos.x + g_Model.vtxMax.x
			&&posOld->x + pPlayer->vtxMaxModel.x > g_Model.pos.x + g_Model.vtxMin.x)
		{//�O��̈ʒu�����f��������O���ɂ���
			if (pos->x + pPlayer->vtxMaxModel.x > g_Model.pos.x + g_Model.vtxMin.x
				&&pos->z + pPlayer->vtxMaxModel.z > g_Model.pos.z + g_Model.vtxMin.z
				&&pos->x + pPlayer->vtxMaxModel.x < g_Model.pos.x + g_Model.vtxMax.x
				&&pos->z + pPlayer->vtxMaxModel.z < g_Model.pos.z + g_Model.vtxMax.z)
			{//��O�ǂɂ߂荞��
				bLand = true;
				pos->z = posOld->z;
			}
		}
	}

	return bLand;
}
