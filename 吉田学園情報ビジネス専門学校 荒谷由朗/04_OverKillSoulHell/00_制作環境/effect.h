//=============================================================================
//
// エフェクト処理 [effect.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

#define EFFECT_TEXTURENAME00 "data/TEXTURE/effect000.jpg"

//=============================================================================
// クラスの定義
//=============================================================================
class CEffect : public CScene2D  // ←派生クラス
{
public:
	CEffect();
	~CEffect();
	static CEffect	*Create	(D3DXVECTOR3 pos, float width, float height);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);
private:
	static D3DXVECTOR3			m_move;				// ポリゴンの移動量
	static LPDIRECT3DTEXTURE9	m_pTexture;			// テクスチャ
	D3DXCOLOR					m_col;				// カラー
	float						m_fWidth;			// 幅
	float						m_fHeight;			// 高さ
	int							m_nCounterAnim;		// アニメーションカウンター
	int							m_nPatternAnim;		// アニメーションパターンNo.
};
#endif