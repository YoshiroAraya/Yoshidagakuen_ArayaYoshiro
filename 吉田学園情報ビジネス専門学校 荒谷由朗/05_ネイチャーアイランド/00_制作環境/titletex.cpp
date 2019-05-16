//=============================================================================
//
// �^�C�g���e�L�X�g�̏��� [titletex.cpp]
// Author : �r�J�R�N
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "title.h"
#include "titletex.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURE_NAME_0		"data\\TEXTURE\\title\\.jpg"					// �����t(��)
#define TITLE_TEXTURE_NAME_1		"data\\TEXTURE\\title\\green0.png"				// ��
#define TITLE_TEXTURE_NAME_2		"data\\TEXTURE\\title\\titleboard.png"			// �^�C�g��
#define TITLE_TEXTURE_NAME_3		"data\\TEXTURE\\title\\flash.png"				// ��
#define TITLE_TEXTURE_NAME_4		"data\\TEXTURE\\title\\title000.jpg"			// ���w�i
#define TITLE_TEXTURE_NAME_5		"data\\TEXTURE\\title\\inSUMMER.png"			// �T�u�^�C�g��
#define TITLE_TEXTURE_NAME_6		"data\\TEXTURE\\title\\nature_n.png"			//�uN�v
#define TITLE_TEXTURE_NAME_7		"data\\TEXTURE\\title\\nature_a.png"			//�ua�v
#define TITLE_TEXTURE_NAME_8		"data\\TEXTURE\\title\\nature_t.png"			//�ut�v
#define TITLE_TEXTURE_NAME_9		"data\\TEXTURE\\title\\nature_u.png"			//�uu�v
#define TITLE_TEXTURE_NAME_10		"data\\TEXTURE\\title\\nature_r.png"			//�ur�v
#define TITLE_TEXTURE_NAME_11		"data\\TEXTURE\\title\\nature_e.png"			//�ue�v
#define TITLE_TEXTURE_NAME_12		"data\\TEXTURE\\title\\island_i(large).png"		//�uI�v
#define TITLE_TEXTURE_NAME_13		"data\\TEXTURE\\title\\island_s.png"			//�us�v
#define TITLE_TEXTURE_NAME_14		"data\\TEXTURE\\title\\island_i(small).png"		//�ul�v
#define TITLE_TEXTURE_NAME_15		"data\\TEXTURE\\title\\island_a.png"			//�ua�v
#define TITLE_TEXTURE_NAME_16		"data\\TEXTURE\\title\\island_n.png"			//�un�v
#define TITLE_TEXTURE_NAME_17		"data\\TEXTURE\\title\\island_d.png"			//�ud�v
#define TITLE_TEXTURE_NAME_18		"data\\TEXTURE\\title\\PressAny.png"			// AnyButton(��)
#define TITLE_TEXTURE_NAME_19		"data\\TEXTURE\\title\\green1.png"				// ��
#define TITLE_TEXTURE_NAME_20		"data\\TEXTURE\\title\\green2.png"				// ��
#define TITLE_TEXTURE_NAME_21		"data\\TEXTURE\\title\\green3.png"				// ��
#define TITLE_TEXTURE_NAME_22		"data\\TEXTURE\\title\\leaf000.png"				// �����t

#define TITLE_STERT (400)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitletex::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CTitletex::CTitletex() : CScene2D(4)//�D��D�ʃC�j�V�����C�Y
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_sizeDest = D3DXVECTOR2(0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nCntflame = 0;
	m_nCntDelete = 0;
	m_nBlink = false;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CTitletex::~CTitletex()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTitletex::Init(void)
{
	srand((unsigned int)time(0));
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitletex::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitletex::Update(void)
{
	// ���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();
	// �ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition(), posAngle;
	D3DXVECTOR2 sizeAngle;
	D3DXCOLOR col[4];

	CTitle::TYPE pTitleType = CTitle::GetType();

	if (m_nType == 0 || m_nType == 1)
	{// ��(gleen0.png)
		BindTexture(m_pTexture[1]);

		// �ړI�̍X�V
		if (m_nType == 0)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();					// ���W�̎擾
				m_posDest.x -= 185.0f;						// �ړ���
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);	// �g���
			}
		}
		else if (m_nType == 1)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();					// ���W�̎擾
				m_posDest.x += 185.0f;						// �ړ���
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);	// �g���
			}
		}

		// ���X�ɓ�����
		// �ʒu---------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.x > D3DX_PI)
		{
			posAngle.x -= D3DX_PI * 2.0f;
		}
		else if (posAngle.x < -D3DX_PI)
		{
			posAngle.x += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// �T�C�Y-------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 19)
	{// ��(gleen1.png)
		BindTexture(m_pTexture[19]);

		// �ړI�̍X�V
		if (m_nCntflame % 60 == 0)
		{
			m_posDest = GetPosition();					   // ���W�̎擾
			m_posDest.y += 35.0f;						   // �ړ���
			m_sizeDest += D3DXVECTOR2(90.0f, 0.0f);		   // �g���
		}
		// ���X�ɓ�����
		// �ʒu---------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.y > D3DX_PI)
		{
			posAngle.y -= D3DX_PI * 2.0f;
		}
		else if (posAngle.y < -D3DX_PI)
		{
			posAngle.y += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// �T�C�Y-------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 20 || m_nType == 22)
	{// ��(gleen2.png)
		BindTexture(m_pTexture[20]);

		// �ړI�̍X�V
		if (m_nType == 20)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // ���W�̎擾
				m_posDest.x -= 120.0f;					   // �ړ���
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);   // �g���
			}
		}
		else if (m_nType == 22)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // ���W�̎擾
				m_posDest.x += 120.0f;					   // �ړ���
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);   // �g���
			}
		}

		// ���X�ɓ�����
		// �ʒu----------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.x > D3DX_PI)
		{
			posAngle.x -= D3DX_PI * 2.0f;
		}
		else if (posAngle.x < -D3DX_PI)
		{
			posAngle.x += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// �T�C�Y--------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 21 || m_nType == 23)
	{// ��(gleen3.png)
		BindTexture(m_pTexture[21]);

		// �ړI�̍X�V
		if (m_nType == 21)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // ���W�̎擾
				m_posDest.x -= 60.0f;					   // �ړ���
				m_sizeDest += D3DXVECTOR2(10.0f, 20.0f);   // �g���
			}
		}
		else if (m_nType == 23)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // ���W�̎擾
				m_posDest.x += 60.0f;					   // �ړ���
				m_sizeDest += D3DXVECTOR2(10.0f, 20.0f);   // �g���
			}
		}

		// ���X�ɓ�����
		// �ʒu----------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.x > D3DX_PI)
		{
			posAngle.x -= D3DX_PI * 2.0f;
		}
		else if (posAngle.x < -D3DX_PI)
		{
			posAngle.x += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// �T�C�Y--------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 2)
	{// �^�C�g�����S
		if (pTitleType == CTitle::TYPE_NONE)
		{// �X�L�b�v��Ԃ��ǂ���
			if (m_nCntflame >= TITLE_STERT)
			{// ������������
				if (m_nCntflame == TITLE_STERT)
				{
					m_posDest = GetPosition();							   // ���W�̎擾
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);	   // �ړ���
				}
				// �ʒu-------------------------------------------------
				posAngle = m_posDest - pos;
				if (posAngle.x > D3DX_PI)
				{
					posAngle.x -= D3DX_PI * 2.0f;
				}
				else if (posAngle.x < -D3DX_PI)
				{
					posAngle.x += D3DX_PI * 2.0f;
				}
				pos += (posAngle / 60);
			}
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{// �X�L�b�v��Ԃ������Ƃ�
			pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f);
		}
	}
	else if (m_nType == 3)
	{// ��
		if ((m_nCounterAnim % 200) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			if (m_nPatternAnim >= 10)
			{// �Ō�̃A�j���[�V�����ŌŒ肷��
				m_nPatternAnim = 9;
			}
			CScene2D::SetTexture(m_nPatternAnim, 1, 10);
		}
		if (m_nCntflame >= 100)
		{// ���X�ɔ�������
			m_nCntDelete++;
			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
		}
		else
		{// �F�̏����l
			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		CScene2D::SetColor(&col[0]);
	}
	else if (m_nType == 5)
	{// �T�u�^�C�g��
		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// �p�x���o��
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);
		m_rot.x = 0.1f;
		m_rot.y = 0.1f;

		if (pTitleType == CTitle::TYPE_NONE)
		{// �X�L�b�v��Ԃ��ǂ���
			if (m_nCntflame >= 10)
			{// ���X�ɑ傫��
				if (m_size.x > 230.0f)
				{
					m_size -= D3DXVECTOR2(8.0f, 8.0f);
				}
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
			}
			else
			{
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			CScene2D::SetColor(&col[0]);
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{
			m_size = D3DXVECTOR2(230.0f, 150.0f);
			m_nCntDelete++;
			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			CScene2D::SetColor(&col[0]);
		}
	}
	else if (m_nType == 6 || m_nType == 7 || m_nType == 8 || m_nType == 9 || m_nType == 10 || m_nType == 11
		|| m_nType == 12 || m_nType == 13 || m_nType == 14 || m_nType == 15 || m_nType == 16 || m_nType == 17)
	{// ����
		if (pTitleType == CTitle::TYPE_NONE)
		{
			switch (m_nType)
			{
			case 6:
				if (m_nCntflame == TITLE_STERT + 100)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 100)
				{
					// �ʒu
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 7:
				if (m_nCntflame == TITLE_STERT + 110)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 110)
				{
					// �ʒu
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 8:
				if (m_nCntflame == TITLE_STERT + 120)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 120)
				{
					// �ʒu
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 9:
				if (m_nCntflame == TITLE_STERT + 130)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 130)
				{
					// �ʒu
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 10:
				if (m_nCntflame == TITLE_STERT + 140)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 140)
				{
					// �ʒu
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 11:
				if (m_nCntflame == TITLE_STERT + 150)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 150)
				{
					// �ʒu
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;

			case 12:
				// ���X�ɑ傫��
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 13:
				// ���X�ɑ傫��
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 14:
				// ���X�ɑ傫��
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 15:
				// ���X�ɑ傫��
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 16:
				// ���X�ɑ傫��
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 17:
				// ���X�ɑ傫��
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			}
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{// �X�L�b�v��
			switch (m_nType)
			{
			case 6:
				pos = D3DXVECTOR3(340.0f, 140.0f, 0.0f);
				break;
			case 7:
				pos = D3DXVECTOR3(405.0f, 155.0f, 0.0f);
				break;
			case 8:
				pos = D3DXVECTOR3(455.0f, 140.0f, 0.0f);
				break;
			case 9:
				pos = D3DXVECTOR3(510.0f, 152.0f, 0.0f);
				break;
			case 10:
				pos = D3DXVECTOR3(570.0f, 153.0f, 0.0f);
				break;
			case 11:
				pos = D3DXVECTOR3(620.0f, 153.0f, 0.0f);
				break;

			case 12:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 13:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 14:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 15:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 16:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 17:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			}
		}
	}
	else if (m_nType == 18)
	{// PressAny
		if (pTitleType == CTitle::TYPE_NONE)
		{
			if (m_nCntflame >= TITLE_STERT + 500)
			{
				if (m_nBlink == false)
				{
					m_nCntDelete++;
					col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					if (col[0].a <= 0.25f)
					{
						m_nCntDelete = 0;
						m_nBlink = true;
					}
				}
				else if (m_nBlink == true)
				{
					m_nCntDelete++;
					col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					if (col[0].a >= 1.0f)
					{
						m_nCntDelete = 0;
						m_nBlink = false;
					}
				}
				CScene2D::SetColor(&col[0]);
			}
			else
			{
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				CScene2D::SetColor(&col[0]);
			}
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{
			if (m_nBlink == false)
			{//	�J���[�𔖂�����
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				if (col[0].a <= 0.25f)
				{
					m_nCntDelete = 0;
					m_nBlink = true;
				}
			}
			else if (m_nBlink == true)
			{//	�J���[��Z������
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				if (col[0].a >= 1.0f)
				{
					m_nCntDelete = 0;
					m_nBlink = false;
				}
			}
			CScene2D::SetColor(&col[0]);
		}
	}
	else if(m_nType == 24)
	{// �����t(��)
		BindTexture(m_pTexture[22]);

		if ((m_nCounterAnim % 100) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 10, 6);
		}

		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// �p�x���o��
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);
		m_rot.x = 0.1f;
		m_rot.y = 0.1f;

		pos.x += 13.0f;		// �ړ���(X)
		pos.y += -4.0f;		// �ړ���(Y)
	}
	else if (m_nType == 25)
	{// �����t(��)
		BindTexture(m_pTexture[22]);

		if ((m_nCounterAnim % 100) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 10, 6);
		}

		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// �p�x���o��
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);
		m_rot.x = 0.1f;
		m_rot.y = 0.1f;

		pos.x += 11.0f;		// �ړ���(X)
		pos.y += -5.0f;		// �ړ���(Y)
	}
	else if (m_nType == 26)
	{// ���w�i
		BindTexture(m_pTexture[4]);
	}

	if (m_nType == 5 || m_nType == 24 || m_nType == 25)
	{
		// ��]����
		CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}
	else
	{
		CScene2D::SetPosSize(pos, m_size);
	}

	// �I������==================================================================================
	if (m_nType == 0 || m_nType == 1 || m_nType == 19 ||
		m_nType == 20 || m_nType == 21 || m_nType == 22 || m_nType == 23)
	{// ��
		if (m_nCntflame == 200)
		{
			Uninit();
		}
	}
	else if (m_nType == 3)
	{// ��
		if (m_nCntflame == 400)
		{
			Uninit();
		}
	}
	else if (m_nType == 24 || m_nType == 25)
	{
		if (pos.x >= SCREEN_WIDTH)
		{
			Uninit();
		}
	}
	else if (m_nType == 26)
	{
		if (m_nCntflame == 250)
		{
			Uninit();
		}
	}
	if (pTitleType == CTitle::TYPE_SKIP)
	{
		if (m_nType == 0 || m_nType == 1 || m_nType == 3 || m_nType == 19
			|| m_nType == 20 || m_nType == 21 || m_nType == 22 || m_nType == 23 || m_nType == 26)
		{
			Uninit();
		}
	}

	m_nCntflame++;		// �J�E���^�[�̍X�V
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTitletex::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CTitletex * CTitletex::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType)
{
	CTitletex *pTitleTEX = NULL;

	//NULL�`�F�b�N
	if (pTitleTEX == NULL)
	{//�������̓��I�m��

		pTitleTEX = new CTitletex;

		if (pTitleTEX != NULL)
		{
			//��ނ����蓖�Ă�
			pTitleTEX->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pTitleTEX->Init();
			//�e�N�X�`�������蓖�Ă�
			pTitleTEX->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pTitleTEX->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pTitleTEX->m_size = size;
			pTitleTEX->m_sizeDest = size;
		}
	}

	return pTitleTEX;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CTitletex::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_3, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_4, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_5, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_6, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_7, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_8, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_9, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_10, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_11, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_12, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_13, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_14, &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_15, &m_pTexture[15]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_16, &m_pTexture[16]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_17, &m_pTexture[17]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_18, &m_pTexture[18]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_19, &m_pTexture[19]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_20, &m_pTexture[20]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_21, &m_pTexture[21]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_22, &m_pTexture[22]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CTitletex::UnLoad(void)
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