//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "time.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM_NAME000		 "data\\MODEL\\Apple.x"		//�e�N�X�`���̃t�@�C����
#define ITEM_NAME001		 "data\\MODEL\\Banana.x"		//�e�N�X�`���̃t�@�C����
#define ITEM_ROT			(0.1f)
#define ITEM_MOVE_Y_UP		(0.3f)
#define ITEM_MOVE_Y_DOWN	(0.5f)

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH			CItem::m_pMesh[MAX_ITEM_TYPE] = {};				//���b�V�����ւ̃|�C���^
LPD3DXBUFFER		CItem::m_pBuffMat[MAX_ITEM_TYPE] = {};			//�}�e���A�����ւ̃|�C���^
DWORD				CItem::m_nNumMat[MAX_ITEM_TYPE] = {};			//�}�e���A���̏��
LPDIRECT3DTEXTURE9	CItem::m_pTexture[MAX_ITEM_TYPE] = {};			//�e�N�X�`�����

//===============================================================================
//�@�R���X�g���N�^
//===============================================================================
CItem::CItem() : CModel3D(4, CScene::OBJTYPE_ITEM)
{
	m_aItem.nType = 0;
	m_move = D3DXVECTOR3(0, 0, 0);
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_posold = D3DXVECTOR3(0, 0, 0);
	m_nMoveTimer = 0;
}

//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CItem::~CItem()
{
}

//===============================================================================
//�@�A�C�e���̐���
//===============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, int type)
{
	CItem *pItem = NULL;

	//NULL�`�F�b�N
	if (pItem == NULL)
	{//�������̓��I�m��
		pItem = new CItem;
		if (pItem != NULL)
		{
			pItem->BindModel(m_pMesh[type], m_pBuffMat[type], m_nNumMat[type], m_pTexture[type]);
			//��ނ����蓖�Ă�
			pItem->m_aItem.nType = type;
			switch (pItem->m_aItem.nType)
			{
			case 0:
				pItem->m_aItem.ItemType = ITEMTYPE_APPLE;
				break;
			case 1:
				pItem->m_aItem.ItemType = ITEMTYPE_BANANA;
				break;
			}
			//���W��ݒ�
			pItem->m_pos = pos;
			//�I�u�W�F�N�g�N���X�̐���
			pItem->Init();
		}
	}
	return pItem;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItem::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_move = D3DXVECTOR3(0, 0, 0);
	m_posold = D3DXVECTOR3(0, 0, 0);

	//3D���f����Init
	CModel3D::Init();

	//�ʒu�̑��
	CModel3D::SetPosition(m_pos);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void)
{
	//3D���f����Uninit
	CModel3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void)
{
	//3D���f����Update
	CModel3D::Update();
	//�ʒu�̏�����
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	D3DXVECTOR3 rot = CModel3D::GetRot();

	//�^�C�}�[�����Z
	m_nMoveTimer++;

	if (m_nMoveTimer <= 60)
	{	//�t���[���� (60) * �ړ���(0.3f) = 18	�����킹��
		pos.y += ITEM_MOVE_Y_UP;
	}
	else if (m_nMoveTimer >= 60 && m_nMoveTimer <= 120)
	{
		//�t���[���� (36) * �ړ���(0.5f) = 18
		pos.y -= ITEM_MOVE_Y_UP;
	}
	else
	{
		m_nMoveTimer = 0;
	}

	//�A�C�e�����Ƃ̉�]
	switch (m_aItem.ItemType)
	{
	case ITEMTYPE_APPLE:
		//��]�̉��Z
		rot.y += ITEM_ROT;
		break;
	case ITEMTYPE_BANANA:
		//��]�̉��Z
		rot.y += ITEM_ROT / 2;
		break;
	}

	//��]�̑��
	CModel3D::SetRot(rot);

	//�ʒu�̑��
	CModel3D::SetPosition(pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void)
{
	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�߂��̕ǈȊO������
	if (m_pos.x + 700.0f >= PlayerPos.x && m_pos.x - 650.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		//3D���f����Draw
		CModel3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		//3D���f����Draw
		CModel3D::Draw();
	}
}

//*****************************************************************************
//�A�C�e���|�C���^����
//*****************************************************************************
CItem::ITEM *CItem::GetItem(void)
{
	return &m_aItem;
}
//*****************************************************************************
//�A�C�e���Ƃ̓����蔻�菈��
//*****************************************************************************
bool CItem::CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;
	//�v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 ItemVtxMax = CModel3D::VtxMax();
	D3DXVECTOR3 ItemVtxMin = CModel3D::VtxMin();
#if 1			//���f����Y���̒�
	if (pPos->y < m_pos.y + ItemVtxMax.y
		&& pPos->y + 100.0f > m_pos.y + ItemVtxMin.y)
	{
		//���f����Z���̒�
		if (pPos->z < m_pos.z + ItemVtxMax.z
			&& pPos->z + 10.0f  > m_pos.z + ItemVtxMin.z)
		{
			//���f����X���̒�
			if (pPos->x < m_pos.x + ItemVtxMax.x
				&& pPos->x + 10.0f > m_pos.x + ItemVtxMin.x)
			{
				//�����蔻��
				bLand = true;

				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SE_ITEMGET);

				//�A�C�e�����Ƃ̉�]
				switch (m_aItem.ItemType)
				{
				case ITEMTYPE_APPLE:
					CTime::MinusTime(5);
					break;
				case ITEMTYPE_BANANA:
					CTime::MinusTime(10);
					break;
				}

#endif
			}
		}
	}
	return bLand;
}

//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(ITEM_NAME000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(ITEM_NAME001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < MAX_ITEM_TYPE; nCnt++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		// �e�N�X�`���̓ǂݍ���
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			m_pTexture[nCnt] = NULL;

			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// �e�N�X�`���̐ݒ�
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
					&m_pTexture[nCnt]);					// �e�N�X�`���ւ̃|�C���^
			}
		}
	}
	return S_OK;
}

//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CItem::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_ITEM_TYPE; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}