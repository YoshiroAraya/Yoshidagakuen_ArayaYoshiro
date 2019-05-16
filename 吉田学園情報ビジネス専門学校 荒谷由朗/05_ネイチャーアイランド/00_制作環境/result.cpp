//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �L�n�@���u & �r�J �R�N
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "serect.h"
#include "player.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"
#include "wall.h"
#include "ground.h"
#include "billboord.h"
#include "effect.h"
#include "item.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer		*CResult::m_pPlayer		= NULL;
CSerect		*CResult::m_pSerect		= NULL;
CBillBoord	*CResult::m_pBillBoord	= NULL;
CPolygon3D	*CResult::m_pPolygon3D	= NULL;
CMeshField	*CResult::m_pMeshField	= NULL;
CObject		*CResult::m_pObject		= NULL;
CModel		*CResult::m_pModel		= NULL;
CEffect		*CResult::m_pEffect		= NULL;
CWall		*CResult::m_pWall		= NULL;
CGround		*CResult::m_pGround		= NULL;
CItem		*CResult::m_pItem		= NULL;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_nCnt = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init()
{
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//===================================
	//		 Load�̓ǂݍ��ݏꏊ
	//===================================
	//�t�F�[�h�̃e�N�X�`���̓ǂݍ���
	CFade::Load();

	//�Z���N�g�̃e�N�X�`���̓ǂݍ���
	m_pSerect->Load();

	//�v���C���[�̃e�N�X�`���̓ǂݍ���
	m_pPlayer->Load();

	//���b�V���t�B�[���h�̃e�N�X�`���̓ǂݍ���
	m_pMeshField->Load();

	//�r���{�[�h�e�N�X�`���̓ǂݍ���
	m_pBillBoord->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//�G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pEffect->Load();

	//�n�ʂ̃e�N�X�`���̓ǂݍ���
	m_pGround->Load();

	//�ǂ̃e�N�X�`���̓ǂݍ���
	m_pWall->Load();

	//�A�C�e���̃e�N�X�`���ǂݍ���
	m_pItem->Load();

	//�e�̃e�N�X�`���ǂݍ���
	m_pShadow->Load();

	//===================================
	//		 ����
	//===================================
	//�Z���N�g�̐���
	m_pSerect = CSerect::Create();

	CreateStage();
	CreateObject();

	//���݂̃Q�[����
	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//�Q�[���N���A�����ꍇ

	}
	else if (GameStateNow == CGame::GAMESTATE_OVER)
	{//�Q�[���I�[�o�[�����ꍇ

	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	//===================================
	//	�@�@UnLoad�̔j������ꏊ
	//===================================
	//���b�V���t�B�[���h�e�N�X�`���̔j��
	m_pMeshField->UnLoad();

	//�t�F�[�h�̃e�N�X�`���̔j��
	CFade::UnLoad();

	//�Z���N�g�̃e�N�X�`���̔j��
	m_pSerect->UnLoad();

	//�r���{�[�h�e�N�X�`���̔j��
	m_pBillBoord->UnLoad();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->UnLoad();

	//�v���C���[�̃e�N�X�`���̔j��
	m_pPlayer->UnLoad();

	//�G�t�F�N�g�̃e�N�X�`���̔j��
	m_pEffect->UnLoad();

	//�n�ʂ̃e�N�X�`���̔j��
	m_pGround->UnLoad();

	//�ǂ̃e�N�X�`���̔j��
	m_pWall->UnLoad();

	//�e�̃e�N�X�`���ǂݍ���
	m_pShadow->UnLoad();

	//���b�V���t�B�[���h�̔j��
	m_pMeshField->Uninit();
	m_pMeshField = NULL;

	//�Z���N�g�̍폜
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

	//�t�F�[�h�ȊO���폜
	CScene::NotFadeReleseAll();
}
//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//���݂ǂ�ȏ󋵂�
	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	if (GameStateNow == CGame::GAMESTATE_OVER)
	{//�Q�[���I�[�o�[�����ꍇ

	}
	else if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//�Q�[���N���A�����ꍇ

	}

	if (m_nCnt == 600)
	{//�T�b��ɉ������ĂȂ��ꍇ�߂�
		//CFade::Create(CManager::MODE_RANKING);
	}

	m_nCnt++;
}
//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CResult::CreateStage(void)
{
	//===================================
	//		 �n�ʂ𐶐�����ꏊ
	//===================================
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-750.0f, 0.0f, 500.0f), 4, 4, 1500.0f, 1000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(750.0f, -200.0f, 0.0f), D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// �E
	m_pWall = CWall::Create(D3DXVECTOR3(-750.0f, -200.0f, 0.0f), D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -200.0f, -500.0f), D3DXVECTOR2(750.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6);		// �w�i
#endif

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-70.0f, 0.0f, -300.0f));
}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CResult::CreateObject(void)
{
#if 1	// ��(��)
	m_pObject = CObject::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), 0.0f, 15, 13, CObject::MOVETYPE_HOUSE, 1);
#endif
#if 1	// ��
	SetTree(D3DXVECTOR3(-470.0f, 0.0f, 150.0f));
	SetTree(D3DXVECTOR3(-450.0f, 0.0f, -100.0f));
	SetTree(D3DXVECTOR3(-410.0f, 0.0f, 320.0f));
	SetTree(D3DXVECTOR3(-370.0f, 0.0f, -20.0f));
	SetTree(D3DXVECTOR3(-350.0f, 0.0f, 200.0f));
	SetTree(D3DXVECTOR3(-290.0f, 0.0f, 400.0f));
	SetTree(D3DXVECTOR3(-130.0f, 0.0f, 270.0f));
	SetTree(D3DXVECTOR3(-10.0f, 0.0f, 400.0f));
	SetTree(D3DXVECTOR3(90.0f, 0.0f, 350.0f));
	SetTree(D3DXVECTOR3(140.0f, 0.0f, 150.0f));
	SetTree(D3DXVECTOR3(160.0f, 0.0f, 450.0f));
	SetTree(D3DXVECTOR3(220.0f, 0.0f, 20.0f));
	SetTree(D3DXVECTOR3(240.0f, 0.0f, 280.0f));
	SetTree(D3DXVECTOR3(270.0f, 0.0f, -180.0f));
	SetTree(D3DXVECTOR3(410.0f, 0.0f, -50.0f));
	SetTree(D3DXVECTOR3(390.0f, 0.0f, 350.0f));
	SetTree(D3DXVECTOR3(380.0f, 0.0f, 100.0f));
#endif
}
//=============================================================================
// �؂̐���
//=============================================================================
void CResult::SetTree(D3DXVECTOR3 pos)
{
	//�؂̊�
	m_pObject = CObject::Create(pos, 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(pos, 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
}