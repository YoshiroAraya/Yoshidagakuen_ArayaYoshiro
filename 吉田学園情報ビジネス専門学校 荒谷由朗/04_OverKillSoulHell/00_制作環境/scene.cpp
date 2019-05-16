//=============================================================================
//
// シーン処理 [scene.cpp]
// Author :		荒谷由朗
//
//=============================================================================
#include "scene.h"

CScene *CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
//　コンストラクタ
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
//　デストラクタ
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
			{// ↑「m_apScene」がNULLじゃないとき
			 // メモリの開放
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
			{// ↑「g_apEnemy」がNULLじゃないとき
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
			{// ↑「m_apScene」がNULLじゃないとき
					m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

void CScene::Release(void)
{
	if (m_apScene[m_nPriID][m_nID] != NULL)		// m_nID が this->m_nID でも可
	{// ↑「m_apScene」がNULLじゃないとき
	 // メモリの開放
		int nID,nPriID;
		nID = m_nID;							// deleteするとシーンが全て破棄されるのでnIDに保存しておく
		nPriID = m_nPriID;
		delete m_apScene[nPriID][nID];			// delete this も出来るが止まる
		m_apScene[nPriID][nID] = NULL;
		m_nNumAll--;							// 総数の減算
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