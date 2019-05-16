//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2D�̔h���N���X
//=====================
class CBullet : public CScene3D
{
public://�N�ł�������
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,		//�v���C���[
		BULLETTYPE_ENEMY,			//�G
		BULLETTYPE_MAX				//�ő吔
	}BULLETTYPE;

	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size, int type);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				  m_move;					//�ړ���
	int						  m_nType;					//���
	int						  m_nDamage;				//�_���[�W
	int						  m_nBulletType;			//�e�̒e�̎��
	D3DXVECTOR2				  m_Size;					//�T�C�Y
};

#endif