//=============================================================================
//
// 最終エネミー処理 [lasteenemy.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _LASTEENEMY_H_
#define _LASTEENEMY_H_

#include "main.h"
#include "scene2D.h"
#include "bullet.h"

#define LASTENEMY_TEXTURENAME00 "data/TEXTURE/enemy000.png"		// 敵0
#define LASTENEMY_TEXTURENAME01 "data/TEXTURE/enemy001.png"		// 敵1
#define MAX_LASTENEMYTEX		(2)								// テクスチャの最大数
#define MAX_LASTENEMYSPEED		(0.4f)							// 移動速度

//=============================================================================
// クラスの定義
//=============================================================================
class CLastEnemy : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		LASTENEMYTYPE_000 = 0,
		LASTENEMYTYPE_001,
		LASTENEMYTYPE_002,
		LASTENEMYTYPE_003,
		LASTENEMYTYPE_004,
		LASTENEMYTYPE_005,
		LASTENEMYTYPE_MAX
	}LASTENEMYTYPE;

	typedef enum
	{
		LASTENEMYSTATSE_NONE = 0,
		LASTENEMYSTATSE_DAMEGE,
		LASTENEMYSTATSE_MAX
	}LASTENEMYSTATSE;

	CLastEnemy();
	~CLastEnemy();
	static CLastEnemy	*Create	(D3DXVECTOR3 pos, float width, float height, int texID);
	static HRESULT		Load	(void);
	static void			Unload	(void);

	HRESULT				Init	(D3DXVECTOR3 pos, float width, float height, int texID);
	void				Uninit	(void);
	void				Update	(void);
	void				Draw	(void);

	void				HitEnemy(int nDamage, CBullet::BULLETTYPE bullettype);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LASTENEMYTEX];	// テクスチャ
	D3DXVECTOR3						m_pos;							// ポリゴンの移動量
	D3DXVECTOR3						m_move;							// ポリゴンの移動量
	D3DXCOLOR						m_col;							// 色
	LASTENEMYSTATSE					m_Statse;						// ステータス
	int								m_TypeNum;						// タイプ番号
	int								m_nCount;						// カウンター
	int								m_nCounterAnim;					// アニメーションカウンター
	int								m_nPatternAnim;					// アニメーションパターンNo.
	int								m_life;							// ライフ
	int								m_nCntBlink;					// 色のカウンター
	float							m_fWidth;						// 幅
	float							m_fHeight;						// 高さ
	bool							m_bRoundtrip;					// 往復
	bool							m_nBlink;						// 色の切り替え
	static int						m_nDed;							// 死亡フラグ
};
#endif