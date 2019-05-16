//=============================================================================
//
// ���U���g���� [result.h]
// Author : �L�n ���u & �r�J �R�N
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CSerect;
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;
class CItem;
class CShadow;

//=====================
// ��{�N���X
//=====================
class CResult
{
public:
	CResult();								// �R���X�g���N�^
	~CResult();								// �f�X�g���N�^
	HRESULT Init();							// ����������
	void	Uninit(void);					// �I������
	void	Update(void);					// �X�V����
	void	Draw(void);						// �`�揈��

	void	CreateStage(void);				// �X�e�[�W				�� �������ꊇ�Ǘ�
	void	CreateObject(void);				// �X�e�[�W��			�� �I�u�W�F�N�g�������ꊇ�Ǘ�
	void	SetTree(D3DXVECTOR3 pos);		// ��					�� ����
private:
	static CSerect		*m_pSerect;			// �Z���N�g				�� �|�C���^
	static CPlayer		*m_pPlayer;			// �v���C���[			�� �|�C���^
	static CPolygon3D	*m_pPolygon3D;		// �RD�|���S��			�� �|�C���^
	static CModel		*m_pModel;			// ���f��				�� �|�C���^
	static CMeshField	*m_pMeshField;		// ���b�V���t�B�[���h	�� �|�C���^
	static CObject		*m_pObject;			// �I�u�W�F�N�g			�� �|�C���^
	static CBillBoord	*m_pBillBoord;		// �r���{�[�h			�� �|�C���^
	static CEffect		*m_pEffect;			// �G�t�F�N�g			�� �|�C���^
	static CWall		*m_pWall;			// ��					�� �|�C���^
	static CGround		*m_pGround;			// �n��					�� �|�C���^
	static CItem		*m_pItem;			// �A�C�e��				�� �|�C���^
	static CShadow		*m_pShadow;			//�e

	int					m_nCnt;				// �J�E���^�[
};
#endif