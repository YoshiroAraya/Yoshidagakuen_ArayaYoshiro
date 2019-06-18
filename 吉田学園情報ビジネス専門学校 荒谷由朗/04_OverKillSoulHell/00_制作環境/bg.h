//=============================================================================
//
// �w�i���� [bg.h]
// Author :	�r�J �R�N
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

// �e�N�X�`���̖��O
#define BG_GAMETEX00		"data/TEXTURE/sky000.jpg"		// �w�i0
#define BG_GAMETEX01		"data/TEXTURE/sky001.png"		// �w�i1
#define BG_GAMETEX02		"data/TEXTURE/kill000.png"		// �\�E��UI
#define BG_TITLETEX00		"data/TEXTURE/title_bg.jpg"		// �^�C�g���w�i
#define BG_TITLETEX01		"data/TEXTURE/titlelogo.png"	// �^�C�g�����S
#define BG_TITLETEX02		"data/TEXTURE/torch000.png"		// ����(��)
#define BG_TITLETEX03		"data/TEXTURE/torch001.png"		// ����(���)
#define BG_TITLETEX04		"data/TEXTURE/PRESSENTER.png"	// �uPRESSENTER�v
#define BG_RESULTTEX00		"data/TEXTURE/GAMECLEAR000.jpg"	// �Q�[���N���A�w�i
#define BG_RESULTTEX01		"data/TEXTURE/GAMECLEAR001.png"	// �Q�[���N���A����
#define BG_RESULTTEX02		"data/TEXTURE/GAMEOVER000.jpg"	// �Q�[���I�[�o�[�w�i
#define BG_RESULTTEX03		"data/TEXTURE/GAMEOVER001.png"	// �Q�[���I�[�o�[����
#define BG_RESULTTEX04		"data/TEXTURE/pause100.png"		// �|�[�Y�w�i
#define BG_RESULTTEX05		"data/TEXTURE/pause001.png"		//�uRETRY�v
#define BG_RESULTTEX06		"data/TEXTURE/pause002.png"		//�uQUIT�v
#define BG_MAX_TEXTURE		(15)							// �e�N�X�`���̍ő吔
#define BG_MAX_2DPOLIGON	(7)								// �|���S���̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CBg : public CScene  // ���h���N���X
{
public:
	CBg();
	~CBg();
	static CBg		*Create	(void);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(void);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);
private:
	static LPDIRECT3DTEXTURE9	m_pTexture	[BG_MAX_TEXTURE];
	CScene2D					*m_apScene2D[BG_MAX_2DPOLIGON];
	D3DXVECTOR3					m_pos;				// �ʒu
	int							m_nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int							m_nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	CManager::MODE				m_mode;				// ���[�h
	int							m_Num2DPoligon;		// �|���S���ԍ�
	int							m_SelectNum;		// �I��ԍ�
	int							m_SelectNumDest;	// �I��ԍ�
};
#endif