//=============================================================================
//
// �������� [explosion.cpp]
// Author :	�r�J �R�N
//
//=============================================================================
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_EXPLOSION				(128)								// �e�̍ő吔
#define POYGON_TEXTURENAME			"data/TEXTURE/explosion000.png"		// �ǂݍ��ރe�N�X�`��
#define EXPLOSION_TEXTURE_UV_U		(1.0f)								// �e�A�j���[�V����U�͈�
#define EXPLOSION_TEXTURE_UV_V		(1.0f)								// �e�A�j���[�V����V�͈�

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXCOLOR	col;			// �F
	D3DXMATRIX  mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXMATRIX	mtxView;		// �r���[�}�g���b�N�X
	int			nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int			nPatternAnim;	// �A�j���[�V�����p�^�[��No.
	bool		bUse;			// �g�p���Ă��邩�ǂ���
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntExplosion;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureExplosion);

	// �����̏��̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim	= 0;
		g_aExplosion[nCntExplosion].nPatternAnim	= 0;
		g_aExplosion[nCntExplosion].bUse			= false;
	}

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 25.0f, 0.0f);		// ���_���W(X���W,Y���W)
		pVtx[1].pos = D3DXVECTOR3(15.0f, 25.0f, 0.0f);		// ���_���W(X���W,Y���W)
		pVtx[2].pos = D3DXVECTOR3(-15.0f, 0.0f, 0.0f);		// ���_���W(X���W,Y���W)
		pVtx[3].pos = D3DXVECTOR3(15.0f, 0.0f, 0.0f);		// ���_���W(X���W,Y���W)

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			// U�����AV�������@(0.0f�`1.0f�j
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);		// U�����AV�������@(0.0f�`1.0f�j
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			// U�����AV�������@(0.0f�`1.0f�j
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);		// U�����AV�������@(0.0f�`1.0f�j

		pVtx += 4;										// ���W��4���i�߂�
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
	VERTEX_3D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	// �������g�p����Ă���
			g_aExplosion[nCntExplosion].nCounterAnim++;			// �J�E���^�[���Z

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 4) == 0)		// �A�j���[�V�����̑�����ς�����
			{
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1);

				// �e�N�X�`���ݒ�
				pVtx[nCntExplosion * 4].tex		= D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, EXPLOSION_TEXTURE_UV_V);

				if (g_aExplosion[nCntExplosion].nPatternAnim > 7)
				{
					g_aExplosion[nCntExplosion].bUse = false;			// �g�p���Ă��Ȃ����
				}
			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̕`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorld);

		// �r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &g_aExplosion[nCntExplosion].mtxView);

		// �J�����̋t�s���ݒ�
		g_aExplosion[nCntExplosion].mtxWorld._11 = g_aExplosion[nCntExplosion].mtxView._11;
		g_aExplosion[nCntExplosion].mtxWorld._12 = g_aExplosion[nCntExplosion].mtxView._21;
		g_aExplosion[nCntExplosion].mtxWorld._13 = g_aExplosion[nCntExplosion].mtxView._31;
		g_aExplosion[nCntExplosion].mtxWorld._21 = g_aExplosion[nCntExplosion].mtxView._12;
		g_aExplosion[nCntExplosion].mtxWorld._22 = g_aExplosion[nCntExplosion].mtxView._22;
		g_aExplosion[nCntExplosion].mtxWorld._23 = g_aExplosion[nCntExplosion].mtxView._32;
		g_aExplosion[nCntExplosion].mtxWorld._31 = g_aExplosion[nCntExplosion].mtxView._13;
		g_aExplosion[nCntExplosion].mtxWorld._32 = g_aExplosion[nCntExplosion].mtxView._23;
		g_aExplosion[nCntExplosion].mtxWorld._33 = g_aExplosion[nCntExplosion].mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
		D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorld, &g_aExplosion[nCntExplosion].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureExplosion);

		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos				= pos;
			g_aExplosion[nCntExplosion].col				= col;
			g_aExplosion[nCntExplosion].nCounterAnim	= 0;
			g_aExplosion[nCntExplosion].nPatternAnim	= 0;
			g_aExplosion[nCntExplosion].bUse			= true;
			break;
		}
	}
}