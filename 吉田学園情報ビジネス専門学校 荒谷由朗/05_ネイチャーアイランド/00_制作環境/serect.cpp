//=============================================================================
//
// �I���̏��� [serect.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "serect.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_0			"data\\TEXTURE\\�|�[�Y.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_1			"data\\TEXTURE\\pause001.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2			"data\\TEXTURE\\pause003.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_PAUSE				(128)							//�|�[�Y�̍ő吔
#define SERECT_POS_X			(0)								//�|�[�Y�̍���X���W
#define SERECT_POS_Y			(0)								//�|�[�Y�̍���Y���W
#define SERECT_WIDTH			(SCREEN_WIDTH)					//�|�[�Y�̕�
#define SERECT_HEIGHT			(SCREEN_HEIGHT)					//�|�[�Y�̍���
#define SERECT_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define SERECT_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define SERECT_SPEED			(0.003f)						//�|�[�Y�X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CSerect::m_pTexture[MAX_SERECT_TEXTURE] = {};
int CSerect::m_SelectNum = NULL;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CSerect::CSerect(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_SelectColor = 0.0f;
	m_nCntState = 0;
	m_SelectNum = 0;
	m_bUse = false;
	m_nSize = D3DXVECTOR2(0.0f,0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CSerect::~CSerect()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSerect::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3((SERECT_POS_X + SERECT_WIDTH) / 2, (SERECT_POS_Y + SERECT_HEIGHT) / 2, 0.0f);
	m_SelectNum = 0;
	m_SelectColor = 1.0f;

	// ���_����ݒ�
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_SERECT_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//�|�[�Y�̍��W
	float PosSerect = (SCREEN_HEIGHT / 2) - 270;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCount = 0;nCount < MAX_SERECT_TEXTURE;nCount++)
	{//����ȊO�̏ꍇ���ׂĂ̏�����

		if (nCount == 0)
		{//�J�E���g�O�������ꍇ
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 145.0f, SERECT_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 645.0f, SERECT_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 145.0f, SERECT_HEIGHT / 2 + 70.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 645.0f, SERECT_HEIGHT / 2 + 70.0f, 0.0f);
			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{//����ȊO�̏ꍇ
		 //���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 195.0f, PosSerect, 0.0f);				//����
			pVtx[1].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 595.0f, PosSerect, 0.0f);				//�E��
			pVtx[2].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 195.0f, PosSerect + 100.0f, 0.0f);		//����
			pVtx[3].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 595.0f, PosSerect + 100.0f, 0.0f);		//�E��

			if (nCount == 1)
			{
				//���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}
			//�I�𗓂̕�
			PosSerect += 150;
		}

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(SERECT_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, SERECT_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(SERECT_TEXTURE_UV_U, SERECT_TEXTURE_UV_V);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSerect::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSerect::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();
	//�t�F�[�h�̃|�C���g
	CFade::FADE pFade = CFade::GetFade();

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_UP) == true || pCInputKeyBoard->GetKeyboardTrigger(DIK_W) == true || pCInputJoypad->GetTrigger(CInputJoypad::STICK_L_UP) == true)
	{//���L�[�̏���������Ƃ�

	 //�|�[�Y�̑I�����ړ���
		pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);

		// ���_�J���[�ݒ�
		pVtx[m_SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[m_SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[m_SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[m_SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		m_SelectNum = (m_SelectNum + 1) % 2;
		m_SelectColor = 1.0f;
	}
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_DOWN) == true || pCInputKeyBoard->GetKeyboardTrigger(DIK_S) == true || pCInputJoypad->GetTrigger(CInputJoypad::STICK_L_DOWN) == true)
	{//���L�[�̉����������Ƃ�

	 //�|�[�Y�̑I�����ړ���
		pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);

		// ���_�J���[�ݒ�
		pVtx[m_SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[m_SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[m_SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[m_SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		m_SelectNum = (m_SelectNum + 1) % 2;
		m_SelectColor = 1.0f;
	}

	//�_�ŏ���
	//�I�����Ă���J���[�̒l�����炵�Ă���
	m_SelectColor -= 0.009f;

	if (m_SelectColor < 0.5f)
	{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
		m_SelectColor = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[m_SelectNum * 4 + 4].col = D3DXCOLOR(m_SelectColor, m_SelectColor, m_SelectColor, 1.0f);
	pVtx[m_SelectNum * 4 + 1 + 4].col = D3DXCOLOR(m_SelectColor, m_SelectColor, m_SelectColor, 1.0f);
	pVtx[m_SelectNum * 4 + 2 + 4].col = D3DXCOLOR(m_SelectColor, m_SelectColor, m_SelectColor, 1.0f);
	pVtx[m_SelectNum * 4 + 3 + 4].col = D3DXCOLOR(m_SelectColor, m_SelectColor, m_SelectColor, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true || pCInputMouse->GetMouseTrigger(0) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true)
	{
		if (m_SelectNum == 0)
		{
			//�Q�[���̍ŏ��ɖ߂�
			CFade::Create(CManager::MODE_GAME);
		}
		else if (m_SelectNum == 1)
		{
			//�Q�[���̃^�C�g���ɖ߂�
			CFade::Create(CManager::MODE_RANKING);
		}

		if (pFade == CFade::FADE_NONE)
		{
			//�|�[�Y�̑I���̌��艹
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSerect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�|���S���̕`��
	for (int nCount = 0; nCount < MAX_SERECT_TEXTURE; nCount++)
	{//�r���{�[�h���J�E���g
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource
		(
			0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_2D)
		);

		//���_�t�H�[�}�b�g
		pDevice->SetFVF(FVF_VERTEX_2D);

		pDevice->SetTexture(0, m_pTexture[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CSerect * CSerect::Create()
{
	CSerect *pPause = NULL;

	//NULL�`�F�b�N
	if (pPause == NULL)
	{//�������̓��I�m��

		pPause = new CSerect;

		if (pPause != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pPause->Init();
		}
	}

	return pPause;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CSerect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_0,
		&m_pTexture[0]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[1]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[2]
	);


	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CSerect::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_SERECT_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}