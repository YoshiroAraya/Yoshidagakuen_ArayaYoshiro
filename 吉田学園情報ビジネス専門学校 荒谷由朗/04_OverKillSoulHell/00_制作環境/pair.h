//=============================================================================
//
// �y�A���� [pair.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _PAIR_H_
#define _PAIR_H_

#include "main.h"
#include "scene2D.h"

#define PAIR_TEXTURENAME00	"data/TEXTURE/pair000.png"
#define MAX_PAIRTAIM		(180)						// �y�A�̍ő吔
#define MAX_PAIRTEX			(1)							// �e�N�X�`���̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CPair : public CScene2D  // ���h���N���X
{
public:
	typedef enum
	{
		PAIRSTATE_NORMAL = 0,
		PAIRSTATE_WORNING,
		PAIRSTATE_DEAD,
		PAIRSTATE_MAX
	}PAIRSTATE;

	CPair();
	~CPair();
	static CPair	*Create	(D3DXVECTOR3 pos, float width, float height);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_PAIRTEX];	// �e�N�X�`��
	D3DXVECTOR3						m_pos;						// �|���S���̈ړ���
	D3DXVECTOR3						m_move;						// �|���S���̈ړ���
	int								m_nCount;					// �J�E���^�[
	int								m_nDeleteCount;				// ���ŃJ�E���^�[
	int								m_nCounterAnim;				// �A�j���[�V�����J�E���^�[
	int								m_nPatternAnim;				// �A�j���[�V�����p�^�[��No.
	float							m_fWidth;					// ��
	float							m_fHeight;					// ����
	float							m_DeleteCol;				// �I��F
};
#endif