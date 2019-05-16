//=============================================================================
//
// エネミー処理 [enemy.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"
#include "bullet.h"

#define MAX_ENEMYTEX (2)
#define MAX_ENEMYSPEED (0.4f)

#define ENEMY_TEXTURENAME00 "data/TEXTURE/enemy000.png"
#define ENEMY_TEXTURENAME01 "data/TEXTURE/enemy001.png"

//=============================================================================
// クラスの定義
//=============================================================================
class CEnemy : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		ENEMYTYPE_000 = 0,
		ENEMYTYPE_001,
		ENEMYTYPE_002,
		ENEMYTYPE_003,
		ENEMYTYPE_004,
		ENEMYTYPE_005,
		ENEMYTYPE_MAX
	}ENEMYTYPE;

	typedef enum
	{
		ENEMYSTATSE_NONE = 0,
		ENEMYSTATSE_DAMEGE,
		ENEMYSTATSE_MAX
	}ENEMYSTATSE;

	CEnemy();
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos, float width, float height,int texID);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height, int texID);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void HitEnemy(int nDamage,CBullet::BULLETTYPE bullettype);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_ENEMYTEX];
	D3DXVECTOR3						m_pos;						// 座標
	D3DXVECTOR3						m_move;						// 移動量
	D3DXCOLOR						m_col;						// 色
	int								m_TypeNum;					// 敵の種類番号
	int								m_nCount;					// 移動のカウンター
	int								m_nCounterAnim;				// アニメーションカウンター
	int								m_nPatternAnim;				// アニメーションパターンNo.
	float							m_fWidth;					// 幅
	float							m_fHeight;					// 高さ
	int								m_life;						// ライフ
	bool							m_bRoundtrip;				// 移動の切り替え
	bool							m_nBlink;					// 色の切り替え
	int								m_nCntBlink;				// 色のカウンター
	ENEMYSTATSE						m_Statse;					// ステータス
};
#endif