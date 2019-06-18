//=============================================================================
//
// 説明画面処理 [description.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _DESCRIPTION_H_
#define _DESCRIPTION_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define DESCRIPTION_TEX00			"data/TEXTURE/tutorial001.jpg"		// 操作説明
#define DESCRIPTION_TEX01			"data/TEXTURE/tutorial002.png"		// UI説明
#define DESCRIPTION_TEX02			"data/TEXTURE/tutorial003.png"		// スキル説明
#define DESCRIPTION_TEX03			"data/TEXTURE/tutorial004.png"		// バレット説明
#define DESCRIPTION_TEX04			"data/TEXTURE/tutorial005.png"		// ゲーム概要
#define DESCRIPTION_TEX05			"data/TEXTURE/tutorial006.png"		// 操作ボタン説明0
#define DESCRIPTION_TEX06			"data/TEXTURE/tutorial007.png"		// 操作ボタン説明1
#define DESCRIPTION_MAX_TEXTURE		(7)									// テクスチャの最大数
#define DESCRIPTION_MAX_2DPOLIGON	(7)									// ポリゴンの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CDescription : public CScene2D  // ←派生クラス
{
public:
	CDescription();
	~CDescription();
	static CDescription *Create	(void);
	static HRESULT		Load	(void);
	static void			Unload	(void);

	HRESULT				Init	(void);
	void				Uninit	(void);
	void				Update	(void);
	void				Draw	(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture	[DESCRIPTION_MAX_TEXTURE];
	CScene2D					*m_apScene2D[DESCRIPTION_MAX_2DPOLIGON];
	D3DXVECTOR3					m_pos;										// ポリゴンの位置
	int							m_nSelect;									// 選択番号
};
#endif