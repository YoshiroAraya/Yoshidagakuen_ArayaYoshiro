//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "MeshField.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "texture.h"
#include "wall.h"
#include "object.h"
#include "particle.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer			*CTutorial::m_pPlayer	= NULL;
CWall			*CTutorial::m_pWall		= NULL;
CObject			*CTutorial::m_pObject	= NULL;
CEnemy			*CTutorial::m_pEnemy	= NULL;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_pPlayer	= NULL;
	m_bWarning	= false;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//===================================
	// ���[�h
	//===================================
	// �e�N�X�`���̓ǂݍ���
	CTexture::Load();

	// �p�[�e�B�N���̃e�N�X�`���̓ǂݍ���
	CParticle::Load();

	//�ǂ̃e�N�X�`���̓ǂݍ���
	m_pWall->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//===================================
	// ����
	//===================================
	SetTex();		  // UI
	SetFloor();		  // ��
	SetWall();		  // ��
	SetObje();		  // �I�u�W�F�N�g

	if (m_pPlayer == NULL)
	{// �v���C���[�̐���
		m_pPlayer->Create(D3DXVECTOR3(0.0f, PLAYER_DOWN_HEIGHT, 0.0f));
	}

	// �T�E���h�̐���
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CTexture::UnLoad();			// �e�N�X�`��
	CParticle::Unload();		// �p�[�e�B�N��

	// �t�F�[�h�ȊO�폜
	CScene::NotFadeReleseAll();

	// �T�E���h�̍폜
	CSound *pSound = CManager::GetSound();
	if (pSound != NULL)
	{
		pSound->AllStopSound();
	}
}

//=============================================================================
//�@�X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CFade::FADE		fade	= CFade::GetFade();					// �t�F�[�h�̎擾
	CInputKeyBoard	*pKey	= CManager::GetInputKeyboard();		// ���͏��̎擾

	if (fade == CFade::FADE_IN)
	{
		if (pKey->GetKeyboardTrigger(DIK_P) == true)
		{// �|�[�Y
			m_bWarning = m_bWarning ? false : true;
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_OPENCLOSE);
		}
	}
}

//=============================================================================
//�@�`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
//�@�e�N�X�`���̐���
//=============================================================================
void CTutorial::SetTex(void)
{// CTexture::Create(���W, �T�C�Y, �e�N�X�`���̎��);
 // HP�Q�[�W
	CTexture::Create(D3DXVECTOR3(180.0f, 30.0f, 0.0f), D3DXVECTOR2(170.0f, 20.0f), 4);				// �Q�[�W(�g)
	CTexture::Create(D3DXVECTOR3(33.0f, 30.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 5);				// HP�A�C�R��
	CTexture::Create(D3DXVECTOR3(60.0f, 30.0f, 0.0f), D3DXVECTOR2(GAUGE_SIZE, 5.0f), 6);			// HP�Q�[�W

	// �댯�x
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), 7);		// �댯�x(�w�i)
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(35.0f, 35.0f), 8);		// �댯�x(�}�[�N)

	// ���e�B�N��
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 12);

	// ������
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(250.0f, 100.0f), 13);			// �\���w�i
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 14);			// �J��������
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 15);			// �ړ�����
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 16);			// �W�����v����
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 17);			// �U������
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 18);			// ���C�t����
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 19);			// �댯�x����
	CTexture::Create(D3DXVECTOR3(1040.0f, 100.0f, 0.0f), D3DXVECTOR2(240.0f, 100.0f), 20);			// �I������

}

//=============================================================================
//�@���̐���
//=============================================================================
void CTutorial::SetFloor(void)
{// ���b�V���t�B�[���h�̐���
 // Create(���W�A�T�C�Y�A������)
	CMeshField::Create(D3DXVECTOR3(-2500.0f, 0.0f, 1000.0f), 5000.0f, 9000.0f, 10, 8);		// �X�e�[�W
}

//=============================================================================
//�@�ǂ̐���
//=============================================================================
void CTutorial::SetWall(void)
{
	CWall::Create(D3DXVECTOR3(2500.0f, 0.0f, -3500.0f), D3DXVECTOR2(4500.0f, MAX_WALL_HEIGHT), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// �X�e�[�W
	CWall::Create(D3DXVECTOR3(-2500.0f, 0.0f, -3500.0f), D3DXVECTOR2(4500.0f, MAX_WALL_HEIGHT), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);
	CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR2(2500.0f, MAX_WALL_HEIGHT), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -8000.0f), D3DXVECTOR2(2500.0f, MAX_WALL_HEIGHT), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
}

//=============================================================================
//�@�I�u�W�F�N�g�̐���
//=============================================================================
void CTutorial::SetObje(void)
{// CObject::Create( ���W , �ړ��� , �g�p����摜�̔ԍ� , ��������I�u�W�F�N�g�̔ԍ� , �I�u�W�F�N�g�̃^�C�v , �����蔻��̗L�� );
	// �N���X�^��
	CObject::Create(D3DXVECTOR3(0.0f, 0.0f, -7000.0f), 0.0f, 2, 2, CObject::MOVETYPE_NOT, 2);
}