//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_EXPLOSION				(128)								// �e�̍ő吔
#define POYGON_TEXTURENAME			"data/TEXTURE/explosion000.png"		// �ǂݍ��ރe�N�X�`��
#define EXPLOSION_POS_X				(300)								// �e�̍���X���W
#define EXPLOSION_POS_Y				(450)								// �e�̍���Y���W
#define EXPLOSION_WIDTH				(600)								// �e�̕�
#define EXPLOSION_HEIGHT			(600)								// �e�̍���
#define EXPLOSIONT_TEXTURE_SPEED	(1)									// �e�A�j���[�V�����X�s�[�h
#define EXPLOSION_TEXTURE_UV_U		(1.0f)								// �e�A�j���[�V����U�͈�
#define EXPLOSION_TEXTURE_UV_V		(1.0f)								// �e�A�j���[�V����V�͈�

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXCOLOR	col;				// �F
	int			nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int			nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	bool		bUse;				// �g�p���Ă��邩�ǂ���
}Explosion;

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Explosion				g_aExplosion[MAX_EXPLOSION];	// �����̏��

//=============================================================================
// ���j�̏���������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureExplosion);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, EXPLOSION_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

		pVtx += 4;				// ���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̏I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �����̍X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{// �������g�p����Ă���
			g_aExplosion[nCntExplosion].nCounterAnim++;			// �J�E���^�[���Z

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 4) == 0)		// �A�j���[�V�����̑�����ς�����
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1);

				// ���_�ݒ�
				pVtx[nCntExplosion * 4].pos		= D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 30, g_aExplosion[nCntExplosion].pos.y - 30, 0.0f);
				pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 30, g_aExplosion[nCntExplosion].pos.y - 30, 0.0f);
				pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 30, 30 + g_aExplosion[nCntExplosion].pos.y, 0.0f);
				pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 30, 30 + g_aExplosion[nCntExplosion].pos.y, 0.0f);

				// ���_�J���[�ݒ�
				pVtx[nCntExplosion * 4].col		= D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
				pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
				pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
				pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);

				// �e�N�X�`���ݒ�
				pVtx[nCntExplosion * 4].tex		= D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, EXPLOSION_TEXTURE_UV_V);

				if (g_aExplosion[nCntExplosion].nPatternAnim > 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;			// �g�p���Ă��Ȃ���Ԃɂ���
				}
			}
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̕`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos				= pos;
			g_aExplosion[nCntExplosion].col				= col;
			g_aExplosion[nCntExplosion].nCounterAnim	= 0;
			g_aExplosion[nCntExplosion].nPatternAnim	= 0;
			g_aExplosion[nCntExplosion].bUse			= true;

			// ���_�ݒ�
			pVtx[nCntExplosion * 4].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �J���[�ݒ�
			pVtx[nCntExplosion * 4].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`���ݒ�
			pVtx[nCntExplosion * 4].tex		= D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.0f, EXPLOSION_TEXTURE_UV_V);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

			break;
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();
}