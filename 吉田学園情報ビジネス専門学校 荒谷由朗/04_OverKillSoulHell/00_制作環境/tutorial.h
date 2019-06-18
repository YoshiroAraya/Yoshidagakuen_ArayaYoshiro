//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//=============================================================================
// �N���X�̒�`
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