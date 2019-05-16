//=============================================================================
//
// 最終エネミー処理 [lasteenemy.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _LASTEENEMY_H_
#define _LASTEENEMY_H_

#include "main.h"
#include "scene2D.h"
#include "bullet.h"

#define MAX_LASTENEMYTEX (2)
#define MAX_LASTENEMYSPEED (0.4f)

#define LASTENEMY_TEXTURENAME00 "data/TEXTURE/enemy000.png"
#define LASTENEMY_TEXTURENAME01 "data/TEXTURE/enemy001.png"

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
	static CLastEnemy *Create(D3DXVECTOR3 pos, float width, float height, int texID);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height, int texID);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void HitEnemy(int nDamage, CBullet::BULLETTYPE bullettype);

private:
	D3DXVECTOR3						m_pos;						// ポリゴンの移動量
	D3DXVECTOR3						m_move;						// ポリゴンの移動量
	D3DXCOLOR						m_col;						// 色
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LASTENEMYTEX];
	int								m_TypeNum;
	int								m_nCount;
	int								m_nCounterAnim;				// アニメーションカウンター
	int								m_nPatternAnim;				// アニメーションパターンNo.
	float							m_fWidth;
	float							m_fHeight;
	int								m_life;
	bool							m_bRoundtrip;
	bool							m_nBlink;					// 色の切り替え
	int								m_nCntBlink;				// 色のカウンター
	LASTENEMYSTATSE					m_Statse;					// ステータス
	static int						m_nDed;
};
#endif