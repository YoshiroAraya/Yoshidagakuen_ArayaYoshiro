//=============================================================================
//
// �������� [number.h]
// Author : keisuke komatsu
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "scene2D.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);	//	�ǂݍ���
	static void Unload(void);	//	�J��

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
};

#endif