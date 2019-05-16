//=============================================================================
//
// 説明画面処理 [creation.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _CREATION_H_
#define _CREATION_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define CREATION_TEX00 "data/TEXTURE/tutorial001.jpg"
#define CREATION_TEX01 "data/TEXTURE/tutorial002.png"
#define CREATION_TEX02 "data/TEXTURE/tutorial003.png"
#define CREATION_TEX03 "data/TEXTURE/tutorial004.png"
#define CREATION_TEX04 "data/TEXTURE/tutorial005.png"
#define CREATION_TEX05 "data/TEXTURE/tutorial006.png"
#define CREATION_TEX06 "data/TEXTURE/tutorial007.png"

#define CREATION_MAX_TEXTURE (7)
#define CREATION_MAX_2DPOLIGON (7)

//=============================================================================
// クラスの定義
//=============================================================================
class CCreation : public CScene2D  // ←派生クラス
{
public:
	CCreation();
	~CCreation();
	static CCreation *Create(void);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[CREATION_MAX_TEXTURE];
	CScene2D					*m_apScene2D[CREATION_MAX_2DPOLIGON];
	D3DXVECTOR3					m_pos;				// ポリゴンの位置
	int							m_nSelect;
};
#endif