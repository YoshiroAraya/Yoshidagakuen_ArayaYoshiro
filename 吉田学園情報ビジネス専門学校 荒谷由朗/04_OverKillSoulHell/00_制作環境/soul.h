//=============================================================================
//
// �\�E������ [soul.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _SOUL_H_
#define _SOUL_H_

#include "main.h"
#include "scene2D.h"

#define SOUL_TEXTURENAME00	"data/TEXTURE/soul000.png"
#define MAX_SOULTEX			(1)								// �e�N�X�`���̍ő吔

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CSoul : public CScene2D  // ���h���N���X
{
public:
	CSoul();
	~CSoul();
	static CSoul	*Create	(D3DXVECTOR3 pos, float width, float height);
	static HRESULT	Load	(void);
	static void		Unload	(void);

	HRESULT			Init	(D3DXVECTOR3 pos, float width, float height);
	void			Uninit	(void);
	void			Update	(void);
	void			Draw	(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_SOULTEX];	// �e�N�X�`��
	D3DXVECTOR3					m_pos;						// �|���S���̈ړ���
	D3DXVECTOR3					m_move;						// �|���S���̈ړ���
	D3DXVECTOR3					m_GaugePos;					// �Q�[�W�̍��W
	float						m_fWidth;					// ��
	float						m_fHeight;					// ����
	float						m_fAngle;					// �p�x
};
#endif