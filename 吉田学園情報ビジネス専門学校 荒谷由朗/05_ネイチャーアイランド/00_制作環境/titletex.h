//=============================================================================
//
// �^�C�g���e�L�X�g�̏��� [titletex.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _TITLETEX_H_
#define _TITLETEX_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CTitletex : public CScene2D
{
public://�N�ł�������
	CTitletex();
	~CTitletex();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitletex *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int m_nType;										//���
	D3DXVECTOR2 m_size;									//�T�C�Y(����)
	D3DXVECTOR2 m_sizeDest;								//�T�C�Y(�ړI)
	float m_fLength;									//����
	float m_fAngle;										//�p�x
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR3 m_posDest;								//���W(�ړI)
	int m_nCounterAnim;									//�A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;									//�A�j���[�V�����p�^�[���̃J�E���^�[
	int m_nCntflame;									//�J�E���^�[
	int m_nCntDelete;									//�J�E���^�[
	bool m_nBlink;										//�_��
};
#endif