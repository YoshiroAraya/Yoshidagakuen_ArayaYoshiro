//=============================================================================
//
// �A�C�e������ [item.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "model3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ITEM_TYPE		(2)
#define MAX_TEXTURE_TYPE	(1)

//=====================
//  CScene�̔h���N���X
//=====================
class CItem : public CModel3D
{
public://�N�ł�������
	typedef enum
	{
		ITEMTYPE_APPLE = 0,		//�����S
		ITEMTYPE_BANANA,		//�o�i�i
		ITEMTYPE_MAX			//��Ԃ̑���
	}ITEMTYPE;					//�A�C�e���̎�ނ̗񋓌^

	typedef struct
	{
		int nType;				//�A�C�e���̎�� int�^
		ITEMTYPE ItemType;		//�A�C�e���̎��
	} ITEM;						//�A�C�e���̍\����

	CItem();
	~CItem();
	static HRESULT Load(void);								//�I�u�W�F�N�g�ǂݍ���
	static void UnLoad(void);								//�I�u�W�F�N�g�̃}�e���A�����j��
	HRESULT Init(void);										//������
	void Uninit(void);										//�I��
	void Update(void);										//�X�V
	void Draw(void);										//�`��
	static CItem *Create(D3DXVECTOR3 pos, int type);		//�I�u�W�F�N�g����

	ITEM *GetItem(void);
	bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);	//�����蔻��

private://�l�ł̂ݎg��
		static LPD3DXMESH			m_pMesh[MAX_ITEM_TYPE];				//���b�V�����ւ̃|�C���^
		static LPD3DXBUFFER			m_pBuffMat[MAX_ITEM_TYPE];			//�}�e���A�����ւ̃|�C���^
		static DWORD				m_nNumMat[MAX_ITEM_TYPE];			//�}�e���A���̏��
		static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ITEM_TYPE];			//�e�N�X�`���ւ̃|�C���^

		D3DXVECTOR3	 m_pos;						//�ʒu
		D3DXVECTOR3	 m_posold;					//�O��̈ʒu
		D3DXVECTOR3	 m_move;					//�ړ���
		D3DXVECTOR3	 m_rot;						//����
		ITEM		 m_aItem;					//�A�C�e���\���̂̕ϐ�
		int			 m_nMoveTimer;				//�ړ�����

};

#endif