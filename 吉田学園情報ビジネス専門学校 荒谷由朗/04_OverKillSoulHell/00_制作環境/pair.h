//=============================================================================
//
// ペア処理 [pair.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _PAIR_H_
#define _PAIR_H_

#include "main.h"
#include "scene2D.h"

#define MAX_PAIRTAIM (180)
#define MAX_PAIRTEX (1)

#define PAIR_TEXTURENAME00 "data/TEXTURE/pair000.png"

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
	static CPair *Create(D3DXVECTOR3 pos, float width, float height);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3				m_pos;						// ポリゴンの移動量
	D3DXVECTOR3				m_move;						// ポリゴンの移動量
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_PAIRTEX];
	int								m_nCount;
	int								m_nCounterAnim;				// アニメーションカウンター
	int								m_nPatternAnim;				// アニメーションパターンNo.
	float							m_fWidth;
	float							m_fHeight;
	float							m_DeleteCol;					// 選択色
	int								m_nDeleteCount;
};
#endif