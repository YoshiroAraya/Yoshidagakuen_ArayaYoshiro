//=============================================================================
//
// �I�u�W�F�N�g�̏��� [object.cpp]
// Author : �L�n���u ���@�����@�[�S
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "object.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME_1	"data\\MODEL\\floor.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_2	"data\\MODEL\\Balloon.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_3	"data\\MODEL\\rock.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_4	"data\\MODEL\\TreeU.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_5	"data\\MODEL\\TreeD.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_6	"data\\MODEL\\wood.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_7	"data\\MODEL\\StumpVer.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_8	"data\\MODEL\\StumpHor.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_9	"data\\MODEL\\StumpMoveHor.x"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_10	"data\\MODEL\\WoodPlanks.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_11	"data\\MODEL\\log.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_12	"data\\MODEL\\grass.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_13	"data\\MODEL\\yazirusi.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_14	"data\\MODEL\\house.x"			//�ǂݍ��ރe�N�X�`���t�@�C��

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(10)		// �v���C���[�̕������p
#define PLAYER_HEIGHT	(100.0f)		// �v���C���[�̔w�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CObject::m_pMeshModel[MAX_OBJECT] = {};						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CObject::m_pBuffMatModel[MAX_OBJECT] = {};					//�}�e���A���̏��ւ̃|�C���^
DWORD CObject::m_nNumMatModel[MAX_OBJECT] = {};							//�}�e���A���̏��
LPDIRECT3DTEXTURE9 CObject::m_pMeshTextures[MAX_OBJECT_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CObject::CObject() : CModel3D(OBJECT_PRIOTITY,CScene::OBJTYPE_OBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CObject::~CObject()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CObject::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3D���f����Init
	CModel3D::Init();
	
	// �ʒu�̏�����
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ʒu�̑��
	CModel3D::SetPosition(pos);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
	//3D���f����Uninit
	CModel3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//3D���f����Update
	CModel3D::Update();

	//�ʒu�̏�����
	D3DXVECTOR3 pos = CModel3D::GetPosition();

	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����̑��
	D3DXVECTOR3 rot = CModel3D::GetRot();

	// MOVETYPE�̐ݒ�
	MOVETYPE MoveType = CModel3D::GetMoveType();

	switch (MoveType)
	{
	case MOVETYPE_X_MOVE:
		// X���ړ�
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Y_MOVE:
		// Y���ړ�
		if (m_nCount <= 120)
		{
			move.y += m_move.y;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.y -= m_move.y;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Z_MOVE:
		// Z���ړ�
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		break;

	case MOVETYPE_ROTATION_X:
		// X���ŉ�]���Ȃ���Z���ړ�
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.x += 0.1f;
		//rot.z += 0.01f;

		CModel3D::SetRot(rot);
		break;

	case MOVETYPE_ROTATION_Z:
		// Z���ŉ�]���Ȃ���X���ړ�
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		//rot.x += 0.01f;
		rot.z += 0.1f;

		CModel3D::SetRot(rot);
		break;
	}


	//���f���̃f�o�b�N�ʒu
	//CDebugProc::Print("�I�u�W�F�N�gpos�̈ʒu :�y%.1f�z�y%.1f�z�y%.1f�z\n", pos.x, pos.y, pos.z);

	// �ړ��ʂ̑��
	pos += move;

	// �e����̑��
	CModel3D::SetPosition(pos);
	CModel3D::SetMove(move);
	CModel3D::SetMoveType(MoveType);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�ʒu�̏�����
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�J�����̈ʒu
	D3DXVECTOR3 CameraPosV = CCamera::GetPosV();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�߂��̃��f���ȊO������
	if (Modelpos.x + 1450.0f >= PlayerPos.x && Modelpos.x - 1300.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		//3D���f����Draw
		CModel3D::Draw();
	}
	else if (Modelpos.x + 1450.0f >= CameraPosV.x && Modelpos.x - 1300.0f <= CameraPosV.x && pMode == CManager::MODE_TITLE)
	{
		//3D���f����Draw
		CModel3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME && pMode != CManager::MODE_TITLE)
	{
		CModel3D::Draw();
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos, float move, int nTexType,int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObject *pObject = NULL;

	// NULL�`�F�b�N
	if (pObject == NULL)
	{// �������̓��I�m��

		pObject = new CObject;

		if (pObject != NULL)
		{
			// ��ނ̐ݒ�
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// �I�u�W�F�N�g�N���X�̐���
			pObject->Init();
			// �I�u�W�F�N�g���Ƃ̐ݒ�p�^�C�v
			pObject->m_nType = nObjectType;
			// �ʒu����
			pObject->SetPosition(pos);
			// �����̎�ނƈړ��ʂ�ݒ�
			pObject->SetMoveType(nMovetype);
			pObject->m_move = D3DXVECTOR3(move, move, move);
			// �R���W������ONOFF
			pObject->m_nCollision = nCollision;
		}
	}

	return pObject;
}
//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[0], NULL, &m_nNumMatModel[0], &m_pMeshModel[0]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_2, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[1], NULL, &m_nNumMatModel[1], &m_pMeshModel[1]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_3, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[2], NULL, &m_nNumMatModel[2], &m_pMeshModel[2]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_4, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[3], NULL, &m_nNumMatModel[3], &m_pMeshModel[3]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_5, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[4], NULL, &m_nNumMatModel[4], &m_pMeshModel[4]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_6, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[5], NULL, &m_nNumMatModel[5], &m_pMeshModel[5]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_7, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[6], NULL, &m_nNumMatModel[6], &m_pMeshModel[6]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_8, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[7], NULL, &m_nNumMatModel[7], &m_pMeshModel[7]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_9, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[8], NULL, &m_nNumMatModel[8], &m_pMeshModel[8]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_10, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[9], NULL, &m_nNumMatModel[9], &m_pMeshModel[9]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_11, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[10], NULL, &m_nNumMatModel[10], &m_pMeshModel[10]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_12, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[11], NULL, &m_nNumMatModel[11], &m_pMeshModel[11]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_13, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[12], NULL, &m_nNumMatModel[12], &m_pMeshModel[12]);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_14, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[13], NULL, &m_nNumMatModel[13], &m_pMeshModel[13]);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\ita.jpg",&m_pMeshTextures[0]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\rock_000.jpg",&m_pMeshTextures[1]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�t����.jpg", &m_pMeshTextures[2]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bark-texture.jpg", &m_pMeshTextures[3]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\scarp06.jpg", &m_pMeshTextures[4]);
	//�e�N�X�`���Ȃ�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\.jpg", &m_pMeshTextures[5]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stump_belt.jpg", &m_pMeshTextures[6]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\WoodPlanks.jpg", &m_pMeshTextures[7]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\grass.png", &m_pMeshTextures[8]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi.jpg", &m_pMeshTextures[9]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_yoko.jpg", &m_pMeshTextures[10]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_tobu.jpg", &m_pMeshTextures[11]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_mizu.jpg", &m_pMeshTextures[12]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_ue.jpg", &m_pMeshTextures[13]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_kaze.jpg", &m_pMeshTextures[14]);
	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\window_close.jpg", &m_pMeshTextures[15]);
	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CObject::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
	//�e�N�X�`��
	for (int nCntTex = 0; nCntTex < MAX_OBJECT_TEXTURE; nCntTex++)
	{
		if (m_pMeshTextures[nCntTex] != NULL)
		{
			m_pMeshTextures[nCntTex]->Release();
			m_pMeshTextures[nCntTex] = NULL;
		}
	}
}
//===============================================================================
// �����蔻��
//===============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//�������Ă��邩�������ĂȂ���
	bool bLand = false;
	int nCollision = m_nCollision;
	CManager::MODE pMode = CManager::GetMode();

	switch (m_nCollision)
	{
	case 1:

		// �e����̎擾
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();	// �ʒu
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();	// �ړ���
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// �����̃^�C�v
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();	// ���f���̍ő�l
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();	// ���f���̍ŏ��l

		D3DXVECTOR3 ModelMax = CModel3D::GetPosition() + CModel3D::VtxMax();	// �ʒu���݂̍ő�l
		D3DXVECTOR3 ModelMin = CModel3D::GetPosition() + CModel3D::VtxMin();	// �ʒu���݂̍ŏ��l

		// �ړ��ʂ̕ێ�
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Z�͈͓̔��ɂ���		
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// X�͈͓̔��ɂ���
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// �I�u�W�F�N�g�̏ォ�瓖����ꍇ
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X�ړ�����
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z�ړ�����
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// �I�u�W�F�N�g�̉����瓖����ꍇ
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}

				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{// �I�u�W�F�N�g���Ƃ̓����蔻��
					//CDebugProc::Print("���f���̉E�� : %.1f\n", ModelMax.x);
					//CDebugProc::Print("���f���̍��� : %.1f\n", ModelMin.x);
					//CDebugProc::Print("���f���̉��� : %.1f\n", ModelMax.z);
					//CDebugProc::Print("���f���̎�O�� : %.1f\n", ModelMin.z);
					//CDebugProc::Print("���f���̒��_�� : %.1f\n", ModelMax.y);
					//CDebugProc::Print("���f���̑����� : %.1f\n", ModelMin.y);

					if (ModelMoveType == MOVETYPE_X_MOVE || ModelMoveType == MOVETYPE_ROTATION_Z)
					{// X�ړ��I�u�W�F�N�g
						if (pPosOld->x - (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x) >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE �E\n");
						}
						else if (pPosOld->x + (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x) <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��O\n");
						}
					}
					else if (ModelMoveType == MOVETYPE_Z_MOVE || ModelMoveType == MOVETYPE_ROTATION_X)
					{// Z�ړ��I�u�W�F�N�g
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE �E\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}

						if (pPosOld->z - (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z) >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}
						else if (pPosOld->z + (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z) <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��O\n");
						}
					}
					else
					{// ���ړ��I�u�W�F�N�g
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT �E\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT ��\n");

							if (pMode == CManager::MODE_GAME && ModelMoveType == MOVETYPE_HOUSE)
							{// �S�[���̉ƂɐG�ꂽ��
								if (CFade::GetFade() == CFade::FADE_NONE)
								{//P�L�[�������ꂽ��
								 //�V�K�ǉ�
									CManager::SetGameScore(CTime::GetTime());
									CManager::RankingScore(CTime::GetTime());

									CFade::Create(CManager::MODE_RESULT);
								}
							}
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT ��\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT ��O\n");
						}
					}
				}
			}
		}

		// �ʒu�̑��
		CModel3D::SetPosition(ModelPos);
		// �ړ��ʂ̑��
		m_ModelMove = ModelMove;

		break;
	}

	return bLand;
}