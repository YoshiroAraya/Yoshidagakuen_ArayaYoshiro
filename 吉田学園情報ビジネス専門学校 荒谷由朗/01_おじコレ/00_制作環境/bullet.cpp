//=============================================================================
//
// �e���� [bullet.cpp]
// Author :	�r�J�R�N
//
//=============================================================================
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "block.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET				(256)								// �e�̍ő吔
#define MAX_TYPE_BULLET			(1)									//�e�̎�ނ̍ő吔
#define BULLET_TEXTURENAME000	"data/TEXTURE/bullet000.png"	//�ǂݍ��ރe�N�X�`��
#define BULLET_POS_X			(1000)								//�e�̍���X���W
#define BULLET_POS_Y			(1200)								//�e�̍���Y���W
#define BULLET_WIDTH			(1090)								//�e�̕�
#define BULLET_HEIGHT			(1200)								//�e�̍���
#define BULLET_TEXTURE_SPEED	(5)									//�e�A�j���[�V�����X�s�[�h
#define BULLET_TEXTURE_UV_U		(1.0f)								//�e�A�j���[�V����U�͈�
#define BULLET_TEXTURE_UV_V		(1.0f)								//�e�A�j���[�V����V�͈�

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_paTextureBullet[MAX_TYPE_BULLET] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��

//=============================================================================
// �e�̏���������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
		g_aBullet[nCntBullet].nType = 0;
		g_aBullet[nCntBullet].nLife = 1;
		g_aBullet[nCntBullet].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME000, &g_paTextureBullet[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
		pVtx[1].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BULLET_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, BULLET_TEXTURE_UV_V);

		pVtx += 4;				//���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̏I������
//=============================================================================
void UninitBullet(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_TYPE_BULLET; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_paTextureBullet[nCntTex] != NULL)
		{
			g_paTextureBullet[nCntTex]->Release();
			g_paTextureBullet[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//�e���g�p����Ă���
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;
			//�e�̈ʒu���ړ�
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���_�ݒ�
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, 10 + g_aBullet[nCntBullet].pos.y, 0.0f);
			}
			//�G�̎擾�i�擪�j
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)	//�G�̒e
			{
				Player *pPlayer;
				//�v���C���[�̎擾
				pPlayer = GetPlayer();
				if (pPlayer->pos.x + 30 > g_aBullet[nCntBullet].pos.x
					&& g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - 30
					&& pPlayer->pos.y + 30 > g_aBullet[nCntBullet].pos.y
					&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 30
					&& pPlayer->bDisp == true)
				{	//���蔻��
					HitPlayer(1);
					HitLife(1);
					g_aBullet[nCntBullet].bUse = false;		//�g�p����ĂȂ���Ԃɂ���
				}
			}
			if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT || g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;			//�g�p����ĂȂ���Ԃɂ���
			}
			if(CollisionBlock_Bullet(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].posOld, &g_aBullet[nCntBullet].move) == true)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		//���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_paTextureBullet[g_aBullet[nCntBullet].type]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type, int nType)
{
	int nCntBullet;
	
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{

			g_aBullet[nCntBullet].pos = pos;

			//���_�ݒ�
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].bUse = true;					
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

void HitBullet(int nDamage)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].nLife -= nDamage;
		if (g_aBullet[nCntBullet].nLife <= 0)
		{
			//g_aBullet[nCntBullet].bUse = false;
		}
	}
}
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}
