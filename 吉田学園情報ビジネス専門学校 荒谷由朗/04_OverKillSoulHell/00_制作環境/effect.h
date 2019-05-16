//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

#define EFFECT_TEXTURENAME00 "data/TEXTURE/effect000.jpg"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CEffect : public CScene2D  // ���h���N���X
{
public:
	CEffect();
	~CEffect();
	static CEffect *Create(D3DXVECTOR3 pos, float width, float height);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static D3DXVECTOR3				m_move;			// �|���S���̈ړ���
	static LPDIRECT3DTEXTURE9		m_pTexture;
	D3DXCOLOR						m_col;
	float m_fWidth;
	float m_fHeight;
	int m_nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;		//�A�j���[�V�����p�^�[��No.
};
#endif