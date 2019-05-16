//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author :	�r�J�R�N
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "fade.h"
#include "game.h"
#include "block.h"
#include "flag.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ITEM				(128)							//�A�C�e���̍ő吔
#define POYGON_TEXTURENAME		"data/TEXTURE/ozisan.png"		//�ǂݍ��ރe�N�X�`��
#define ITEM_TEXTURE_SPEED		(6)								//�A�C�e���A�j���[�V�����X�s�[�h
#define ITEM_TEXTURE_UV_U		(0.125f)						//�A�C�e���A�j���[�V����U�͈�
#define ITEM_TEXTURE_UV_V		(1.0f)							//�A�C�e���A�j���[�V����V�͈�
#define MAX_PATTERN				(8)								//�p�^�[���̐�
#define COLLISION_AREA			(11.0f)							//�����蔻��̒���

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];							// �A�C�e���̏��
int g_nNumItem;									// �A�C�e���̑���

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;
	g_nNumItem = 0;	//�������N���A

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�A�C�e���̏��̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].posStart = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nDirectionMove = 0;
		g_aItem[nCntItem].fHeight = 0.0f;
		g_aItem[nCntItem].fWidth = 0.0f;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTextureItem);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		pVtx[1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);

		pVtx += 4;				//���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void UninitItem(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{//�A�C�e�����g�p����Ă���
			g_aItem[nCntItem].nCounterAnim++;			//�J�E���^�[���Z

			if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0)		//�A�j���[�V�����̑�����ς�����
			{
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1) % MAX_PATTERN;	//�p�^�[��No.�X�V
				//�O��ʒu��ۑ�
				g_aItem[nCntItem].posOld = g_aItem[nCntItem].pos;
				//�ʒu�����X�V
				g_aItem[nCntItem].pos += g_aItem[nCntItem].move;

				if (g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth <= g_aItem[nCntItem].posStart.x - g_aItem[nCntItem].fHorLimit		//��
					|| g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth >= g_aItem[nCntItem].posStart.x + g_aItem[nCntItem].fHorLimit)	//�E
				{//�ړ�����(���E)
					g_aItem[nCntItem].move.x *= -1;
				}

				if (g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fWidth <= g_aItem[nCntItem].posStart.x - g_aItem[nCntItem].fHorLimit)
				{//���[�܂ł������Ƃ�
					g_aItem[nCntItem].nDirectionMove = 0;
				}
				if (g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth >= g_aItem[nCntItem].posStart.x + g_aItem[nCntItem].fHorLimit)
				{//�E�[�܂ł������Ƃ�
					g_aItem[nCntItem].nDirectionMove = 1;
				}

				// ���_�ݒ�
				pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
				pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
				pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);
				pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);

				//�e�N�X�`���X�V
				pVtx[nCntItem * 4].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f), 0.5f * g_aItem[nCntItem].nDirectionMove);
				pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f) + 0.125f, 0.5f * g_aItem[nCntItem].nDirectionMove);
				pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f), 0.5f * g_aItem[nCntItem].nDirectionMove + 0.5f);
				pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(((g_aItem[nCntItem].nPatternAnim % 4) * 0.125f) + 0.125f, 0.5f * g_aItem[nCntItem].nDirectionMove + 0.5f);

			}
		}
	}
	//�X�e�[�W
	if (g_nNumItem <= 0)
	{
		//�t���b�O
		SetFlag(D3DXVECTOR3(1150.0f, SCREEN_HEIGHT - 70.0f, 0.0f), 30.0f, 40.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̕`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItem);

	// �|���S���̕`��
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fHorLimit, float fWidth, float fHeight)
{
	int nCntItem;

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].posStart = pos;
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].fWidth = fWidth;
			g_aItem[nCntItem].fHeight = fHeight;
			g_aItem[nCntItem].fHorLimit = fHorLimit;

			//���_�ݒ�
			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fWidth, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fHeight, g_aItem[nCntItem].fWidth + g_aItem[nCntItem].pos.y, 0.0f);

			g_aItem[nCntItem].bUse = true;
			g_nNumItem++;			//���������Z
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth)
{
	int nCntItem;
	bool bLand = false;		//���n�������ǂ���

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	FADE fade;
	fade = GetFade();

	Player *pPlayer;
	pPlayer = GetPlayer();		//�v���C���[�̎擾

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//�����蔻��
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (g_aItem[nCntItem].pos.x - fWidth / 2 <= pPos->x
				&& g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth + fWidth / 2 >= pPos->x
				&& g_aItem[nCntItem].pos.y < pPos->y
				&& g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight + fHeight > pPos->y)
			{
				AddScore(1000);
				PlaySound(SOUND_LABEL_SE_OZISANGET);
				g_nNumItem--;
				g_aItem[nCntItem].bUse = false;
			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffItem->Unlock();

	return bLand;
}
//=============================================================================
// �A�C�e���̎擾
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}
//=============================================================================
// �A�C�e���̎擾(��)
//=============================================================================
int GetItemNumber(void)
{
	return g_nNumItem;
}