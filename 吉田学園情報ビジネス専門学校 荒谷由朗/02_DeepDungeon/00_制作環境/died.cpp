//===========================================================================
//
// ���S������ [Died.cpp]
// Author : TEAM_Fascinator
//
//===========================================================================
#include "main.h"
#include "died.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "sound.h"

//===========================================================================
// �}�N����`
//===========================================================================
#define DIED_TEXTURE_NAME		"data/TEXTURE/die.png"	// �e�N�X�`��
#define DIED_SIZE_X				(320.0f)						// ����X���W
#define DIED_SIZE_Y				(140.0f)						// ����Y���W
#define DIED_WIDTH				(SCREEN_WIDTH)				// ��
#define DIED_HEIGHT			(SCREEN_HEIGHT)				// ����
#define DIED_TEXTURE_UV_U		(1.0f)						// �A�j���[�V����U�͈�
#define DIED_TEXTURE_UV_V		(1.0f)						// �A�j���[�V����V�͈�
#define DIED_SPEED				(0.003f)					// �X�s�[�h

//===========================================================================
// �O���[�o���ϐ�
//===========================================================================
LPDIRECT3DTEXTURE9 g_pTextureDied = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDied = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
JoyState	g_JoyStateDied;							// �W���C�p�b�h�̏��
DIED g_Died[2];
//===========================================================================
// ����������
//===========================================================================
void InitDied(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Died[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -100.0f, 0.0f);	// ���S�l
	g_Died[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_Died[0].type = DIEDTYPE_APPER;
	g_Died[0].bUse = false;


	g_Died[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 0.0f);	// ���S�l
	g_Died[1].Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Died[1].type = DIEDTYPE_APPER;
	g_Died[1].bUse = false;

	g_JoyStateDied.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, DIED_TEXTURE_NAME, &g_pTextureDied);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDied,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N
	g_pVtxBuffDied->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(-DIED_SIZE_X, -DIED_SIZE_Y, 0.0f) + g_Died[0].pos;
	pVtx[1].pos = D3DXVECTOR3(DIED_SIZE_X, -DIED_SIZE_Y, 0.0f) + g_Died[0].pos;
	pVtx[2].pos = D3DXVECTOR3(-DIED_SIZE_X, DIED_SIZE_Y, 0.0f) + g_Died[0].pos;
	pVtx[3].pos = D3DXVECTOR3(DIED_SIZE_X, DIED_SIZE_Y, 0.0f) + g_Died[0].pos;

	// 1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�ݒ�
	pVtx[0].col = g_Died[0].Col;
	pVtx[1].col = g_Died[0].Col;
	pVtx[2].col = g_Died[0].Col;
	pVtx[3].col = g_Died[0].Col;

	// �e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(DIED_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, DIED_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(DIED_TEXTURE_UV_U, DIED_TEXTURE_UV_V);

	pVtx += 4;
	
	// ���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 0.0f) + g_Died[1].pos;
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, 0.0f) + g_Died[1].pos;
	pVtx[2].pos = D3DXVECTOR3(-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f) + g_Died[1].pos;
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f) + g_Died[1].pos;

	// 1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�ݒ�
	pVtx[0].col = g_Died[1].Col;
	pVtx[1].col = g_Died[1].Col;
	pVtx[2].col = g_Died[1].Col;
	pVtx[3].col = g_Died[1].Col;

	// �e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(DIED_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, DIED_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(DIED_TEXTURE_UV_U, DIED_TEXTURE_UV_V);
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffDied->Unlock();
}

//===========================================================================
// �I������
//===========================================================================
void UninitDied(void)
{
	// �e�N�X�`���j��
	if (g_pTextureDied != NULL)
	{
		g_pTextureDied->Release();
		g_pTextureDied = NULL;
	}
	// ���_�o�b�t�@�j��
	if (g_pVtxBuffDied != NULL)
	{
		g_pVtxBuffDied->Release();
		g_pVtxBuffDied = NULL;
	}
}

//===========================================================================
// �X�V����
//===========================================================================
void UpdateDied(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	for (int nCntDied = 0; nCntDied < 2; nCntDied++)
	{
		if (g_Died[nCntDied].bUse == true)
		{
			if (g_Died[0].Col.a == 0.01f)
			{
				PlaySound(SOUND_LABEL_SE_DEAD);
			}

			switch (g_Died[nCntDied].type)
			{
			case DIEDTYPE_APPER:
				g_Died[0].Col.a += 0.01f;
				if (g_Died[0].Col.a >= 1.0f)
				{
					g_Died[0].Col.a = 1.0f;
					g_Died[nCntDied].type = DIEDTYPE_NORMAL;
				}

				g_Died[1].Col.a += 0.01f;
				if (g_Died[1].Col.a >= 0.4f)
				{
					g_Died[1].Col.a = 0.4f;

				}
				break;
			case DIEDTYPE_NORMAL:

				break;
			}
		}
	}
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffDied->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntDied = 0; nCntDied < 2; nCntDied++)
	{
		// ���_�J���[�ݒ�
		pVtx[0].col = g_Died[nCntDied].Col;
		pVtx[1].col = g_Died[nCntDied].Col;
		pVtx[2].col = g_Died[nCntDied].Col;
		pVtx[3].col = g_Died[nCntDied].Col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffDied->Unlock();

}

//===========================================================================
// �`�揈��
//===========================================================================
void DrawDied(void)
{
	for (int nCntDied = 0; nCntDied < 2; nCntDied++)
	{

		if (g_Died[nCntDied].bUse == true)
		{

			LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

														// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffDied, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, 0);

			// �`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureDied);

			// �`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

DIED *GetDied(void)
{
	return &g_Died[0];
}