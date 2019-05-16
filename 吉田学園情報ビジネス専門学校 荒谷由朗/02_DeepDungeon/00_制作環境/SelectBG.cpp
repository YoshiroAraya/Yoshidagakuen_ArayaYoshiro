//=============================================================================
//
// �|�[�Y�w�i���� [bg.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "SelectBG.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSE_TEXTUER		"data/TEXTURE/nextstage.png"	//�ǂݍ��ރe�N�X�`��
#define PAUSE_POS_X			(230)					    //�|�[�Y�w�i����X
#define PAUSE_POS_Y			(180)					    //�|�[�Y�w�i����Y
#define PAUSE_WIDTH			(990)					    //�|�[�Y�w�i�̕�
#define PAUSE_HEIGHT		(580)					    //�|�[�Y�w�i����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSelectBG = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffSelectBG = NULL;

//=============================================================================
// �|���S������������[InitPolygon]
//=============================================================================
void InitSelectBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSE_TEXTUER, &g_pTextureSelectBG);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectBG, NULL);

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelectBG->Lock(0, 0, (void**)&pVtx, 0);

	//----------�}�X�N-----------
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	 //rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|�[�Y�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);//��ڂ̒��_�̐F�w��i�E���j

	//�|�[�Y�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�w�i--------------------------------
	//�|�[�Y�w�i�̍��W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��
	pVtx[5].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[6].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
	pVtx[7].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�|�[�Y�w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�l�ڂ̒��_�̐F�w��i�E���j

	//�|�[�Y�w�i�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffSelectBG->Unlock();
}

//=============================================================================
//�|���S���I������ [UninitPolygon]
//=============================================================================
void UninitSelectBG(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSelectBG != NULL)
	{
		g_pTextureSelectBG->Release();
		g_pTextureSelectBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelectBG != NULL)
	{
		g_pVtxBuffSelectBG->Release();
		g_pVtxBuffSelectBG = NULL;
	}

}

//=============================================================================
// �|���S���X�V����[UpdataPolygon]
//=============================================================================
void UpdateSelectBG(void)
{

}

//=============================================================================
// �|���S���`�ʏ���[DrawPolygon]
//=============================================================================
void DrawSelectBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾����

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelectBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectBG);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}