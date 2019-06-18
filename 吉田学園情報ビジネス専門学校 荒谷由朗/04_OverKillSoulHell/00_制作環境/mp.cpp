//=============================================================================
//
// �X�L���A�C�R������ [mp.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "scene2D.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "mp.h"
#include "player.h"
#include "mpicon.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CMPIcon			*CMP::m_apMPIcon[MAX_SKILL] = {};
D3DXVECTOR3		CMP::m_pos					= {};
int				CMP::m_nNumSelect			= NULL;
int				CMP::m_nNumSelectPast		= NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMP::CMP() : CScene(1)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMP::~CMP()
{
}

//=============================================================================
// ��������
//=============================================================================
CMP *CMP::Create(D3DXVECTOR3 pos)
{
	CMP *pMP = NULL;

	// �f�[�^�̑��
	m_pos = pos;

	pMP = new CMP;
	pMP->Init();

	return pMP;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMP::Init(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		m_apMPIcon[nCntSkill] = new CMPIcon; // ��������Create����Ă���
		m_apMPIcon[nCntSkill]->Init(D3DXVECTOR3(m_pos.x - (60.0f * nCntSkill), m_pos.y, m_pos.z), nCntSkill);
		SetObjType(CScene::OBJTYPE_MPICON);
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMP::Uninit(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		m_apMPIcon[nCntSkill]->Uninit();
		m_apMPIcon[nCntSkill] = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMP::Update(void)
{
	CInputKeyboard	*pKey		= CManager::GetInputKeyboard();		// ���͏��̎擾
	CPlayer			*pPlayer	= CManager::GetPlayer();			// �v���C���[�̎擾

	CInputJoyPad *apInputJoyPad[1] = {};
	apInputJoyPad[0] = CManager::GetInputJoyPad();
	// �W���C�p�b�h�{�^����Ԃ̎擾
	CInputJoyPad::JoyState apJoyState[1];
	apJoyState[0] = apInputJoyPad[0]->GetJoyState(0);
	// �W���C�p�b�h�ڑ���Ԃ̎擾
	bool abConect[1] = {};
	abConect[0] = apInputJoyPad[0]->GetConnect(0);
	// �W���C�p�b�h���̎擾
	XINPUT_STATE state;
	XInputGetState(0, &state);


	if (pPlayer != NULL)
	{
		int nMpNow = pPlayer->GetPlayerMp();

		if (nMpNow >= 1)
		{
			m_apMPIcon[0]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
		else
		{
			m_apMPIcon[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (nMpNow >= 5)
		{
			m_apMPIcon[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apMPIcon[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (nMpNow >= 10)
		{
			m_apMPIcon[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apMPIcon[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (nMpNow >= 20)
		{
			m_apMPIcon[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apMPIcon[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene = CScene::GetScene(nCntPri, nCntScene);

			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��擾
				CScene::OBJTYPE objtype;
				objtype = pScene->GetObjType();

				if (objtype == OBJTYPE_BULLETICON)
				{//	�G�̓����蔻��
					// �G�l�~�[�̍��W���擾
					CScene2D *pScene2D = ((CScene2D*)pScene);
					if (pScene2D != NULL)
					{
						if (pKey != NULL)
						{
							if (pKey->GetTrigger(DIK_LEFT) == true ||
								state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && abConect[0] == true)
							{
								if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
								{
									m_nNumSelectPast	= m_nNumSelect;
									m_nNumSelect		= (m_nNumSelect + 1) % 4;
									CSound *pSound		= CManager::GetSound();
									pSound->PlaySound(CSound::SOUND_LABEL_SKILL_SELECT);
								}
								apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
							}

							if (pKey->GetTrigger(DIK_RIGHT) == true ||
								state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && abConect[0] == true)
							{
								if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
								{
									m_nNumSelectPast	= m_nNumSelect;
									m_nNumSelect		= (m_nNumSelect + 3) % 4;
									CSound *pSound		= CManager::GetSound();
									pSound->PlaySound(CSound::SOUND_LABEL_SKILL_SELECT);
								}
								apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
							}

						}
					}
					for (int nCntNumber = 0; nCntNumber < 4; nCntNumber++)
					{
						if (nCntNumber == m_nNumSelect)
						{
							D3DXVECTOR3 posnow = m_apMPIcon[nCntNumber]->GetPos();
							posnow += D3DXVECTOR3(0.0f, 60.0f, 0.0f);
							m_apMPIcon[nCntNumber]->SetPos(posnow);
						}
						else if (nCntNumber == m_nNumSelectPast)
						{
							D3DXVECTOR3 posnow = m_apMPIcon[m_nNumSelectPast]->GetPos();
							m_apMPIcon[m_nNumSelectPast]->SetPos(posnow);
						}
					}
				}
			}
		}
	}
	// �W���C�p�b�h�̏�ԍX�V
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMP::Draw(void)
{
	for (int nCntSkill = 0; nCntSkill < MAX_SKILL; nCntSkill++)
	{
		m_apMPIcon[nCntSkill]->Draw();
	}
}

//=============================================================================
// �X�L���A�C�R�����̎擾
//=============================================================================
int CMP::GetNumber(void)
{
	return m_nNumSelect;
}