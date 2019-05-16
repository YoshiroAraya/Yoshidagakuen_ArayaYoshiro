//=============================================================================
//
// 爆発処理 [explosion.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

#define EXPLOSION_TEXTURENAME00 "data/TEXTURE/explosion000_slash.png"
#define EXPLOSION_TEXTURENAME01 "data/TEXTURE/explosion001_poison.png"
#define EXPLOSION_TEXTURENAME02 "data/TEXTURE/explosion002_fire.png"
#define EXPLOSION_TEXTURENAME03 "data/TEXTURE/explosion003_wind.png"
#define EXPLOSION_TEXTURENAME04 "data/TEXTURE/explosion004_enemy.png"

#define EXPLOSION_MAX_TEXTURE (5)

//=============================================================================
// クラスの定義
//=============================================================================
class CExplosion : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_SLASH = 0,
		EXPLOSIONTYPE_POISON,
		EXPLOSIONTYPE_FLAME,
		EXPLOSIONTYPE_WIND,
		EXPLOSIONTYPE_ENEMY,
		EXPLOSIONTYPE_MAX
	}EXPLOSIONTYPE;

	CExplosion();
	~CExplosion();
	static CExplosion *Create(D3DXVECTOR3 pos, float width, float height, EXPLOSIONTYPE type);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static D3DXVECTOR3				m_move;			// ポリゴンの移動量
	static LPDIRECT3DTEXTURE9		m_pTexture[EXPLOSION_MAX_TEXTURE];
	EXPLOSIONTYPE					m_type;
	int m_nCounterAnim;		//アニメーションカウンター
	int m_nPatternAnim;		//アニメーションパターンNo.
};
#endif