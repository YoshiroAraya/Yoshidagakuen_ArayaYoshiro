//=============================================================================
//
// �Q�[�W(�~)�̏��� [circle.h]
// Author : �r�J �R�N
//
//=============================================================================
#include "circle.h"
#include "renderer.h"
#include "player.h"

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CCircle::CCircle()
{
	m_Radius	= NULL;
	m_Radius2	= NULL;
	m_fCircle	= 583.0f;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CCircle::~CCircle()
{
}

//=============================================================================
//�@��������
//=============================================================================
CCircle *CCircle::Create(D3DXVECTOR3 pos, float radius, float radius2, CIRCLETYPE type)
{
	CCircle *pCircle = NULL;

	pCircle = new CCircle;
	pCircle->Init(pos, radius, radius2, type);

	return pCircle;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCircle::Init(D3DXVECTOR3 pos, float radius, float radius2,CIRCLETYPE type)
{
	// �e�f�[�^�̑��
	m_pos			= pos;
	m_Radius		= radius;
	m_Radius2		= radius2;
	m_CircleType	= type;

	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	switch (type)
	{// �^�C�v���ƂɃJ���[��ݒ�
	case CIRCLETYPE_HP:
		m_col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);
		break;
	case CIRCLETYPE_MP:
		m_col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}

	MakeVertex	(pDevice);
	MakeIndex	(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCircle::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CCircle::Update(void)
{
}

//=============================================================================
// �`�揈��7
//=============================================================================
void CCircle::Draw(void)
{
	// �v���C���[�̎擾
	CPlayer *pPlayer = CManager::GetPlayer();

	if (pPlayer != NULL)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9		pDevice = {};
		if (CManager::GetRenderer() != NULL)
		{// GetRenderer()��NULL�������痎���邽��
			pDevice = CManager::GetRenderer()->GetDevice();
		}

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(m_pIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, 0);

		if (m_CircleType == CIRCLETYPE_HP)
		{
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CIRCLE_VERTEX, 0, (UINT)(CIRCLE_POLYGON * 2 * (pPlayer->GetPlayerLife() / 100.0f)));
		}
		else if (m_CircleType == CIRCLETYPE_MP)
		{
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, CIRCLE_VERTEX, 0, (UINT)(CIRCLE_POLYGON * 2 * (pPlayer->GetPlayerMp() / 200.0f)));
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CCircle::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * CIRCLE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = D3DX_PI * 2 / CIRCLE_H;
	float fDestAngle;

	for (int nCntCIRCLE_V = 0; nCntCIRCLE_V < CIRCLE_V + 1; nCntCIRCLE_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntCIRCLE_H = 0; nCntCIRCLE_H < CIRCLE_H + 1; nCntCIRCLE_H++)
		{
			if (nCntCIRCLE_V == 0)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				// ���_���W
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.x = -sinf(fDestAngle) * m_Radius + m_pos.x;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.y = cosf(fDestAngle) * m_Radius + m_pos.y;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.z = 0.0f;

				// ���_�J���[
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].col = m_col;

				// �e�N�X�`�����W
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].tex = D3DXVECTOR2(nCntCIRCLE_H * (1.0f / (CIRCLE_H / 2)), nCntCIRCLE_V * -1.0f);
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
			if (nCntCIRCLE_V == 1)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				// ���_���W
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.x = -sinf(fDestAngle) * (m_Radius - m_Radius2) + m_pos.x;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.y = cosf(fDestAngle) * (m_Radius - m_Radius2) + m_pos.y;
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].pos.z = 0.0f;

				// ���_�J���[
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].col = m_col;

				// �e�N�X�`�����W
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].tex = D3DXVECTOR2(nCntCIRCLE_H * (1.0f / (CIRCLE_H / 2)), nCntCIRCLE_V * -1.0f);
				pVtx[nCntCIRCLE_V * (CIRCLE_H + 1) + nCntCIRCLE_H].rhw = 1.0f;
				fDestAngle += fAngle;
			}
		}
	}
	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �C���f�b�N�X���̍쐬
//=============================================================================
void CCircle::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * CIRCLE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	// �C���f�b�N�X�̃J�E���g

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < CIRCLE_V; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= CIRCLE_H; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (CIRCLE_H + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == CIRCLE_H && nCntIndex_V <= CIRCLE_V)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (CIRCLE_H + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();
}