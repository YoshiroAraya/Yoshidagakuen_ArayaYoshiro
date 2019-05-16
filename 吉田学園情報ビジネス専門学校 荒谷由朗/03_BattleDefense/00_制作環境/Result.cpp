//=============================================================================
//
// ���U���g���� [result.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAME_MAX		(1)										//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAME_WIN		"data/TEXTURE/Battle Defense_CLEAR.png"		//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAME_LOSE		"data/TEXTURE/Battle Defense_OVER.png"		//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAME_RETRY	"data/TEXTURE/pause001.png"				//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAME_QUIT		"data/TEXTURE/pause002.png"				//�ǂݍ��ރe�N�X�`��

#define BG_POS_X			(0)											//���_���W�iX���W�j
#define BG_POS_Y			(0)											//���_���W�iY���W�j
#define BG_POS_WIDTH		(SCREEN_WIDTH)								//DirectX�̕�
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)								//DirectX�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[BG_TEXTURENAME_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
JoyState		g_JoyStateResult;
int								g_nResultNum;					// �I��ԍ�
float							g_fResultCol;					// �I��F

//�^�C�g����ʂ̏���������
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	g_nResultNum = 0;							// �I��ԍ�
	g_fResultCol = 1.0f;						// �I���J���[

	GAMESTATE pGame;

	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	pGame = GetGameStateNow();

	//�e�N�X�`���̓ǂݍ���
	if (pGame == GAMESTATE_CLEAR)
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_WIN, &g_pTextureResult[0]);
		PlaySound(SOUND_LABEL_BGM002);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_LOSE, &g_pTextureResult[0]);
		PlaySound(SOUND_LABEL_BGM003);
	}
	//D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_RETRY, &g_pTextureResult[1]);
	//D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME_QUIT, &g_pTextureResult[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BG_TEXTURENAME_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSelect = 0; nCntSelect < BG_TEXTURENAME_MAX; nCntSelect++)
	{
		if (nCntSelect == 0)
		{	//�w�i
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);			//���_���W(X���W,Y���W)
			pVtx[1].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_Y, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_HEIGHT, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[3].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_HEIGHT, 0.0f);	//���_���W(X���W,Y���W)

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		}
		if (nCntSelect == 1)
		{	//�v���C���[0
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(70.0f, 450.0f, 0.0f);			//���_���W(X���W,Y���W)
			pVtx[1].pos = D3DXVECTOR3(1180.0f, 450.0f, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[2].pos = D3DXVECTOR3(70.0f, 525.0f, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[3].pos = D3DXVECTOR3(1180.0f, 525.0f, 0.0f);	//���_���W(X���W,Y���W)

																			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

															  //�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		}
		else if (nCntSelect == 2)
		{	//�v���C���[1
			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(70.0f, 525.0f, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[1].pos = D3DXVECTOR3(1180.0f, 525.0f, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[2].pos = D3DXVECTOR3(70.0f, 600.0f, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[3].pos = D3DXVECTOR3(1180.0f, 600.0f, 0.0f);		//���_���W(X���W,Y���W)

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);  //�F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffResult->Unlock();
}

//=============================================================================
// �L�����N�^�[�I���̏I������
//=============================================================================
void UninitResult(void)
{
	for (int nCntTex = 0; nCntTex < BG_TEXTURENAME_MAX; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCntTex] != NULL)
		{
			g_pTextureResult[nCntTex]->Release();
			g_pTextureResult[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	StopSound();
}

//=============================================================================
// �L�����N�^�[�I���̍X�V����
//=============================================================================
void UpdateResult(void)
{

	//VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^
	//// ���_�o�b�t�@�����b�N
	//g_pVtxBuffResult->Lock
	//(
	//	0,
	//	0,
	//	(void**)&pVtx,
	//	0
	//);
	//if (GetKeyboardTrigger(DIK_LEFT) == true || GetKeyboardTrigger(DIK_A) == true)
	//{
	//	// ���_�J���[�ݒ�
	//	pVtx[g_nResultNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	//	g_nResultNum = (g_nResultNum + 1) % 2;
	//	g_fResultCol = 1.0f;
	//	//PlaySound(SOUND_LABEL_SE_RESULT);
	//}
	//if (GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_D) == true)
	//{
	//	// ���_�J���[�ݒ�
	//	pVtx[g_nResultNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	//	pVtx[g_nResultNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	//	g_nResultNum = (g_nResultNum + 1) % 2;
	//	g_fResultCol = 1.0f;
	//	//PlaySound(SOUND_LABEL_SE_RESULT);
	//}

	//// ���_�J���[�ݒ�
	//pVtx[g_nResultNum * 4 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);
	//pVtx[g_nResultNum * 4 + 1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);
	//pVtx[g_nResultNum * 4 + 2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);
	//pVtx[g_nResultNum * 4 + 3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fResultCol);

	//// ���_�o�b�t�@���A�����b�N
	//g_pVtxBuffResult->Unlock();

	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	FADE fade;

	fade = GetFade();

	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && pJoyState.bConnectionJoypad == true))
	{
		PlaySound(SOUND_LABEL_SE_SELEKUTO);
		if (fade != FADE_OUT)
		{
			if (g_nResultNum == 1)
			{
				//���[�h
				SetFade(MODE_GAME);
				//PlaySound(SOUND_LABEL_BGM001);
			}
			else if (g_nResultNum == 0)
			{
				//���[�h
				SetFade(MODE_SCOER);
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
}

//=============================================================================
// �L�����N�^�[�I���̕`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSelect = 0; nCntSelect < BG_TEXTURENAME_MAX; nCntSelect++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCntSelect]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSelect * 4, 2);
	}
}