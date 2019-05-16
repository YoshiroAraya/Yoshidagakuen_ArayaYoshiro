//=============================================================================
//
// ゲージ(円)の処理 [circle.h]
// Author :		荒谷由朗
//
//=============================================================================
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define MAX_Circle				(1)									// ゲージの最大数
#define REDUCE_Circle			(0.3f)								// ゲージの減る量(毎フレーム)

#define CIRCLE_H (100) //メッシュの分割数(H)
#define CIRCLE_V (10) //メッシュの分割数(V)
#define CIRCLE_VERTEX ((CIRCLE_H + 1) * (CIRCLE_V + 1))
#define CIRCLE_INDEX ( (CIRCLE_H * CIRCLE_V )* 2 + (4 * (CIRCLE_V - 1)) + 2 )
#define CIRCLE_POLYGON (100.0f)

//=============================================================================
// クラスの定義
//=============================================================================
class CCircle
{
public:
	typedef enum
	{
		CIRCLETYPE_HP = 0,
		CIRCLETYPE_MP,
		CIRCLETYPE_MAX
	}CIRCLETYPE;

	CCircle();
	~CCircle();
	static CCircle *Create(D3DXVECTOR3 pos, float radius, float radius2, CIRCLETYPE type);

	HRESULT		Init(D3DXVECTOR3 pos, float radius, float radius2,CIRCLETYPE type);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);
	void		MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void		MakeIndex(LPDIRECT3DDEVICE9 pDevice);

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff; //インデックスバッファへのポインタ
	D3DXVECTOR3					m_pos;			// ポリゴンの位置
	D3DXCOLOR					m_col;			// ゲージの色
	float						m_Radius;		// 半径
	float						m_Radius2;		// 半径
	CIRCLETYPE					m_CircleType;
	float						m_fCircle;	// ゲージの値
};
#endif