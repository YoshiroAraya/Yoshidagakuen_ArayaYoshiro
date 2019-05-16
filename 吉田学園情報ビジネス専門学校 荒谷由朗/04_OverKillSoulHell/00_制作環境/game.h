//=============================================================================
//
// ƒQ[ƒ€ˆ— [game.h]
// Author :		r’J—R˜N
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//=============================================================================
// ƒNƒ‰ƒX‚Ì’è‹`
//=============================================================================
class CGame
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void Update(void);
	void Uninit(void);

	static CPlayer *GetPlayer(void);
	bool GetPause(void) { return m_bPause; }
	void SetPause(bool bPause);

private:
	static CPlayer		*m_pPlayer;
	int					m_nCounter;
	bool				m_bPause;
};
#endif