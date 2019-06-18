//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2D.h"
#include "bullet.h"

#define ENEMY_TEXTURENAME00 "data/TEXTURE/enemy000.png"		// �G�̃e�N�X�`��0
#define ENEMY_TEXTURENAME01 "data/TEXTURE/enemy001.png"		// �G�̃e�N�X�`��1
#define MAX_ENEMYTEX		(2)								// �e�N�X�`���̍ő吔
#define MAX_ENEMYSPEED		(0.4f)							// �ړ����x

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CEnemy : public CScene2D  // ���h���N���X
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
	static CEnemy	*Create	(D3DXVECTOR3 pos, float width, float height,int texID);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height, int texID);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

	void			HitEnemy(int nDamage,CBullet::BULLETTYPE bullettype);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_ENEMYTEX];
	D3DXVECTOR3						m_pos;						// ���W
	D3DXVECTOR3						m_move;						// �ړ���
	D3DXCOLOR						m_col;						// �F
	int								m_TypeNum;					// �G�̎�ޔԍ�
	int								m_nCount;					// �ړ��̃J�E���^�[
	int								m_nCounterAnim;				// �A�j���[�V�����J�E���^�[
	int								m_nPatternAnim;				// �A�j���[�V�����p�^�[��No.
	int								m_life;						// ���C�t
	int								m_nCntBlink;				// �F�̃J�E���^�[
	float							m_fWidth;					// ��
	float							m_fHeight;					// ����
	bool							m_bRoundtrip;				// ����
	bool							m_nBlink;					// �F�̐؂�ւ�
	ENEMYSTATSE						m_Statse;					// �X�e�[�^�X
};
#endif