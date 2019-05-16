//=============================================================================
//
// �Z���N�g���Yes���� [Select_Yes.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "Select_YES.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PAUSECONRINUE_TEXTUER	"data/TEXTURE/yes.png"		//�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X				(320)						//�|�[�Y�����iYES�j����X
#define PAUSE_POS_Y				(350)						//�|�[�Y�����iYES�j����Y
#define PAUSE_WIDTH				(540)						//�|�[�Y�����iYES�j�̕�
#define PAUSE_HEIGHT			(500)						//�|�[�Y�����iYES�j����

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9			g_pTextureSelectYes = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSelectYes = NULL;
YESSTATE					g_YesState;

//=============================================================================
// ����������[InitPolygon]
//=============================================================================
void InitSelectYes(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
	
	g_YesState = YESSTATE_SELECT;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSECONRINUE_TEXTUER, &g_pTextureSelectYes);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectYes, 
		NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelectYes->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	//Yes���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y , 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y , 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSelectYes->Unlock();
}

//=============================================================================
//�I������ [UninitPolygon]
//=============================================================================
void UninitSelectYes(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSelectYes != NULL)
	{
		g_pTextureSelectYes->Release();
		g_pTextureSelectYes = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelectYes != NULL)
	{
		g_pVtxBuffSelectYes->Release();
		g_pVtxBuffSelectYes = NULL;
	}
}

//=============================================================================
// �X�V����[UpdataPolygon]
//=============================================================================
void UpdateSelectYes(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelectYes->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_YesState)
	{
	case YESSTATE_SELECT:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		break;
	case YESSTATE_NOSELECT:
		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
		break;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSelectYes->Unlock();
}

//=============================================================================
// �`�ʏ���[DrawPolygon]
//=============================================================================
void DrawSelectYes(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelectYes, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSelectYes);

	//�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// QUIT�ݒ菈��[DrawPolygon]
//=============================================================================
void SetSelectYes(YESSTATE state)
{
	g_YesState = state;
}
