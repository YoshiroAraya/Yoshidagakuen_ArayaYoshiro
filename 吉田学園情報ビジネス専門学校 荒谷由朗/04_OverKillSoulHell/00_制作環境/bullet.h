//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define BULLET_TEXTURENAME00	"data/TEXTURE/bullet000_slash.png"		// �a��
#define BULLET_TEXTURENAME01	"data/TEXTURE/bullet001_poison.png"		// ��
#define BULLET_TEXTURENAME02	"data/TEXTURE/bullet002_fire.png"		// ��
#define BULLET_TEXTURENAME03	"data/TEXTURE/bullet003_wind.png"		// ��
#define BULLET_TEXTURENAME04	"data/TEXTURE/bullet004_enemy.png"		// �G�̒e
#define BULLET_TEXTURENAME05	"data/TEXTURE/missile.png"				// �z�[�~���O
#define MAX_BULLETTEXTURE		(6)										// �e�N�X�`���̍ő吔
#define SLASH_SPEED				(8.0f)									// �a���̑���
#define POISON_SPEED			(1.0f)									// �ł̑���
#define FLAME_SPEED				(3.0f)									// ���̑���
#define WIND_SPEED				(15.0f)									// ���̑���
#define ENEMY_SPEED				(0.15f)									// �G�̒e�̑���
#define HOMING_SPEED			(10.0f)									// �z�[�~���O�̑���
#define PAIR_SPEED				(0.5f)									// �y�A�̑���
#define SLASH_POWER				(2)										// �a���̃_���[�W��
#define POISON_POWER			(4)										// �ł̃_���[�W��
#define FLAME_POWER				(3)										// ���̃_���[�W��
#define WIND_POWER				(1)										// ���̃_���[�W��
#define HOMING_POWER			(2)										// �G�̒e�̃_���[�W��
#define PAIR_POWER				(1)										// �y�A�̃_���[�W��

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CBullet : public CScene2D  // ���h���N���X
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
	{// �p�����[�^�[�̃e�[�u��
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
	CManager::MODE					m_mode;							// ���[�h
	D3DXVECTOR3						m_PlayerPos;					// �v���C���[�̍��W
	D3DXVECTOR3						m_move;							// �|���S���̈ړ���
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_BULLETTEXTURE];	// �e�N�X�`��
	float							m_fWidth;						// ��
	float							m_fHeight;						// ����
	float							m_fAngle;						// ����
	BULLETTYPE						m_BulletType;					// �o���b�g�^�C�v
	int								m_nCounterAnim;					// �A�j���[�V�����J�E���^�[
	int								m_nPatternAnim;					// �A�j���[�V�����p�^�[��No.
};
#endif