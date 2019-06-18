//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "score.h"
#include "fade.h"
#include "explosion.h"
#include "player.h"
#include "soul.h"
#include "item.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		CEnemy::m_pTexture[MAX_ENEMYTEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() :CScene2D(3)
{
	m_fWidth	= NULL;
	m_fHeight	= NULL;
	m_life		= 10;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ��������
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, float width, float height, int texID)
{
	CEnemy *pEnemy = NULL;

	pEnemy = new CEnemy;
	pEnemy->Init(pos, width, height, texID);
	pEnemy->BindTexture(m_pTexture[texID]);

	return pEnemy;
}

//=============================================================================
//�@���[�h
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X�̎擾
	CRenderer			*pRenderer	= CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice		= pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME00, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURENAME01, &m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CEnemy::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntEnemyTex = 0; nCntEnemyTex < MAX_ENEMYTEX; nCntEnemyTex++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCntEnemyTex]->Release();
			m_pTexture[nCntEnemyTex] = NULL;
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float width, float height, int texID)
{
	srand((unsigned int)time(0));	// �����_���֐�

	// �e�f�[�^�̑��
	m_pos		= pos;
	m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fWidth	= width;
	m_fHeight	= height;
	m_TypeNum	= texID;
	m_life		= (rand() % 10 + 2);
	m_Statse	= ENEMYSTATSE_NONE;
	m_nBlink	= false;

	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_ENEMY);				// �I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene2D::SetPosition(pos, width, height);		// ���W�̐ݒ�
	CScene2D::SetTexture(m_nPatternAnim, 1, 1);		// �e�N�X�`�����W�̐ݒ�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = CScene2D::GetVtxBuff();	// �o�[�e�b�N�X�o�b�t�@�̎擾
	CFade::FADE				fade	= CFade::GetFade();			// �t�F�[�h�̎擾
	D3DXVECTOR3				pos		= CScene2D::GetPosition();	// ���W�̎擾

	// �J�E���^�[�̉��Z
	m_nCount++;
	m_nCounterAnim++;

	if ((m_nCount % (rand() % 180 + 50)) == 0)
	{// �U���p�x
		CPlayer *pPlayer = CManager::GetPlayer();	// �v���C���[�̎擾
		if (pPlayer != NULL)
		{
			CPlayer::PLAYER_STATUSTYPE playerstatus = pPlayer->GetStatusType();		// �v���C���[��Ԃ̎擾

			if (playerstatus != CPlayer::PLAYER_STATUSTYPE_DEAD)
			{// �v���C���[������ł��Ȃ�������
				CBullet::Create(pos + D3DXVECTOR3(-70.0f, 0.0f, 0.0f), 50, 40, CBullet::BULLETTYPE_ENEMY);
			}
		}
	}

	if (m_TypeNum == 1)
	{
		if (m_bRoundtrip == false)
		{
			if (pos.y < SCREEN_HEIGHT)
			{
				m_move.y += MAX_ENEMYSPEED;
			}
			if ((m_nCount % 80) == 0)
			{
				m_bRoundtrip = true;
			}
		}
		else if (m_bRoundtrip == true)
		{
			if (pos.y > 0)
			{
				m_move.y -= MAX_ENEMYSPEED;
			}
			if ((m_nCount % 80) == 0)
			{
				m_bRoundtrip = false;
			}
		}

		//����
		m_move.y += (0.0f - m_move.y) * 0.25f;

		//�ʒu�X�V
		pos.y += m_move.y;

		CScene2D::SetPosition(pos, m_fWidth, m_fHeight);
	}

	m_move.x -= MAX_ENEMYSPEED;

	//����
	m_move.x += (0.0f - m_move.x) * 0.25f;

	//�ʒu�X�V
	pos.x += m_move.x;

	CScene2D::SetPosition(pos, m_fWidth, m_fHeight);

	if (m_Statse == ENEMYSTATSE_DAMEGE)
	{// �_���[�W���
		if (m_nBlink == false)
		{//	�J���[��Ԃ�
			m_col		= D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f);
			m_nBlink	= true;
		}
		else if (m_nBlink == true)
		{//	�J���[��߂�
			if (m_nCntBlink > 5)
			{
				m_col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_nCntBlink = 0;
				m_nBlink	= false;
				m_Statse	= ENEMYSTATSE_NONE;
			}
		}
		CScene2D::SetCol(m_col);
		m_nCntBlink++;
	}

	if (m_life <= 0)
	{
		Uninit();
		CScore::AddScore(1);				// �X�R�A�̉��Z
		CSoul::Create(pos, 40.0f, 30.0f);	// �\�E���̐���
		if (rand() % 5 == 0)
		{
			CItem::Create(pos, 30, 30, rand() % 4);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �_���[�W����
//=============================================================================
void CEnemy::HitEnemy(int nDamage, CBullet::BULLETTYPE bullettype)
{
	m_life -= nDamage;		// ���C�t�̌��Z

	if (m_life <= 0)
	{// ����
		if (bullettype != CBullet::BULLETTYPE_ENEMY)
		{
			D3DXVECTOR3 pos = CScene2D::GetPosition();		// ���W�̎擾
			switch (bullettype)
			{// �^�C�v���Ƃɐ���
			case CBullet::BULLETTYPE_SLASH:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_SLASH);
				break;
			case CBullet::BULLETTYPE_POISON:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_POISON);
				break;
			case CBullet::BULLETTYPE_FLAME:
				CExplosion::Create(pos, 30, 80, CExplosion::EXPLOSIONTYPE_FLAME);
				break;
			case CBullet::BULLETTYPE_WIND:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_WIND);
				break;
			case CBullet::BULLETTYPE_ENEMY:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_ENEMY);
				break;
			case CBullet::BULLETTYPE_MP_HOMING:
				CExplosion::Create(pos, 50, 50, CExplosion::EXPLOSIONTYPE_ENEMY);
				break;
			}
			// �T�E���h�̍Đ�
			CSound *pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SELECT000);
			return;		// ���P�񂾂��ʂ�
		}
	}
	else
	{
		m_Statse = ENEMYSTATSE_DAMEGE;		// ��Ԃ̍X�V
		// �T�E���h�̍Đ�
		CSound *pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_ENEMY_DAMEGE);
	}
}