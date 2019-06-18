//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "result.h"
#include "tutorial.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CSound *CManager::m_pSound = NULL;
CInputKeyBoard *CManager::m_pInputKeyBoard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CResult *CManager::m_pResult = NULL;
CRanking *CManager::m_pRanking = NULL;
CInputJoypad *CManager::m_pJoyPad = NULL;

//�Q�[���̈�ԍŏ�
CManager::MODE CManager::m_mode = MODE_TITLE;

int				CManager::m_nScore[MAX_RANKING] = {};
int				CManager::m_nGameScore = 0;
//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CManager::CManager()
{

}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CManager::~CManager()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindows)
{
	//NULL�`�F�b�N
	if (m_pRenderer == NULL)
	{
		//���I�m��
		m_pRenderer = new CRenderer;

		//NULL�`�F�b�N
		if (m_pRenderer != NULL)
		{
			// ����������
			if (FAILED(m_pRenderer->Init(hWnd, bWindows)))		//FALSE.TRUE
			{
				return -1;
			}
		}
		else
		{//�x����
			MessageBox(0, "�x���F���������Ȃ��ł�", "�x��", MB_OK);
		}
	}
	else
	{//�x����
		MessageBox(0, "�x���F�����������Ă܂�", "�x��", MB_OK);
	}

	//�L�[�{�[�h����
	m_pInputKeyBoard = CInputKeyBoard::Create(hInstance, hWnd);

	//�}�E�X����
	m_pInputMouse = CInputMouse::Create(hInstance, hWnd);

	//�W���C�p�b�h����
	m_pJoyPad = CInputJoypad::Create(hInstance, hWnd);

	//NULL�`�F�b�N
	if (m_pSound == NULL)
	{
		//�T�E���h�̓��I�m��
		m_pSound = new CSound;

		//NULL�`�F�b�N
		if (m_pSound != NULL)
		{
			//�T�E���h�̏���������
			m_pSound->InitSound(hWnd);
		}
	}

	//NULL�`�F�b�N
	if (m_pCamera == NULL)
	{
		//�J�����̓��I�m��
		m_pCamera = new CCamera;

		//NULL�`�F�b�N
		if (m_pCamera != NULL)
		{
			//�T�E���h�̏���������
			m_pCamera->Init(hInstance, hWnd);
		}
	}

	//NULL�`�F�b�N
	if (m_pLight == NULL)
	{
		//���C�g�̓��I�m��
		m_pLight = new CLight;

		//NULL�`�F�b�N
		if (m_pLight != NULL)
		{
			//�T�E���h�̏���������
			m_pLight->Init(hInstance, hWnd);
		}
	}

	//NULL�`�F�b�N
	if (m_pDebugProc == NULL)
	{
		//�f�o�b�N�t�H���g
		m_pDebugProc = new CDebugProc;

		//NULL�`�F�b�N
		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}

	//�����L���O
	m_nScore[0] = 5;
	m_nScore[1] = 50;
	m_nScore[2] = 100;
	m_nScore[3] = 200;
	m_nScore[4] = 300;

	//���[�h�̐ݒ�
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�Ă̍폜
	CScene::ReleseAll();

	//Sound�@NULL�`�F�b�N
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I������
		m_pSound->UninitSound();
		//�������̉��
		delete m_pSound;
		m_pSound = NULL;
	}

	//Renderer NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		//�������̉��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//pCInput NULL�`�F�b�N
	if (m_pInputKeyBoard != NULL)
	{
		// �I������
		m_pInputKeyBoard->Uninit();
		//�������̉��
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//�}�E�XInput�� NULL�`�F�b�N
	if (m_pInputMouse != NULL)
	{
		// �I������
		m_pInputMouse->Uninit();
		//�������̉��
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�}�E�XInput�� NULL�`�F�b�N
	if (m_pJoyPad != NULL)
	{
		// �I������
		m_pJoyPad->Uninit();
		//�������̉��
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}


	//�J�����̏I������
	if(m_pCamera != NULL)
	{
		// �I������
		m_pCamera->Uninit();
		//�������̉��
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//���C�g�̏I������
	if (m_pLight != NULL)
	{
		// �I������
		m_pLight->Uninit();
		//�������̉��
		delete m_pLight;
		m_pLight = NULL;
	}

	//�t�H���g�̏I������
	if (m_pDebugProc != NULL)
	{
		// �I������
		m_pDebugProc->Uninit();
		//�������̉��
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �X�V����
	m_pRenderer->Update();

	// �L�[�{�[�h�X�V����
	m_pInputKeyBoard->Update();

	//�}�E�X�X�V����
	m_pInputMouse->Update();

	//�W���C�p�b�h�X�V����
	m_pJoyPad->Update();

	//���C�g�̍X�V����
	m_pLight->Update();

	//�J�����̍X�V����
	m_pCamera->Update();

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�f�o�b�N�p
	CDebugProc::Print("F1 ���C���[�t���[���@F2�@�ʏ�\n");

	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_TUTORIAL:	//�`���[�g���A��
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;
	case MODE_GAME:		//�Q�[��
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case MODE_RANKING:	//�����L���O
		if (m_pRanking != NULL)
		{
			m_pRanking->Update();
		}
		break;
	}

	//���[�h�̐؂�ւ�莞�A���̒���ReleaseAll���Ă��܂��B
}
//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �`�揈��
	m_pRenderer->Draw();

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	//�`��̊J�n
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		switch (m_mode)
		{
		case MODE_TITLE:	//�^�C�g��
			if (m_pTitle != NULL)
			{
				m_pTitle->Draw();
			}
			break;
		case MODE_TUTORIAL:	//�`���[�g���A��
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Draw();
			}
			break;
		case MODE_GAME:		//�Q�[��
			if (m_pGame != NULL)
			{
				m_pGame->Draw();
			}
			break;
		case MODE_RESULT:	//���U���g
			if (m_pResult != NULL)
			{
				m_pResult->Draw();
			}
			break;
		case MODE_RANKING:	//�����L���O
			if (m_pRanking != NULL)
			{
				m_pRanking->Draw();
			}
			break;
		}
		// �`��̏I��
		pDevice->EndScene();
	}
}
//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
			CCamera::Delete();
		}
		break;
	case MODE_TUTORIAL:	//�`���[�g���A��
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
			CCamera::Delete();
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
	case MODE_GAME:		//�Q�[��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
			CCamera::Delete();
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_NATURE);
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_GAME);
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
			CCamera::Delete();
		}
		break;
	case MODE_RANKING:	//�����L���O
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			//delete m_pRanking;
			m_pRanking = NULL;
			CCamera::Delete();
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		}
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle == NULL)
		{//�������𓮓I�m��
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
				m_pSound->StopSound();
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
			}
		}
		break;
	case MODE_TUTORIAL:	//�`���[�g���A��
		if (m_pTutorial == NULL)
		{//�������𓮓I�m��
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init();
			}
		}
		break;
	case MODE_GAME:		//�Q�[��
		if (m_pGame == NULL)
		{//�������𓮓I�m��
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				m_pGame->Init();
				m_pSound->StopSound();
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_NATURE);
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
			}
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult == NULL)
		{//�������𓮓I�m��
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				m_pResult->Init();
				m_pSound->StopSound();
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
			}
		}
		break;
	case MODE_RANKING:	//�����L���O
		if (m_pRanking == NULL)
		{//�������𓮓I�m��
			m_pRanking = new CRanking;

			if (m_pRanking != NULL)
			{
				m_pRanking->Init();
			}
		}
		break;
	}
}
//=============================================================================
// �����L���O���ёւ��Z�b�g
//=============================================================================
void CManager::RankingScore(int nScore)
{
	int nSaveScore = 0;
	//int FinalScore;
	//FinalScore = 1000 / nScore;

	//�X�R�A�X�V
	if (m_nScore[MAX_RANKING - 1] > nScore)
	{//�V�����^�C�����Ⴂ������ւ�
		m_nScore[MAX_RANKING - 1] = nScore;
	}
	//�\�[�g���� ��������
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < MAX_RANKING - 1; nCnt2++)
		{
			if (m_nScore[nCnt2] > m_nScore[nCnt2 + 1])
			{//���Ɣ�ׂĎ������傫��������ւ�(�傫���l�͔z��̉��̂ق���)
				nSaveScore = m_nScore[nCnt2];			//�ꎞ�ۑ�
				m_nScore[nCnt2] = m_nScore[nCnt2 + 1];	//���������ւ�
				m_nScore[nCnt2 + 1] = nSaveScore;		//�ۑ���������������
			}
		}
	}
}

//=============================================================================
//�����L���O���擾
//=============================================================================
int *CManager::GetRankingScore(int nidx)
{
	return &m_nScore[nidx];
}
//=============================================================================
//�Q�[���̃X�R�A���Z�b�g
//=============================================================================
void CManager::SetGameScore(int nScore)
{
	m_nGameScore = nScore;
}
//=============================================================================
//�Q�[���̃X�R�A���擾
//=============================================================================
int * CManager::GetGameScore()
{
	return &m_nGameScore;
}
