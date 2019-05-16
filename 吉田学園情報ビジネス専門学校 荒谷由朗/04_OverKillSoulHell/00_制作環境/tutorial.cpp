//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "tutorial.h"
#include "bg.h"
#include "player.h"
#include "bullet.h"
#include "bulleticon.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "gauge.h"
#include "item.h"
#include "barrier.h"
#include "mp.h"
#include "mpicon.h"
#include "pair.h"
#include "creation.h"
#include "sound.h"

CPlayer			*CTutorial::m_pPlayer = NULL;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	m_pPlayer = NULL;
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
	// �w�i�̐���
	CBg::Load();
	CBg::Create();

	// ������ʂ̐���
	CCreation::Load();
	CCreation::Create();

	// �v���C���[�̐���
	m_pPlayer = new CPlayer;
	m_pPlayer->Load();
	m_pPlayer->Init();

	// �q�@�̐���
	CPair::Load();

	// �Q�[�W�̐���
	CGauge::Load();
	CGauge::Create();

	// �X�L���A�C�R���̐���
	CMPIcon::Load();
	CMP::Create(D3DXVECTOR3(400.0f, 70.0f, 0.0f));

	// �e�A�C�R���̐���
	CBulletIcon::Load();
	CBulletIcon::Create();

	// �o���A�̐���
	CBarrier::Load();

	// �e�̐���
	CBullet::Load();

	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//=============================================================================
//�@�I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CBg::Unload();
	CCreation::Unload();
	m_pPlayer->Unload();
	CPair::Unload();
	CGauge::Unload();
	CMPIcon::Unload();
	CBulletIcon::Unload();
	CBarrier::Unload();
	CBullet::Unload();

	CSound *pSound = CManager::GetSound();
	pSound->AllStopSound();
}

//=============================================================================
//�@�X�V����
//=============================================================================
void CTutorial::Update(void)
{

}

CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}