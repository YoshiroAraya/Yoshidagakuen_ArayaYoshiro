//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author :	�r�J�R�N
//
//=============================================================================
#include "block.h"
#include "player.h"
#include "main.h"
#include "item.h"
#include "bullet.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_BLOCK				(256)								//�u���b�N�̍ő吔
#define BLOCK_TEXTURENAME000	"data/TEXTURE/texture140921002.jpg"	//�ǂݍ��ރe�N�X�`��
#define BLOCK_TEXTURE_UV_U		(1.0f)								//�u���b�N�̃A�j���[�V����U�͈�
#define BLOCK_TEXTURE_UV_V		(1.0f)								//�u���b�N�̃A�j���[�V����V�͈�

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_paTextureBlock = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];							//�u���b�N�̏��

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0;
		g_aBlock[nCntBlock].fHeight = 0;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].type = BlockType_NORMAL;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME000, &g_paTextureBlock);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BLOCK_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, BLOCK_TEXTURE_UV_V);

		pVtx += 4;				//���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void UninitBlock(void)
{
	// �e�N�X�`���̊J��
	if (g_paTextureBlock != NULL)
	{
		g_paTextureBlock->Release();
		g_paTextureBlock = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void UpdateBlock(void)
{
	int nCntBlock;
	
	int nItemKey;
	nItemKey = GetItemNumber();

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (nItemKey == 0 && g_aBlock[nCntBlock].type == BlockType_DELETE)
			{
				g_aBlock[nCntBlock].bUse = false;
			}
		}
	}
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_paTextureBlock);

	// �|���S���̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth,float fHeight, BlockType type)
{
	int nCntBlock;

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		
		if (g_aBlock[nCntBlock].bUse == false)
		{

			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].type = type;

			//���_�ݒ�
			pVtx[nCntBlock * 4].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[nCntBlock * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			g_aBlock[nCntBlock].bUse = true;
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̓����蔻��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int nCntBlock;
	bool bLand = false;		//���n�������ǂ���

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	Player *pPlayer;
	pPlayer = GetPlayer();		//�v���C���[�̎擾

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�����蔻��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			
			if (g_aBlock[nCntBlock].pos.x - 14.9 <= pPos->x
				&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 14.9 >= pPos->x)
			{//�v���C���[���㉺�͈͓̔��ɂ��邩�ǂ���
				if (g_aBlock[nCntBlock].pos.y <= pPos->y
					&& g_aBlock[nCntBlock].pos.y >= pPosOld->y)
				{//��
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;	
					pPlayer->nCounterJump = 0;
				}
				else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight > pPos->y - 50
					&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight < pPosOld->y - 50)
				{//��
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + 50;
					pMove->y = 0.0f;
				}
			}
			if (g_aBlock[nCntBlock].pos.y < pPos->y
				&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + 50 > pPos->y)
			{//�v���C���[�����E�͈͓̔��ɂ��邩�ǂ���
				if (g_aBlock[nCntBlock].pos.x - 15 >= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x -15 <= pPos->x)
				{//��
					pPos->x = g_aBlock[nCntBlock].pos.x - 15;
					//pMove->x = 0.0f;
				}
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 15 <= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 15 >= pPos->x)
				{//�E
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + 15;
					//pMove->x = 0.0f;
				}
			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();


	return bLand;	//�l��Ԃ�
}
//=============================================================================
// �e�̓����蔻��
//=============================================================================
bool CollisionBlock_Bullet(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int nCntBlock;
	bool bLand = false;		//���n�������ǂ���

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	Bullet *pBullet;
	pBullet = GetBullet();		//�e�̎擾

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�����蔻��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].pos.x <= pPos->x
				&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x)
			{//�v���C���[���㉺�͈͓̔��ɂ��邩�ǂ���
				if (g_aBlock[nCntBlock].pos.y <= pPos->y
					&& g_aBlock[nCntBlock].pos.y >= pPosOld->y)
				{//��
					bLand = true;
				}
				else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight > pPos->y
					&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight < pPosOld->y)
				{//��
					bLand = true;
				}
			}
			if (g_aBlock[nCntBlock].pos.y < pPos->y
				&& g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight > pPos->y)
			{//�v���C���[�����E�͈͓̔��ɂ��邩�ǂ���
				if (g_aBlock[nCntBlock].pos.x >= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x <= pPos->x)
				{//��
					bLand = true;
				}
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth <= pPosOld->x
					&& g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x)
				{//�E
					bLand = true;
				}
			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlock->Unlock();


	return bLand;	//�l��Ԃ�
}
