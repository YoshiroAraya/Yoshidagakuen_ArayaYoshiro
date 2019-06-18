//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "game.h"
#include "title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_CAMERA			(3.0f)			//�J�����̈ړ���
#define MOVE_ANGLE			(0.01f)			//�J�����p�x�̈ړ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CCamera::m_pPlayer = NULL;
D3DXVECTOR3 CCamera::m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_�̏����l
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_fAngle = 0.0f;
	m_fCameraAngle = 45.0f;								//�p�x
	m_CameraCount = 0;									//�J�����̐�������
	m_fRot = 0;											//�J�����̌���������
	m_fLength = m_posV.z - m_posR.z;					//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	m_nType = CAMERA_TYPE_NONE;							//���
	m_nCntTitle = 0;
	m_bReset = false;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CCamera::~CCamera()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);		//���_�̏����l
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���

	m_fLength = m_posV.z - m_posR.z;					//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	m_fRange = m_posV.y - m_posR.y;						//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	m_nCntTitle = 0;
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CManager::MODE pMode = CManager::GetMode();

	if (pMode == CManager::MODE_TITLE)
	{
		CTitle::TYPE pTitleType = CTitle::GetType();

		if (m_bReset == false)
		{
			m_posV = D3DXVECTOR3(0.0f, 300.0f, -550.0f);		//���_�̏����l
			m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
			m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
			m_bReset = true;
		}
		if (pTitleType == CTitle::TYPE_SKIP)
		{
			m_nCntTitle = 250;
		}
		m_nCntTitle++;
		if (m_nCntTitle >= 250)
		{
			//============================
			//     ���_�̉E�ړ�
			//============================
			m_posV.x += sinf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			//m_posR�ɑ��
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;

			// ��
			m_posV.y += 0.5f;
			m_posR.y += 0.5f;
		}
		if (m_posV.x >= 10500.0f)
		{
			m_bReset = false;
		}
	}
	else if (pMode == CManager::MODE_GAME)
	{
		//�v���C���[��pos����
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
		D3DXVECTOR3 PlayerRot = m_pPlayer->GetRot();

#ifdef _DEBUG

		//============================
		//     ���_�̍��E�O��ړ�
		//============================
		if (pCInputKeyBoard->GetKeyboardPress(DIK_RIGHT) == true)//�E���L�[���������Ƃ�
		{//�E�ړ�							�@�@�@���p�x�@�@�@�@���ړ���
			m_posV.x += sinf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			//m_posR�ɑ��
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_LEFT) == true)//�����L�[���������Ƃ�
		{//���ړ�									���p�x�@�@�@���ړ���
			m_posV.x += sinf((D3DX_PI * -0.5f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * -0.5f) + m_fAngle) * MOVE_CAMERA;
			//m_posR�ɑ��
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_UP) == true)//����L�[���������Ƃ�
		{//�O�ړ�								  ���p�x�@�@�@�@���ړ���
			m_posV.x += sinf((D3DX_PI * 0.0f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * 0.0f) + m_fAngle) * MOVE_CAMERA;
			//m_posR�ɑ��
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;

		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_DOWN) == true)//�����L�[���������Ƃ�
		{//��ړ�						  ���p�x�@�@�@�@���ړ���
			m_posV.x += sinf((D3DX_PI)+m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI)+m_fAngle) * MOVE_CAMERA;
			//m_posR�ɑ��
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
		}
		//============================
		//        ���_�ړ�
		//============================
		if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD1) == true)
		{//C�L�[���������Ƃ��@�@�@���p�x�̈ړ���
			m_fAngle += MOVE_ANGLE;
			if (m_fAngle > D3DX_PI)
			{//������
				m_fAngle = -D3DX_PI;
			}
			//g_Camera.posV��D3DXVECTOR3��sin��cos����
			m_posV = D3DXVECTOR3(m_posR.x + sinf(m_fAngle) * m_fLength, m_posV.y, m_posR.z + cosf(m_fAngle) * m_fLength);
		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD2) == true)
		{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
			m_fAngle -= MOVE_ANGLE;
			if (m_fAngle < -D3DX_PI)
			{//�E����
				m_fAngle = D3DX_PI;
			}
			//g_Camera.posV��D3DXVECTOR3��sin��cos����
			m_posV = D3DXVECTOR3(m_posR.x + sinf(m_fAngle) * m_fLength, m_posV.y, m_posR.z + cosf(m_fAngle) * m_fLength);
		}

		if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD7) == true)
		{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
			m_posV.y += 2.0f;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD8) == true)
		{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
			m_posV.y -= 2.0f;
		}
#endif

		//���_�E�����_�̍X�V
		m_posVDest.x = PlayerPos.x + sinf(m_rot.y) * m_fLength;
		m_posVDest.y = PlayerPos.y + m_fRange;
		m_posVDest.z = PlayerPos.z + cosf(m_rot.y) * m_fLength;

		m_posRDest.x = PlayerPos.x - sinf(PlayerRot.y) * 1.0f;
		m_posRDest.y = PlayerPos.y;
		m_posRDest.z = PlayerPos.z - cosf(PlayerRot.y) * 1.0f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.3f;
		m_posV.y += (m_posVDest.y - m_posV.y) * 0.3f;
		m_posR += (m_posRDest - m_posR) * 0.3f;
		//�ړ��̃f�o�b�N�p
		//CDebugProc::Print("�J����������@ �y���@�O�ړ��z�y���@���ړ��z�y���@��ړ��z�y���@�E�ړ��z�yNUM 1 ����]�z�yNUM 2�@�E��]�z\n");
		//�J�����̃f�o�b�N�ʒu
		//CDebugProc::Print("�J����posV�̈ʒu :�y%.1f�z�y%.1f�z�y%.1f�z\n", m_posV.x, m_posV.y, m_posV.z);
		//CDebugProc::Print("�J����posR�̈ʒu :�y%.1f�z�y%.1f�z�y%.1f�z\n", m_posR.x, m_posR.y, m_posR.z);
	}
	else if (pMode == CManager::MODE_RESULT || pMode == CManager::MODE_RANKING)
	{
#if 1
		m_posV = D3DXVECTOR3(0.0f, 50.0f, -550.0f);		//���_
		m_posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);				//�����_
#endif
	}
}
//=============================================================================
//�@�J�����̐���
//=============================================================================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		10000
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
//	�J�������폜
//=============================================================================
void CCamera::Delete(void)
{
	CCamera *pCamere = CManager::GetCamera();
	pCamere->m_posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);	//���_�̏����l
	pCamere->m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	pCamere->m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���

	pCamere->m_fLength = pCamere->m_posV.z - pCamere->m_posR.z;					//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	pCamere->m_fRange = pCamere->m_posV.y - pCamere->m_posR.y;					//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	pCamere->m_nCntTitle = 0;
}