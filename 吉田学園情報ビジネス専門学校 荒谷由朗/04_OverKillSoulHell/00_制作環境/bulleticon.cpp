//=============================================================================
//
// �e�A�C�R������ [bulleticon.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "bulleticon.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9		CBulletIcon::m_pTexture[MAX_BI_TEX] = {};

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CBulletIcon::CBulletIcon() :CScene(0)
{
	m_Type = ICONTYPE_SLASH;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CBulletIcon::~CBulletIcon()
{

}

CBulletIcon *CBulletIcon::Create()
{
	CBulletIcon *pBulletIcon = NULL;

	pBulletIcon = new CBulletIcon;
	pBulletIcon->Init();

	return pBulletIcon;
}

HRESULT CBulletIcon::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BI_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BI_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

void CBulletIcon::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_BI_TEX; nCntEnemyTex++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCntEnemyTex]->Release();
			m_pTexture[nCntEnemyTex] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBulletIcon::Init()
{
	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init();
	m_apScene2D[0]->BindTexture(m_pTexture[0]);
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(640, 60, 0.0f), 30, 30);

	SetObjType(CScene::OBJTYPE_BULLETICON);

	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init();
	m_apScene2D[1]->BindTexture(m_pTexture[1]);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(645, 60, 0.0f), 25, 25);
	m_apScene2D[1]->SetTexture(0,4,1);

	SetObjType(CScene::OBJTYPE_BULLETICON);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBulletIcon::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_BI_TEX; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();
		m_apScene2D[nCntBg] = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBulletIcon::Update(void)
{
	switch (m_Type)
	{
	case ICONTYPE_SLASH:
		m_apScene2D[1]->SetTexture(0, 4, 1);
		break;
	case ICONTYPE_POISON:
		m_apScene2D[1]->SetTexture(2, 4, 1);
		break;
	case ICONTYPE_FLAME:
		m_apScene2D[1]->SetTexture(1, 4, 1);
		break;
	case ICONTYPE_WIND:
		m_apScene2D[1]->SetTexture(3, 4, 1);
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBulletIcon::Draw(void)
{

}

void CBulletIcon::SetIconType(ICONTYPE icontype)
{
	m_Type = icontype;
}
