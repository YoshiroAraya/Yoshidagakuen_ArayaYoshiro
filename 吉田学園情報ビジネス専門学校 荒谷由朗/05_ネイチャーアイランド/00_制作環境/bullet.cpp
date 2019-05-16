//=============================================================================
//
// �o���b�g�̏��� [bullet.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\bullet000.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULLET_X		(2)										//���̑傫��
#define	BULLET_Y		(10)									//�c�̑傫��
#define DAMAGE			(1)										//�_���[�W��
#define CANNON			(5)										//��C�̃_���[�W��
#define SKYCANNON		(1)										//�΋�C�̃_���[�W��
#define TORPEDO			(50)									//�����̃_���[�W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CBullet::CBullet() : CScene3D(3, CScene::OBJTYPE_BULLET)//�D��D�ʃC�j�V�����C�Y
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_nBulletType = 0;
	m_nDamage = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// ����������

//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene3D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//m_pos����
	D3DXVECTOR3 Bulletpos = CScene3D::GetPosition();

	//�ړ��ʂ̑��
	Bulletpos += m_move;

	//�ړ��l�̃Z�b�g
	CScene3D::SetMove(m_move);
	//�ʒu�̃Z�b�g
	CScene3D::SetPosition(Bulletpos);

	//�ǂƂ̂����蔻��
	if (Bulletpos.z >= 300 || Bulletpos.z <= -300 || Bulletpos.x >= 300 || Bulletpos.x <= -300)
	{
		//�e�̏I������
		CBullet::Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene3D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size, int type)
{
	CBullet *pBullet = NULL;

	//NULL�`�F�b�N
	if (pBullet == NULL)
	{//�������̓��I�m��

		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pBullet->Init();
			//�e�N�X�`�������蓖�Ă�
			pBullet->BindTexture(m_pTexture[type]);
			//��ނ����蓖�Ă�
			pBullet->m_nType = type;
			//�ړ��ʂ̊��蓖��
			pBullet->m_move = move;
			//�e�̈ʒu�ƃT�C�Y���w��
			pBullet->SetPosSize(pos,size);
		}
	}
	return pBullet;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_1,&m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CBullet::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}