//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "effect.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
D3DXVECTOR3					CEffect::m_move = {};
LPDIRECT3DTEXTURE9			CEffect::m_pTexture = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect():CScene2D(1)
{
	m_fWidth = NULL;
	m_fHeight = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// ��������
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, float width, float height)
{
	CEffect *pEffect = NULL;

	pEffect = new CEffect;
	pEffect->Init(pos, width, height);
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CEffect::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CEffect::Unload(void)
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
HRESULT CEffect::Init(D3DXVECTOR3 pos, float width, float height)
{
	// �e�f�[�^�̑��
	m_fWidth	= width;
	m_fHeight	= height;

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_EFFECT);					// �I�u�W�F�N�g�̎�ނ�ݒ�
	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);	// ���W�̐ݒ�
	CScene2D::SetCol(m_col);							// �J���[�̐ݒ�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	m_col.a -= 0.05f;

	CScene2D::SetCol(D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a));	// �J���[�̐ݒ�

	if (m_col.a <=  0.0f)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}