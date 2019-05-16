//---------------------------------------------------------------------
// �����L���O���� [ranking.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ranking.h"
#include "manager.h"
#include "scene.h"
#include "fade.h"
#include "time.h"
#include "number.h"
#include "logo.h"
#include "player.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"
#include "wall.h"
#include "ground.h"
#include "billboord.h"
#include "effect.h"
#include "item.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKINGLOGO_TEXTURENAME		"data\\TEXTURE\\Ranking.png"		//�e�N�X�`���̃t�@�C����
#define RANK1_TEXTURENAME			"data\\TEXTURE\\rank1.png"		//�e�N�X�`���̃t�@�C����
#define RANK2_TEXTURENAME			"data\\TEXTURE\\rank2.png"		//�e�N�X�`���̃t�@�C����
#define RANK3_TEXTURENAME			"data\\TEXTURE\\rank3.png"		//�e�N�X�`���̃t�@�C����
#define RANK4_TEXTURENAME			"data\\TEXTURE\\rank4.png"		//�e�N�X�`���̃t�@�C����
#define RANK5_TEXTURENAME			"data\\TEXTURE\\rank5.png"		//�e�N�X�`���̃t�@�C����

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer		*CRanking::m_pPlayer = NULL;
CBillBoord	*CRanking::m_pBillBoord = NULL;
CPolygon3D	*CRanking::m_pPolygon3D = NULL;
CMeshField	*CRanking::m_pMeshField = NULL;
CObject		*CRanking::m_pObject = NULL;
CModel		*CRanking::m_pModel = NULL;
CEffect		*CRanking::m_pEffect = NULL;
CWall		*CRanking::m_pWall = NULL;
CGround		*CRanking::m_pGround = NULL;
CItem		*CRanking::m_pItem = NULL;

//--------------------------------------------
//�����L���O�N���X �R���X�g���N�^
//--------------------------------------------
CRanking::CRanking(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nCntTimer = 0;
	m_nCntCor = 0;
}

//--------------------------------------------
//�����L���O�N���X �f�X�g���N�^
//--------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CRanking *CRanking::Create(void)
{
	//�^�C�g���̃|�C���^
	CRanking *pRanking;
	pRanking = new CRanking;
	//�^�C�g���̏�����
	pRanking->Init();
	//�^�C�g���̏���Ԃ�
	return pRanking;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	//===================================
	//		 Load�̓ǂݍ��ݏꏊ
	//===================================
	CNumber::Load();

	CLogo::Load();

	//�t�F�[�h�̃e�N�X�`���̓ǂݍ���
	CFade::Load();

	//�v���C���[�̃e�N�X�`���̓ǂݍ���
	m_pPlayer->Load();

	//���b�V���t�B�[���h�̃e�N�X�`���̓ǂݍ���
	m_pMeshField->Load();

	//�r���{�[�h�e�N�X�`���̓ǂݍ���
	m_pBillBoord->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//�G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pEffect->Load();

	//�n�ʂ̃e�N�X�`���̓ǂݍ���
	m_pGround->Load();

	//�ǂ̃e�N�X�`���̓ǂݍ���
	m_pWall->Load();

	//�A�C�e���̃e�N�X�`���ǂݍ���
	m_pItem->Load();

	//�e�̃e�N�X�`���ǂݍ���
	m_pShadow->Load();

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		RANKINGLOGO_TEXTURENAME,
		&m_pTexture[0]);
	// ���ʃe�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		RANK1_TEXTURENAME,
		&m_pTextureRank[0]);
	// ���ʃe�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		RANK2_TEXTURENAME,
		&m_pTextureRank[1]);
	// ���ʃe�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		RANK3_TEXTURENAME,
		&m_pTextureRank[2]);
	// ���ʃe�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		RANK4_TEXTURENAME,
		&m_pTextureRank[3]);
	// ���ʃe�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		RANK5_TEXTURENAME,
		&m_pTextureRank[4]);


	//===================================
	//		 ��������ꏊ
	//===================================
	CreateStage();
	CreateObject();
	//���b�V���t�B�[���h��̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-700.0f, -50.0f, 700.0f), 14, 14, 1400.0f, 1400.0f,0.0f,0.0f,0.0f,0.0f, 1, 0);

	//�V�[��2D�̃��S
	m_pScene2DLogo = CScene2D::Create();
	m_pScene2DLogo->BindTexture(m_pTexture[0]);
	m_pScene2DLogo->SetPosSize(D3DXVECTOR3(600, 100, 0), D3DXVECTOR2(200, 50));

	//�����L���O�p�X�R�A
	int aScore[MAX_RANKING] = {};

	//�^�C���e�N�X�`���p�ϐ�
	int nAnswer = 0;
	int nKeisan = 1;

	//�i���o�[�ƃ��S�̐���
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{	//nCnt�Ԃ̃^�C�����擾����
		aScore[nCnt] = *CManager::GetRankingScore(nCnt);
		//�^�C���e�N�X�`���p�ϐ�������
		nAnswer = 0;
		nKeisan = 1;

		for (int nCntNum = 0; nCntNum < TIME_MAX; nCntNum++)
		{	//�^�C������
			m_RankTime[nCnt][nCntNum] = new CNumber;
			m_RankTime[nCnt][nCntNum]->Init(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - (nCntNum * 30.0f), 200.0f + (nCnt * 80.0f), 0));
			//�e�N�X�`���̒l�����߂� 1�̈ʂ���100�̈ʂ܂�
			nAnswer = aScore[nCnt] % (nKeisan * 10) / nKeisan;
			nKeisan *= 10;
			// �e�N�X�`���ɔ��f
			m_RankTime[nCnt][nCntNum]->SetNumber(nAnswer);
		}
		//���ʂ̃��S
		m_pScene2DRank[nCnt] = CScene2D::Create();
		m_pScene2DRank[nCnt]->BindTexture(m_pTextureRank[nCnt]);
		m_pScene2DRank[nCnt]->SetPosSize(D3DXVECTOR3(750.0f, 200.0f + (nCnt * 80), 0), D3DXVECTOR2(30, 30));
	}

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 200.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 280.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 440.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 520.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);


	return S_OK;
}

//=============================================================================
// �����L���O�N���X �I������
//=============================================================================
void CRanking::Uninit(void)
{
	//===================================
	//	�@�@UnLoad�̔j������ꏊ
	//===================================
	CLogo::UnLoad();

	//���b�V���t�B�[���h�e�N�X�`���̔j��
	m_pMeshField->UnLoad();

	//�t�F�[�h�̃e�N�X�`���̔j��
	CFade::UnLoad();

	//�r���{�[�h�e�N�X�`���̔j��
	m_pBillBoord->UnLoad();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->UnLoad();

	//�v���C���[�̃e�N�X�`���̔j��
	m_pPlayer->UnLoad();

	//�G�t�F�N�g�̃e�N�X�`���̔j��
	m_pEffect->UnLoad();

	//�n�ʂ̃e�N�X�`���̔j��
	m_pGround->UnLoad();

	//�ǂ̃e�N�X�`���̔j��
	m_pWall->UnLoad();

	//�e�̃e�N�X�`���ǂݍ���
	m_pShadow->UnLoad();

	//���b�V���t�B�[���h�̔j��
	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	if (m_pObject != NULL)
	{
		m_pObject = NULL;
	}

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTextureRank[nCnt] != NULL)
		{
			m_pTextureRank[nCnt]->Release();
			m_pTextureRank[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCntNum = 0; nCntNum < TIME_MAX; nCntNum++)
		{
			if (m_RankTime[nCnt][nCntNum] != NULL)
			{
				//�i���o�[(�^�C��) �j��  ��CScene�h���ł͂Ȃ���
				m_RankTime[nCnt][nCntNum]->Uninit();
				m_RankTime[nCnt][nCntNum] = NULL;
			}
		}
	}

	//�V�[���h���̎������폜
	CScene::Release();
	CScene::Delete();
	//�t�F�[�h�ȊO�폜
	CScene::NotFadeReleseAll();
}

//=============================================================================
// �����L���O�N���X �X�V����
//=============================================================================
void CRanking::Update(void)
{
	//�L�[�{�[�h�����擾
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound();

	int GameScore = 0;
	int RankingScore = 0;
	//�F�ς��J�E���g
	m_nCntCor++;

	//�؂�ւ�����
	//�t�F�[�h�̃|�C���g
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true || pCInputMouse->GetMouseTrigger(0) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true)
	{//�^�C�g������Q�[����
	 //�t�F�[�h���n�܂�����
		if (pFade == CFade::FADE_NONE)
		{
			//�|�[�Y�̑I���̌��艹
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
			CFade::Create(CManager::MODE_TITLE);
		}
	}
	//�؂�ւ�����(�^�C�}�[)
	m_nCntTimer++;
	if (m_nCntTimer >= 600 && CFade::GetFade() == CFade::FADE_NONE)
	{

		CFade::Create(CManager::MODE_TITLE);
		m_nCntTimer = 0;
	}
}

//=============================================================================
// �����L���O�N���X �`�揈��
//=============================================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{
			m_RankTime[nCnt][nCntTime]->Draw();
		}
	}
}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CRanking::CreateStage(void)
{
	//===================================
	//		 �n�ʂ𐶐�����ꏊ
	//===================================
#if 1
	//���b�V���t�B�[���h�̐��� Create(�ʒu,������X,������Z,�͈�X,�͈�Z,�e�N�X�`���^�C�v,���b�V���̎��)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-750.0f, 0.0f, 500.0f), 4, 4, 1500.0f, 1000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//�ǂ̐���
	m_pWall = CWall::Create(D3DXVECTOR3(750.0f, -200.0f, 0.0f), D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// �E
	m_pWall = CWall::Create(D3DXVECTOR3(-750.0f, -200.0f, 0.0f), D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// ��
	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -200.0f, -500.0f), D3DXVECTOR2(750.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// ��O

	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6);		// �w�i
#endif

																																	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-70.0f, 0.0f, -300.0f));
}
//=============================================================================
// �X�e�[�W�̐������ꊇ�Ǘ�
//=============================================================================
void CRanking::CreateObject(void)
{
#if 1	// ��(��)
	m_pObject = CObject::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), 0.0f, 15, 13, CObject::MOVETYPE_HOUSE, 1);
#endif
#if 1	// ��
	SetTree(D3DXVECTOR3(-470.0f, 0.0f, 150.0f));
	SetTree(D3DXVECTOR3(-450.0f, 0.0f, -100.0f));
	SetTree(D3DXVECTOR3(-410.0f, 0.0f, 320.0f));
	SetTree(D3DXVECTOR3(-370.0f, 0.0f, -20.0f));
	SetTree(D3DXVECTOR3(-350.0f, 0.0f, 200.0f));
	SetTree(D3DXVECTOR3(-290.0f, 0.0f, 400.0f));
	SetTree(D3DXVECTOR3(-130.0f, 0.0f, 270.0f));
	SetTree(D3DXVECTOR3(-10.0f, 0.0f, 400.0f));
	SetTree(D3DXVECTOR3(90.0f, 0.0f, 350.0f));
	SetTree(D3DXVECTOR3(140.0f, 0.0f, 150.0f));
	SetTree(D3DXVECTOR3(160.0f, 0.0f, 450.0f));
	SetTree(D3DXVECTOR3(220.0f, 0.0f, 20.0f));
	SetTree(D3DXVECTOR3(240.0f, 0.0f, 280.0f));
	SetTree(D3DXVECTOR3(270.0f, 0.0f, -180.0f));
	SetTree(D3DXVECTOR3(410.0f, 0.0f, -50.0f));
	SetTree(D3DXVECTOR3(390.0f, 0.0f, 350.0f));
	SetTree(D3DXVECTOR3(380.0f, 0.0f, 100.0f));
#endif
}
//=============================================================================
// �؂̐���
//=============================================================================
void CRanking::SetTree(D3DXVECTOR3 pos)
{
	//�؂̊�
	m_pObject = CObject::Create(pos, 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(pos, 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
}