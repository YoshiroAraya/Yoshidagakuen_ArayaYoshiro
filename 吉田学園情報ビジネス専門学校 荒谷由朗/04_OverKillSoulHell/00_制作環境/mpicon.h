//=============================================================================
//
// スキルアイコン処理 [mpicon.h]
// Author :		Yoshiro Araya
//
//=============================================================================
#ifndef _MPICON_H_
#define _MPICON_H_

#include "main.h"
#include "scene2D.h"

#define MAX_MI_POLIGON (4)
#define MAX_MI_TEX (1)

#define MP_TEXTURENAME00 "data/TEXTURE/MP_icon.png"

//=============================================================================
// クラスの定義
//=============================================================================
class CMPIcon
{
public:
	typedef enum
	{
		MPICONTYPE_MISSILE = 0,
		MPICONTYPE_PAIR,
		MPICONTYPE_SHIELD,
		MPICONTYPE_HP,
		MPICONTYPE_MAX
	}MPICONTYPE;

	CMPIcon();
	~CMPIcon();
	static CMPIcon *Create();
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, int mptype);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void		SetType(MPICONTYPE mpicontype);
	MPICONTYPE			GetType(void);

	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetCol(D3DXCOLOR col);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3						m_pos;			// ポリゴンの位置
	D3DXCOLOR						m_col;
	MPICONTYPE						m_Type;
	int								m_nCount;
	int								m_nCounterAnim;				// アニメーションカウンター
	int								m_nPatternAnim;				// アニメーションパターンNo.
	int								m_nSelect;
	bool							m_bUse;
};
#endif