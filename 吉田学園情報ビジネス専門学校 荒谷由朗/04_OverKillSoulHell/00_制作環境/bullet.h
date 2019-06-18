//=============================================================================
//
// バレット処理 [bullet.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define BULLET_TEXTURENAME00	"data/TEXTURE/bullet000_slash.png"		// 斬撃
#define BULLET_TEXTURENAME01	"data/TEXTURE/bullet001_poison.png"		// 毒
#define BULLET_TEXTURENAME02	"data/TEXTURE/bullet002_fire.png"		// 炎
#define BULLET_TEXTURENAME03	"data/TEXTURE/bullet003_wind.png"		// 風
#define BULLET_TEXTURENAME04	"data/TEXTURE/bullet004_enemy.png"		// 敵の弾
#define BULLET_TEXTURENAME05	"data/TEXTURE/missile.png"				// ホーミング
#define MAX_BULLETTEXTURE		(6)										// テクスチャの最大数
#define SLASH_SPEED				(8.0f)									// 斬撃の速さ
#define POISON_SPEED			(1.0f)									// 毒の速さ
#define FLAME_SPEED				(3.0f)									// 炎の速さ
#define WIND_SPEED				(15.0f)									// 風の速さ
#define ENEMY_SPEED				(0.15f)									// 敵の弾の速さ
#define HOMING_SPEED			(10.0f)									// ホーミングの速さ
#define PAIR_SPEED				(0.5f)									// ペアの速さ
#define SLASH_POWER				(2)										// 斬撃のダメージ量
#define POISON_POWER			(4)										// 毒のダメージ量
#define FLAME_POWER				(3)										// 炎のダメージ量
#define WIND_POWER				(1)										// 風のダメージ量
#define HOMING_POWER			(2)										// 敵の弾のダメージ量
#define PAIR_POWER				(1)										// ペアのダメージ量

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
		int			damege;
		const char* texture;
		int			animMax;
	};

	CBullet();
	~CBullet();
	static CBullet	*Create			(D3DXVECTOR3 pos, float width, float height, BULLETTYPE Bullettype);
	static HRESULT	Load			(void);
	static void		Unload			(void);

	HRESULT			Init			(D3DXVECTOR3 pos, float width, float height, BULLETTYPE Bullettype);
	void			Uninit			(void);
	void			Update			(void);
	void			Draw			(void);

	void			SetBulletType	(BULLETTYPE bullettype);
	BULLETTYPE		GetBulletType	(void);
private:
	CManager::MODE					m_mode;							// モード
	D3DXVECTOR3						m_PlayerPos;					// プレイヤーの座標
	D3DXVECTOR3						m_move;							// ポリゴンの移動量
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_BULLETTEXTURE];	// テクスチャ
	float							m_fWidth;						// 幅
	float							m_fHeight;						// 高さ
	float							m_fAngle;						// 差分
	BULLETTYPE						m_BulletType;					// バレットタイプ
	int								m_nCounterAnim;					// アニメーションカウンター
	int								m_nPatternAnim;					// アニメーションパターンNo.
};
#endif