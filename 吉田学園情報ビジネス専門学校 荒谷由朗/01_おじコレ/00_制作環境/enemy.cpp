//=============================================================================
//
// �G���� [enemy.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY					(2)									// �G�̎��
#define POYGON_TEXTURENAME000			"data/TEXTURE/enemy002.png"			//�ǂݍ��ރe�N�X�`��
#define ENEMY_TEXTURE_UV_U				(1.0f)								//�e�A�j���[�V����U�͈�
#define ENEMY_TEXTURE_UV_V				(1.0f)								//�e�A�j���[�V����V�͈�

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy;												//�G�̑���
int nHitEnemy;
int nCountEnemy;

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].type = EnemyType_NORMAL1;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME000, &g_apTextureEnemy[0]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;				//���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0;		//�G�̑������N���A
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//�G���g�p����Ă��鎞
			g_aEnemy[nCntEnemy].nCounterAnim++;			//�J�E���^�[���Z

			if (rand() % 100 == 0)
			{
				SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(g_aEnemy[nCntEnemy].move_bullet, 0.0f, 0.0f), BULLETTYPE_ENEMY, 0);
			}

			//�G�̈ړ����x
			if (g_aEnemy[nCntEnemy].pos.x < 0 && g_aEnemy[nCntEnemy].pos.y > 0)
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnim % 10) == 0)		//�A�j���[�V�����̑�����ς�����
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;

				// ���_�X�V
				pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);

				//�e�N�X�`���X�V
				pVtx[nCntEnemy * 4].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim  * 0.5f), 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f), ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, ENEMY_TEXTURE_UV_V);

			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureEnemy[0]);

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, EnemyType type, float move_bullet)
{
	int nCntEnemy;

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].fWidth = fWidth;
			g_aEnemy[nCntEnemy].type = type;
			g_aEnemy[nCntEnemy].move_bullet = move_bullet;

			//���_�ݒ�
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight, 0.0f);

			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//=============================================================================
// �u���b�N�̓����蔻��
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	int nCntEnemy;
	bool bLand = false;		//���n�������ǂ���

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	Player *pPlayer;
	pPlayer = GetPlayer();		//�v���C���[�̎擾

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�����蔻��
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			if (g_aEnemy[nCntEnemy].pos.x - 14.9 <= pPos->x
				&& g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 14.9 >= pPos->x)
			{//�v���C���[���㉺�͈͓̔��ɂ��邩�ǂ���
				if (g_aEnemy[nCntEnemy].pos.y <= pPos->y
					&& g_aEnemy[nCntEnemy].pos.y >= pPosOld->y)
				{//��
					bLand = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y;
					pMove->y = 0.0f;
					pPlayer->nCounterJump = 0;
				}
				else if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight > pPos->y - 50
					&& g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight < pPosOld->y - 50)
				{//��
					bLand = true;
					pPos->y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight + 50;
					pMove->y = 0.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].pos.y < pPos->y
				&& g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fHeight + 50 > pPos->y)
			{//�v���C���[�����E�͈͓̔��ɂ��邩�ǂ���
				if (g_aEnemy[nCntEnemy].pos.x - 15 >= pPosOld->x
					&& g_aEnemy[nCntEnemy].pos.x - 15 <= pPos->x)
				{//��
					pPos->x = g_aEnemy[nCntEnemy].pos.x - 15;
					pMove->x = 0.0f;
				}
				if (g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 15 <= pPosOld->x
					&& g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 15 >= pPos->x)
				{//�E
					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth + 15;
					pMove->x = 0.0f;
				}
			}
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();


	return bLand;	//�l��Ԃ�
}
////=============================================================================
//// �G�̎擾
////=============================================================================
//Enemy *GetEnemy(void)
//{
//	return &g_aEnemy[0];
//}
