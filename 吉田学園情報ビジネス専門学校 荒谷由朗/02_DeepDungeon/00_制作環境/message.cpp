//===========================================================================
//
// ���b�Z�[�W���� [Message.cpp]
// Author : TEAM_Fascinator
//
//===========================================================================
#include "main.h"
#include "message.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "sound.h"

//===========================================================================
// �}�N����`
//===========================================================================
#define MAX_TYPE (5)
#define MESSAGE_TEXTURE_NAME0		"data/TEXTURE/message01.png"	// �e�N�X�`��
#define MESSAGE_TEXTURE_NAME1		"data/TEXTURE/message02.png"	// �e�N�X�`��
#define MESSAGE_TEXTURE_NAME2		"data/TEXTURE/message03.png"	// �e�N�X�`��

#define MESSAGE_SIZE_X				(200.0f)						// ����X���W
#define MESSAGE_SIZE_Y				(50.0f)						// ����Y���W
#define MESSAGE_WIDTH				(SCREEN_WIDTH)				// ��
#define MESSAGE_HEIGHT			(SCREEN_HEIGHT)				// ����
#define MESSAGE_TEXTURE_UV_U		(1.0f)						// �A�j���[�V����U�͈�
#define MESSAGE_TEXTURE_UV_V		(1.0f)						// �A�j���[�V����V�͈�
#define MESSAGE_SPEED				(0.003f)					// �X�s�[�h

//===========================================================================
// �O���[�o���ϐ�
//===========================================================================
LPDIRECT3DTEXTURE9 g_pTextureMessage[MAX_TYPE] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMessage = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
JoyState	g_JoyStateMessage;							// �W���C�p�b�h�̏��
MESSAGE g_Message[MAX_TYPE];
//===========================================================================
// ����������
//===========================================================================
void InitMessage(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntMeaage = 0; nCntMeaage < MAX_TYPE; nCntMeaage++)
	{
		g_Message[nCntMeaage].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f);	// ���S�l
		g_Message[nCntMeaage].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_Message[nCntMeaage].type = MESSAGETYPE_APPER;
		g_Message[nCntMeaage].bUse = false;
	}


	g_JoyStateMessage.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESSAGE_TEXTURE_NAME0, &g_pTextureMessage[0]);
	D3DXCreateTextureFromFile(pDevice, MESSAGE_TEXTURE_NAME1, &g_pTextureMessage[1]);
	D3DXCreateTextureFromFile(pDevice, MESSAGE_TEXTURE_NAME2, &g_pTextureMessage[2]);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMessage,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	for (int nCntMeaage = 0; nCntMeaage < MAX_TYPE; nCntMeaage++)
	{
		// ���_�o�b�t�@�����b�N
		g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(-MESSAGE_SIZE_X, -MESSAGE_SIZE_Y, 0.0f) + g_Message[0].pos;
		pVtx[1].pos = D3DXVECTOR3(MESSAGE_SIZE_X, -MESSAGE_SIZE_Y, 0.0f) + g_Message[0].pos;
		pVtx[2].pos = D3DXVECTOR3(-MESSAGE_SIZE_X, MESSAGE_SIZE_Y, 0.0f) + g_Message[0].pos;
		pVtx[3].pos = D3DXVECTOR3(MESSAGE_SIZE_X, MESSAGE_SIZE_Y, 0.0f) + g_Message[0].pos;

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�ݒ�
		pVtx[0].col = g_Message[0].Col;
		pVtx[1].col = g_Message[0].Col;
		pVtx[2].col = g_Message[0].Col;
		pVtx[3].col = g_Message[0].Col;

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(MESSAGE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, MESSAGE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(MESSAGE_TEXTURE_UV_U, MESSAGE_TEXTURE_UV_V);

		pVtx += 4;
		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffMessage->Unlock();
	}
}

//===========================================================================
// �I������
//===========================================================================
void UninitMessage(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TYPE; nCntTex++)
	{
		// �e�N�X�`���j��
		if (g_pTextureMessage[nCntTex] != NULL)
		{
			g_pTextureMessage[nCntTex]->Release();
			g_pTextureMessage[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�j��
	if (g_pVtxBuffMessage != NULL)
	{
		g_pVtxBuffMessage->Release();
		g_pVtxBuffMessage = NULL;
	}
}

//===========================================================================
// �X�V����
//===========================================================================
void UpdateMessage(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	for (int nCntMessage = 0; nCntMessage < 2; nCntMessage++)
	{
		if (g_Message[nCntMessage].bUse == true)
		{
			

			switch (g_Message[nCntMessage].type)
			{
			case MESSAGETYPE_APPER:
				g_Message[nCntMessage].Col.a += 0.05f;
				if (g_Message[nCntMessage].Col.a >= 1.0f)
				{
					g_Message[nCntMessage].Col.a = 1.0f;
					g_Message[nCntMessage].type = MESSAGETYPE_NORMAL;
				}

				
			case MESSAGETYPE_NORMAL:

				break;
			}
		}
	}
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntMessage = 0; nCntMessage < 2; nCntMessage++)
	{
		// ���_�J���[�ݒ�
		pVtx[0].col = g_Message[nCntMessage].Col;
		pVtx[1].col = g_Message[nCntMessage].Col;
		pVtx[2].col = g_Message[nCntMessage].Col;
		pVtx[3].col = g_Message[nCntMessage].Col;

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMessage->Unlock();

}

//===========================================================================
// �`�揈��
//===========================================================================
void DrawMessage(void)
{
	for (int nCntMessage = 0; nCntMessage < MAX_TYPE; nCntMessage++)
	{

		if (g_Message[nCntMessage].bUse == true)
		{

			LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�擾

														// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMessage, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_2D);

			

			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureMessage[g_Message[nCntMessage].nType]);

			// �`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMessage * 4, 2);
		}
	}
}

void DeleteMessage(void)
{
	for (int nCntMessage = 0; nCntMessage < 2; nCntMessage++)
	{
		if (g_Message[nCntMessage].bUse == true)
		{
			g_Message[nCntMessage].Col.a -= 0.05f;
			if (g_Message[nCntMessage].Col.a <= 0.0f)
			{
				g_Message[nCntMessage].Col.a = 0.0f;
				g_Message[nCntMessage].bUse = false;
			}
		}
	}
}

MESSAGE *GetMessageBox(void)
{
	return &g_Message[0];
}

void SetMessageBox(D3DXVECTOR3 pos, int ntype)
{
	int nCntMessage;
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMessage = 0; nCntMessage < MAX_TYPE; nCntMessage++)
	{
		if (g_Message[nCntMessage].bUse == false)	
		{
			g_Message[nCntMessage].pos = pos;

			g_Message[nCntMessage].type = MESSAGETYPE_APPER;


			g_Message[nCntMessage].nType = ntype;
			

			g_Message[nCntMessage].bUse = true;	//�g�p���Ă����Ԃɂ���

			break;
		}
		pVtx += 4;


	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMessage->Unlock();
}
