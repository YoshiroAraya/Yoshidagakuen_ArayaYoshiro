//=============================================================================
//
// ���S�̏��� [logo.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "logo.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOGO_TEXTURE_NAME_1		"data\\TEXTURE\\second.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_2		"data\\TEXTURE\\timeback.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_3		"data\\TEXTURE\\tutorial.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_4		"data\\TEXTURE\\tutorial000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_5		"data\\TEXTURE\\tutorial001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_6		"data\\TEXTURE\\�`���[�g���A��.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_7		"data\\TEXTURE\\PressAny.png"		//�ǂݍ��ރe�N�X�`���t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CLogo::CLogo() : CScene2D(5, CScene::OBJTYPE_LOGO)//�D��D�ʃC�j�V�����C�Y
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTutorial = 0;
	m_bOneCnt = false;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CLogo::~CLogo()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLogo::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogo::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�ʒu�̊��蓖��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ړ��ʂ̊��蓖��
	D3DXVECTOR3 move;
	move = GetMove();

	m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y ));
	// �p�x���o��
	m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

	m_rot.x += 0.02f;
	m_rot.y += 0.02f;

	//�ʒu���X�V(�ړ�)
	pos.x += move.x;
	pos.y += move.y;

	if (m_nType == 2)
	{
		//��x�̂ݓ���
		if (m_bOneCnt == false)
		{
			if (pos.x <= 160.0f)
			{//�E�ɓ�����
				move.x = 5;
			}
			else if (pos.x >= 160.0f)
			{//��x�~�߂�
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
		//4�b���ʊO�ɖ߂�
		if (m_nCntTutorial == 340)
		{//���ɓ�����
			move.x -= 5;
		}
		else if (m_nCntTutorial == 440)
		{
			//�e�N�X�`���̕ύX
			BindTexture(m_pTexture[3]);

			m_bOneCnt = false;
		}

		//4�b���ʊO�ɖ߂�
		if (m_nCntTutorial == 780)
		{//���ɓ�����
			move.x -= 5;
		}
		else if (m_nCntTutorial == 880)
		{
			//�e�N�X�`���̕ύX
			BindTexture(m_pTexture[4]);

			m_bOneCnt = false;
		}

	}

	m_nCntTutorial++;

	//���S�̈ʒu�ƃT�C�Y
	CScene2D::SetPosSize(pos,m_size);
	//���S�̈ʒu�ƃT�C�Y
	CScene2D::SetMove(move);
	//��]����
	//CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);

	//============================
	//     �f�o�b�N�p����
	//============================
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_1) == true)
	{
		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CLogo *pLogo = NULL;

	//NULL�`�F�b�N
	if (pLogo == NULL)
	{//�������̓��I�m��

		pLogo = new CLogo;

		if (pLogo != NULL)
		{
			//��ނ����蓖�Ă�
			pLogo->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pLogo->Init();
			//�e�N�X�`�������蓖�Ă�
			pLogo->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pLogo->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pLogo->m_size = size;
		}
	}

	return pLogo;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CLogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_7, &m_pTexture[6]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CLogo::UnLoad(void)
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