//=============================================================================
//
// �|���S������ [scene2D.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_pTexture	= NULL;
	m_pVtxBuff	= NULL;
	m_fRot		= NULL;
	m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9		pDevice = {};
	if (CManager::GetRenderer() != NULL)
	{// GetRenderer()��NULL�������痎���邽��
		pDevice = CManager::GetRenderer()->GetDevice();
	}

	//���_�o�b�t�@�̓ǂݍ���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	// ���_�o�b�t�@�̐���
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`���̐���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �I�u�W�F�N�g(�������g)�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
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
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���W�̐ݒ菈��
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float width, float height)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	m_pos		= pos;
	m_fWidth	= width;
	m_fHeight	= height;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y - height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y - height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - width, m_pos.y + height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + width, m_pos.y + height, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CScene2D::SetRot(float rot, float width, float height)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	m_fRot = rot;
	m_fWidth = width;
	m_fHeight = height;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(m_fRot) * m_fHeight) + (cosf(m_fRot) * m_fWidth), m_pos.y - (sinf(m_fRot) * m_fWidth) + (cosf(m_fRot) * m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(m_fRot) * m_fHeight) - (cosf(m_fRot) * m_fWidth), m_pos.y + (sinf(m_fRot) * m_fWidth) + (cosf(m_fRot) * m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(m_fRot) * m_fHeight) + (cosf(m_fRot) * m_fWidth), m_pos.y - (sinf(m_fRot) * m_fWidth) - (cosf(m_fRot) * m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(m_fRot) * m_fHeight) - (cosf(m_fRot) * m_fWidth), m_pos.y + (sinf(m_fRot) * m_fWidth) - (cosf(m_fRot) * m_fHeight), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �F�̐ݒ菈��
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	if (m_pVtxBuff != NULL)
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_����ݒ�
		pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �e�N�X�`���̐ݒ菈��
//=============================================================================
void CScene2D::SetTexture(int PatternAnim, int X, int Y)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X),				(PatternAnim / X) * (1.0f / Y));
	pVtx[1].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X) + (1.0f / X),	(PatternAnim / X) * (1.0f / Y));
	pVtx[2].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X),				(PatternAnim / X) * (1.0f / Y) + (1.0f / Y));
	pVtx[3].tex = D3DXVECTOR2((PatternAnim % X) * (1.0f / X) + (1.0f / X),	(PatternAnim / X) * (1.0f / Y) + (1.0f / Y));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e�N�X�`��(�X�R�A)�̐ݒ菈��
//=============================================================================
void CScene2D::SetScore(int nValue)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2((nValue % 10) * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nValue % 10) * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nValue % 10) * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nValue % 10) * 0.1f + 0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

D3DXCOLOR CScene2D::GetCol(void)
{
	return m_col;
}

float CScene2D::GetWidth(void)
{
	return m_fWidth;
}

float CScene2D::GetHeight(void)
{
	return m_fHeight;
}

LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}