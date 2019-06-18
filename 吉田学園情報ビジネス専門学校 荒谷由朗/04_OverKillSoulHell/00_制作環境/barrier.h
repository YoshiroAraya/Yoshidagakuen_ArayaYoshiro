//=============================================================================
//
// �o���A���� [barrier.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "main.h"
#include "scene2D.h"

#define BARRIER_TEXTURENAME00	"data/TEXTURE/barrier.png"		// �e�N�X�`���̖��O
#define BARRIER_MAX_TIME		(20)							// ���Ԑ���

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CBarrier : public CScene2D  // ���h���N���X
{
public:
	CBarrier();
	~CBarrier();
	static CBarrier *Create	(D3DXVECTOR3 pos);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT Init	(D3DXVECTOR3 pos);
	void	Uninit	(void);
	void	Update	(void);
	void	Draw	(void);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`��
	D3DXVECTOR3						m_pos;			// �ʒu
	D3DXVECTOR3						m_move;			// �ړ���
	D3DXCOLOR						m_col;			// �F
	float							m_fWidth;		// ��
	float							m_fHeight;		// ����
	int								m_nCntFrame;	// �J�E���^�[
};
#endif