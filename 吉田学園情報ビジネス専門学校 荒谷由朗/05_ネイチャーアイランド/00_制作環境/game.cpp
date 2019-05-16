//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �L�n�@���u & �����[�S
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "fade.h"
#include "pause.h"
#include "logo.h"
#include "sound.h"
#include "billboord.h"
#include "meshfield.h"
#include "object.h"
#include "fade.h"
#include "effect.h"
#include "time.h"
#include "wall.h"
#include "ground.h"
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
CPlayer *CGame::m_pPlayer = NULL;
CBullet *CGame::m_pBullet = NULL;
CNumber *CGame::m_pNumber = NULL;
CBillBoord *CGame::m_pBillBoord = NULL;
CPolygon3D *CGame::m_pPolygon3D = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CObject *CGame::m_pObject = NULL;
CPause *CGame::m_pPause = NULL;
CModel *CGame::m_pModel = NULL;
CEffect *CGame::m_pEffect = NULL;
CWall *CGame::m_pWall = NULL;
CGround *CGame::m_pGround = NULL;
CShadow *CGame::m_pShadow = NULL;
CItem *CGame::m_pItem = NULL;
bool CGame::m_bPause = false;
CGame::GAMESTATE CGame::m_gameState = GAMESTATE_NONE;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_gameState = GAMESTATE_NONE;
	m_nCounterGameState = 0;
	m_NowGameState = GAMESTATE_NONE;
	CGame::GetPlayer() = NULL;
	m_bPause = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init()
{
	//===================================
	//		 Load�̓ǂݍ��ݏꏊ
	//===================================
	//2D�摜�e�N�X�`���̓ǂݍ���
	CLogo::Load();

	//�t�F�[�h�̃e�N�X�`���̓ǂݍ���
	CFade::Load();

	//�Z���N�g�̃e�N�X�`���̓ǂݍ���
	m_pPause->Load();

	//���b�V���t�B�[���h�̃e�N�X�`���̓ǂݍ���
	m_pMeshField->Load();

	//�r���{�[�h�e�N�X�`���̓ǂݍ���
	m_pBillBoord->Load();

	//�e�̃e�N�X�`���̓ǂݍ���
	m_pBullet->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//�v���C���[�̃e�N�X�`���̓ǂݍ���
	//m_pPlayer->Load();

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
	//		 ��������ꏊ
	//===================================
	//2D�摜�𐶐�
	CLogo::Create(D3DXVECTOR3(160.0f, 75.0f, 0.0f), D3DXVECTOR2(160.0f, 75.0f), 1);
	CLogo::Create(D3DXVECTOR3(275.0f, 90.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);
	CLogo::Create(D3DXVECTOR3(-200.0f, 240.0f, 0.0f), D3DXVECTOR2(150.0f, 75.0f), 2);

	//�X�e�[�W�̐������ꊇ�Ǘ�
	CGame::CreateStage();

	//�X�e�[�W��̃I�u�W�F�N�g�������ꊇ�Ǘ�
	CGame::CreateObject();

	//�^�C�}�[�̐���
	CTime::Create(D3DXVECTOR3(200.0f, 70.0f, 0.0f));

	//�ʏ��Ԃ�
	m_gameState = GAMESTATE_NORMAL;

	//�|�[�Y��������
	m_bPause = false;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�|�[�Y�폜
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	//===================================
	//	�@�@UnLoad�̔j������ꏊ
	//===================================
	//�Z���N�g�̃e�N�X�`���̔j��
	m_pPause->UnLoad();

	//���b�V���t�B�[���h�e�N�X�`���̔j��
	m_pMeshField->UnLoad();

	//2D�摜�e�N�X�`���̔j��
	CLogo::UnLoad();

	//�t�F�[�h�̃e�N�X�`���̔j��
	CFade::UnLoad();

	//�r���{�[�h�e�N�X�`���̔j��
	m_pBillBoord->UnLoad();

	//�e�̃e�N�X�`���̔j��
	m_pBullet->UnLoad();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->UnLoad();

	//�v���C���[�̃e�N�X�`���̔j��
	//m_pPlayer->UnLoad();

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

	//�t�F�[�h�ȊO�̔j��
	CScene::NotFadeReleseAll();
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�|�[�Y�̏���
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_P) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_START) == true)
	{//P�L�[�������ꂽ��

		m_bPause = m_bPause ? false : true;

		switch (m_bPause)
		{
		case true:
			if (m_pPause == NULL)
			{
				//�|�[�Y���J����
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_OPEN);

				//�|�[�Y�̐���
				m_pPause = CPause::Create();

				//�|�[�Y�ƃt�F�[�h������
				CScene::SetUpdatePri(7);
			}
			break;
		case false:
			if (m_pPause != NULL)
			{
				//�|�[�Y����鉹
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_CLOSE);

				//�|�[�Y���폜
				m_pPause->Uninit();
				m_pPause = NULL;

				//�A�b�v�f�[�g���Ԃ����ׂĉ�
				CScene::SetUpdatePri(0);
			}
		}
	}
	if (m_pPause == false)
	{//�J����
		//���݂̏�Ԃ�ۑ�
		m_NowGameState = GetGameState();

		switch (m_NowGameState)
		{
		case GAMESTATE_NORMAL:	//�ʏ�̏��

				//��G�t�F�N�g
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(4970.0f, 450.0f, -50.0f), 50, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(4970.0f, 450.0f, -100.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(4970.0f, 450.0f, -150.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(4970.0f, 450.0f, -200.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(4970.0f, 450.0f, -250.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(4970.0f, 450.0f, -300.0f), 50, 20, 2);

				//��G�t�F�N�g
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(6770.0f, 830.0f, 200.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(6770.0f, 830.0f, 250.0f), 40, 20, 2);

				//��G�t�F�N�g
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7825.0f, 1070.0f, -30.0f), 20, 15, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7875.0f, 1070.0f, -30.0f), 20, 15, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7900.0f, 1070.0f, -30.0f), 20, 15, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7950.0f, 1070.0f, -30.0f), 20, 15, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(8000.0f, 1070.0f, -30.0f), 20, 15, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(8050.0f, 1070.0f, -30.0f), 20, 15, 2);

				//��G�t�F�N�g
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7825.0f, 1270.0f, 530.0f), 50, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7875.0f, 1270.0f, 530.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7900.0f, 1270.0f, 530.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(7950.0f, 1270.0f, 530.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(8000.0f, 1270.0f, 530.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(8050.0f, 1270.0f, 530.0f), 40, 20, 2);
				m_pEffect = CEffect::Create(CEffect::EFFECTTYPE_ERUPTION, D3DXVECTOR3(8100.0f, 1270.0f, 530.0f), 50, 20, 2);

			break;
		case GAMESTATE_CLEAR:	//�Q�[�����N���A�������
			m_nCounterGameState++;

			if (m_nCounterGameState >= 60)
			{//��ʁi���[�h�j�̐ݒ�
				CFade::Create(CManager::MODE_RESULT);
			}
			break;
		case GAMESTATE_OVER:	//�Q�[���ŕ������Ƃ��̏��
			m_nCounterGameState++;

			if (m_nCounterGameState >= 60)
			{//��ʁi���[�h�j�̐ݒ�
				CFade::Create(CManager::MODE_RESULT);
			}
			break;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CGame::CreateStage(void)
{
	//===================================
	//		 �O���̕�
	//===================================
	m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, 0.0f, 150.0f), D3DXVECTOR2(450.0f, 800.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 9);	// ��

	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(600.0f, 150.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1200.0f, 150.0f, 600.0f), D3DXVECTOR2(300.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1900.0f, 150.0f, 600.0f), D3DXVECTOR2(400.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(2800.0f, 500.0f, 600.0f), D3DXVECTOR2(500.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��

	//�؂����
	m_pWall = CWall::Create(D3DXVECTOR3(3300.0f, 500.0f, 1000.0f), D3DXVECTOR2(400.0f, 900.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 9);	//
	m_pWall = CWall::Create(D3DXVECTOR3(3750.0f, 500.0f, 1400.0f), D3DXVECTOR2(450.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	//
	m_pWall = CWall::Create(D3DXVECTOR3(4600.0f, 600.0f, 1400.0f), D3DXVECTOR2(400.0f, 900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	//
	m_pWall = CWall::Create(D3DXVECTOR3(5000.0f, 600.0f, 1000.0f), D3DXVECTOR2(400.0f, 900.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 9);	//

	m_pWall = CWall::Create(D3DXVECTOR3(5500.0f, 900.0f, 600.0f), D3DXVECTOR2(500.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(6400.0f, 900.0f, 600.0f), D3DXVECTOR2(400.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(7000.0f, 1100.0f, 600.0f), D3DXVECTOR2(200.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(7500.0f, 1300.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��

	//��
	m_pWall = CWall::Create(D3DXVECTOR3(7950.0f, 1130.0f, 650.0f), D3DXVECTOR2(150.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(7800.0f, 1130.0f, 1000.0f), D3DXVECTOR2(400.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 9);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(8100.0f, 1130.0f, 1000.0f), D3DXVECTOR2(400.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 9);	// �E
																																		//��̒n��
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(7800.0f, 1930.0f, 1350.0f), 4, 2, 300.0f, 700.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);

	// ��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(7950.0f, 1570.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), D3DXVECTOR2(150.0f, 400.0f), 0);	// ��
	m_pGround = CGround::Create(D3DXVECTOR3(7950.0f, 1970.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0, 0.0f, 0.0f), D3DXVECTOR2(150.0f, 400.0f), 0);	// ��

	m_pWall = CWall::Create(D3DXVECTOR3(8350.0f, 1300.0f, 600.0f), D3DXVECTOR2(250.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(8900.0f, 1500.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(9500.0f, 1500.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(10100.0f, 1500.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(10700.0f, 1500.0f, 600.0f), D3DXVECTOR2(300.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(11400.0f, 1500.0f, 600.0f), D3DXVECTOR2(400.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9);	// ��


	//===================================
	//		 �n�ʂ𐶐�����ꏊ
	//===================================
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), 4, 4, 600.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-300.0f, 0.0f, 600.0f), 4, 2, 600.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -200.0f, 300.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -200.0f, -300.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(300.0f, 150.0f, 300.0f), 4, 4, 600.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(300.0f, 150.0f, 600.0f), 4, 2, 600.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(600.0f, -200.0f, 300.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(900.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// �E
	m_pWall = CWall::Create(D3DXVECTOR3(300.0f, -200.0f, 150.0f), D3DXVECTOR2(450.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(600.0f, -200.0f, -300.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(900.0f, 155.0f, 100.0f), 1, 1, 200.0f, 300.0f, 0.0f, 0.0f, -350.0f, -350.0f, 4, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(900.0f, 150.0f, 600.0f), 4, 2, 1400.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�p�x�����Ă�@
	m_pWall = CWall::Create(D3DXVECTOR3(1100.0f, -200.0f, -50.0f), D3DXVECTOR2(150.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);	// �E

	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(900.0f, 150.0f, 300.0f), 1, 1, 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(1400.0f, -200.0f, 300.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1100.0f, -200.0f, 200.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(1200.0f, 150.0f, 300.0f), 1, 1, 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(1300.0f, -200.0f, 300.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1400.0f, -200.0f, 200.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(1200.0f, -200.0f, 200.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1300.0f, -200.0f, 100.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(1200.0f, 150.0f, 0.0f), 1, 1, 200.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(1300.0f, -200.0f, 0.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1400.0f, -200.0f, -150.0f), D3DXVECTOR2(150.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(1200.0f, -200.0f, -150.0f), D3DXVECTOR2(150.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1300.0f, -200.0f, -300.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(1500.0f, 150.0f, -100.0f), 1, 1, 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(1600.0f, -200.0f, -100.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1500.0f, -200.0f, -200.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(1600.0f, -200.0f, -300.0f), D3DXVECTOR2(100.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(1700.0f, 150.0f, 300.0f), 4, 4, 600.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(2000.0f, -200.0f, 300.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(2300.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// �E
	m_pWall = CWall::Create(D3DXVECTOR3(1700.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(2000.0f, -200.0f, -300.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(2300.0f, 500.0f, 300.0f), 4, 4, 300.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(2300.0f, 500.0f, 1500.0f), 4, 2, 1900.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(2450.0f, -200.0f, 300.0f), D3DXVECTOR2(150.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(2300.0f, -200.0f, 150.0f), D3DXVECTOR2(450.0f, 700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(2300.0f, 500.0f, 1500.0f), 4, 2, 1900.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(2600.0f, 430.0f, 300.0f), 4, 4, 800.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(2450.0f, -200.0f, -300.0f), D3DXVECTOR2(150.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��

	m_pWall = CWall::Create(D3DXVECTOR3(3000.0f, -200.0f, 300.0f), D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(3400.0f, -200.0f, 150.0f), D3DXVECTOR2(150.0f, 700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// �E
	m_pWall = CWall::Create(D3DXVECTOR3(2600.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 700.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(3000.0f, -200.0f, -300.0f), D3DXVECTOR2(400.0f, 630.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);	// ��O
	//��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(3000.0f, 460.0f, 0.0f),D3DXVECTOR3(-1.5f, 0.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR2(400.0f, 300.0f), 0);
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(3400.0f, 430.0f, 0.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(3400.0f, 500.0f, 300.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//��̒�̕�
	m_pWall = CWall::Create(D3DXVECTOR3(3800.0f, -200.0f, -300.0f), D3DXVECTOR2(400.0f, 630.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);	// ��O
	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(3800.0f, -200.0f, 300.0f), D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(3800.0f, -200.0f, 0.0f), D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
	//��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(3800.0f, 460.0f, -150.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(400.0f, 150.0f), 0);

#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(4200.0f, 600.0f, 300.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(4200.0f, 600.0f, 1500.0f), 4, 2, 800.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(4600.0f, -200.0f, 300.0f), D3DXVECTOR2(400.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(4200, -200.0f, 750.0f), D3DXVECTOR2(750.0f, 800.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(4600.0f, -200.0f, 0.0f), D3DXVECTOR2(400.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

	//��̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(4200.0f, 430.0f, 0.0f), 4, 2, 840.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(4600.0f, -200.0f, -300.0f), D3DXVECTOR2(440.0f, 630.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);	// ��O
	m_pGround = CGround::Create(D3DXVECTOR3(4600.0f, 460.0f, -150.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(400.0f, 150.0f), 0);
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5000.0f, 900.0f, 300.0f), 4, 2, 400.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5000.0f, 900.0f, 600.0f), 4, 2, 1800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
	//m_pWall = CWall::Create(D3DXVECTOR3(5200.0f, -200.0f, 300.0f), D3DXVECTOR2(200.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(5400.0f, -200.0f, 150.0f), D3DXVECTOR2(150.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(5000, -200.0f, 300.0f), D3DXVECTOR2(300.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(5200.0f, -200.0f, 0.0f), D3DXVECTOR2(200.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

	//��̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5040.0f, 830.0f, 0.0f), 2, 2, 360.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(5320.0f, -200.0f, -300.0f), D3DXVECTOR2(280.0f, 1030.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);	// ��O
	m_pWall = CWall::Create(D3DXVECTOR3(5040.0f, 400.0f, 0.0f), D3DXVECTOR2(300.0f, 430.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);		// ��
	m_pGround = CGround::Create(D3DXVECTOR3(5300.0f, 860.0f, -150.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(300.0f, 150.0f), 0);
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5000.0f, 900.0f, 300.0f), 4, 2, 400.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(5200.0f, -200.0f, 300.0f), D3DXVECTOR2(200.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(5400.0f, -200.0f, 150.0f), D3DXVECTOR2(150.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(5000, -200.0f, 150.0f), D3DXVECTOR2(150.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(5200.0f, -200.0f, 0.0f), D3DXVECTOR2(200.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

	//��̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5040.0f, 830.0f, 0.0f), 2, 2, 560.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(5040.0f, 400.0f, 0.0f), D3DXVECTOR2(300.0f, 430.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);		// ��

#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5600.0f, 900.0f, 0.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(6000.0f, -200.0f, -300.0f), D3DXVECTOR2(400.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(5600, -200.0f, -150.0f), D3DXVECTOR2(150.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(6000.0f, -200.0f, 0.0f), D3DXVECTOR2(400.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

	// ��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(5000.0f, 650.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.5f), D3DXVECTOR2(210.0f, 150.0f), 0);	// ��

	//��̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5400.0f, 830.0f, 300.0f), 6, 2, 1000.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pGround = CGround::Create(D3DXVECTOR3(5500.0f, 860.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 150.0f), 0);	// ��
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(6400.0f, 900.0f, 0.0f), 1, 1, 400.0f, 300.0f, 0.0f, 200.0f, 0.0f, 200.0f, 1, 0);

	//�ǂ̐���
	//�p�x�����Ă�@
	m_pWall = CWall::Create(D3DXVECTOR3(6600.0f, -200.0f, -300.0f), D3DXVECTOR2(200.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(6600.0f, 900.0f, -300.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(6800.0f, -200.0f, 450.0f), D3DXVECTOR2(150.0f, 1300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(6200.0f, -200.0f, -150.0f), D3DXVECTOR2(150.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	//�p�x�����Ă�@
	m_pWall = CWall::Create(D3DXVECTOR3(6600.0f, -200.0f, 0.0f), D3DXVECTOR2(200.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
	m_pWall = CWall::Create(D3DXVECTOR3(6600.0f, 900.0f, 0.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);	// ��O

	// ��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(6800.0f, 930.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.5f), D3DXVECTOR2(140.0f, 150.0f), 0);	// ��

	//��̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(5400.0f, 830.0f, 300.0f), 6, 2, 1440.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(6120.0f, -200.0f, 300.0f), D3DXVECTOR2(720.0f, 1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pGround = CGround::Create(D3DXVECTOR3(6200.0f, 860.0f, 150.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(600.0f, 150.0f), 0);	// ��
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(6800.0f,1100.0f, 0.0f), 1, 1, 200.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(6800.0f, 1100.0f, 600.0f), 1, 1, 400.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐����@
	m_pWall = CWall::Create(D3DXVECTOR3(6900.0f, -200.0f, -300.0f), D3DXVECTOR2(100.0f, 1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(7000.0f, -200.0f, -150.0f), D3DXVECTOR2(150.0f, 1300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(6900.0f, -200.0f, 0.0f), D3DXVECTOR2(100.0f, 1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

																																	//��̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(6840.0f, 1030.0f, 300.0f), 2, 2, 360.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(7200.0f, 1000.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(6840.0f, -200.0f, 150.0f), D3DXVECTOR2(150.0f, 1230.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 3);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(7000.0f, -200.0f, 300.0f), D3DXVECTOR2(200.0f, 1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��
	m_pGround = CGround::Create(D3DXVECTOR3(7000.0f, 1070.0f, 150.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(200.0f, 150.0f), 0);	// ��
#endif
#if 1
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(7200.0f, 1300.0f, 300.0f), 4, 2, 600.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(7200.0f, 1300.0f, 600.0f), 4, 2, 600.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(7000.0f, 1030.0f, 30.0f), 6, 2, 1100.0f, 330.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(7500.0f, 1000.0f, 0.0f), D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ����O
	m_pWall = CWall::Create(D3DXVECTOR3(7550.0f, -200.0f, -300.0f), D3DXVECTOR2(550.0f, 1230.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);	// ��O
	m_pWall = CWall::Create(D3DXVECTOR3(7800.0f, 1000.0f, 300.0f), D3DXVECTOR2(300.0f, 300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pGround = CGround::Create(D3DXVECTOR3(7100.0f, 1070.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 150.0f), 0);	// ��
	m_pGround = CGround::Create(D3DXVECTOR3(7650.0f, 1070.0f, -150.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(450.0f, 150.0f), 0);	// ��
#endif
#if 1
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(7800.0f, 1230.0f, 600.0f), 2, 2, 300.0f, 570.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8100.0f, 1300.0f, 300.0f), 2, 4, 300.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8100.0f, 1300.0f, 600.0f), 2, 4, 500.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(7950.0f, 1030.0f, 30.0f), D3DXVECTOR2(150.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);	// ����O
	m_pWall = CWall::Create(D3DXVECTOR3(8100.0f, 1000.0f, 150.0f), D3DXVECTOR2(450.0f, 300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �E
	m_pWall = CWall::Create(D3DXVECTOR3(8250.0f, -200.0f, -300.0f), D3DXVECTOR2(150.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
	m_pGround = CGround::Create(D3DXVECTOR3(7950.0f, 1270.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(150.0f, 300.0f), 0);	// ��

	// ��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(7950.0f, 1150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), D3DXVECTOR2(150.0f, 120.0f), 0);
#endif
#if 1
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8400.0f, 1300.0f, 0.0f), 1, 2, 200.0f, 300.0f, 0.0f, 100.0f, 0.0f, 100.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8600.0f, 1400.0f, 0.0f), 1, 2, 200.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8600.0f, 1400.0f, 150.0f), 1, 1, 200.0f, 150.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8600.0f, 1500.0f, 300.0f), 1, 1, 200.0f, 150.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8600.0f, 1500.0f, 600.0f), 10, 2, 2300.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8400.0f, 1230.0f, 300.0f), 2, 2, 200.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);

	m_pWall = CWall::Create(D3DXVECTOR3(8500.0f, 1100.0f, 0.0f), D3DXVECTOR2(100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8600.0f, 1100.0f, 150.0f), D3DXVECTOR2(150.0f, 300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 6);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8600.0f, 1300.0f, 375.0f), D3DXVECTOR2(225.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 6);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8600.0f, 1400.0f, 75.0f), D3DXVECTOR2(75.0f, 100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 4);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8400.0f, 1100.0f, 150.0f), D3DXVECTOR2(150.0f, 200.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), 6);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8500.0f, 1100.0f, 300.0f), D3DXVECTOR2(100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8600.0f, -200.0f, -300.0f), D3DXVECTOR2(200.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8700.0f, 1300.0f, -300.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8500.0f, 1300.0f, -300.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(9500.0f, 1300.0f, 300.0f), D3DXVECTOR2(600.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// �r

	// �r�̐���
	m_pGround = CGround::Create(D3DXVECTOR3(8500.0f, 1270.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 150.0f), 0);	// ��

#endif
#if 1
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(8800.0f, 1500.0f, 300.0f), 1, 2, 200.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(8900.0f, -200.0f, -300.0f), D3DXVECTOR2(100.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(8800.0f, 1300, -50.0f), D3DXVECTOR2(250.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(9000.0f, 1300, 0.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �r

#endif
#if 1
	//��
	m_pGround = CGround::Create(D3DXVECTOR3(9550.0f, 1470.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(550.0f, 300.0f), 0);	// ��

#endif
#if 1
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(10100.0f, 1500.0f, 300.0f), 1, 2, 800.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(9000.0f, 1430.0f, 300.0f), 6, 4, 1100.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(9550.0f, 500.0f, -300.0f), D3DXVECTOR2(550.0f, 930.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(10500.0f, 500.0f, -300.0f), D3DXVECTOR2(400.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(10100.0f, 1300, 0.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(10900.0f, 1500, 150.0f), D3DXVECTOR2(450.0f, 250.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �r
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(10900.0f, 1750.0f, 600.0f), 1, 1, 900.0f, 900.0f, 0.0f, 150.0f, 0.0f, 150.0f, 1, 0);
	m_pWall = CWall::Create(D3DXVECTOR3(11200.0f, 500.0f, -300.0f), D3DXVECTOR2(300.0f, 1250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// �r
	m_pWall = CWall::Create(D3DXVECTOR3(11200.0f, 1750.0f, -300.0f), D3DXVECTOR2(300.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7);	// �r
#endif

	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(900.0f, -200.0f, 300.0f), 4, 4, 800.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2, 0);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CGame::CreateObject(void)
{
#if 1 // �W�����v���ēn��n��
	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(1680.0f, -180.0f, 270.0f), 0);// apple

#endif
#if 1	// 1�ڂ̊R�O
	//�I�u�W�F�N�g�̐��� �ۑ�(�K�i��)
	m_pObject = CObject::Create(D3DXVECTOR3(1800.0f, 200.0f, -50.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(1860.0f, 250.0f, 60.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(1960.0f, 300.0f, 150.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(2090.0f, 350.0f, 150.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(2200.0f, 400.0f, 60.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(2270.0f, 450.0f, -50.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(2270.0f, 150.0f, 150.0f), 0);// apple

#endif
#if 1	// 1�ڂ̐�̓n��
	//�I�u�W�F�N�g�̐��� ���̏�̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2700.0f, 450.0f, 150.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(2850.0f, 450.0f, 10.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(3000.0f, 450.0f, 150.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(3150.0f, 450.0f, 10.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(3300.0f, 450.0f, 150.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);

#endif
#if 1	// 1�ڂ̐�̉��̓�
	// 1�i��
	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(3650.0f, 550.0f, 600.0f), -5.0f, 6, 8, CObject::MOVETYPE_Z_MOVE, 1);
	//�I�u�W�F�N�g�̐��� ���D(�ۑ�)
	m_pObject = CObject::Create(D3DXVECTOR3(3650.0f, 600.0f, 990.0f), -5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3650.0f, 600.0f, 610.0f), -5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);

	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(3950.0f, 550.0f, -50.0f), 5.0f, 6, 8, CObject::MOVETYPE_Z_MOVE, 1);
	//�I�u�W�F�N�g�̐��� ���D(�ۑ�)
	m_pObject = CObject::Create(D3DXVECTOR3(3950.0f, 600.0f, 340.0f), 5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3950.0f, 600.0f, -40.0f), 5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);

	// 2�i��
	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(4300.0f, 650.0f, 600.0f), -5.0f, 6, 8, CObject::MOVETYPE_Z_MOVE, 1);
	//�I�u�W�F�N�g�̐��� ���D(�ۑ�)
	m_pObject = CObject::Create(D3DXVECTOR3(4300.0f, 700.0f, 990.0f), -5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4300.0f, 700.0f, 990.0f), -5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);

	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(4600.0f, 650.0f, -50.0f), 5.0f, 6, 8, CObject::MOVETYPE_Z_MOVE, 1);
	//�I�u�W�F�N�g�̐��� ���D(�ۑ�)
	m_pObject = CObject::Create(D3DXVECTOR3(4600.0f, 700.0f, 340.0f), 5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4600.0f, 700.0f, -40.0f), 5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);

	//�I�u�W�F�N�g�̐��� ��
	m_pObject = CObject::Create(D3DXVECTOR3(4850.0f, 750.0f, 200.0f), 2.0f, 0, 0, CObject::MOVETYPE_Y_MOVE, 1);
	//�I�u�W�F�N�g�̐��� ���D(��)
	m_pObject = CObject::Create(D3DXVECTOR3(4950.0f, 750.0f, 300.0f), 2.0f, 5, 1, CObject::MOVETYPE_Y_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4750.0f, 750.0f, 300.0f), 2.0f, 5, 1, CObject::MOVETYPE_Y_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4950.0f, 750.0f, 100.0f), 2.0f, 5, 1, CObject::MOVETYPE_Y_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4750.0f, 750.0f
		, 100.0f), 2.0f, 5, 1, CObject::MOVETYPE_Y_MOVE, 0);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(4300.0f, 800.0f, 150.0f), 0);// apple

#endif
#if 1	// 1�ڂ̑�̏㗬
	//�I�u�W�F�N�g�̐��� ���̏�̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5100.0f, 850.0f, -250.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5140.0f, 840.0f, -20.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5100.0f, 850.0f, -40.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	//�@�I�u�W�F�N�g�̐����@����
	m_pObject = CObject::Create(D3DXVECTOR3(5130.0f, 870.0f, -140.0f), 0.0f, 4, 5, CObject::MOVETYPE_NOT, 1);

	//�I�u�W�F�N�g�̐��� ���̏�̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5450.0f, 850.0f, 105.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5300.0f, 850.0f, -100.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5500.0f, 850.0f, -130.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);

#endif
#if 1	// 2�ڂ̑����
	// �I�u�W�F�N�g�̐��� �ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(5630.0f, 900.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5690.0f, 900.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5630.0f, 960.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5690.0f, 960.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	// ��
	m_pGround = CGround::Create(D3DXVECTOR3(5820.0f, 950.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f, 3.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 200.0f), 1);
	// �I�u�W�F�N�g�̐��� �ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(5950.0f, 900.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6010.0f, 900.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5950.0f, 960.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6010.0f, 960.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	// ��
	m_pGround = CGround::Create(D3DXVECTOR3(6140.0f, 950.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f, 3.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 200.0f), 1);
	// �I�u�W�F�N�g�̐��� �ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(6270.0f, 900.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6330.0f, 900.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6270.0f, 960.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6330.0f, 960.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(5980.0f, 1050.0f, -270.0f), 0);// apple

#endif
#if 1	// 2�ڂ̑�̏㗬
	//�I�u�W�F�N�g�̐��� ���̏�̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1070.0f, 250.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6940.0f, 1050.0f, 70.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1060.0f, 35.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);
	//�@�I�u�W�F�N�g�̐����@����
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1090.0f, 140.0f), 0.0f, 4, 5, CObject::MOVETYPE_NOT, 1);

#endif
#if 1	// 3�ڂ̑�̉��ւ̓�
	//�I�u�W�F�N�g�̐��� ���̏�̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7150.0f, 1060.0f, -150.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);

	//�@�I�u�W�F�N�g�̐����@�ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(7290.0f, 1150.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7310.0f, 1150.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7440.0f, 1250.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7460.0f, 1250.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7690.0f, 1070.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7710.0f, 1070.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(7700.0f, 1100.0f, -40.0f), 1);// banana
#endif
#if 1	// 3�ڂ̑����
	// �I�u�W�F�N�g�̐��� �ؔ�(���Ƃ��p)
	m_pObject = CObject::Create(D3DXVECTOR3(7300.0f, 1350.0f, 220.0f), -5.0f, 7, 9, CObject::MOVETYPE_Z_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7450.0f, 1350.0f, -400.0f), 5.0f, 7, 9, CObject::MOVETYPE_Z_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7700.0f, 1350.0f, 220.0f), -5.0f, 7, 9, CObject::MOVETYPE_Z_MOVE, 1);

	//�I�u�W�F�N�g�̐��� ���D(�ؔ�)
	m_pObject = CObject::Create(D3DXVECTOR3(7300.0f, 1400.0f, 220.0f), -5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7450.0f, 1400.0f, -400.0f), 5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7700.0f, 1400.0f, 220.0f), -5.0f, 5, 1, CObject::MOVETYPE_Z_MOVE, 0);

	// �I�u�W�F�N�g�̐��� �ؔ�(��)
	m_pObject = CObject::Create(D3DXVECTOR3(7830.0f, 1240.0f, 150.0f), 0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7910.0f, 1240.0f, 150.0f), -0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7990.0f, 1240.0f, 150.0f), 0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8070.0f, 1240.0f, 150.0f), -0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);

#endif
#if 1	// 3�ڂ̑��n������
	// �I�u�W�F�N�g�̐��� �ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(8130.0f, 1300.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8130.0f, 1360.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8130.0f, 1300.0f, -210.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8190.0f, 1300.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);

	// �I�u�W�F�N�g�̐��� �r�̖ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(8550.0f, 1240.0f, 250.0f), 0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(8130.0f, 1450.0f, -270.0f), 1);// banana
	m_pItem = CItem::Create(D3DXVECTOR3(8550.0f, 1320.0f, 250.0f), 0);// apple

#endif
#if 1	// 1�ԍŌ�̐�
	// �I�u�W�F�N�g�̐��� �ۑ�(�ړ���)
	m_pObject = CObject::Create(D3DXVECTOR3(9050, 1500, 220.0f), 2.0f, 3, 10, CObject::MOVETYPE_X_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(9300, 1500, -200.0f), -2.0f, 3, 10, CObject::MOVETYPE_X_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(9400, 1500, -230.0f), 4.0f, 3, 10, CObject::MOVETYPE_Z_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(9500, 1500, -200.0f), 3.0f, 3, 10, CObject::MOVETYPE_X_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(9850, 1500, 200.0f), -3.0f, 3, 10, CObject::MOVETYPE_X_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(10000, 1500, 230.0f), -4.0f, 3, 10, CObject::MOVETYPE_Z_MOVE, 1);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(9600.0f, 1500.0f, 230.0f), 0);// apple
#endif
#if 1	// ��
	m_pObject = CObject::Create(D3DXVECTOR3(10600, 1500, 0.0f), 0.0f, 15, 13, CObject::MOVETYPE_HOUSE, 1);

	//�A�C�e���̐���
	m_pItem = CItem::Create(D3DXVECTOR3(10850, 1500.0f, 0.0f), 0);// apple
	m_pItem = CItem::Create(D3DXVECTOR3(10850, 1500.0f, 150.0f), 1);// banana

#endif

	//==========================
	//   ��ʊO�̃I�u�W�F�N�g
	//==========================
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(-200.0f, 0.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(-200.0f, 0.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(-100.0f, 0.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(-100.0f, 0.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(0.0f, 0.0f,550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(100.0f, 0.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(100.0f, 0.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(220.0f, 0.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(220.0f, 0.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(400.0f, 150.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(400.0f, 150.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(500.0f, 150.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(500.0f, 150.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(600.0f, 150.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(600.0f, 150.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(700.0f, 150.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(700.0f, 150.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(820.0f, 150.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(820.0f, 150.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(900.0f, 150.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(900.0f, 150.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1000.0f, 150.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1000.0f, 150.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1100.0f, 150.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1100.0f, 150.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1200.0f, 150.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1200.0f, 150.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1320.0f, 150.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1320.0f, 150.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1400.0f, 150.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1400.0f, 150.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1500.0f, 150.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1500.0f, 150.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1600.0f, 150.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1600.0f, 150.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1700.0f, 150.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1700.0f, 150.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1820.0f, 150.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1820.0f, 150.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(1900.0f, 150.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1900.0f, 150.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2000.0f, 150.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2000.0f, 150.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2100.0f, 150.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2100.0f, 150.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2200.0f, 150.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2200.0f, 150.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2400.0f, 500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2400.0f, 500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2500.0f, 500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2500.0f, 500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2600.0f, 500.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2600.0f, 500.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2700.0f, 500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2700.0f, 500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2820.0f, 500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2820.0f, 500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(2900.0f, 500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2900.0f, 500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3000.0f, 500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3000.0f, 500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3100.0f, 500.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3100.0f, 500.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3200.0f, 500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3200.0f, 500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3320.0f, 500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3320.0f, 500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3400.0f, 500.0f, 1250.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3400.0f, 500.0f, 1250.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3500.0f, 500.0f, 1180.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3500.0f, 500.0f, 1180.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3600.0f, 500.0f, 1350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3600.0f, 500.0f, 1350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3700.0f, 500.0f, 1150.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3700.0f, 500.0f, 1150.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3820.0f, 500.0f, 1200.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3820.0f, 500.0f, 1200.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3900.0f, 500.0f, 1350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3900.0f, 500.0f, 1350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4000.0f, 500.0f, 1150.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4000.0f, 500.0f, 1150.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4120.0f, 500.0f, 1200.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4120.0f, 500.0f, 1200.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4320.0f, 600.0f, 1250.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4320.0f, 600.0f, 1250.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4400.0f, 600.0f, 1180.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4400.0f, 600.0f, 1180.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4500.0f, 600.0f, 1350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4500.0f, 600.0f, 1350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4600.0f, 600.0f, 1150.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4600.0f, 600.0f, 1150.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4720.0f, 600.0f, 1200.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4720.0f, 600.0f, 1200.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4800.0f, 600.0f, 1150.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4800.0f, 600.0f, 1150.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4920.0f, 600.0f, 1200.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4920.0f, 600.0f, 1200.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5100.0f, 900.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5100.0f, 900.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5200.0f, 900.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5200.0f, 900.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5300.0f, 900.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5300.0f, 900.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5400.0f, 900.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5400.0f, 900.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5520.0f, 900.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5520.0f, 900.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5600.0f, 900.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5600.0f, 900.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5700.0f, 900.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5700.0f, 900.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5800.0f, 900.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5800.0f, 900.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(5900.0f, 900.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5900.0f, 900.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6020.0f, 900.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6020.0f, 900.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6100.0f, 900.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6100.0f, 900.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6200.0f, 900.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6200.0f, 900.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6300.0f, 900.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6300.0f, 900.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6400.0f, 900.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6400.0f, 900.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6520.0f, 900.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6520.0f, 900.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6600.0f, 900.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6600.0f, 900.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6700.0f, 900.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6700.0f, 900.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1100.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1100.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7000.0f, 1100.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7000.0f, 1100.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7100.0f, 1100.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7100.0f, 1100.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7300.0f, 1300.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7300.0f, 1300.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7400.0f, 1300.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7400.0f, 1300.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7500.0f, 1300.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7500.0f, 1300.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7600.0f, 1300.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7600.0f, 1300.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(7720.0f, 1300.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7720.0f, 1300.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8200.0f, 1300.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8200.0f, 1300.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8300.0f, 1300.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8300.0f, 1300.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8400.0f, 1300.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8400.0f, 1300.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8500.0f, 1300.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8500.0f, 1300.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8700.0f, 1500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8700.0f, 1500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8800.0f, 1500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8800.0f, 1500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(8900.0f, 1500.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8900.0f, 1500.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9000.0f, 1500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9000.0f, 1500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9120.0f, 1500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9120.0f, 1500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9200.0f, 1500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9200.0f, 1500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9300.0f, 1500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9300.0f, 1500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9400.0f, 1500.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9400.0f, 1500.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9500.0f, 1500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9500.0f, 1500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9620.0f, 1500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9620.0f, 1500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9700.0f, 1500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9700.0f, 1500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9800.0f, 1500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9800.0f, 1500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(9900.0f, 1500.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9900.0f, 1500.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10000.0f, 1500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10000.0f, 1500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10120.0f, 1500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10120.0f, 1500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10200.0f, 1500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10200.0f, 1500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10300.0f, 1500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10300.0f, 1500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10400.0f, 1500.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10400.0f, 1500.0f, 550.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10500.0f, 1500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10500.0f, 1500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10620.0f, 1500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10620.0f, 1500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10700.0f, 1500.0f, 350.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10700.0f, 1500.0f, 350.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(10820.0f, 1500.0f, 400.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10820.0f, 1500.0f, 400.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
#endif
#if 1
	//��
	m_pObject = CObject::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(-200.0f, 0.0f, 100.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(200.0f, 0.0f, -200.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 150.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(165.0f, 0.0f, 500.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(-200.0f, 0.0f, -150.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

#endif
#if 1
	m_pObject = CObject::Create(D3DXVECTOR3(400.0f, 150.0f, 300.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(820.0f, 150.0f, -100.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(800.0f, 150.0f, -230.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(600.0f, 150.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(670.0f, 150.0f, -230.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

#endif
#if 1
	m_pObject = CObject::Create(D3DXVECTOR3(1000.0f, 150.0f, 500.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1300.0f, 150.0f, 350.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1370.0f, 150.0f, 530.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

#endif
#if 1
	m_pObject = CObject::Create(D3DXVECTOR3(1700.0f, 150.0f, -200.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(1800.0f, 150.0f, 200.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2000.0f, 150.0f, 500.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2200.0f, 150.0f, 300.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2200.0f, 150.0f, -200.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

#endif
#if 1
	m_pObject = CObject::Create(D3DXVECTOR3(2400.0f, 500.0f, -200.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2500.0f, 500.0f, 350.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(2530.0f, 500.0f, -100.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3000.0f, 500.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3200.0f, 500.0f, 470.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3300.0f, 500.0f, 360.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4900.0f, 600.0f, 100.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4750.0f, 600.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3400.0f, 500.0f, 450.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3400.0f, 500.0f, 450.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3430.0f, 500.0f, 700.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3430.0f, 500.0f, 700.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3500.0f, 500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3500.0f, 500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(3820.0f, 500.0f, 500.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(3820.0f, 500.0f, 500.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4050.0f, 500.0f, 380.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4050.0f, 500.0f, 380.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4150.0f, 500.0f, 670.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4150.0f, 500.0f, 670.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4500.0f, 600.0f, 540.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4500.0f, 600.0f, 540.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4700.0f, 600.0f, 670.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4700.0f, 600.0f, 670.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4850.0f, 600.0f, 540.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4850.0f, 600.0f, 540.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
	//�؂̊�
	m_pObject = CObject::Create(D3DXVECTOR3(4880.0f, 600.0f, 800.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(4880.0f, 600.0f, 800.0f), 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);

	//�r���{�[�h�̐���
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3400.0f, 540.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3450.0f, 540.0f, 1150.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3550.0f, 540.0f, 1100.0f), D3DXVECTOR2(100, 40), 0);

	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3600.0f, 540.0f, 1300.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3650.0f, 540.0f, 1250.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3750.0f, 540.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);

	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3800.0f, 540.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3850.0f, 540.0f, 1150.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(3950.0f, 540.0f, 1100.0f), D3DXVECTOR2(100, 40), 0);

	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4000.0f, 540.0f, 1300.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4050.0f, 540.0f, 1250.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4150.0f, 540.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);

	//�r���{�[�h�̐���
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4300.0f, 640.0f, 1150.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4350.0f, 640.0f, 1100.0f), D3DXVECTOR2(100, 40), 0);

	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4400.0f, 640.0f, 1300.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4450.0f, 640.0f, 1250.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4550.0f, 640.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);

	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4600.0f, 640.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4650.0f, 640.0f, 1150.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4750.0f, 640.0f, 1100.0f), D3DXVECTOR2(100, 40), 0);

	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4800.0f, 640.0f, 1300.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4850.0f, 640.0f, 1250.0f), D3DXVECTOR2(100, 40), 0);
	m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(4950.0f, 640.0f, 1200.0f), D3DXVECTOR2(100, 40), 0);

#endif
	m_pObject = CObject::Create(D3DXVECTOR3(5100.0f, 900.0f, 350.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5300.0f, 900.0f, 490.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5600.0f, 900.0f, 550.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(5760.0f, 900.0f, 390.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6300.0f, 900.0f, 350.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6400.0f, 900.0f, 550.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6700.0f, 900.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1100.0f, 350.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7100.0f, 1100.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(7300.0f, 1300.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7500.0f, 1300.0f, 350.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7600.0f, 1300.0f, 500.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(7700.0f, 1300.0f, 100.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(8200.0f, 1300.0f, 200.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8300.0f, 1300.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8350.0f, 1300.0f, 530.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8500.0f, 1300.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(8300.0f, 1300.0f, -100.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(8730.0f, 1400.0f, -220.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(8900.0f, 1500.0f, -230.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(8900.0f, 1500.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9050.0f, 1500.0f, 530.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9100.0f, 1500.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9200.0f, 1500.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9350.0f, 1500.0f, 530.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(9500.0f, 1500.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(9900.0f, 1500.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(10300.0f, 1500.0f, 400.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10400.0f, 1500.0f, 530.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(D3DXVECTOR3(10500.0f, 1500.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	m_pObject = CObject::Create(D3DXVECTOR3(10750.0f, 1500.0f, 450.0f), 0.0f, 8, 11, CObject::MOVETYPE_NOT, 0);

	//�Ŕ�
	m_pObject = CObject::Create(D3DXVECTOR3(200.0f, 0.0f, 350.0f), 0.0f, 9, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(870.0f, 150.0f, 350.0f), 0.0f, 11, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(1800.0f, 150.0f, 350.0f), 0.0f, 9, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(2500.0f, 500.0f, 350.0f), 0.0f, 12, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(3400.0f, 500.0f, 350.0f), 0.0f, 10, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(4850.0f, 600.0f, 350.0f), 0.0f, 13, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5300.0f, 900.0f, 350.0f), 0.0f, 12, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5500.0f, 900.0f, 350.0f), 0.0f, 14, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7100.0f, 1100.0f, 350.0f), 0.0f, 12, 12, CObject::MOVETYPE_NOT, 1);

	//�ŐV��
	m_pObject = CObject::Create(D3DXVECTOR3(7700.0f, 1300.0f, 350.0f), 0.0f, 10, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8400.0f, 1300.0f, 350.0f), 0.0f, 9, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8700.0f, 1500.0f, 350.0f), 0.0f, 12, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8900.0f, 1500.0f, 350.0f), 0.0f, 11, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(5100.0f, 900.0f, 350.0f), 0.0f, 11, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1100.0f, 350.0f), 0.0f, 9, 12, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(6900.0f, 1100.0f, 350.0f), 0.0f, 9, 12, CObject::MOVETYPE_NOT, 1);

}
//=============================================================================
//
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;

	switch (m_bPause)
	{
	case true:
		if (m_pPause == NULL)
		{
			//�|�[�Y�̐���
			m_pPause = CPause::Create();

			CScene::SetUpdatePri(7);
		}
		break;
	case false:
		if (m_pPause != NULL)
		{
			m_pPause->Uninit();
			m_pPause = NULL;

			CScene::SetUpdatePri(0);
		}
	}
}
