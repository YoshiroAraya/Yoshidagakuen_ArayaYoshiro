//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "input.h"
#include "sound.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "time.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKING			(5)							//�����L���O�̐�
#define MAX_TIME			(3)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
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

//*********************************************************************
//�����L���O�N���X�̒�`
//*********************************************************************
class CRanking : public CScene //��{�N���X
{
public:
	CRanking(int nPriority = 7, CScene::OBJTYPE objType = CScene::OBJTYPE_FADE);
	~CRanking();
	static CRanking *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void	CreateStage(void);				// �X�e�[�W				�� �������ꊇ�Ǘ�
	void	CreateObject(void);				// �X�e�[�W��			�� �I�u�W�F�N�g�������ꊇ�Ǘ�
	void	SetTree(D3DXVECTOR3 pos);		// ��					�� ����

	//�����o�ϐ�
private:
	CScene2D			*m_pScene2DLogo;				//�V�[��2D���g�������S
	LPDIRECT3DTEXTURE9	m_pTexture[1];					//�e�N�X�`���ւ̃|�C���^
	CScene2D			*m_pScene2DRank[MAX_RANKING];	//�V�[��2D���g���������N�̃��S
	LPDIRECT3DTEXTURE9	m_pTextureRank[MAX_RANKING];	//�e�N�X�`���ւ̃|�C���^
	CNumber				*m_RankTime[MAX_RANKING][MAX_TIME];	//�����L���O�̐����i���o�[��p��
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
	static CShadow		*m_pShadow;			// �e

	int					m_nCntTimer;					//�t�F�[�h�܂ł̃J�E���g
	int					m_nCntCor;						//�F�ς��J�E���g
};

#endif