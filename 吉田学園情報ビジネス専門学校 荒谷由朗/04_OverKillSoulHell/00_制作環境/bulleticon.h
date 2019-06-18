//=============================================================================
//
// 弾アイコン処理 [bulleticon.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _BULLETICON_H_
#define _BULLETICON_H_

#include "main.h"
#include "scene2D.h"

#define BI_TEXTURENAME00	"data/TEXTURE/icon_frame.png"		// フレーム
#define BI_TEXTURENAME01	"data/TEXTURE/bullet_icon001.png"	// アイコン
#define MAX_BI_POLIGON		(2)									// ポリゴンの最大数
#define MAX_BI_TEX			(2)									// テクスチャの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CBulletIcon : public CScene  // ←派生クラス
{
public:
	typedef enum
	{
		ICONTYPE_SLASH = 0,
		ICONTYPE_POISON,
		ICONTYPE_FLAME,
		ICONTYPE_WIND,
		ICONTYPE_MAX
	}ICONTYPE;

	CBulletIcon();
	~CBulletIcon();
	static CBulletIcon	*Create	(void);
	static HRESULT		Load	(void);
	static void			Unload	(void);

	HRESULT Init		(void);
	void	Uninit		(void);
	void	Update		(void);
	void	Draw		(void);

	void	SetIconType	(ICONTYPE icontype);

private:
	CScene2D						*m_apScene2D[MAX_BI_POLIGON];
	static LPDIRECT3DTEXTURE9		m_pTexture	[MAX_BI_TEX];
	ICONTYPE						m_Type;
	int								m_nCount;
	int								m_nCounterAnim;				// アニメーションカウンター
	int								m_nPatternAnim;				// アニメーションパターンNo.
};
#endif