//=============================================================================
//
// マネージャ処理 [manager.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CInputKeyboard;
class CInputJoyPad;
//=============================================================================
// クラスの定義
//=============================================================================
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	typedef enum
	{
		GAMERESULT_WIN = 0,
		GAMERESULT_LOSE,
		GAMERESULT_MAX
	}GAMERESULT;

	CManager();
	~CManager();

	HRESULT					Init				(HINSTANCE hInstance,HWND hWnd, bool bWindow);
	void					Uninit				(void);
	void					Update				(void);
	void					Draw				(void);

	static CRenderer		*GetRenderer		(void);
	static CInputKeyboard	*GetInputKeyboard	(void);
	static CInputJoyPad		*GetInputJoyPad		(void);

	static void				SetMode				(MODE mode);
	static MODE				GetMode				(void);
	static CPlayer			*&GetPlayer			(void);
	static CGauge			*&GetGauge			(void);
	static CGame			*&GetGame			(void) { return m_pGame; }
	static void				SetResult			(GAMERESULT result);
	static GAMERESULT		GetResult			(void);
	static CSound			*GetSound			(void);

private:
	static GAMERESULT		m_Result;
	static CRenderer		*m_pRenderer;
	static CFade			*m_pFade;
	static CInputKeyboard	*m_pInputKeyboard;
	static CInputJoyPad		*m_pInputJoyPad;
	static CSound			*m_pSound;
	static CTitle			*m_pTitle;
	static CTutorial		*m_pTutorial;
	static CGame			*m_pGame;
	static CResult			*m_pResult;
	static CPlayer			*m_pPlayer;
	static CGauge			*m_pGauge;
	static MODE				m_mode;
	static CPause			*m_pPause;
};
#endif