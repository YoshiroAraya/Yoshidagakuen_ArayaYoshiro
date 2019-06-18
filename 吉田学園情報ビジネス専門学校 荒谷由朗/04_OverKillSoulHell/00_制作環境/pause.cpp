//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "pause.h"
#include "scene2D.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9				CPause::m_pTexture[PAUSE_MAX_TEXTURE]	= {};
LPDIRECT3DVERTEXBUFFER9			CPause::m_pVtxBuff						= NULL;
int								CPause::m_SelectNum						= NULL;			// �I��ԍ�
float							CPause::m_SelectColor					= NULL;			// �I��F

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CPause::CPause()
{
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SelectNum		= NULL;
	m_SelectColor	= 0.0f;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CPause::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME01, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME02, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTURENAME03, &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CPause::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PAUSE_MAX_TEXTURE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	m_SelectNum		= 0;						// �I��ԍ�
	m_SelectColor	= 0.0f;						// �I���J���[

	int nCntPause;								// �|�[�Y�J�E���^
	float fPosPause = -170;						// �|�[�Y�ʒu

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * PAUSE_MAX_POLIGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	Load();

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntPause = 0; nCntPause < PAUSE_MAX_POLIGON; nCntPause++)
	{// �|�[�Y���J�E���g
		if (nCntPause == 0)
		{// BG
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (nCntPause == 1)
		{// �|�[�Y
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 190, (SCREEN_HEIGHT / 2) - 210, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 190, (SCREEN_HEIGHT / 2) - 210, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 190, (SCREEN_HEIGHT / 2) + 210, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 190, (SCREEN_HEIGHT / 2) + 210, 0.0f);
			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (nCntPause == 2)
		{// �|�[�Y���j���[
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 170, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 170, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 170, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 170, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			fPosPause += 100;
		}
		else if (nCntPause == 3)
		{// �|�[�Y���j���[
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 150, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 150, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			fPosPause += 100;
		}
		else if (nCntPause == 4)
		{// �|�[�Y���j���[
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 130, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 130, (SCREEN_HEIGHT / 2) + fPosPause, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - 130, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + 130, (SCREEN_HEIGHT / 2) + fPosPause + 100, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

			fPosPause += 100;
		}
		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	Unload();

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	CFade::FADE		fade	= CFade::GetFade();					// �t�F�[�h�̎擾
	CInputKeyboard	*pKey	= CManager::GetInputKeyboard();		// ���͏��̎擾

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

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	if (pKey->GetTrigger(DIK_UP) == true || pKey->GetTrigger(DIK_W) == true ||
		state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
	{
		if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
		{
		// ���_�J���[�ݒ�
		pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		m_SelectNum		= (m_SelectNum + 2) % 3;
		m_SelectColor	= 1.0f;

		// �T�E���h�̍Đ�
		CSound *pSound	= CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT001);
		}
		apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
	}
	if (pKey->GetTrigger(DIK_DOWN) == true || pKey->GetTrigger(DIK_S) == true ||
		state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && abConect[0] == true)
	{
		if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
		{
		// ���_�J���[�ݒ�
		pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		m_SelectNum		= (m_SelectNum + 1) % 3;
		m_SelectColor	= 1.0f;

		// �T�E���h�̍Đ�
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT001);
		}
		apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
	}

	m_SelectColor -= 0.004f;

	if (m_SelectColor < 0.65f)
	{
		m_SelectColor = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);
	pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);
	pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);
	pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SelectColor);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if (pKey->GetTrigger(DIK_RETURN) == true ||
		state.Gamepad.wButtons & XINPUT_GAMEPAD_B && abConect[0] == true)
	{
		if (apJoyState[0] == CInputJoyPad::INPUT_JOYSTATE_NOTPUSH)
		{
			CGame *pGame	= CManager::GetGame();
			CGame *pPause	= ((CGame*)pGame);
			bool bPause		= pPause->GetPause();

			if (m_SelectNum == 0)
			{
				pPause->SetPause(false);

				// �T�E���h�̍Đ�
				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
			}
			else if (m_SelectNum == 1)
			{
				if (fade != CFade::FADE_OUT)
				{
					CFade::SetFade(CManager::MODE_GAME);
					pPause->SetPause(false);

					// ���_�J���[�ݒ�
					pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

					m_SelectNum	= 0;

					// �T�E���h�̍Đ�
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
				}
			}
			else if (m_SelectNum == 2)
			{
				if (fade != CFade::FADE_OUT)
				{
					CFade::SetFade(CManager::MODE_TITLE);
					pPause->SetPause(false);

					// ���_�J���[�ݒ�
					pVtx[m_SelectNum * 4 + 8].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 1 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 2 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					pVtx[m_SelectNum * 4 + 3 + 8].col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

					m_SelectNum = 0;

					// �T�E���h�̍Đ�
					CSound *pSound = CManager::GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
				}
			}
		}
		apJoyState[0] = CInputJoyPad::INPUT_JOYSTATE_PUSH;
	}
	// �W���C�p�b�h�̏�ԍX�V
	apInputJoyPad[0]->SetJoyState(apJoyState[0], 0);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{
	int nCntPause;					// �|�[�Y�J�E���^
	int nCntTex = 0;				// �e�N�X�`���J�E���^

	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D)
	);

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < PAUSE_MAX_POLIGON; nCntPause++)
	{// �|�[�Y���J�E���g
		if (nCntPause >= 1)
		{
			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntTex]);
			nCntTex++;
		}

		// �|�[�Y�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}