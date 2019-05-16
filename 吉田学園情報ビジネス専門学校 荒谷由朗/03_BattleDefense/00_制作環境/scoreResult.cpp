//=============================================================================
//
// �n�C�X�R�A���� [scoreResult.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "main.h"
#include "scoreResult.h"
#include "score.h"
#include "input.h"
#include "inputx.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BG_TEXTURENAME_MAX		(2)										//�ǂݍ��ރe�N�X�`��
#define	TEXTURE_SCORERSULT		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define SCORERSULT_BGTEXTURE		"data/TEXTURE/Battle Defense_SCOER.png"		//�ǂݍ��ރe�N�X�`��
#define MAX_SCORERSULT (8)	//����
#define BG_POS_X			(0)											//���_���W�iX���W�j
#define BG_POS_Y			(0)											//���_���W�iY���W�j
#define BG_POS_WIDTH		(SCREEN_WIDTH)								//DirectX�̕�
#define BG_POS_HEIGHT		(SCREEN_HEIGHT)								//DirectX�̍���
#define TIME_SPEED (60)		//�^�C���̃X�s�[�h

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexScoreResult(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScoreResult[BG_TEXTURENAME_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreResult = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
SCORERESULT				g_ScoreResult;
JoyState		g_JoyStateScoreResult;

//=============================================================================
// ����������
//=============================================================================
void InitScoreResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SCORE g_Score;
	g_Score = GetScore();

	JoyState g_JoyState;
	g_JoyState = GetJoystate();

	g_JoyStateScoreResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	// �X�R�A�̏�����
	g_ScoreResult.nScoreResult = g_Score.nScore;

	// �^�C���̏�����
	g_ScoreResult.nTimeScoreResult = 4;

	g_ScoreResult.nCntTimeScoreResult = 0;


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		SCORERSULT_BGTEXTURE,		// �t�@�C���̖��O
		&g_pTextureScoreResult[1]);	// �e�N�X�`���ւ̃|�C���^
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORERSULT,		// �t�@�C���̖��O
		&g_pTextureScoreResult[0]);	// �e�N�X�`���ւ̃|�C���^

								// ���_���̍쐬
	MakeVertexScoreResult(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScoreResult(void)
{
	for (int nCntTex = 0; nCntTex < BG_TEXTURENAME_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureScoreResult[nCntTex] != NULL)
		{
			g_pTextureScoreResult[nCntTex]->Release();
			g_pTextureScoreResult[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScoreResult != NULL)
	{
		g_pVtxBuffScoreResult->Release();
		g_pVtxBuffScoreResult = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScoreResult(void)
{
	JoyState pJoyState = GetJoystate();
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//�ϐ��錾
	int nTexData;

	FADE fade;
	fade = GetFade();

	g_ScoreResult.nCntTimeScoreResult++;
	if ((g_ScoreResult.nCntTimeScoreResult % TIME_SPEED) == 0)		//�A�j���[�V�����̑�����ς�����
	{
		AddTimeScore(-1);
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
			SetFade(MODE_TITLE);
		}
	}

	nTexData = g_ScoreResult.nScoreResult;	//�X�R�A���i�[

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScoreResult = 1; nCntScoreResult < MAX_SCORERSULT; nCntScoreResult++)
	{//�X�R�A�J�E���g
	 //�e�N�X�`���ݒ�
		pVtx[nCntScoreResult * 4].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
		pVtx[nCntScoreResult * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
		pVtx[nCntScoreResult * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
		pVtx[nCntScoreResult * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
		nTexData /= 10;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScoreResult->Unlock();

	if (g_JoyStateScoreResult.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateScoreResult.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateScoreResult.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateScoreResult.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScoreResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScoreResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScoreResult[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	for (int nCntScoreResult = 1; nCntScoreResult < MAX_SCORERSULT; nCntScoreResult++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScoreResult[0]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScoreResult * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScoreResult(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntScoreResult;
	float fScoreResultPos;				//�X�R�A�ʒu

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORERSULT + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreResult,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i
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

												//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx += 4;				//���_�f�[�^�ւ̃|�C���^��4�i�߂�

	//�X�R�A
	for (nCntScoreResult = 0, fScoreResultPos = 900; nCntScoreResult < MAX_SCORERSULT; nCntScoreResult++, fScoreResultPos -= 100)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(fScoreResultPos, 390.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(fScoreResultPos + 60.0f, 390.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(fScoreResultPos, 590.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(fScoreResultPos + 60.0f, 590.0f, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				//���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffScoreResult->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
//void AddScoreResult(int nValue)
//{
//}
//=============================================================================
// �^�C���̉��Z
//=============================================================================
void AddTimeScore(int nValue)
{
	//�ϐ��錾
	int nTexData;

	FADE fade;

	fade = GetFade();

	g_ScoreResult.nTimeScoreResult += nValue;		//�^�C������
	nTexData = g_ScoreResult.nTimeScoreResult;		//�^�C�����i�[

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�}�[��0�ȉ��ɂȂ����Ƃ�
	if (g_ScoreResult.nTimeScoreResult <= 0)
	{
		if (fade != FADE_OUT)
		{
			//���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffScoreResult->Unlock();
}