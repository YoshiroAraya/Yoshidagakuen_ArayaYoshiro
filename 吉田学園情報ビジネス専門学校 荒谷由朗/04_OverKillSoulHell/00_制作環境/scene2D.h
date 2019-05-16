//=============================================================================
//
// �|���S������ [scene2D.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CScene2D : public CScene  // ���h���N���X
{
public:
	CScene2D(int nPriority = 0);
	~CScene2D();
	static CScene2D *Create(void);

	HRESULT		Init(void);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);
	void		SetPosition(D3DXVECTOR3 pos, float width, float height);
	void		SetRot(float rot, float width, float height);
	void		SetCol(D3DXCOLOR col);
	void		SetTexture(int PatternAnim, int X, int Y);
	void		SetScore(int nValue);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);
	void BindTexture(LPDIRECT3DTEXTURE9 Texture);
	D3DXVECTOR3 GetPosition(void);
	D3DXCOLOR GetCol(void);
	float CScene2D::GetWidth(void);
	float CScene2D::GetHeight(void);

private:
	LPDIRECT3DTEXTURE9			m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;			// �|���S���̈ʒu
	D3DXCOLOR					m_col;
	D3DXVECTOR3					m_rot;			// �|���S���̌���
	D3DXVECTOR2					m_tex;			// �e�N�X�`���̍��W
	float m_fRot;
	float m_fWidth;
	float m_fHeight;
	float m_fLength;
	float m_fAngle;
};

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	float		rhw;
	D3DCOLOR	col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

#endif