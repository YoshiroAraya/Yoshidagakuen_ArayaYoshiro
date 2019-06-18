//=============================================================================
//
// �X�L���A�C�R������ [mpicon.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _MPICON_H_
#define _MPICON_H_

#include "main.h"
#include "scene2D.h"

#define MP_TEXTURENAME00	"data/TEXTURE/MP_icon.png"		// �A�C�R��
#define MAX_MI_POLIGON		(4)								// �|���S���̍ő吔
#define MAX_MI_TEX			(1)								// �e�N�X�`���̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CMPIcon
{
public:
	typedef enum
	{
		MPICONTYPE_MISSILE = 0,
		MPICONTYPE_PAIR,
		MPICONTYPE_SHIELD,
		MPICONTYPE_HP,
		MPICONTYPE_MAX
	}MPICONTYPE;

	CMPIcon();
	~CMPIcon();
	static CMPIcon	*Create	();
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, int mptype);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

	void			SetType	(MPICONTYPE mpicontype);
	MPICONTYPE		GetType	(void);

	D3DXVECTOR3		GetPos	(void);
	void			SetPos	(D3DXVECTOR3 pos);
	void			SetCol	(D3DXCOLOR col);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3						m_pos;				// �|���S���̈ʒu
	D3DXCOLOR						m_col;				// �J���[
	MPICONTYPE						m_Type;				// �^�C�v
	int								m_nCount;			// �J�E���^�[
	int								m_nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int								m_nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	int								m_nSelect;			// �I��ԍ�
	bool							m_bUse;				// �g�p���Ă��邩�ǂ���
};
#endif