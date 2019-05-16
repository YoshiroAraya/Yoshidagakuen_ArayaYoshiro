//=============================================================================
//
// �}�l�[�W������ [manager.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "bg.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
#include "tutorial.h"
#include "sound.h"

CManager::GAMERESULT CManager::m_Result = GAMERESULT_WIN;
CRenderer			*CManager::m_pRenderer		= NULL;
CFade				*CManager::m_pFade			= NULL;
CInputKeyboard		*CManager::m_pInputKeyboard = NULL;
CInputJoyPad		*CManager::m_pInputJoyPad	= NULL;
CSound				*CManager::m_pSound			= NULL;
CTitle				*CManager::m_pTitle			= NULL;
CGame				*CManager::m_pGame			= NULL;
CResult				*CManager::m_pResult		= NULL;
CTutorial			*CManager::m_pTutorial		= NULL;
CPlayer				*CManager::m_pPlayer		= NULL;
CGauge				*CManager::m_pGauge			= NULL;
CManager::MODE		CManager::m_mode			= MODE_TITLE;
CPause				*CManager::m_pPause			= NULL;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_pRenderer			= NULL;
	m_pFade				= NULL;
	m_pInputKeyboard	= NULL;
	m_pInputJoyPad		= NULL;
	m_pSound			= NULL;
	m_pTitle			= NULL;
	m_pGame				= NULL;
	m_pTutorial			= NULL;
	m_pPlayer			= NULL;
	m_pGauge			= NULL;
	m_Result			= GAMERESULT_WIN;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_�����O�N���X�̐���
	m_pRenderer = new CRenderer;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	m_pInputKeyboard = new CInputKeyboard;

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return -1;
	}

	m_pInputJoyPad = new CInputJoyPad;

	if (m_pInputJoyPad != NULL)
	{
		m_pInputJoyPad->Init();
	}

	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	if (m_pPause == NULL)
	{
		m_pPause = new CPause;
		if (m_pPause != NULL)
		{
			m_pPause->Init();
		}
	}

	SetMode(m_mode);

	m_pFade = new CFade;
	m_pFade->Init();

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CManager::Uninit(void)
{
	// �j��
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pInputKeyboard != NULL)
	{
		// �I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	if (m_pInputJoyPad != NULL)
	{
		// �I������
		m_pInputJoyPad->Uninit();
		delete m_pInputJoyPad;
		m_pInputJoyPad = NULL;
	}
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}
	if (m_pFade != NULL)
	{
		// �I������
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
}

//=============================================================================
//�@�X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pRenderer != NULL)
	{
		// �X�V����
		m_pRenderer->Update();
	}
	if (m_pInputKeyboard != NULL)
	{
		// �X�V����
		m_pInputKeyboard->Update();
	}
	if (m_pInputJoyPad != NULL)
	{
		// �X�V����
		m_pInputJoyPad->Update();
	}
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	}
}

//=============================================================================
//�@�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
// �f�o�C�X�̎擾(�����_�����O)
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//=============================================================================
// ���͏��̎擾(�L�[�{�[�h)
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//=============================================================================
// ���͏��̎擾(�R���g���[���[)
//=============================================================================
CInputJoyPad * CManager::GetInputJoyPad(void)
{
	return m_pInputJoyPad;
}
//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	CScene2D::ReleaseAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
			}
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init();
			}
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{
				m_pGame->Init();
			}
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				m_pResult->Init();
			}
		}
		break;
	}
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer *&CManager::GetPlayer(void)
{
	return m_pPlayer;
}
//=============================================================================
// �Q�[�W�̎擾
//=============================================================================
CGauge *& CManager::GetGauge(void)
{
	return m_pGauge;
}

void CManager::SetResult(GAMERESULT result)
{
	m_Result = result;
}

CManager::GAMERESULT CManager::GetResult(void)
{
	return m_Result;
}

CSound *CManager::GetSound(void)
{
	return m_pSound;
}
