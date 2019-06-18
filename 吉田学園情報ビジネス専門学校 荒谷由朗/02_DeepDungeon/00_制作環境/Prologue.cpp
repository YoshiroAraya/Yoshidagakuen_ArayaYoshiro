//=============================================================================
//
// ����ʏ��� [Tuto.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "main.h"
#include "prologue.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "bg.h"
#include "inputx.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TYPE_PROLOGUE (3)
#define MAX_PROLOGUE (3)

#define PROLOGUE_TEXTURENAME	"DATA/TEXTURE/prologue.png"	//�^�C�g���̃e�N�X�`����
#define PROLOGUE_TEXTURENAME_2	"DATA/TEXTURE/page.png"	//�^�C�g���̃e�N�X�`����
#define PROLOGUE_TEXTURENAME_3	"DATA/TEXTURE/start.png"	//�^�C�g���̃e�N�X�`����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePrologue[MAX_TYPE_PROLOGUE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPrologue = NULL;	//���_�o�b�t�@�ւ̃|�C���^

PROLOGUE g_aPrologue[MAX_PROLOGUE];

//int 	g_nSelectPase;
int nPrologueAnimation_X;
int nPrologueReturnCount;

int g_nCntProloguePage;

JoyState g_JoyStatePrologue;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitPrologue(void)
{
	g_nCntProloguePage = 0;

	LPDIRECT3DDEVICE9 pDevice;


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntPrologue = 0; nCntPrologue < MAX_PROLOGUE; nCntPrologue++)
	{
		g_aPrologue[nCntPrologue].state = PROLOGUESTATE_NONE;
		g_aPrologue[nCntPrologue].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPrologue[nCntPrologue].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	nPrologueAnimation_X = 0;
	nPrologueReturnCount = 0;

	g_aPrologue[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aPrologue[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT - 70, 0.0f);
	g_aPrologue[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 330, SCREEN_HEIGHT - 70, 0.0f);



	g_aPrologue[0].bUse = true;
	g_aPrologue[1].bUse = true;
	g_aPrologue[2].bUse = false;

	/*g_nSelectPase = PASE_ONE;*/



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PROLOGUE_TEXTURENAME, &g_pTexturePrologue[0]);
	D3DXCreateTextureFromFile(pDevice, PROLOGUE_TEXTURENAME_2, &g_pTexturePrologue[1]);
	D3DXCreateTextureFromFile(pDevice, PROLOGUE_TEXTURENAME_3, &g_pTexturePrologue[2]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PROLOGUE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPrologue,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPrologue->Lock(0, 0, (void**)&pVtx, 0);


	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aPrologue[0].pos.x - (SCREEN_WIDTH / 2 ), g_aPrologue[0].pos.y - (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPrologue[0].pos.x + (SCREEN_WIDTH / 2 ), g_aPrologue[0].pos.y - (SCREEN_HEIGHT / 2 ), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPrologue[0].pos.x - (SCREEN_WIDTH / 2), g_aPrologue[0].pos.y + (SCREEN_HEIGHT / 2 ), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPrologue[0].pos.x + (SCREEN_WIDTH / 2), g_aPrologue[0].pos.y + (SCREEN_HEIGHT / 2 ), 0.0f);


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
	pVtx[0].pos = D3DXVECTOR3(g_aPrologue[1].pos.x - 300, g_aPrologue[1].pos.y - 50, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPrologue[1].pos.x + 300, g_aPrologue[1].pos.y - 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPrologue[1].pos.x - 300, g_aPrologue[1].pos.y + 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPrologue[1].pos.x + 300, g_aPrologue[1].pos.y + 50, 0.0f);


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
	pVtx[0].pos = D3DXVECTOR3(g_aPrologue[2].pos.x - 300, g_aPrologue[2].pos.y - 70, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPrologue[2].pos.x + 300, g_aPrologue[2].pos.y - 70, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPrologue[2].pos.x - 300, g_aPrologue[2].pos.y + 70, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPrologue[2].pos.x + 300, g_aPrologue[2].pos.y + 70, 0.0f);

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
	g_pVtxBuffPrologue->Unlock();

	//�Q�[���p�b�h�̏��
	g_JoyStatePrologue.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitPrologue(void)
{

	for (int nCntPrologue = 0; nCntPrologue < MAX_TYPE_PROLOGUE; nCntPrologue++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePrologue[nCntPrologue] != NULL)
		{
			g_pTexturePrologue[nCntPrologue]->Release();
			g_pTexturePrologue[nCntPrologue] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPrologue != NULL)
	{
		g_pVtxBuffPrologue->Release();
		g_pVtxBuffPrologue = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdatePrologue(void)
{
	//�Q�[���p�b�h��Ԏ擾
	JoyState pJoyState = GetJoystate();
	//���
	XINPUT_STATE state;
	XInputGetState(0, &state);

	FADE pFade;
	pFade = GetFade();

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^





	if (GetKeyboardTrigger(DIK_D) == true || GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_RIGHTARROW) == true
		|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_DPAD_RIGHT && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePrologue.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			//g_nSelectPase = (g_nSelectPase + (PASE_MAX - 1)) % PASE_MAX;//�I����Ԃ���グ��
			PlaySound(SOUND_LABEL_SE_MEKURI);
			nPrologueAnimation_X = (nPrologueAnimation_X + 1);
			if (nPrologueAnimation_X > 3)
			{
				nPrologueAnimation_X = 3;
			}
		}
		g_JoyStatePrologue.nJoypadState = INPUT_JOYSTATE_PUSH;
	}


	if (GetKeyboardTrigger(DIK_A) == true || GetKeyboardTrigger(DIK_LEFTARROW) == true
		|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_DPAD_LEFT && pJoyState.bConnectionJoypad == true))
	{
		if (g_JoyStatePrologue.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{


			//g_nSelectPase = (g_nSelectPase + 1) % PASE_MAX;//�I����Ԃ��������

			PlaySound(SOUND_LABEL_SE_MEKURI);

			nPrologueAnimation_X = (nPrologueAnimation_X - 1);
			if (nPrologueAnimation_X < 0)
			{
				nPrologueAnimation_X = 0;
			}
		}
		g_JoyStatePrologue.nJoypadState = INPUT_JOYSTATE_PUSH;
	}



	if (nPrologueAnimation_X == 3)
	{
		g_aPrologue[0].bUse = true;
		g_aPrologue[1].bUse = false;
		g_aPrologue[2].bUse = true;
	}
	if (nPrologueAnimation_X != 3)
	{
		g_aPrologue[0].bUse = true;
		g_aPrologue[1].bUse = true;
		g_aPrologue[2].bUse = false;
	}





	if (nPrologueAnimation_X == 3)
	{
		if (pFade == FADE_NONE)
		{

			if (GetKeyboardTrigger(DIK_SPACE) == true
				|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true))
			{
				if (g_JoyStatePrologue.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
				{
				PlaySound(SOUND_LABEL_SE_DECISION);

				//���[�h�I��
				//SetMode(MODE_TUTO);
				SetFade(MODE_TITLE);
				}
				g_JoyStatePrologue.nJoypadState = INPUT_JOYSTATE_PUSH;
			}
		}
	}





	if (g_JoyStatePrologue.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStatePrologue.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStatePrologue.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStatePrologue.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}


	if (g_aPrologue[1].bUse == true)
	{
		switch (g_aPrologue[1].state)
		{
		case PROLOGUESTATE_NONE:
			g_aPrologue[1].col.a -= 0.02f;
			if (g_aPrologue[1].col.a <= 0.0f)
			{
				g_aPrologue[1].col.a = 0.0f;
				g_aPrologue[1].state = PROLOGUESTATE_USE;
			}
			break;

		case PROLOGUESTATE_USE:
			g_aPrologue[1].col.a += 0.02f;
			if (g_aPrologue[1].col.a >= 1.0f)
			{
				g_aPrologue[1].col.a = 1.0f;
				g_aPrologue[1].state = PROLOGUESTATE_NONE;
			}
			break;
		}
	}


	if (g_aPrologue[2].bUse == true)
	{
		switch (g_aPrologue[2].state)
		{
		case PROLOGUESTATE_NONE:
			g_aPrologue[2].col.a -= 0.01f;
			if (g_aPrologue[2].col.a <= 0.0f)
			{
				g_aPrologue[2].col.a = 0.0f;
				g_aPrologue[2].state = PROLOGUESTATE_USE;
			}
			break;

		case PROLOGUESTATE_USE:
			g_aPrologue[2].col.a += 0.01f;
			if (g_aPrologue[2].col.a >= 1.0f)
			{
				g_aPrologue[2].col.a = 1.0f;
				g_aPrologue[2].state = PROLOGUESTATE_NONE;
			}
			break;
		}
	}


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPrologue->Lock(0, 0, (void**)&pVtx, 0);



	if (nPrologueAnimation_X < 4)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f * nPrologueAnimation_X, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f* (nPrologueAnimation_X + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f* nPrologueAnimation_X, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f* (nPrologueAnimation_X + 1), 1.0f);
	}

	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aPrologue[1].col;
	pVtx[1].col = g_aPrologue[1].col;
	pVtx[2].col = g_aPrologue[1].col;
	pVtx[3].col = g_aPrologue[1].col;


	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aPrologue[2].col;
	pVtx[1].col = g_aPrologue[2].col;
	pVtx[2].col = g_aPrologue[2].col;
	pVtx[3].col = g_aPrologue[2].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPrologue->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawPrologue(void)
{
	

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPrologue, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPrologue = 0; nCntPrologue < MAX_TYPE_PROLOGUE; nCntPrologue++)
	{
		if (g_aPrologue[nCntPrologue].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePrologue[nCntPrologue]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPrologue * 4, 2);

		}
	}
}
