//=============================================================================
//
// プレイヤー処理 [player.h]
// Author :	荒谷 由朗
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define PLAYER_TEXTURENAME00 "data/TEXTURE/player000.png"
#define MAX_LIFE	(100)									// ライフの最大数
#define MAX_MP		(200)									// MPの最大数

//=============================================================================
// クラスの定義
//=============================================================================
class CPlayer : public CScene2D  // ←派生クラス
{
public:
	typedef enum
	{
		PLAYER_STATUSTYPE_NORMAL = 0,
		PLAYER_STATUSTYPE_DAMAGE,
		PLAYER_STATUSTYPE_DEAD,
		PLAYER_STATUSTYPE_MP_BARRIER,
		PLAYER_STATUSTYPE_MP_PAIR,
		PLAYER_STATUSTYPE_MAX
	}PLAYER_STATUSTYPE;

	typedef enum
	{
		PLAYER_BULLETTYPE_SLASH = 0,
		PLAYER_BULLETTYPE_POISON,
		PLAYER_BULLETTYPE_FLAME,
		PLAYER_BULLETTYPE_WIND,
		PLAYER_BULLETTYPE_MP_LASER,
		PLAYER_BULLETTYPE_MAX
	}PLAYER_BULLETTYPE;

	CPlayer();
	~CPlayer();
	static CPlayer		*Create			(void);
	static HRESULT		Load			(void);
	static void			Unload			(void);

	HRESULT				Init			(void);
	void				Uninit			(void);
	void				Update			(void);
	void				Draw			(void);

	void				HitPlayer		(int nDamage);
	void				Recovery		(int nRecovery);
	void				MpAbsorption	(int nAbsorption);
	int					GetPlayerLife	(void);
	int					GetPlayerMp		(void);

	void				SetStatusType	(PLAYER_STATUSTYPE statustype);
	PLAYER_STATUSTYPE	GetStatusType	(void);

	void				SetBulletType	(PLAYER_BULLETTYPE bullettype);
	PLAYER_BULLETTYPE	GetBulletType	(void);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャ
	CManager::MODE					m_mode;			// モード
	PLAYER_STATUSTYPE				m_StatusType;	// 情報のタイプ
	PLAYER_BULLETTYPE				m_BuletType;	// 弾のタイプ
	D3DXVECTOR3						m_pos;			// ポリゴンの位置
	D3DXCOLOR						m_col;			// カラー
	D3DXVECTOR3						m_move;			// ポリゴンの移動量
	int								m_Life;			// ライフ
	int								m_Mp;			// MP
	int								m_nCount;		// カウンター
	int								m_nCntDamage;	// ダメージカウンター
	int								m_nSkillCount;	// スキルカウンター
	float							m_fWidth;		// 幅
	float							m_fHeight;		// 高さ
	float							m_DamageCol;	// ダメージ時のカラー
};
#endif