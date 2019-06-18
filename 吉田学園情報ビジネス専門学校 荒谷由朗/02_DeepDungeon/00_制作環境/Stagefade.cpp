//=============================================================================
//
// �t�F�[�h���� [StageFade.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "StageFade.h"
#include "game.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON (2)
#define VTX_POS_X (0)
#define VTX_POS_Y (0)
#define FADE_TEXTUER " "

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexStageFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureStageFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
STAGEFADE				g_StageFade;				// �t�F�[�h���
STAGEMODE				g_modeStageNext;			// ���̃��[�h
D3DXCOLOR				g_colorStageFade;			// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitStageFade(STAGEMODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�l�̏�����
	g_StageFade = STAGEFADE_IN;
	g_modeStageNext = modeNext;
	g_colorStageFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexStageFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitStageFade(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureStageFade != NULL)
	{
		g_pTextureStageFade->Release();
		g_pTextureStageFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffStageFade != NULL)
	{
		g_pVtxBuffStageFade->Release();
		g_pVtxBuffStageFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStageFade(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	PLAYER *pPlayer = GetPlayer();			//�v���C���[���̎擾

	if (g_StageFade != STAGEFADE_NONE)
	{
		if (g_StageFade == STAGEFADE_IN)//�t�F�[�h�C�����
		{
			g_colorStageFade.a -= 0.03f;
			if (g_colorStageFade.a <= 0.0f)
			{
				g_colorStageFade.a = 0.0f;
				g_StageFade = STAGEFADE_NONE;//�������ĂȂ���Ԃ�
				//pPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�v���C���[�̈ʒu���ړ�������

			}
		}
		else if (g_StageFade == STAGEFADE_OUT)//�t�F�[�h�A�E�g���
		{
			g_colorStageFade.a += 0.03f;
			if (g_colorStageFade.a >= 1.0f)
			{
				g_colorStageFade.a = 1.0f;
				g_StageFade = STAGEFADE_IN;//�t�F�[�h�C����Ԃ�

				//���[�h�̐ݒ�
				SetStageMode(g_modeStageNext);
				//pPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�v���C���[�̈ʒu���ړ�������

			}
		}

		//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffStageFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̍X�V
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorStageFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorStageFade.a);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorStageFade.a);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorStageFade.a);//�O�ڂ̒��_�̐F�w��i�E���j
														
		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffStageFade->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStageFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffStageFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStageFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexStageFade(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FADE_TEXTUER, &g_pTextureStageFade);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStageFade,
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStageFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�o�b�t�@�̏���ݒ�
	pVtx[0].pos = D3DXVECTOR3(VTX_POS_X, VTX_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, VTX_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(VTX_POS_X, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�F
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffStageFade->Unlock();
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetStageFade(STAGEMODE modeNext)
{
	g_StageFade = STAGEFADE_OUT;
	g_modeStageNext = modeNext;
	g_colorStageFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
STAGEFADE GetStageFade(void)
{
	return g_StageFade;
}

