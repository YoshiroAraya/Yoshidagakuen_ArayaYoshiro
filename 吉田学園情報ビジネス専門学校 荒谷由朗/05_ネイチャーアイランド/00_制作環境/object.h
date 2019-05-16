//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �L�n���u &�@�����[�S
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "model3D.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT_TEXTURE			(16)				// �I�u�W�F�N�g�̃e�N�X�`����
#define MAX_OBJECT					(14)				// �I�u�W�F�N�g�̃��f����
#define OBJECT_PRIOTITY				(2)

//=====================
//  CModel3D�̔h���N���X
//=====================
class CObject : public CModel3D
{
public://�N�ł�������
	CObject();
	~CObject();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject *Create(D3DXVECTOR3 pos, float move, int nTexTypeint,int nObjectType, MOVETYPE nMovetype, int nCollision);
	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private://�l�ł̂ݎg��
	static LPD3DXMESH	m_pMeshModel[MAX_OBJECT];					//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel[MAX_OBJECT];				//�}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMatModel[MAX_OBJECT];					//�}�e���A���̏��
	static LPDIRECT3DTEXTURE9 m_pMeshTextures[MAX_OBJECT_TEXTURE];
	D3DXVECTOR3			m_move;										// �ړ���
	int					m_nCount;									// �J�E���^�[
	int					m_nCollision;								// �����蔻���ONOFF
	int					m_nType;									// ���
	D3DXVECTOR3			m_ModelMove;								// �ړ��̎d��
};
#endif