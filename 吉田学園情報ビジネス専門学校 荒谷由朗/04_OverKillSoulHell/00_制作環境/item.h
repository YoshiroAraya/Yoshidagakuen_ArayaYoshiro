//=============================================================================
//
// �A�C�e������ [item.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

#define MAX_ITEMTEX (1)

#define ITEM_TEXTURENAME00 "data/TEXTURE/bullet_icon001.png"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CItem : public CScene2D  // ���h���N���X
{
public:
	typedef enum
	{
		ITEMTYPE_SLASH = 0,
		ITEMTYPE_POISON,
		ITEMTYPE_FLAME,
		ITEMTYPE_WIND,
		ITEMTYPE_MAX
	}ITEMTYPE;

	CItem();
	~CItem();
	static CItem *Create(D3DXVECTOR3 pos, float width, float height, int texID);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, float width, float height, int texID);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3				m_pos;						// �|���S���̈ړ���
	D3DXVECTOR3				m_move;						// �|���S���̈ړ���
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_ITEMTEX];
	ITEMTYPE						m_Type;
	float							m_fWidth;
	float							m_fHeight;
	int								m_nCount;
	float							m_DeleteCol;		// �I��F
	int								m_nDeleteCount;
};
#endif