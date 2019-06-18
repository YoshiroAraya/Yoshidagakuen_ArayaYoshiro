//=============================================================================
//
// ソウル処理 [soul.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _SOUL_H_
#define _SOUL_H_

#include "main.h"
#include "scene2D.h"

#define SOUL_TEXTURENAME00	"data/TEXTURE/soul000.png"
#define MAX_SOULTEX			(1)								// テクスチャの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CSoul : public CScene2D  // ←派生クラス
{
public:
	CSoul();
	~CSoul();
	static CSoul	*Create	(D3DXVECTOR3 pos, float width, float height);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_SOULTEX];	// テクスチャ
	D3DXVECTOR3					m_pos;						// ポリゴンの移動量
	D3DXVECTOR3					m_move;						// ポリゴンの移動量
	D3DXVECTOR3					m_GaugePos;					// ゲージの座標
	float						m_fWidth;					// 幅
	float						m_fHeight;					// 高さ
	float						m_fAngle;					// 角度
};
#endif