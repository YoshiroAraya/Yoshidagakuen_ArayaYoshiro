//=============================================================================
//
// バリア処理 [barrier.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "main.h"
#include "scene2D.h"

#define BARRIER_TEXTURENAME00	"data/TEXTURE/barrier.png"		// テクスチャの名前
#define BARRIER_MAX_TIME		(20)							// 時間制限

//=============================================================================
// クラスの定義
//=============================================================================
class CBarrier : public CScene2D  // ←派生クラス
{
public:
	CBarrier();
	~CBarrier();
	static CBarrier *Create	(D3DXVECTOR3 pos);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT Init	(D3DXVECTOR3 pos);
	void	Uninit	(void);
	void	Update	(void);
	void	Draw	(void);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャ
	D3DXVECTOR3						m_pos;			// 位置
	D3DXVECTOR3						m_move;			// 移動量
	D3DXCOLOR						m_col;			// 色
	float							m_fWidth;		// 幅
	float							m_fHeight;		// 高さ
	int								m_nCntFrame;	// カウンター
};
#endif