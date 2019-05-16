//=============================================================================
//
// �^�C�}�[���� [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "number.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)	// X�̒��S���W
#define TIMER_SPACE			(70.0f)				// �����Ɛ����̊Ԃ̃T�C�Y
#define TIMER_POSITION_Y	(70.0f)				// �^�C�}�[��Y���W

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
int CTime::m_nTime = 0;

//=============================================================================
// ��������
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{//���I�m��
		pTime = new CTime;

		//NULL�`�F�b�N
		if (pTime != NULL)
		{
			//�ʒu�̐ݒ�
			pTime->m_pos = pos;
			//����������
			pTime->Init();
		}
	}

	return pTime;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTime::Init(void)
{
	CNumber::Load();

	m_nTime = 0;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apNumber[nCntTime] = new CNumber;
		m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntTime), m_pos.y, m_pos.z));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apNumber[nCntTime]->Uninit();
	}

	CNumber::Unload();

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTime::Update(void)
{
	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();

	if (GameMode == CManager::MODE_GAME)
	{//�`���[�g���A���w���\��
		m_nTimeCount++;

		if (m_nTimeCount % 60 == 0)
		{// 1�b���Ƃɉ��Z
			m_nTime++;
		}

		int nTexData = m_nTime;
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{// �e�N�X�`���ɔ��f
			m_apNumber[nCntTime]->SetNumber(nTexData);
			nTexData /= 10;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apNumber[nCntTime]->Draw();
	}
}

//=============================================================================
// �^�C�����Z����
//=============================================================================
void CTime::MinusTime(int nTime)
{
	m_nTime -= nTime;
	if (m_nTime < 0)
	{
		m_nTime = 0;
	}
}