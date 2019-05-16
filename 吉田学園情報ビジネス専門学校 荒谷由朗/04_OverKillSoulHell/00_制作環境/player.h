//=============================================================================
//
// �v���C���[���� [player.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define PLAYER_TEXTURENAME00 "data/TEXTURE/player000.png"

#define MAX_LIFE	(100)
#define MAX_MP		(200)

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CPlayer : public CScene2D  // ���h���N���X
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
	static CPlayer *Create(void);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void HitPlayer(int nDamage);
	void Recovery(int nRecovery);
	void MpAbsorption(int nAbsorption);
	int GetPlayerLife(void);
	int GetPlayerMp(void);

	void				SetStatusType(PLAYER_STATUSTYPE statustype);
	PLAYER_STATUSTYPE			GetStatusType(void);

	void				SetBulletType(PLAYER_BULLETTYPE bullettype);
	PLAYER_BULLETTYPE			GetBulletType(void);

private:
	CManager::MODE					m_mode;
	D3DXVECTOR3						m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3						m_move;			// �|���S���̈ړ���
	D3DXCOLOR						m_col;
	static LPDIRECT3DTEXTURE9		m_pTexture;
	PLAYER_STATUSTYPE				m_StatusType;
	PLAYER_BULLETTYPE				m_BuletType;
	float							m_fWidth;
	float							m_fHeight;
	float							m_GamageCol;
	int								m_Life;
	int								m_Mp;
	int								m_nCntDamage;
	int								m_nCount;
	int								m_nSkillCount;
};
#endif