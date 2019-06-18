//=============================================================================
//
// �\�E������ [soul.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "soul.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "player.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		CSoul::m_pTexture[MAX_SOULTEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSoul::CSoul() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSoul::~CSoul()
{
}

//=============================================================================
// ��������
//=============================================================================
CSoul *CSoul::Create(D3DXVECTOR3 pos, float width, float height)
{
	CSoul *pItem = NULL;

	pItem = new CSoul;
	pItem->Init(pos, width, height);
	pItem->BindTexture(m_pTexture[0]);

	return pItem;
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CSoul::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SOUL_TEXTURENAME00, &m_pTexture[0]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CSoul::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_SOULTEX; nCntEnemyTex++)
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
HRESULT CSoul::Init(D3DXVECTOR3 pos, float width, float height)
{
	srand((unsigned int)time(0));		// �����_���֐�

	// �e�f�[�^�̑��
	m_pos		= pos;
	m_fWidth	= width;
	m_fHeight	= height;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_SOUL);
	CScene2D::SetPosition(pos, width, height);
	CScene2D::SetTexture(0, 1, 1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSoul::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSoul::Update(void)
{
	CPlayer		*pPlayer	= CManager::GetPlayer();		// �v���C���[�̎擾
	D3DXVECTOR3 pos			= CScene2D::GetPosition();		// ���W�̎擾

	m_GaugePos = D3DXVECTOR3(60.0f, 60.0f, 0.0f);

	m_fAngle = atan2f(m_GaugePos.x - pos.x, m_GaugePos.y - pos.y);
	m_move.x += sinf(m_fAngle) * 0.25f;
	m_move.y += cosf(m_fAngle) * 0.25f;

	// �ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;

	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);

	bool bOnOff = false;

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

				if (objtype == OBJTYPE_GAUGE0)
				{//	�G�̓����蔻��
					// �G�l�~�[�̍��W���擾
					if (m_GaugePos.x + 30.0f > pos.x && pos.x > m_GaugePos.x - 30.0f
						&& m_GaugePos.y + 30.0f > pos.y && pos.y > m_GaugePos.y - 30.0f && bOnOff == false)
					{	//���蔻��
						if (pPlayer != NULL)
						{
							pPlayer->MpAbsorption(rand() % 20 + 1);
							Uninit();
							bOnOff = true;
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSoul::Draw(void)
{
	CScene2D::Draw();
}