//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	HRESULT			Init		(void);
	void			Update		(void);
	void			Uninit		(void);

	static CPlayer	*GetPlayer	(void);

private:
	static CPlayer	*m_pPlayer;
};
#endif