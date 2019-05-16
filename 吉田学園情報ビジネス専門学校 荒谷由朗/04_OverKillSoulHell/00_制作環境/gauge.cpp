//=============================================================================
//
// �Q�[�W���� [gauge.h]
// Author :		�r�J�R�N
//
//=============================================================================
#include "gauge.h"
#include "scene2D.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9			CGauge::m_pTexture[GAUGE_MAX_TEXTURE] = {};

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CGauge::CGauge() :CScene(0)
{
	m_fWidth		= NULL;
	m_fHeight		= NULL;
	m_nCounterAnim	= NULL;
	m_nPatternAnim	= NULL;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CGauge::~CGauge()
{

}

CGauge *CGauge::Create(void)
{
	CGauge *pBg = NULL;

	pBg = new CGauge;
	pBg->Init();

	return pBg;
}

HRESULT CGauge::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, GAUGE_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, GAUGE_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

void CGauge::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntGauge = 0; nCntGauge < GAUGE_MAX_TEXTURE; nCntGauge++)
	{
		if (m_pTexture[nCntGauge] != NULL)
		{
			m_pTexture[nCntGauge]->Release();
			m_pTexture[nCntGauge] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGauge::Init(void)
{
	m_fWidth = 30;
	m_fHeight = 30;

	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init();
	m_apScene2D[0]->BindTexture(m_pTexture[0]);
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(60, 60, 0.0f), m_fWidth, m_fHeight);
	m_apScene2D[0]->SetObjType(CScene::OBJTYPE_GAUGE0);		// �I�u�W�F�N�g�̎�ނ�ݒ�

	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init();
	m_apScene2D[1]->BindTexture(m_pTexture[1]);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(60, 60, 0.0f), m_fWidth - 5, m_fHeight - 5);
	m_apScene2D[1]->SetObjType(CScene::OBJTYPE_GAUGE1);		// �I�u�W�F�N�g�̎�ނ�ݒ�

	for (int nCntScore = 0; nCntScore < MAX_CIRCLE; nCntScore++)
	{
		m_apCircle[nCntScore] = new CCircle; // ��������Create����Ă���
		if (nCntScore == 0)
		{
			m_apCircle[nCntScore]->Init(D3DXVECTOR3(60, 60, 0.0f), 40.0f + (14.0f * nCntScore), 14.0f,CCircle::CIRCLETYPE_HP);
		}
		else if (nCntScore == 1)
		{
			m_apCircle[nCntScore]->Init(D3DXVECTOR3(60, 60, 0.0f), 40.0f + (12.0f * nCntScore), 12.0f, CCircle::CIRCLETYPE_MP);
		}
		SetObjType(CScene::OBJTYPE_CIRCLE);		// �I�u�W�F�N�g�̎�ނ�ݒ�
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGauge::Uninit(void)
{
	for (int nCntGauge = 0; nCntGauge < GAUGE_MAX_2DPOLIGON; nCntGauge++)
	{
		m_apScene2D[nCntGauge]->Uninit();
		m_apScene2D[nCntGauge] = NULL;
	}

	for (int nCntScore = 0; nCntScore < MAX_CIRCLE; nCntScore++)
	{
		m_apCircle[nCntScore]->Uninit();
		m_apCircle[nCntScore] = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGauge::Update(void)
{
	m_nCounterAnim++;

	if (m_nCounterAnim % 3 == 0)
	{
		m_nPatternAnim++;
		m_apScene2D[0]->SetRot(-m_nPatternAnim/50, m_fWidth, m_fHeight);
		m_apScene2D[1]->SetRot(m_nPatternAnim/50, m_fWidth - 5, m_fHeight - 5);
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntPri, nCntScene);

			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��擾
				CScene::OBJTYPE objtype;
				objtype = pScene->GetObjType();
				if (objtype == OBJTYPE_CIRCLE)
				{//	�G�̓����蔻��
					CCircle *pCircle = ((CCircle*)pScene);
					pCircle->Update();
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGauge::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_CIRCLE; nCntScore++)
	{
		m_apCircle[nCntScore]->Draw();
	}
}