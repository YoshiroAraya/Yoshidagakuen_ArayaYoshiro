//=============================================================================
//
// �Z���N�g���No���� [Select_No.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "Select_NO.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PAUSE_TEXTUER	"data/TEXTURE/no.png"		//�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X		(680)					    //�|�[�Y�����iNO�j����X
#define PAUSE_POS_Y		(350)					    //�|�[�Y�����iNO�j����Y
#define PAUSE_WIDTH		(920)					    //�|�[�Y�����iNO�j�̕�
#define PAUSE_HEIGHT	(500)					    //�|�[�Y�����iNO�j����

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9			g_pTextureSelectNO = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSelectNO = NULL;
NOSTATE						g_NoState;

//=============================================================================
// ����������[InitPolygon]
//=============================================================================
void InitSelectNo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_NoState = NOSTATE_NOSELECT;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTextureSelectNO);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectNO, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelectNO->Lock(0, 0, (void**)&pVtx, 0);

	//�Z���N�g���No�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�Z���N�g���No�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

	//�Z���N�g���No�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSelectNO->Unlock();
}

//=============================================================================
//�I������ [UninitPolygon]
//=============================================================================
void UninitSelectNo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSelectNO != NULL)
	{
		g_pTextureSelectNO->Release();
		g_pTextureSelectNO = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelectNO != NULL)
	{
		g_pVtxBuffSelectNO->Release();
		g_pVtxBuffSelectNO = NULL;
	}
}

//=============================================================================
// �X�V����[UpdataPolygon]
//=============================================================================
void UpdateSelectNo(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

   //���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelectNO->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_NoState)
	{
	case NOSTATE_SELECT:
		//�Z���N�g���No�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		break;

	case NOSTATE_NOSELECT:
		//�Z���N�g���No�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		break;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSelectNO->Unlock();
}

//=============================================================================
// �`�ʏ���[DrawPolygon]
//=============================================================================
void DrawSelectNo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelectNO, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSelectNO);

	//�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// QUIT�ݒ菈��[DrawPolygon]
//=============================================================================
void SetSelectNo(NOSTATE state)
{
	g_NoState = state;
}
