//=============================================================================
//
// �o���A���� [barrier.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "barrier.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9			CBarrier::m_pTexture = {};

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CBarrier::CBarrier() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CBarrier::~CBarrier()
{
}

//=============================================================================
//�@��������
//=============================================================================
CBarrier *CBarrier::Create(D3DXVECTOR3 pos)
{
	CBarrier *pBarrier = NULL;

	pBarrier = new CBarrier;
	pBarrier->Init(pos);

	return pBarrier;
}

//=============================================================================
//�@���[�h
//=============================================================================
HRESULT CBarrier::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BARRIER_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

//=============================================================================
//�@�A�����[�h
//=============================================================================
void CBarrier::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBarrier::Init(D3DXVECTOR3 pos)
{
	m_fWidth	= 50;
	m_fHeight	= 50;
	CScene2D::Init();									// ����������
	SetObjType				(CScene::OBJTYPE_BARRIER);	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene2D::SetPosition	(pos, m_fWidth, m_fHeight);	// ���W�̐ݒ�
	CScene2D::SetCol		(m_col);					// �F�̐ݒ�
	BindTexture				(m_pTexture);				// �e�L�X�g�̐ݒ�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBarrier::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBarrier::Update(void)
{
	m_nCntFrame++;	// �J�E���^�[�̉��Z

	CPlayer *pPlayer = CManager::GetPlayer();	// ���̎擾
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPosition();			// ���W�̎擾
		CScene2D::SetPosition(posPlayer, m_fWidth, m_fHeight);	// �v���C���[�Ɠ������W��

		if ((m_nCntFrame % 600) == 0)
		{// ���Ԃ��؂ꂽ��o���A������
			pPlayer->SetStatusType(CPlayer::PLAYER_STATUSTYPE_NORMAL);
			Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBarrier::Draw(void)
{
	CScene2D::Draw();
}