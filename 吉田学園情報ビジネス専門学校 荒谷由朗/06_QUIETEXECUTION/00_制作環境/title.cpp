//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "fade.h"		// ��"texture.h"�Ŏg���Ă���̂ŏ����Ȃ�
#include "title.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "texture.h"
#include "MeshField.h"
#include "object.h"
#include "wall.h"
#include "object.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CWall			*CTitle::m_pWall	= NULL;
CObject			*CTitle::m_pObject	= NULL;
CTitle::TYPE	CTitle::m_pType		= TYPE_NONE;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pType = TYPE_NONE;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
//�@����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//===================================
	// ���[�h
	//===================================
	// UI�̓ǂݍ���
	CTexture::Load();

	// �ǂ̃e�N�X�`���̓ǂݍ���
	m_pWall->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//===================================
	// ����
	//===================================
	SetTex();		 // UI
	SetFloor();		 // ��
	SetWall();		 // ��
	SetObje();		 // �I�u�W�F�N�g

	// �T�E���h�̐���
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CTitle::Uninit(void)
{
	CTexture::UnLoad();		// �e�N�X�`��

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
void CTitle::Update(void)
{
	CInputKeyBoard	*pKey	= CManager::GetInputKeyboard();		// ���͏��̎擾
	CInputMouse		*pMouse = CManager::GetInputMouse();		// ���͏��̎擾(�}�E�X)

	if (pKey != NULL)
	{
		if (pKey->GetKeyboardPress(DIK_RETURN) == true || pMouse->GetMouseTrigger(0) == true)
		{// �}�E�X�N���b�N�����Ƃ�
			m_pType = TYPE_PRESS;	// PRESS��Ԃɂ���
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_DECISION);
		}
	}
}

//=============================================================================
//�@�`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
//�@�e�N�X�`���̐���
//=============================================================================
void CTitle::SetTex(void)
{
	CTexture::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 180.0f, 0.0f), D3DXVECTOR2(350.0f, 150.0f), 0);	// �^�C�g�����S(��)
	CTexture::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 180.0f, 0.0f), D3DXVECTOR2(350.0f, 150.0f), 1);	// �^�C�g�����S(�E)
	CTexture::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 650.0f, 0.0f), D3DXVECTOR2(170.0f, 40.0f), 2);		// PRESS�w�i
	CTexture::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 650.0f, 0.0f), D3DXVECTOR2(150.0f, 20.0f), 3);		// PRESS
}

//=============================================================================
//�@���̐���
//=============================================================================
void CTitle::SetFloor(void)
{// CMeshField::Create(���W�A�T�C�Y�A������)
	CMeshField::Create(D3DXVECTOR3(-5000.0f, 0.0f, 5000.0f), 10000.0f, 10000.0f, 100, 100);	// Create(���W�A�T�C�Y�A������)
}

//=============================================================================
//�@�ǂ̐���
//=============================================================================
void CTitle::SetWall(void)
{
}

//=============================================================================
//�@�I�u�W�F�N�g�̐���
//=============================================================================
void CTitle::SetObje(void)
{// CObject::Create( ���W , �ړ��� , �g�p����摜�̔ԍ� , ��������I�u�W�F�N�g�̔ԍ� , �I�u�W�F�N�g�̃^�C�v , �����蔻��̗L�� );
	// �N���X�^��
	CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 2, 2, CObject::MOVETYPE_NOT, 0);
}