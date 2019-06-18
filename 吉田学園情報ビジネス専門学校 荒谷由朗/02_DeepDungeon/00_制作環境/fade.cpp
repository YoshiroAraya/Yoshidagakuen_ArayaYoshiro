//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FADE_POS_X		(0)					// �|���S���̊J�nX���W
#define FADE_POS_Y		(0)					// �|���S���̊J�nY���W
#define FADE_WIDTH		(SCREEN_WIDTH)		// ����
#define FADE_HEIGHT		(SCREEN_HEIGHT)		// �c��

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	VERTEX_2D *pVtx;	// ���_�o�b�t�@�ւ̃|�C���^

	// �l�̏�����
	g_fade = FADE_IN;	// �t�F�[�h�A�E�g���
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// �������(�s����)�ɂ��Ă���

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FADE_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, FADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FADE_WIDTH, FADE_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	g_pVtxBuffFade->Unlock();	// ���_�o�b�t�@���A�����b�N
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade!= NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	VERTEX_2D *pVtx;	// ���_�o�b�t�@�ւ̃|�C���^

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)			// �t�F�[�h�C�����
		{
			g_colorFade.a -= 0.03f;		// ��ʂ𓧖��ɂ��Ă���
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)	// �t�F�[�h�A�E�g���
		{
			g_colorFade.a += 0.03f;		// ��ʂ�s�����ɂ��Ă���
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;		// �t�F�[�h�C����Ԃɂ���

				//���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}

		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

		// ���_�J���[�̍X�V
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		g_pVtxBuffFade->Unlock();	// ���_�o�b�t�@���A�����b�N
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetFade(MODE modeNext)
{
	// �l�̏�����
	g_fade = FADE_OUT;	//�t�F�[�h�A�E�g���
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�������(����)�ɂ��Ă���
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

