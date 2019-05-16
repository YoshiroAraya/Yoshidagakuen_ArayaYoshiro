//=============================================================================
//
// ゲージ処理 [gauge.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"
#include "scene2D.h"
#include "circle.h"

#define GAUGE_TEXTURENAME00 "data/TEXTURE/gauge_000.png"
#define GAUGE_TEXTURENAME01 "data/TEXTURE/gauge_001.png"

#define GAUGE_MAX_TEXTURE (2)
#define GAUGE_MAX_2DPOLIGON (2)

#define MAX_CIRCLE (2)			// ゲージ数

//=============================================================================
// クラスの定義
//=============================================================================
class CGauge : public CScene  // ←派生クラス
{
public:
	CGauge();
	~CGauge();
	static CGauge *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CCircle *m_apCircle[MAX_CIRCLE];
	CScene2D						*m_apScene2D[GAUGE_MAX_2DPOLIGON];
	static LPDIRECT3DTEXTURE9		m_pTexture[GAUGE_MAX_TEXTURE];
	float							m_fWidth;
	float							m_fHeight;
	int								m_nCounterAnim;		//アニメーションカウンター
	float							m_nPatternAnim;		//アニメーションパターンNo.
};
#endif