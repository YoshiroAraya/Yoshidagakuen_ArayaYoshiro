//=============================================================================
//
// �������� [explosion.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "explosion.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"

D3DXVECTOR3					CExplosion::m_move = {};
LPDIRECT3DTEXTURE9			CExplosion::m_pTexture[EXPLOSION_MAX_TEXTURE] = {};

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CExplosion::CExplosion() :CScene2D(4)
{

}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}

CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float width, float height, EXPLOSIONTYPE type)
{
	CExplosion *pExplosion = NULL;

	pExplosion = new CExplosion;
	pExplosion->Init(pos, width, height);
	switch (type)
	{
	case EXPLOSIONTYPE_SLASH:
		pExplosion->BindTexture(m_pTexture[0]);
		break;
	case EXPLOSIONTYPE_POISON:
		pExplosion->BindTexture(m_pTexture[1]);
		break;
	case EXPLOSIONTYPE_FLAME:
		pExplosion->BindTexture(m_pTexture[2]);
		break;
	case EXPLOSIONTYPE_WIND:
		pExplosion->BindTexture(m_pTexture[3]);
		break;
	case EXPLOSIONTYPE_ENEMY:
		pExplosion->BindTexture(m_pTexture[4]);
		break;
	}
	pExplosion->m_type = type;

	return pExplosion;
}

HRESULT CExplosion::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAME01, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAME02, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAME03, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAME04, &m_pTexture[4]);

	return S_OK;
}

void CExplosion::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntExplosion = 0; nCntExplosion < EXPLOSION_MAX_TEXTURE; nCntExplosion++)
	{
		if (m_pTexture[nCntExplosion] != NULL)
		{
			m_pTexture[nCntExplosion]->Release();
			m_pTexture[nCntExplosion] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float width, float height)
{
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EXPLOSION);
	CScene2D::SetTexture(m_nPatternAnim, 5, 6);
	CScene2D::SetPosition(pos, width, height);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	m_nCounterAnim++;

	switch (m_type)
	{
	case EXPLOSIONTYPE_SLASH:
		if ((m_nCounterAnim % 3) == 0)		//�A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 5, 2);

			if (m_nPatternAnim > 8)
			{
				Uninit();
			}
		}
		break;
	case EXPLOSIONTYPE_POISON:
		if ((m_nCounterAnim % 2) == 0)		//�A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 5, 3);

			if (m_nPatternAnim > 14)
			{
				Uninit();
			}
		}
		break;
	case EXPLOSIONTYPE_FLAME:
		if ((m_nCounterAnim % 2) == 0)		//�A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 8, 2);

			if (m_nPatternAnim > 15)
			{
				Uninit();
			}
		}
		break;
	case EXPLOSIONTYPE_WIND:
		if ((m_nCounterAnim % 3) == 0)		//�A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 5, 2);

			if (m_nPatternAnim > 9)
			{
				Uninit();
			}
		}
		break;
	case EXPLOSIONTYPE_ENEMY:
		if ((m_nCounterAnim % 3) == 0)		//�A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 5, 1);

			if (m_nPatternAnim > 4)
			{
				Uninit();
			}
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}