//=============================================================================
//
// アイテム処理 [item.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

#define ITEM_TEXTURENAME00	"data/TEXTURE/bullet_icon001.png"	// アイコン
#define MAX_ITEMTEX			(1)									// テクスチャの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CItem : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		ITEMTYPE_SLASH = 0,
		ITEMTYPE_POISON,
		ITEMTYPE_FLAME,
		ITEMTYPE_WIND,
		ITEMTYPE_MAX
	}ITEMTYPE;

	CItem();
	~CItem();
	static CItem	*Create	(D3DXVECTOR3 pos, float width, float height, int texID);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height, int texID);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_ITEMTEX];	// テクスチャ
	D3DXVECTOR3						m_pos;						// ポリゴンの移動量
	D3DXVECTOR3						m_move;						// ポリゴンの移動量
	int								m_nCount;					// カウンター
	int								m_nDeleteCount;				// 消滅カウンター
	ITEMTYPE						m_Type;						// タイプ
	float							m_fWidth;					// 幅
	float							m_fHeight;					// 高さ
	float							m_DeleteCol;				// 選択色
};
#endif