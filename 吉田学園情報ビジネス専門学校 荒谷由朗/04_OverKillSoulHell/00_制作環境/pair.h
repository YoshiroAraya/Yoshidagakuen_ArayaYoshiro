//=============================================================================
//
// ペア処理 [pair.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _PAIR_H_
#define _PAIR_H_

#include "main.h"
#include "scene2D.h"

#define PAIR_TEXTURENAME00	"data/TEXTURE/pair000.png"
#define MAX_PAIRTAIM		(180)						// ペアの最大数
#define MAX_PAIRTEX			(1)							// テクスチャの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CPair : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		PAIRSTATE_NORMAL = 0,
		PAIRSTATE_WORNING,
		PAIRSTATE_DEAD,
		PAIRSTATE_MAX
	}PAIRSTATE;

	CPair();
	~CPair();
	static CPair	*Create	(D3DXVECTOR3 pos, float width, float height);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_PAIRTEX];	// テクスチャ
	D3DXVECTOR3						m_pos;						// ポリゴンの移動量
	D3DXVECTOR3						m_move;						// ポリゴンの移動量
	int								m_nCount;					// カウンター
	int								m_nDeleteCount;				// 消滅カウンター
	int								m_nCounterAnim;				// アニメーションカウンター
	int								m_nPatternAnim;				// アニメーションパターンNo.
	float							m_fWidth;					// 幅
	float							m_fHeight;					// 高さ
	float							m_DeleteCol;				// 選択色
};
#endif