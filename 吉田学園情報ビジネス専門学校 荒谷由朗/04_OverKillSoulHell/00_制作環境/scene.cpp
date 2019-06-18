//=============================================================================
//
// �V�[������ [scene.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "scene.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScene	*CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int		CScene::m_nNumAll							= 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nNumAll++;
			m_nID		= nCntScene;
			m_nPriID	= nPriority;
			m_objtype	= OBJTYPE_NONE;
			break;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �����[�X�I�[��
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{// ���um_apScene�v��NULL����Ȃ��Ƃ�
				// �������̊J��
				m_apScene[nCntPriority][nCntScene]->Uninit();
				delete[] m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}

//=============================================================================
// �S�Ă̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{// ���ug_apEnemy�v��NULL����Ȃ��Ƃ�
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// �S�Ă̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{// ���um_apScene�v��NULL����Ȃ��Ƃ�
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// �����[�X
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriID][m_nID] != NULL)		// m_nID �� this->m_nID �ł���
	{// ���um_apScene�v��NULL����Ȃ��Ƃ�
		// �������̊J��
		int nID,nPriID;
		nID = m_nID;							// delete����ƃV�[�����S�Ĕj�������̂�nID�ɕۑ����Ă���
		nPriID = m_nPriID;
		delete m_apScene[nPriID][nID];			// delete this ���o���邪�~�܂�
		m_apScene[nPriID][nID] = NULL;
		m_nNumAll--;							// �����̌��Z
	}
}

//=============================================================================
// �I�u�W�F�N�g�^�C�v�̐ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objtype)
{
	m_objtype = objtype;
}

//=============================================================================
// �I�u�W�F�N�g�^�C�v�̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objtype;
}

//=============================================================================
// �I�u�W�F�N�g�̎擾
//=============================================================================
CScene *CScene::GetScene(int PRI_Idx, int SCENE_Idx)
{
	return m_apScene[PRI_Idx][SCENE_Idx];
}

//=============================================================================
// ���W�̎擾
//=============================================================================
D3DXVECTOR3 CScene::GetPosition(void)
{
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}