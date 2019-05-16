//=============================================================================
//
// �X�L���A�C�R������ [mpicon.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "mpicon.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "score.h"
#include "explosion.h"

LPDIRECT3DTEXTURE9		CMPIcon::m_pTexture = NULL;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CMPIcon::CMPIcon()
{
	m_bUse = false;
	m_nSelect = NULL;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CMPIcon::~CMPIcon()
{

}

CMPIcon *CMPIcon::Create()
{
	CMPIcon *pMPIcon = NULL;

	pMPIcon = new CMPIcon;

	return pMPIcon;
}

HRESULT CMPIcon::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MP_TEXTURENAME00, &m_pTexture);

	return S_OK;
}

void CMPIcon::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMPIcon::Init(D3DXVECTOR3 pos, int mptype)
{
	m_pos = pos;
	// �f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 30.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

	//�e�N�X�`�����W�̐ݒ�
	switch (mptype)
	{
	case MPICONTYPE_MISSILE:
		m_Type = MPICONTYPE_MISSILE;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		break;
	case MPICONTYPE_PAIR:
		m_Type = MPICONTYPE_PAIR;
		pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		break;
	case MPICONTYPE_SHIELD:
		m_Type = MPICONTYPE_SHIELD;
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(0.75f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(0.75f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		break;
	case MPICONTYPE_HP:
		m_Type = MPICONTYPE_HP;
		pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		break;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMPIcon::Uninit(void)
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
void CMPIcon::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMPIcon::Draw(void)
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

void CMPIcon::SetType(MPICONTYPE mpicontype)
{
	m_Type = mpicontype;
}

CMPIcon::MPICONTYPE CMPIcon::GetType(void)
{
	return m_Type;
}

D3DXVECTOR3 CMPIcon::GetPos(void)
{
	return m_pos;
}

void CMPIcon::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 30.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 30.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 30.0f, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

void CMPIcon::SetCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[1].col = col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[2].col = col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[3].col = col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}