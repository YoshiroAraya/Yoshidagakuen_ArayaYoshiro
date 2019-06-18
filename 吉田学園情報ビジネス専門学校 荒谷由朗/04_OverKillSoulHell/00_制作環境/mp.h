//=============================================================================
//
// �X�L���A�C�R������ [mp.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _MP_H_
#define _MP_H_

#include "main.h"
#include "mpicon.h"

#define MAX_SKILL (4)			// �X�L����

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CMP : public CScene  // ���h���N���X
{
public:
	CMP();
	~CMP();
	static CMP	*Create		(D3DXVECTOR3 pos);

	HRESULT		Init		(void);
	void		Uninit		(void);
	void		Update		(void);
	void		Draw		(void);

	static int	GetNumber	(void);

private:
	static CMPIcon			*m_apMPIcon[MAX_SKILL];			// �A�C�R��
	static D3DXVECTOR3		m_pos;							// �|���S���̈ʒu
	static int				m_nNumSelect, m_nNumSelectPast;	// �I��ԍ��A�I��ԍ�(�ߋ�)
};
#endif