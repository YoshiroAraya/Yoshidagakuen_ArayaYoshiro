//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "sound.h"

#define TITLEWORD_INITPOS_Y (350.0f)		// �^�C�g�������̏�������
#define SUBTITLE_INITSIZE (1000.0f)			// �T�u�^�C�g���̏����T�C�Y
#define ISLAND_STERT (600)

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
// ��{�N���X
//=====================
class CTutorial
{
public:
	CTutorial();								// �R���X�g���N�^
	~CTutorial();								// �f�X�g���N�^
	HRESULT Init();							// ����������
	void	Uninit(void);					// �I������
	void	Update(void);					// �X�V����
	void	Draw(void);						// �`�揈��

private:
	int					m_nCount;			// �����t				�� �J�E���^�[
	int					m_nCnt;				// �e�N�X�`��			�� �J�E���^�[
	int				m_nLeafposY;			// �����t				�� �������W
	int				m_nLeafsize;			// �����t				�� �T�C�Y
};
#endif