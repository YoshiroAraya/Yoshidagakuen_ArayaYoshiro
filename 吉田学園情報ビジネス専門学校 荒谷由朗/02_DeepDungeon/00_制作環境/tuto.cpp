//=============================================================================
//
// ����ʏ��� [Tuto.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "main.h"
#include "tuto.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "bg.h"
#include "sound.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TYPE_TUTO (3)
#define MAX_TUTO (3)

#define TUTO_TEXTURENAME	"DATA/TEXTURE/tuto.png"	//�^�C�g���̃e�N�X�`����
#define TUTO_TEXTURENAME_2	"DATA/TEXTURE/page.png"	//�^�C�g���̃e�N�X�`����
#define TUTO_TEXTURENAME_3	"DATA/TEXTURE/start2.png"	//�^�C�g���̃e�N�X�`����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTuto[MAX_TYPE_TUTO] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTuto = NULL;	//���_�o�b�t�@�ւ̃|�C���^

TUTO g_aTuto[MAX_TUTO];

//int 	g_nSelectPase;
int nAnimation_X;
int nReturnCount;

int g_nCntTutoPase;
JoyState g_JoyStateTuto;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitTuto(void)
{
	



	g_nCntTutoPase = 0;

	LPDIRECT3DDEVICE9 pDevice;


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntTuto = 0; nCntTuto < MAX_TUTO; nCntTuto++)
	{
		//g_aTuto[nCntTuto].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2, 0.0f);
		g_aTuto[nCntTuto].state = TUTOSTATE_NONE;
		g_aTuto[nCntTuto].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTuto[nCntTuto].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	nAnimation_X = 0;
	nReturnCount = 0;

	g_aTuto[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aTuto[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT/2 -120, 0.0f);
	g_aTuto[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 120, 0.0f);



	g_aTuto[0].bUse = true;
	g_aTuto[1].bUse = true;
	g_aTuto[2].bUse = false;

	/*g_nSelectPase = PASE_ONE;*/



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTO_TEXTURENAME, &g_pTextureTuto[0]);
	D3DXCreateTextureFromFile(pDevice, TUTO_TEXTURENAME_2, &g_pTextureTuto[1]);
	D3DXCreateTextureFromFile(pDevice, TUTO_TEXTURENAME_3, &g_pTextureTuto[2]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTuto,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTuto->Lock(0, 0, (void**)&pVtx, 0);


	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTuto[0].pos.x - SCREEN_WIDTH / 2, g_aTuto[0].pos.y - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTuto[0].pos.x + SCREEN_WIDTH / 2, g_aTuto[0].pos.y - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTuto[0].pos.x - SCREEN_WIDTH / 2, g_aTuto[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTuto[0].pos.x + SCREEN_WIDTH / 2, g_aTuto[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);


	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	pVtx += 4;

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTuto[1].pos.x - 300, g_aTuto[1].pos.y - 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTuto[1].pos.x + 300, g_aTuto[1].pos.y - 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTuto[1].pos.x - 300, g_aTuto[1].pos.y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTuto[1].pos.x + 300, g_aTuto[1].pos.y + 50, 0.0f);


	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;


	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTuto[2].pos.x - 300, g_aTuto[2].pos.y - 70, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTuto[2].pos.x + 300, g_aTuto[2].pos.y - 70, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTuto[2].pos.x - 300, g_aTuto[2].pos.y + 70, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTuto[2].pos.x + 300, g_aTuto[2].pos.y + 70, 0.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTuto->Unlock();

	//�Q�[���p�b�h�̏��
	g_JoyStateTuto.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTuto(void)
{

	for (int nCntTuto = 0; nCntTuto < MAX_TYPE_TUTO; nCntTuto++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTuto[nCntTuto] != NULL)
		{
			g_pTextureTuto[nCntTuto]->Release();
			g_pTextureTuto[nCntTuto] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTuto != NULL)
	{
		g_pVtxBuffTuto->Release();
		g_pVtxBuffTuto = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTuto(void)
{

	//�Q�[���p�b�h��Ԏ擾
	JoyState pJoyState = GetJoystate();
	//���
	XINPUT_STATE state;
	XInputGetState(0, &state);
	FADE pFade;
	pFade = GetFade();

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	

	g_nCntTutoPase++;

	if (g_nCntTutoPase % 900 == 0)
	{
		nAnimation_X = (nAnimation_X + 1);
	}

	if (GetKeyboardTrigger(DIK_D) == true || GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_RIGHTARROW) == true
		|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_DPAD_RIGHT && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStateTuto.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			//g_nSelectPase = (g_nSelectPase + (PASE_MAX - 1)) % PASE_MAX;//�I����Ԃ���グ��
			PlaySound(SOUND_LABEL_SE_MEKURI);
			nAnimation_X = (nAnimation_X + 1);
			if (nAnimation_X > 3)
			{
				nAnimation_X = 3;
			}
		}
			g_JoyStateTuto.nJoypadState = INPUT_JOYSTATE_PUSH;

	}


	if (GetKeyboardTrigger(DIK_A) == true || GetKeyboardTrigger(DIK_LEFTARROW) == true
		|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_DPAD_LEFT && pJoyState.bConnectionJoypad == true))
	{

		if (g_JoyStateTuto.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{


			PlaySound(SOUND_LABEL_SE_MEKURI);

			nAnimation_X = (nAnimation_X - 1);
			if (nAnimation_X < 0)
			{
				nAnimation_X = 0;
			}
		}
		g_JoyStateTuto.nJoypadState = INPUT_JOYSTATE_PUSH;
	}





	/*	if (g_nSelectPase == PASE_FIVE)
	{
	g_aTuto[0].bUse = true;
	g_aTuto[1].bUse = false;
	g_aTuto[2].bUse = true;
	}
	if (g_nSelectPase != PASE_FIVE)
	{
	g_aTuto[0].bUse = true;
	g_aTuto[1].bUse = true;
	g_aTuto[2].bUse = false;
	}*/

	if (nAnimation_X == 3)
	{
		g_aTuto[0].bUse = true;
		g_aTuto[1].bUse = false;
		g_aTuto[2].bUse = true;
	}
	if (nAnimation_X != 3)
	{
		g_aTuto[0].bUse = true;
		g_aTuto[1].bUse = true;
		g_aTuto[2].bUse = false;
	}





	if (nAnimation_X == 3)
	{
		if (pFade == FADE_NONE)
		{

			if (GetKeyboardTrigger(DIK_SPACE) == true
				|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true))
			{
				if (g_JoyStateTuto.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
				{

				PlaySound(SOUND_LABEL_SE_DECISION);

				//���[�h�I��
				//SetMode(MODE_TUTO);
				SetFade(MODE_GAME);
				}
				g_JoyStateTuto.nJoypadState = INPUT_JOYSTATE_PUSH;
			}
		}
	}



	if (g_JoyStateTuto.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateTuto.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateTuto.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateTuto.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}





	if (g_aTuto[1].bUse == true)
	{
		switch (g_aTuto[1].state)
		{
		case TUTOSTATE_NONE:
			g_aTuto[1].col.a -= 0.02f;
			if (g_aTuto[1].col.a <= 0.0f)
			{
				g_aTuto[1].col.a = 0.0f;
				g_aTuto[1].state = TUTOSTATE_USE;
			}
			break;

		case TUTOSTATE_USE:
			g_aTuto[1].col.a += 0.02f;
			if (g_aTuto[1].col.a >= 1.0f)
			{
				g_aTuto[1].col.a = 1.0f;
				g_aTuto[1].state = TUTOSTATE_NONE;
			}
			break;
		}
	}


	if (g_aTuto[2].bUse == true)
	{
		switch (g_aTuto[2].state)
		{
		case TUTOSTATE_NONE:
			g_aTuto[2].col.a -= 0.01f;
			if (g_aTuto[2].col.a <= 0.0f)
			{
				g_aTuto[2].col.a = 0.0f;
				g_aTuto[2].state = TUTOSTATE_USE;
			}
			break;

		case TUTOSTATE_USE:
			g_aTuto[2].col.a += 0.01f;
			if (g_aTuto[2].col.a >= 1.0f)
			{
				g_aTuto[2].col.a = 1.0f;
				g_aTuto[2].state = TUTOSTATE_NONE;
			}
			break;
		}
	}


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTuto->Lock(0, 0, (void**)&pVtx, 0);

	

	if (nAnimation_X < 4)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f * nAnimation_X, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f* (nAnimation_X + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f* nAnimation_X, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f* (nAnimation_X + 1), 1.0f);
	}

	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aTuto[1].col;
	pVtx[1].col = g_aTuto[1].col;
	pVtx[2].col = g_aTuto[1].col;
	pVtx[3].col = g_aTuto[1].col;


	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aTuto[2].col;
	pVtx[1].col = g_aTuto[2].col;
	pVtx[2].col = g_aTuto[2].col;
	pVtx[3].col = g_aTuto[2].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTuto->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTuto(void)
{
	


	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^



								//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTuto, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTuto = 0; nCntTuto < MAX_TYPE_TUTO; nCntTuto++)
	{
		if (g_aTuto[nCntTuto].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTuto[nCntTuto]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTuto * 4, 2);

		}
	}
}
