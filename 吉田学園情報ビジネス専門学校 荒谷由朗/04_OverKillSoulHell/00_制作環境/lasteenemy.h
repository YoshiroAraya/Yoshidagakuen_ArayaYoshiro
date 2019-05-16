//=============================================================================
//
// �ŏI�G�l�~�[���� [lasteenemy.h]
// Author :		�r�J�R�N
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
// �N���X�̒�`
//=============================================================================
class CLastEnemy : public CScene2D  // ���h���N���X
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
	D3DXVECTOR3						m_pos;						// �|���S���̈ړ���
	D3DXVECTOR3						m_move;						// �|���S���̈ړ���
	D3DXCOLOR						m_col;						// �F
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LASTENEMYTEX];
	int								m_TypeNum;
	int								m_nCount;
	int								m_nCounterAnim;				// �A�j���[�V�����J�E���^�[
	int								m_nPatternAnim;				// �A�j���[�V�����p�^�[��No.
	float							m_fWidth;
	float							m_fHeight;
	int								m_life;
	bool							m_bRoundtrip;
	bool							m_nBlink;					// �F�̐؂�ւ�
	int								m_nCntBlink;				// �F�̃J�E���^�[
	LASTENEMYSTATSE					m_Statse;					// �X�e�[�^�X
	static int						m_nDed;
};
#endif