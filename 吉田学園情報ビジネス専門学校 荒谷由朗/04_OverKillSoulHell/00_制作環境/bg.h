//=============================================================================
//
// 背景処理 [bg.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

// テクスチャの名前
#define BG_GAMETEX00		"data/TEXTURE/sky000.jpg"		// 背景0
#define BG_GAMETEX01		"data/TEXTURE/sky001.png"		// 背景1
#define BG_GAMETEX02		"data/TEXTURE/kill000.png"		// ソウルUI
#define BG_TITLETEX00		"data/TEXTURE/title_bg.jpg"		// タイトル背景
#define BG_TITLETEX01		"data/TEXTURE/titlelogo.png"	// タイトルロゴ
#define BG_TITLETEX02		"data/TEXTURE/torch000.png"		// 松明(火)
#define BG_TITLETEX03		"data/TEXTURE/torch001.png"		// 松明(台座)
#define BG_TITLETEX04		"data/TEXTURE/PRESSENTER.png"	// 「PRESSENTER」
#define BG_RESULTTEX00		"data/TEXTURE/GAMECLEAR000.jpg"	// ゲームクリア背景
#define BG_RESULTTEX01		"data/TEXTURE/GAMECLEAR001.png"	// ゲームクリア文字
#define BG_RESULTTEX02		"data/TEXTURE/GAMEOVER000.jpg"	// ゲームオーバー背景
#define BG_RESULTTEX03		"data/TEXTURE/GAMEOVER001.png"	// ゲームオーバー文字
#define BG_RESULTTEX04		"data/TEXTURE/pause100.png"		// ポーズ背景
#define BG_RESULTTEX05		"data/TEXTURE/pause001.png"		//「RETRY」
#define BG_RESULTTEX06		"data/TEXTURE/pause002.png"		//「QUIT」
#define BG_MAX_TEXTURE		(15)							// テクスチャの最大数
#define BG_MAX_2DPOLIGON	(7)								// ポリゴンの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CBg : public CScene  // ←派生クラス
{
public:
	CBg();
	~CBg();
	static CBg		*Create	(void);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(void);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);
private:
	static LPDIRECT3DTEXTURE9	m_pTexture	[BG_MAX_TEXTURE];
	CScene2D					*m_apScene2D[BG_MAX_2DPOLIGON];
	D3DXVECTOR3					m_pos;				// 位置
	int							m_nCounterAnim;		// アニメーションカウンター
	int							m_nPatternAnim;		// アニメーションパターンNo.
	CManager::MODE				m_mode;				// モード
	int							m_Num2DPoligon;		// ポリゴン番号
	int							m_SelectNum;		// 選択番号
	int							m_SelectNumDest;	// 選択番号
};
#endif