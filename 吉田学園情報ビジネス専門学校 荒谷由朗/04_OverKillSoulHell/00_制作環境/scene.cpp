//=============================================================================
//
// �V�[������ [scene.cpp]
// Author :		�r�J�R�N
//
//=============================================================================
#include "scene.h"

CScene *CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
//�@�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nNumAll++;
			m_nID = nCntScene;
			m_nPriID = nPriority;
			m_objtype = OBJTYPE_NONE;
			break;
		}
	}
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

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

void CScene::SetObjType(OBJTYPE objtype)
{
	m_objtype = objtype;
}

CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objtype;
}

CScene *CScene::GetScene(int PRI_Idx, int SCENE_Idx)
{
	return m_apScene[PRI_Idx][SCENE_Idx];
}

D3DXVECTOR3 CScene::GetPosition(void)
{
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}