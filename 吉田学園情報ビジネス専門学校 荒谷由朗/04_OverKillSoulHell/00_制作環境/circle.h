//=============================================================================
//
// �Q�[�W(�~)�̏��� [circle.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define MAX_Circle				(1)									// �Q�[�W�̍ő吔
#define REDUCE_Circle			(0.3f)								// �Q�[�W�̌����(���t���[��)

#define CIRCLE_H (100) //���b�V���̕�����(H)
#define CIRCLE_V (10) //���b�V���̕�����(V)
#define CIRCLE_VERTEX ((CIRCLE_H + 1) * (CIRCLE_V + 1))
#define CIRCLE_INDEX ( (CIRCLE_H * CIRCLE_V )* 2 + (4 * (CIRCLE_V - 1)) + 2 )
#define CIRCLE_POLYGON (100.0f)

//=============================================================================
// �N���X�̒�`
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
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_pIdxBuff; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;			// �|���S���̈ʒu
	D3DXCOLOR					m_col;			// �Q�[�W�̐F
	float						m_Radius;		// ���a
	float						m_Radius2;		// ���a
	CIRCLETYPE					m_CircleType;
	float						m_fCircle;	// �Q�[�W�̒l
};
#endif