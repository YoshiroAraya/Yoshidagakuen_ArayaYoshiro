//=============================================================================
//
// スキルアイコン処理 [mp.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _MP_H_
#define _MP_H_

#include "main.h"
#include "mpicon.h"

#define MAX_SKILL (4)			// スキル数

//=============================================================================
// クラスの定義
//=============================================================================
class CMP : public CScene  // ←派生クラス
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
	static CMPIcon			*m_apMPIcon[MAX_SKILL];			// アイコン
	static D3DXVECTOR3		m_pos;							// ポリゴンの位置
	static int				m_nNumSelect, m_nNumSelectPast;	// 選択番号、選択番号(過去)
};
#endif