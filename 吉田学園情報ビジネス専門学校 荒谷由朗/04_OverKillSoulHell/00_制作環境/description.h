//=============================================================================
//
// ������ʏ��� [description.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _DESCRIPTION_H_
#define _DESCRIPTION_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define DESCRIPTION_TEX00			"data/TEXTURE/tutorial001.jpg"		// �������
#define DESCRIPTION_TEX01			"data/TEXTURE/tutorial002.png"		// UI����
#define DESCRIPTION_TEX02			"data/TEXTURE/tutorial003.png"		// �X�L������
#define DESCRIPTION_TEX03			"data/TEXTURE/tutorial004.png"		// �o���b�g����
#define DESCRIPTION_TEX04			"data/TEXTURE/tutorial005.png"		// �Q�[���T�v
#define DESCRIPTION_TEX05			"data/TEXTURE/tutorial006.png"		// ����{�^������0
#define DESCRIPTION_TEX06			"data/TEXTURE/tutorial007.png"		// ����{�^������1
#define DESCRIPTION_MAX_TEXTURE		(7)									// �e�N�X�`���̍ő吔
#define DESCRIPTION_MAX_2DPOLIGON	(7)									// �|���S���̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CDescription : public CScene2D  // ���h���N���X
{
public:
	CDescription();
	~CDescription();
	static CDescription *Create	(void);
	static HRESULT		Load	(void);
	static void			Unload	(void);

	HRESULT				Init	(void);
	void				Uninit	(void);
	void				Update	(void);
	void				Draw	(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture	[DESCRIPTION_MAX_TEXTURE];
	CScene2D					*m_apScene2D[DESCRIPTION_MAX_2DPOLIGON];
	D3DXVECTOR3					m_pos;										// �|���S���̈ʒu
	int							m_nSelect;									// �I��ԍ�
};
#endif