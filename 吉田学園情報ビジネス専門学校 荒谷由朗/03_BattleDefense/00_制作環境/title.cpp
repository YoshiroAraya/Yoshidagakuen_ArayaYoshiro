//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define BG_TEXTURENAME		"data/TEXTURE/Battle Defense_TITOL.png"		//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAME0		"data/TEXTURE/[PLEASE PLESS BUTTON].png"		//�ǂݍ��ރe�N�X�`��
#define BG_POS_X			(0)								//���_���W�iX���W�j
#define BG_POS_Y			(0)								//���_���W�iY���W�j
#define BG_POS_WIDTH		(SCREEN_WIDTH)					//DirectX�̕�
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)					//DirectX�̍���
#define TIME_SPEED (60)		//�^�C���̃X�s�[�h
#define MAX_TITLE_TEXTURE		(2)								// �|�[�Y�e�N�X�`���ő吔

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
JoyState		g_JoyStateTitle;
int						g_nTimeTitle;					// �^�C��
int						nCntTimeTitle;
float					g_TitleColor;					// �I��F

//=============================================================================
//�^�C�g����ʂ̏���������
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �^�C���̏�����
	g_nTimeTitle = 4;

	nCntTimeTitle = 0;

	g_TitleColor = 1.0f;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAME0, &g_pTextureTitle[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < 2; nCntPause++)
	{// �|�[�Y���J�E���g
		if (nCntPause == 0)
		{// BG
		 // ���_�ݒ�
		 //���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);			//���_���W(X���W,Y���W)
			pVtx[1].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_Y, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_POS_HEIGHT, 0.0f);		//���_���W(X���W,Y���W)
			pVtx[3].pos = D3DXVECTOR3(BG_POS_WIDTH, BG_POS_HEIGHT, 0.0f);	//���_���W(X���W,Y���W)

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// �|�[�Y���j���[
		 // ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(400.0f, 600.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1200.0f, 600.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 750.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200.0f, 750.0f, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);		//U�����AV�������@(0.0f�`1.0f�j

		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//�I������
void UninitTitle(void)
{
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}


}

//�X�V����
void UpdateTitle(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^
	FADE fade;

	fade = GetFade();

	nCntTimeTitle++;

	g_pVtxBuffTitle->Lock(0,0,(void**)&pVtx,0);

	if ((nCntTimeTitle % TIME_SPEED) == 0)		//�A�j���[�V�����̑�����ς�����
	{
		AddTimeTitle(-1);
	}

	//����L�[�������ꂽ��
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && pJoyState.bConnectionJoypad == true)
		|| (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && pJoyState.bConnectionJoypad == true))
	{
		PlaySound(SOUND_LABEL_SE_SELEKUTO);
		if (fade != FADE_OUT)
		{
			//���[�h�ݒ�
			SetFade(MODE_TUTORIARU);
		}
	}

	g_TitleColor -= 0.004f;

	if (g_TitleColor < 0.65f)
	{
		g_TitleColor = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);
	pVtx[1 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);
	pVtx[2 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);
	pVtx[3 + 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleColor);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateTitle.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateTitle.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//�`�揈��
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < 2; nCntPause++)
	{// �|�[�Y���J�E���g
			//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntPause]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}

//=============================================================================
// �^�C���̉��Z
//=============================================================================
void AddTimeTitle(int nValue)
{
	//�ϐ��錾
	//int nCntTimeTitle;
	int nTexData;

	//MODE pMode;
	FADE fade;

	fade = GetFade();
	//pMode = GetModeNow();

	g_nTimeTitle += nValue;		//�^�C������
	nTexData = g_nTimeTitle;		//�^�C�����i�[

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//if (g_nTimeTitle >= 0)
	//{
	//	for (nCntTimeTitle = 0; nCntTimeTitle < MAX_TIME; nCntTimeTitle++)
	//	{//�^�C���J�E���g
	//	 //�e�N�X�`���ݒ�
	//		pVtx[nCntTimeTitle * 4].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
	//		pVtx[nCntTimeTitle * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
	//		pVtx[nCntTimeTitle * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
	//		pVtx[nCntTimeTitle * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
	//		nTexData /= 10;
	//	}
	//}
	//�^�C�}�[��0�ȉ��ɂȂ����Ƃ�
	if (g_nTimeTitle <= 0)
	{
		if (fade != FADE_OUT)
		{
			//���[�h�ݒ�
			SetFade(MODE_SCOER);
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}