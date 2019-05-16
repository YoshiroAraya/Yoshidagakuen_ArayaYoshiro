//=============================================================================
//
// �w�i���� [bg.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

// �e�N�X�`���̖��O
#define BG_GAMETEX00 "data/TEXTURE/sky000.jpg"
#define BG_GAMETEX01 "data/TEXTURE/sky001.png"
#define BG_GAMETEX02 "data/TEXTURE/kill000.png"
#define BG_TITLETEX00 "data/TEXTURE/title_bg.jpg"
#define BG_TITLETEX01 "data/TEXTURE/titlelogo.png"
#define BG_TITLETEX02 "data/TEXTURE/torch000.png"
#define BG_TITLETEX03 "data/TEXTURE/torch001.png"
#define BG_TITLETEX04 "data/TEXTURE/PRESSENTER.png"
#define BG_RESULTTEX00 "data/TEXTURE/GAMECLEAR000.jpg"
#define BG_RESULTTEX01 "data/TEXTURE/GAMECREAR001.png"
#define BG_RESULTTEX02 "data/TEXTURE/GAMEOVER000.jpg"
#define BG_RESULTTEX03 "data/TEXTURE/GAMEOVER001.png"
#define BG_RESULTTEX04 "data/TEXTURE/pause100.png"
#define BG_RESULTTEX05 "data/TEXTURE/pause001.png"
#define BG_RESULTTEX06 "data/TEXTURE/pause002.png"

#define BG_MAX_TEXTURE		(15)	// �e�N�X�`���̍ő吔
#define BG_MAX_2DPOLIGON	(7)		// �|���S���̍ő吔

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

	HRESULT Init	(void);
	void	Uninit	(void);
	void	Update	(void);
	void	Draw	(void);
private:
	static LPDIRECT3DTEXTURE9	m_pTexture	[BG_MAX_TEXTURE];
	CScene2D					*m_apScene2D[BG_MAX_2DPOLIGON];

	D3DXVECTOR3		m_pos;				// �ʒu
	int				m_nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int				m_nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	CManager::MODE	m_mode;
	int				m_Num2DPoligon;
	int				m_SelectNum;		// �I��ԍ�
	int				m_SelectNumDest;	// �I��ԍ�
};
#endif