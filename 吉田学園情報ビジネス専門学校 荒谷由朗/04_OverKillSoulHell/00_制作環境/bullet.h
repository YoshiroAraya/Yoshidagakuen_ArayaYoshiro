//=============================================================================
//
// バレット処理 [bullet.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define BULLET_TEXTURENAME00 "data/TEXTURE/bullet000_slash.png"
#define BULLET_TEXTURENAME01 "data/TEXTURE/bullet001_poison.png"
#define BULLET_TEXTURENAME02 "data/TEXTURE/bullet002_fire.png"
#define BULLET_TEXTURENAME03 "data/TEXTURE/bullet003_wind.png"
#define BULLET_TEXTURENAME04 "data/TEXTURE/bullet004_enemy.png"
#define BULLET_TEXTURENAME05 "data/TEXTURE/missile.png"

#define MAX_BULLETTEXTURE (6)

#define SLASH_SPEED (8.0f)
#define POISON_SPEED (1.0f)
#define FLAME_SPEED (3.0f)
#define WIND_SPEED (15.0f)
#define ENEMY_SPEED (0.15f)
#define HOMING_SPEED (10.0f)
#define PAIR_SPEED (0.5f)

#define SLASH_POWER (2)
#define POISON_POWER (4)
#define FLAME_POWER (3)
#define WIND_POWER (1)
#define HOMING_POWER (2)
#define PAIR_POWER (1)

//=============================================================================
// テーブル
//=============================================================================

//=============================================================================
// クラスの定義
//=============================================================================
class CBullet : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		BULLETTYPE_SLASH = 0,
		BULLETTYPE_POISON,
		BULLETTYPE_FLAME,
		BULLETTYPE_WIND,
		BULLETTYPE_ENEMY,
		BULLETTYPE_MP_HOMING,
		BULLETTYPE_MP_PAIR,
		BULLETTYPE_MAX
	}BULLETTYPE;

	struct BULLET_PARAM
	{// パラメーターのテーブル
		int damege;
		const char* texture;
		int animMax;
	};



	CBullet();
	~CBullet();
	static CBullet *Create(D3DXVECTOR3 pos, float width, float height, BULLETTYPE Bullettype);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height, BULLETTYPE Bullettype);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void				SetBulletType(BULLETTYPE bullettype);
	BULLETTYPE			GetBulletType(void);
private:
	CManager::MODE		m_mode;
	D3DXVECTOR3				m_PlayerPos;
	D3DXVECTOR3				m_move;			// ポリゴンの移動量
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_BULLETTEXTURE];
	float							m_fWidth;
	float							m_fHeight;
	float							m_fAngle;
	BULLETTYPE						m_BulletType;
	int m_nCounterAnim;		//アニメーションカウンター
	int m_nPatternAnim;		//アニメーションパターンNo.
};
#endif