//=============================================================================
//
// �^�C�g������ [title.h]
// Author : �L�n ���u & �r�J �R�N
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "sound.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"

#define TITLEWORD_INITPOS_Y (350.0f)		// �^�C�g�������̏�������
#define SUBTITLE_INITSIZE	(1000.0f)		// �T�u�^�C�g���̏����T�C�Y
#define ISLAND_STERT		(600)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;

//=====================
// ��{�N���X
//=====================
class CTitle
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SKIP,
		TYPE_MAX
	}TYPE;

	CTitle();								// �R���X�g���N�^
	~CTitle();								// �f�X�g���N�^
	HRESULT Init();							// ����������
	void	Uninit	(void);					// �I������
	void	Update	(void);					// �X�V����
	void	Draw	(void);					// �`�揈��
	void	Set		(void);					// �ŏ���Create

	void	CreateStage	(void);				// �X�e�[�W				�� �������ꊇ�Ǘ�
	void	CreateObject(void);				// �X�e�[�W��			�� �I�u�W�F�N�g�������ꊇ�Ǘ�
	static TYPE GetType	(void);				// �^�C�v				�� �擾

private:
	static TYPE			m_pType;			// �^�C�g�����			�� �^�C�v

	static CPolygon3D	*m_pPolygon3D;		// �RD�|���S��			�� �|�C���^
	static CModel		*m_pModel;			// ���f��				�� �|�C���^
	static CMeshField	*m_pMeshField;		// ���b�V���t�B�[���h	�� �|�C���^
	static CObject		*m_pObject;			// �I�u�W�F�N�g			�� �|�C���^
	static CBillBoord	*m_pBillBoord;		// �r���{�[�h			�� �|�C���^
	static CEffect		*m_pEffect;			// �G�t�F�N�g			�� �|�C���^
	static CWall		*m_pWall;			// ��					�� �|�C���^
	static CGround		*m_pGround;			// �n��					�� �|�C���^

	int					m_nCount;			// �����t				�� �J�E���^�[
	int					m_nCnt;				// �e�N�X�`��			�� �J�E���^�[
	int					m_nLagCnt;
	int					m_nLeafposY;		// �����t				�� �������W
	int					m_nLeafsize;		// �����t				�� �T�C�Y
	bool				m_bOnOff;
};
#endif