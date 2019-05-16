//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �L�n ���u & �r�J �R�N
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"
#include "titletex.h"
#include "wall.h"
#include "ground.h"
#include "billboord.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CBillBoord		*CTitle::m_pBillBoord	= NULL;
CPolygon3D		*CTitle::m_pPolygon3D	= NULL;
CMeshField		*CTitle::m_pMeshField	= NULL;
CObject			*CTitle::m_pObject		= NULL;
CModel			*CTitle::m_pModel		= NULL;
CEffect			*CTitle::m_pEffect		= NULL;
CWall			*CTitle::m_pWall		= NULL;
CGround			*CTitle::m_pGround		= NULL;
CTitle::TYPE	CTitle::m_pType			= TYPE_NONE;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_nCnt		= 0;
	m_nCount	= 0;
	m_nLeafposY = 0;
	m_nLeafsize = 0;
	m_nLagCnt	= 0;
	m_pType		= TYPE_NONE;
	m_bOnOff = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init()
{
	srand((unsigned int)time(0));		// �����_���̂��
	//===================================
	//		 Load�̓ǂݍ��ݏꏊ
	//===================================
	//�t�F�[�h�̃e�N�X�`���̓ǂݍ���
	CFade::Load();

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

	CTitletex::Load();

	//===================================
	//		 ����
	//===================================
	Set();
	CreateStage();
	CreateObject();


	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//===================================
	//	�@�@UnLoad�̔j������ꏊ
	//===================================
	//���b�V���t�B�[���h�e�N�X�`���̔j��
	m_pMeshField->UnLoad();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->UnLoad();

	CTitletex::UnLoad();

	//���b�V���t�B�[���h�̔j��
	m_pMeshField->Uninit();
	m_pMeshField = NULL;

	//�t�F�[�h�ȊO�폜
	CScene::NotFadeReleseAll();
}
//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�t�F�[�h�̃|�C���g
	CFade::FADE pFade = CFade::GetFade();

	if (m_pType == TYPE_NONE)
	{// �X�L�b�v����Ȃ��Ƃ�
		if (m_nCnt == 150)
		{//��
			CTitletex::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 3);
		}
		else if (m_nCnt == ISLAND_STERT)
		{
			CTitletex::Create(D3DXVECTOR3(675.0f, 260.0f, 0.0f), D3DXVECTOR2(20.0f, 50.0f), 12);	//�uI�v
		}
		else if (m_nCnt == ISLAND_STERT + 15)
		{
			CTitletex::Create(D3DXVECTOR3(730.0f, 270.0f, 0.0f), D3DXVECTOR2(27.0f, 38.0f), 13);	//�us�v
		}
		else if (m_nCnt == ISLAND_STERT + 30)
		{
			CTitletex::Create(D3DXVECTOR3(772.0f, 260.0f, 0.0f), D3DXVECTOR2(8.0f, 50.0f), 14);		//�ul�v
		}
		else if (m_nCnt == ISLAND_STERT + 45)
		{
			CTitletex::Create(D3DXVECTOR3(815.0f, 270.0f, 0.0f), D3DXVECTOR2(25.0f, 37.0f), 15);	//�ua�v
		}
		else if (m_nCnt == ISLAND_STERT + 60)
		{
			CTitletex::Create(D3DXVECTOR3(875.0f, 270.0f, 0.0f), D3DXVECTOR2(25.0f, 37.0f), 16);	//�un�v
		}
		else if (m_nCnt == ISLAND_STERT + 75)
		{
			CTitletex::Create(D3DXVECTOR3(932.0f, 260.0f, 0.0f), D3DXVECTOR2(25.0f, 50.0f), 17);	//�ud�v
		}
		else if (m_nCnt == ISLAND_STERT + 100)
		{
			CTitletex::Create(D3DXVECTOR3(902.0f, 370.0f, 0.0f), D3DXVECTOR2(230.0f + SUBTITLE_INITSIZE, 150.0f + SUBTITLE_INITSIZE), 5);	// �T�u�^�C�g��
		}
	}
	else if (m_pType == TYPE_SKIP)
	{
		if (m_nCount == 401)
		{
			CTitletex::Create(D3DXVECTOR3(675.0f, 260.0f, 0.0f), D3DXVECTOR2(20.0f, 50.0f), 12);	//�uI�v
			CTitletex::Create(D3DXVECTOR3(730.0f, 270.0f, 0.0f), D3DXVECTOR2(27.0f, 38.0f), 13);	//�us�v
			CTitletex::Create(D3DXVECTOR3(772.0f, 260.0f, 0.0f), D3DXVECTOR2(8.0f, 50.0f), 14);		//�ul�v
			CTitletex::Create(D3DXVECTOR3(815.0f, 270.0f, 0.0f), D3DXVECTOR2(25.0f, 37.0f), 15);	//�ua�v
			CTitletex::Create(D3DXVECTOR3(875.0f, 270.0f, 0.0f), D3DXVECTOR2(25.0f, 37.0f), 16);	//�un�v
			CTitletex::Create(D3DXVECTOR3(932.0f, 260.0f, 0.0f), D3DXVECTOR2(25.0f, 50.0f), 17);	//�ud�v
			CTitletex::Create(D3DXVECTOR3(902.0f, 370.0f, 0.0f), D3DXVECTOR2(230.0f + SUBTITLE_INITSIZE, 150.0f + SUBTITLE_INITSIZE), 5);	// �T�u�^�C�g��
		}
	}
	if (m_nCount >= 370)
	{// ������������
		if ((m_nCount % (rand() % 50 + 10)) == 0)
		{// �����t
			if (rand() % 2 == 0)
			{// ��
				m_nLeafposY = (rand() % (SCREEN_HEIGHT + 200) + 100);		// Y���̐���
				m_nLeafsize = (rand() % 70 + 50);							// �T�C�Y�̐���
				CTitletex::Create(D3DXVECTOR3(-10.0f, (float)m_nLeafposY, 0.0f), D3DXVECTOR2((float)m_nLeafsize, (float)m_nLeafsize), 24);
			}
			else
			{// ��
				m_nLeafposY = (rand() % (SCREEN_HEIGHT + 200) + 100);		// Y���̐���
				m_nLeafsize = (rand() % 30 + 10);							// �T�C�Y�̐���
				CTitletex::Create(D3DXVECTOR3(-10.0f, (float)m_nLeafposY, 0.0f), D3DXVECTOR2((float)m_nLeafsize, (float)m_nLeafsize), 25);
			}
		}
	}

	if (pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputKeyBoard->GetKeyboardAny(1) == true || pCInputMouse->GetMouseTrigger(0) == true)
	{//�^�C�g������Q�[����

		if (m_nLagCnt >= 1)
		{
			//�t�F�[�h���n�܂�����
			if (pFade == CFade::FADE_NONE)
			{
				//�|�[�Y�̑I���̌��艹
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
				CFade::Create(CManager::MODE_TUTORIAL);
			}
		}
		else if (m_nCount <= 400)
		{
			m_pType = TYPE_SKIP;	// �X�L�b�v��Ԃɂ���
			m_nCount = 400;			// ������������ɂ���
		}
		m_nLagCnt++;
	}

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

	m_nCnt++;		// �e�N�X�`����Create�J�E���^�[
	m_nCount++;		// �����t��Create�J�E���^�[
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}
void CTitle::Set(void)
{
		CTitletex::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(370.0f, 150.0f), 2);	// ��
																																//�uNature Island�v
		CTitletex::Create(D3DXVECTOR3(340.0f, 140.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(30.0f, 50.0f), 6);	//�uN�v
		CTitletex::Create(D3DXVECTOR3(405.0f, 155.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(25.0f, 37.0f), 7);	//�ua�v
		CTitletex::Create(D3DXVECTOR3(455.0f, 140.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(20.0f, 50.0f), 8);	//�ut�v
		CTitletex::Create(D3DXVECTOR3(510.0f, 152.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(27.0f, 38.0f), 9);	//�uu�v
		CTitletex::Create(D3DXVECTOR3(570.0f, 153.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(22.0f, 38.0f), 10);	//�ur�v
		CTitletex::Create(D3DXVECTOR3(620.0f, 153.0f - TITLEWORD_INITPOS_Y, 0.0f), D3DXVECTOR2(25.0f, 38.0f), 11);	//�ue�v

		CTitletex::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR2(175.0f, 70.0f), 18);	// AnyButton

		CTitletex::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 26);	// ���w�i
		CTitletex::Create(D3DXVECTOR3((SCREEN_WIDTH / 4) * 1, 450.0f, 0.0f), D3DXVECTOR2(350.0f, 300.0f), 21);								// green3.png
		CTitletex::Create(D3DXVECTOR3((SCREEN_WIDTH / 4) * 3, 450.0f, 0.0f), D3DXVECTOR2(350.0f, 300.0f), 23);								// green3.png
		CTitletex::Create(D3DXVECTOR3((SCREEN_WIDTH / 4) * 1, 320.0f, 0.0f), D3DXVECTOR2(350.0f, 450.0f), 20);								// green2.png
		CTitletex::Create(D3DXVECTOR3((SCREEN_WIDTH / 4) * 3, 320.0f, 0.0f), D3DXVECTOR2(350.0f, 450.0f), 22);								// green2.png
		CTitletex::Create(D3DXVECTOR3((SCREEN_WIDTH / 4) * 1, 450.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 4.0f, 300.0f), 0);					// green0.png
		CTitletex::Create(D3DXVECTOR3((SCREEN_WIDTH / 4) * 3, 450.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 4.0f, 300.0f), 1);					// green0.png
		CTitletex::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 390.0f, 0.0f), D3DXVECTOR2(640.0f, 380.0f), 19);									// green1.png
}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CTitle::CreateStage(void)
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
	m_pWall = CWall::Create(D3DXVECTOR3(-300.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -200.0f, -300.0f), D3DXVECTOR2(300.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(300.0f, 150.0f, 300.0f), 4, 4, 600.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(300.0f, 150.0f, 600.0f), 4, 2, 600.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
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
	m_pWall = CWall::Create(D3DXVECTOR3(2300.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// �E
	m_pWall = CWall::Create(D3DXVECTOR3(1700.0f, -200.0f, 0.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// ��
	m_pWall = CWall::Create(D3DXVECTOR3(2000.0f, -200.0f, -300.0f), D3DXVECTOR2(300.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(2300.0f, 500.0f, 300.0f), 4, 4, 300.0f, 600.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(2300.0f, 500.0f, 1500.0f), 4, 2, 1900.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//�ǂ̐���
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
	m_pGround = CGround::Create(D3DXVECTOR3(3000.0f, 460.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(400.0f, 300.0f), 0);
#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(3400.0f, 430.0f, 0.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(3400.0f, 500.0f, 300.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	//��̒�̕�
	m_pWall = CWall::Create(D3DXVECTOR3(3800.0f, -200.0f, -300.0f), D3DXVECTOR2(400.0f, 630.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);	// ��O
	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(3800.0f, -200.0f, 0.0f), D3DXVECTOR2(400.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O
	//��̐���
	m_pGround = CGround::Create(D3DXVECTOR3(3800.0f, 460.0f, -150.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(400.0f, 150.0f), 0);

#endif
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(4200.0f, 600.0f, 300.0f), 4, 2, 800.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(4200.0f, 600.0f, 1500.0f), 4, 2, 800.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
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
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(6800.0f, 1100.0f, 0.0f), 1, 1, 200.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);
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
}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CTitle::CreateObject(void)
{
#if 1	// 1�ڂ̊R�O
	//�I�u�W�F�N�g�̐��� �ۑ�(�K�i��)
	m_pObject = CObject::Create(D3DXVECTOR3(1800.0f, 200.0f, -50.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);// �c
	m_pObject = CObject::Create(D3DXVECTOR3(1860.0f, 250.0f, 60.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);// �c
	m_pObject = CObject::Create(D3DXVECTOR3(1960.0f, 300.0f, 150.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);// �c
	m_pObject = CObject::Create(D3DXVECTOR3(2090.0f, 350.0f, 150.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);// �c
	m_pObject = CObject::Create(D3DXVECTOR3(2200.0f, 400.0f, 60.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);// �c
	m_pObject = CObject::Create(D3DXVECTOR3(2270.0f, 450.0f, -50.0f), 0.0f, 3, 6, CObject::MOVETYPE_NOT, 1);// �c

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
	m_pObject = CObject::Create(D3DXVECTOR3(3650.0f, 550.0f, 400.0f), 0.0f, 6, 8, CObject::MOVETYPE_NOT, 1);

	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(3950.0f, 550.0f, 400.0f), 0.0f, 6, 8, CObject::MOVETYPE_NOT, 1);

	// 2�i��
	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(4300.0f, 650.0f, 400.0f), 0.0f, 6, 8, CObject::MOVETYPE_NOT, 1);

	// �I�u�W�F�N�g�̐��� �ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(4600.0f, 650.0f, 400.0f), 0.0f, 6, 8, CObject::MOVETYPE_NOT, 1);

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
	m_pObject = CObject::Create(D3DXVECTOR3(7150.0f, 1070.0f, -150.0f), 0.0f, 1, 2, CObject::MOVETYPE_NOT, 1);

	//�@�I�u�W�F�N�g�̐����@�ۑ�
	m_pObject = CObject::Create(D3DXVECTOR3(7290.0f, 1150.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7310.0f, 1150.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7440.0f, 1250.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7460.0f, 1250.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7690.0f, 1070.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7710.0f, 1070.0f, -100.0f), 0.0f, 3, 7, CObject::MOVETYPE_NOT, 1);

#endif
#if 1	// 3�ڂ̑����
	// �I�u�W�F�N�g�̐��� �ؔ�(��)
	m_pObject = CObject::Create(D3DXVECTOR3(7830.0f, 1240.0f, 150.0f), 0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7910.0f, 1240.0f, 150.0f), -0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(7990.0f, 1240.0f, 150.0f), 0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8070.0f, 1240.0f, 150.0f), -0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);

#endif
#if 1	// 3�ڂ̑��n������
	// �I�u�W�F�N�g�̐��� �r�̖ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(8550.0f, 1240.0f, 250.0f), 0.05f, 7, 9, CObject::MOVETYPE_Y_MOVE, 1);

	// �I�u�W�F�N�g�̐��� �ؔ�(������)
	m_pObject = CObject::Create(D3DXVECTOR3(8130.0f, 1300.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8130.0f, 1360.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8130.0f, 1300.0f, -210.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);
	m_pObject = CObject::Create(D3DXVECTOR3(8190.0f, 1300.0f, -270.0f), 0.0f, 7, 9, CObject::MOVETYPE_NOT, 1);

#endif
#if 1	// ��
	m_pObject = CObject::Create(D3DXVECTOR3(10600, 1500, 0.0f), 0.0f, 15, 13, CObject::MOVETYPE_HOUSE, 1);
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
	m_pObject = CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 550.0f), 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
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

CTitle::TYPE CTitle::GetType(void)
{
	return m_pType;
}
