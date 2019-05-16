//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author :		�r�J�R�N
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene2D.h"
#include "manager.h"

#define PAUSE_TEXTURENAME00 "data/TEXTURE/pause100.png"
#define PAUSE_TEXTURENAME01 "data/TEXTURE/pause000.png"
#define PAUSE_TEXTURENAME02 "data/TEXTURE/pause001.png"
#define PAUSE_TEXTURENAME03 "data/TEXTURE/pause002.png"

#define PAUSE_MAX_TEXTURE (4)
#define PAUSE_MAX_POLIGON (5)
#define PAUSE_WIDTH				(SCREEN_WIDTH)					// �|�[�Y�̕�
#define PAUSE_HEIGHT			(SCREEN_HEIGHT)					// �|�[�Y�̍���
//*****************************************************************************
//	�N���X��`
//*****************************************************************************
class CPause
{
public:
	typedef enum
	{
		TYPE_CONTINUE,
		TYPE_RETRY,
		TYPE_QUIT,
		TYPE_MAX
	}TYPE;

	CPause();
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	static void Update(void);
	static void Draw(void);

	// �ÓI�����o�ϐ�
	static HRESULT Load(void);	//	�ǂݍ��ފ֐�(�e�N�X�`��)
	static void Unload(void);	// �J������֐�(�e�N�X�`��)

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[PAUSE_MAX_TEXTURE];				// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3						m_pos;						// �|�[�Y�̈ʒu
	static int						m_SelectNum;					// �I��ԍ�
	static float					m_SelectColor;					// �I��F

};
#endif