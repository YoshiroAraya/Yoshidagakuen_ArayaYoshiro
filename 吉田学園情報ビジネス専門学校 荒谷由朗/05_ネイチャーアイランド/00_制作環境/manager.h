//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "scene2D.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "tutorial.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  ��{�N���X
//=====================
class CManager
{
public://�N�ł�������
	typedef enum
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_TUTORIAL,		//�`���[�g���A��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_RANKING,		//�����L���O
		MODE_MAX			//�ő吔
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindows);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyBoard *GetInput(void) { return m_pInputKeyBoard; }
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }
	static CInputJoypad *GetInputJoyPad(void) { return m_pJoyPad; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CSound *GetSound(void) { return m_pSound; }

	static void RankingScore(int nScore);
	static int *GetRankingScore(int nidx);
	static void SetGameScore(int nScore);
	static int *GetGameScore();

private://�l�ł̂ݎg��
	static MODE m_mode;
	static CRenderer *m_pRenderer;
	static CSound *m_pSound;
	static CInputKeyBoard *m_pInputKeyBoard;
	static CInputMouse *m_pInputMouse;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CDebugProc *m_pDebugProc;
	static CGame *m_pGame;
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CResult *m_pResult;
	static CRanking *m_pRanking;
	static CInputJoypad *m_pJoyPad;

	static int				m_nScore[MAX_RANKING];
	static int				m_nGameScore;
};
#endif