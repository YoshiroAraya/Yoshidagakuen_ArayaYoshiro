//=============================================================================
//
// �t�F�[�h�̏��� [fade.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1					"data\\TEXTURE\\.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define FADE_TIME						(0.02f)						//�t�F�[�h�̎���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFade::m_pTexture[MAX_TEXTURE] = {};
CFade::FADE CFade::m_fade = CFade::FADE_NONE;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CFade::CFade() : CScene2D(7, CScene::OBJTYPE_FADE)//�D��D�ʃC�j�V�����C�Y
{
	// �l�̏�����
	m_fade = FADE_NONE;									//�t�F�[�h�C�����
	m_colorFade = D3DXCOLOR(0.0f,0.0f, 0.0f, 0.0f);		//�����s�����ɂ��Ă���
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CFade::~CFade()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init()
{	
	CScene2D::Init();

	//�ʒu�̐錾
	D3DXVECTOR3 VtxPos[4];

	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = m_colorFade;
	}

	//�e�N�X�`���ݒ� �c�X�N���[���p
	VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_FADE);

	//�J���[�̊��蓖��
	CScene2D::SetColor(&Color[0]);

	//�ʒu�̐ݒ�
	CScene2D::SetVtxPos(&VtxPos[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];
	bool bDelete = false;

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)				//�t�F�[�h�C��
		{
			m_colorFade.a -= FADE_TIME;		//��ʂ𓧖��ɂ��Ă���
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;

				m_fade = FADE_NONE;			//�������Ă��Ȃ�
				bDelete = true;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_colorFade.a += FADE_TIME;		//��ʂ�s�����ɂ��Ă���
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;

				m_fade = FADE_IN;			//�t�F�[�h�C��

				//���[�h�ݒ�
				CManager::SetMode(m_modeNext);

				//UpdateAll��߂��I
				CScene::SetUpdatePri(0);
			}
		}

		//���_�J���[�̐ݒ�
		Color[0] = m_colorFade;
		Color[1] = m_colorFade;
		Color[2] = m_colorFade;
		Color[3] = m_colorFade;

		//�J���[�̊��蓖��
		CScene2D::SetColor(&Color[0]);

		if (bDelete == true)
		{//�t�F�[�h�̏I������
			Uninit();
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CFade * CFade::Create(CManager::MODE modeNext)
{
	CFade *pFade = NULL;

	if (m_fade == FADE_NONE)
	{
		//NULL�`�F�b�N
		if (pFade == NULL)
		{//�������̓��I�m��

			pFade = new CFade;

			if (pFade != NULL)
			{
				//�I�u�W�F�N�g�N���X�̐���
				pFade->Init();

				m_modeNext = modeNext;

				m_fade = FADE_OUT;
			}
		}
	}

	return pFade;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CFade::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CFade::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}