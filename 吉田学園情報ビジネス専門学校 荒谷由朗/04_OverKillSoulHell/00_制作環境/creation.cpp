//=============================================================================
//
// ������ʏ��� [creation.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "creation.h"
#include "renderer.h"
#include "player.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

LPDIRECT3DTEXTURE9			CCreation::m_pTexture[CREATION_MAX_TEXTURE] = {};

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CCreation::CCreation() :CScene2D(1)
{
	m_nSelect = NULL;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CCreation::~CCreation()
{

}

CCreation *CCreation::Create(void)
{
	CCreation *pBg = NULL;

	pBg = new CCreation;
	pBg->Init();

	return pBg;
}

HRESULT CCreation::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX01, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX02, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX03, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX04, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX05, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, CREATION_TEX06, &m_pTexture[6]);

	return S_OK;
}

void CCreation::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntBg = 0; nCntBg < CREATION_MAX_TEXTURE; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCreation::Init(void)
{
	// ������@
	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init();
	m_apScene2D[0]->BindTexture(m_pTexture[0]);
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(900.0f, 380.0f, 0.0f), 350.0f, 250.0f);
	m_apScene2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	// ��ʐ���
	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init();
	m_apScene2D[1]->BindTexture(m_pTexture[1]);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(900.0f, 380.0f, 0.0f), 350.0f, 250.0f);
	m_apScene2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	// �X�L������
	m_apScene2D[2] = new CScene2D;
	m_apScene2D[2]->Init();
	m_apScene2D[2]->BindTexture(m_pTexture[2]);
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(900.0f, 380.0f, 0.0f), 350.0f, 250.0f);
	m_apScene2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	// �o���b�g����
	m_apScene2D[3] = new CScene2D;
	m_apScene2D[3]->Init();
	m_apScene2D[3]->BindTexture(m_pTexture[3]);
	m_apScene2D[3]->SetPosition(D3DXVECTOR3(900.0f, 380.0f, 0.0f), 350.0f, 250.0f);
	m_apScene2D[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	// �Q�[���T�v
	m_apScene2D[4] = new CScene2D;
	m_apScene2D[4]->Init();
	m_apScene2D[4]->BindTexture(m_pTexture[4]);
	m_apScene2D[4]->SetPosition(D3DXVECTOR3(900.0f, 380.0f, 0.0f), 350.0f, 250.0f);
	m_apScene2D[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	// �I��
	m_apScene2D[5] = new CScene2D;
	m_apScene2D[5]->Init();
	m_apScene2D[5]->BindTexture(m_pTexture[5]);
	m_apScene2D[5]->SetTexture(1, 1, 2);
	m_apScene2D[5]->SetPosition(D3DXVECTOR3(1180.0f, 680.0f, 0.0f), 100.0f, 45.0f);
	// �؂�ւ��{�^��
	m_apScene2D[6] = new CScene2D;
	m_apScene2D[6]->Init();
	m_apScene2D[6]->BindTexture(m_pTexture[6]);
	m_apScene2D[6]->SetTexture(0, 1, 2);
	m_apScene2D[6]->SetPosition(D3DXVECTOR3(930.0f, 670.0f, 0.0f), 120.0f, 45.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCreation::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCreation::Update(void)
{
	CFade::FADE fade = CFade::GetFade();
	CInputKeyboard *pKey = CManager::GetInputKeyboard();		// ���͏��̎擾
																// �W���C�p�b�h���͏�Ԃ̎擾
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

	D3DXVECTOR3 pos = m_apScene2D[m_nSelect]->GetPosition();
	D3DXCOLOR col = m_apScene2D[m_nSelect]->GetCol();


	if (pKey != NULL)
	{
		if (pKey->GetTrigger(DIK_Q) == true ||
			state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && abConect[0] == true)
		{// ������ʂ̐؂�ւ�
			if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
			{
				// ���_�J���[�ݒ�
				m_apScene2D[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_nSelect = (m_nSelect + 4) % 5;
				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SKILL_SELECT);
			}
			apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
		}
		if (pKey->GetTrigger(DIK_E) == true ||
			state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && abConect[0] == true)
		{// ������ʂ̐؂�ւ�
			if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
			{
				// ���_�J���[�ݒ�
				m_apScene2D[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_nSelect = (m_nSelect + 1) % 5;
				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SKILL_SELECT);
			}
			apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
		}
		if (pKey->GetTrigger(DIK_RETURN) == true ||
			state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && abConect[0] == true)
		{// ������ʂ̐؂�ւ�
			if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
			{
				if (fade != CFade::FADE_OUT)
				{
					//���[�h�ݒ�
					CFade::SetFade(CManager::MODE_GAME);
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
				}
			}
			apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
		}
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

				if (objtype == OBJTYPE_PLAYER)
				{
					CScene2D *pScene2D = ((CScene2D*)pScene);
					D3DXVECTOR3 posPlayer = pScene2D->GetPosition();

					if (pScene2D != NULL)
					{
						if (posPlayer.x + 350.0f > pos.x && pos.x > posPlayer.x - 350.0f
							&& posPlayer.y + 250.0f > pos.y && pos.y > posPlayer.y - 250.0f)
						{	//���蔻��
							if (col.a > 0.3f)
							{
								col.a -= 0.05f;
								// ���_�J���[�ݒ�
								m_apScene2D[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
							}
							else
							{
								col.a += 0.05f;
								// ���_�J���[�ݒ�
								m_apScene2D[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
							}
						}
						else
						{
							if (col.a < 1.0f)
							{
								col.a += 0.05f;
								// ���_�J���[�ݒ�
								m_apScene2D[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
							}
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
void CCreation::Draw(void)
{

}