//=============================================================================
//
// ����ʏ��� [Result.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "bg.h"
#include "sound.h"
#include "inputx.h"
#include "game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TYPE_RESULT (6)
#define MAX_RESULT (3)

#define RESULT_TEXTURENAME0	"DATA/TEXTURE/0true.png"	//�^�C�g���̃e�N�X�`����
#define RESULT_TEXTURENAME1	"DATA/TEXTURE/25.png"	//�^�C�g���̃e�N�X�`����
#define RESULT_TEXTURENAME2	"DATA/TEXTURE/50.png"	//�^�C�g���̃e�N�X�`����
#define RESULT_TEXTURENAME3	"DATA/TEXTURE/75.png"	//�^�C�g���̃e�N�X�`����

//#define RESULT_TEXTURENAME0	"DATA/TEXTURE/tuto.png"	//�^�C�g���̃e�N�X�`����
//#define RESULT_TEXTURENAME1	"DATA/TEXTURE/tuto.png"	//�^�C�g���̃e�N�X�`����
//#define RESULT_TEXTURENAME2	"DATA/TEXTURE/tuto.png"	//�^�C�g���̃e�N�X�`����
//#define RESULT_TEXTURENAME3	"DATA/TEXTURE/tuto.png"	//�^�C�g���̃e�N�X�`����



#define RESULT_TEXTURENAME98	"DATA/TEXTURE/page.png"	//�^�C�g���̃e�N�X�`����
#define RESULT_TEXTURENAME99	"DATA/TEXTURE/start.png"	//�^�C�g���̃e�N�X�`����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TYPE_RESULT] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^

RESULT g_aResult[MAX_RESULT];

//int 	g_nSelectPase;
int nResultAnimation_X;
int nRResulteturnCount;

int g_nCntResultPase;
JoyState g_JoyStateResult;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitResult(void)
{




	g_nCntResultPase = 0;

	LPDIRECT3DDEVICE9 pDevice;


	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++)
	{
		//g_aResult[nCntResult].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2, 0.0f);
		g_aResult[nCntResult].state = RESULTSTATE_NONE;
		g_aResult[nCntResult].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nCntResult].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	nResultAnimation_X = 0;
	nRResulteturnCount = 0;

	g_aResult[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aResult[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 + 350, 0.0f);
	g_aResult[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 + 300, 0.0f);



	g_aResult[0].bUse = true;
	g_aResult[1].bUse = true;
	g_aResult[2].bUse = false;

	/*g_nSelectPase = PASE_ONE;*/



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME0, &g_pTextureResult[0]);//tru
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME1, &g_pTextureResult[1]);//25
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME2, &g_pTextureResult[2]);//50
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME3, &g_pTextureResult[3]);//75

	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME98, &g_pTextureResult[4]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAME99, &g_pTextureResult[5]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);


	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aResult[0].pos.x - SCREEN_WIDTH / 2, g_aResult[0].pos.y - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aResult[0].pos.x + SCREEN_WIDTH / 2, g_aResult[0].pos.y - SCREEN_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aResult[0].pos.x - SCREEN_WIDTH / 2, g_aResult[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aResult[0].pos.x + SCREEN_WIDTH / 2, g_aResult[0].pos.y + SCREEN_HEIGHT / 2, 0.0f);


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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

	pVtx += 4;

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aResult[1].pos.x - 200, g_aResult[1].pos.y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aResult[1].pos.x + 200, g_aResult[1].pos.y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aResult[1].pos.x - 200, g_aResult[1].pos.y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aResult[1].pos.x + 200, g_aResult[1].pos.y + 20, 0.0f);


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
	pVtx[0].pos = D3DXVECTOR3(g_aResult[2].pos.x - 200, g_aResult[2].pos.y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aResult[2].pos.x + 200, g_aResult[2].pos.y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aResult[2].pos.x - 200, g_aResult[2].pos.y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aResult[2].pos.x + 200, g_aResult[2].pos.y + 20, 0.0f);

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
	g_pVtxBuffResult->Unlock();

	//�Q�[���p�b�h�̏��
	g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitResult(void)
{

	for (int nCntResult = 0; nCntResult < MAX_TYPE_RESULT; nCntResult++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateResult(void)
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
		if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{
			//g_nSelectPase = (g_nSelectPase + (PASE_MAX - 1)) % PASE_MAX;//�I����Ԃ���グ��
			PlaySound(SOUND_LABEL_SE_MEKURI);
			nResultAnimation_X = (nResultAnimation_X + 1);
			if (nResultAnimation_X > 3)
			{
				nResultAnimation_X = 3;
			}
		}
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_PUSH;

	}


	if (GetKeyboardTrigger(DIK_A) == true || GetKeyboardTrigger(DIK_LEFTARROW) == true
		|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_DPAD_LEFT && pJoyState.bConnectionJoypad == true))
	{

		if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{


			PlaySound(SOUND_LABEL_SE_MEKURI);

			nResultAnimation_X = (nResultAnimation_X - 1);
			if (nResultAnimation_X < 0)
			{
				nResultAnimation_X = 0;
			}
		}
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_PUSH;
	}


	if (nResultAnimation_X == 3)
	{
		g_aResult[0].bUse = true;
		g_aResult[1].bUse = false;
		g_aResult[2].bUse = true;
	}
	if (nResultAnimation_X != 3)
	{
		g_aResult[0].bUse = true;
		g_aResult[1].bUse = true;
		g_aResult[2].bUse = false;
	}





	if (nResultAnimation_X == 3)
	{
		if (pFade == FADE_NONE)
		{

			if (GetKeyboardTrigger(DIK_SPACE) == true
				|| (state.Gamepad.wButtons &XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true))
			{
				if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
				{

					PlaySound(SOUND_LABEL_SE_DECISION);

					//���[�h�I��
					SetFade(MODE_TITLE);
				}
				g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_PUSH;
			}
		}
	}



	if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateResult.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}





	if (g_aResult[1].bUse == true)
	{
		switch (g_aResult[1].state)
		{
		case RESULTSTATE_NONE:
			g_aResult[1].col.a -= 0.02f;
			if (g_aResult[1].col.a <= 0.0f)
			{
				g_aResult[1].col.a = 0.0f;
				g_aResult[1].state = RESULTSTATE_USE;
			}
			break;

		case RESULTSTATE_USE:
			g_aResult[1].col.a += 0.02f;
			if (g_aResult[1].col.a >= 1.0f)
			{
				g_aResult[1].col.a = 1.0f;
				g_aResult[1].state = RESULTSTATE_NONE;
			}
			break;
		}
	}


	if (g_aResult[2].bUse == true)
	{
		switch (g_aResult[2].state)
		{
		case RESULTSTATE_NONE:
			g_aResult[2].col.a -= 0.01f;
			if (g_aResult[2].col.a <= 0.0f)
			{
				g_aResult[2].col.a = 0.0f;
				g_aResult[2].state = RESULTSTATE_USE;
			}
			break;

		case RESULTSTATE_USE:
			g_aResult[2].col.a += 0.01f;
			if (g_aResult[2].col.a >= 1.0f)
			{
				g_aResult[2].col.a = 1.0f;
				g_aResult[2].state = RESULTSTATE_NONE;
			}
			break;
		}
	}


	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);



	if (nResultAnimation_X < 4)
	{
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.25f * nResultAnimation_X, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f* (nResultAnimation_X + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f* nResultAnimation_X, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f* (nResultAnimation_X + 1), 1.0f);
	}

	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aResult[1].col;
	pVtx[1].col = g_aResult[1].col;
	pVtx[2].col = g_aResult[1].col;
	pVtx[3].col = g_aResult[1].col;


	pVtx += 4;

	//���_�J���[
	pVtx[0].col = g_aResult[2].col;
	pVtx[1].col = g_aResult[2].col;
	pVtx[2].col = g_aResult[2].col;
	pVtx[3].col = g_aResult[2].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawResult(void)
{



	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	GAMESTATE pGame;
	pGame = *GetGameState2();


								//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_aResult[2].bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[5]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);

	}
	if (g_aResult[1].bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[4]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	}
		if (g_aResult[0].bUse == true)
		{
			
			if (pGame == GAMESTATE_CLEAR_TRUE)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureResult[0]);
			}
			else if (pGame == GAMESTATE_CLEAR_25)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureResult[1]);
			}
			else if (pGame == GAMESTATE_CLEAR_50)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureResult[2]);
			}
			else if (pGame == GAMESTATE_CLEAR_75)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureResult[3]);
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
	
}
