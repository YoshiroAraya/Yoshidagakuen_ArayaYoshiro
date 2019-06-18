//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "fade.h"
#include "scene2D.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CFade::FADE					CFade::m_fadeType	= {};
CManager::MODE				CFade::m_modeNext	= {};		// ���̃Q�[���̏��
D3DXCOLOR					CFade::m_fadeColor	= {};		// �t�F�[�h�̐F
LPDIRECT3DTEXTURE9			CFade::m_pTexture	= NULL;
LPDIRECT3DVERTEXBUFFER9		CFade::m_pVtxBuff	= NULL;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_fadeType	= FADE_IN;
	m_modeNext	= CManager::MODE_GAME;
	m_fadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// ��������
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade = NULL;

	pFade = new CFade;
	pFade->Init();

	return pFade;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 2, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
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
void CFade::Update(void)
{
	if (m_fadeType != FADE_NONE)
	{
		if (m_fadeType == FADE_IN)				// �t�F�[�h�C����Ԃ�
		{
			m_fadeColor.a -= 0.01f;				// ��ʂ𓧖��ɂ��Ă���
			if (m_fadeColor.a == 0.0f)
			{
				m_fadeColor.a = 0.0f;
				m_fadeType = FADE_NONE;			// �������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_fadeType == FADE_OUT)		// �t�F�[�h�A�E�g��Ԃ�
		{
			m_fadeColor.a += 0.01f;				// ��ʂ�s�����ɂ��Ă���
			if (m_fadeColor.a >= 1.0f)
			{
				m_fadeColor.a = 1.0f;
				m_fadeType = FADE_IN;			// �t�F�[�h�C����Ԃ�
				// ���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}

		VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_fadeColor;		// �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[1].col = m_fadeColor;		// �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[2].col = m_fadeColor;		// �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[3].col = m_fadeColor;		// �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9		pDevice = {};

	if (CManager::GetRenderer() != NULL)
	{// GetRenderer()��NULL�������痎���邽��
		pDevice = CManager::GetRenderer()->GetDevice();
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, 0);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fadeType	= FADE_OUT;								// �t�F�[�h�A�E�g��Ԃ�
	m_modeNext	= modeNext;								// ���[�h�̍X�V
	m_fadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �������(����)�ɂ��Ă���
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fadeType;
}