//=============================================================================
//
// �I������ [serect.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _SERECT_H_
#define _SERECT_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SERECT_TEXTURE	(3)

//=====================
//  CScene�̔h���N���X
//=====================
class CSerect : public CScene
{
public://�N�ł�������
	typedef enum
	{
		SERECT_NORMAL = 0,		//�I�����Ă��Ȃ����
		SERECT_SELECT,			//�I���������
		SERECT_MAX				//�I�����̍ő吔
	}PAUSESTATE;

	typedef enum
	{
		SERECT_START = 0,		//�y�Q�[�������Ȃ����z
		SERECT_TITLE,			//�y�^�C�g���ɖ߂�z
		MAX_MEMU				//�I�����̍ő吔
	}SERECT;

	static HRESULT Load(void);
	static void UnLoad(void);
	CSerect(int nPriority = 7, CScene::OBJTYPE objType = CScene::OBJTYPE_SERECT);
	~CSerect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSerect *Create();
	static int Get(void) { return m_SelectNum; };

private://�l�ł̂ݎg��
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SERECT_TEXTURE];	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;								//�ʒu
	D3DXCOLOR				m_col;								//�F
	float					m_SelectColor;						//�I�����Ă���Ƃ��̐F
	int						m_nCntState;						//�J�E���g���Ă�����
	static int						m_SelectNum;						//�Z���N�g�̐�
	bool					m_bUse;								//�g�p���Ă��邩�ǂ���
	SERECT					m_Serect;							//���j���[�̍\����
	PAUSESTATE				m_state;							//�|�[�Y�̏��
	D3DXVECTOR2				m_nSize;							//�T�C�Y
};
#endif