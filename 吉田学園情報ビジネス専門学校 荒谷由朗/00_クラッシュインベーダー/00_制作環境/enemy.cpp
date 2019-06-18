//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �r�J �R�N
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

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_TYPE_ENEMY					(4)								// �G�̎��
#define POYGON_TEXTURENAME000			"data/TEXTURE/enemy000.png"		// �ǂݍ��ރe�N�X�`��
#define POYGON_TEXTURENAME001			"data/TEXTURE/enemy001.png"		// �ǂݍ��ރe�N�X�`��
#define POYGON_TEXTURENAME002			"data/TEXTURE/enemy002.png"		// �ǂݍ��ރe�N�X�`��
#define POYGON_TEXTURENAME003			"data/TEXTURE/enemy003.png"		// �ǂݍ��ރe�N�X�`��
#define ENEMY_TEXTURE_UV_U				(1.0f)							// �e�A�j���[�V����U�͈�
#define ENEMY_TEXTURE_UV_V				(1.0f)							// �e�A�j���[�V����V�͈�

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY]	= {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy						= NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Enemy					g_aEnemy[MAX_ENEMY];							// �G�̏��
int						g_nNumEnemy;									// �G�̑���
int						nHitEnemy;
int						nCountEnemy;

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
		g_aEnemy[nCntEnemy].pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].col				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEnemy[nCntEnemy].nType			= 0;
		g_aEnemy[nCntEnemy].nCounterAnim	= 0;
		g_aEnemy[nCntEnemy].nPatternAnim	= 0;
		g_aEnemy[nCntEnemy].nLife			= 0;
		g_aEnemy[nCntEnemy].nSpped			= 0;
		g_aEnemy[nCntEnemy].bUse			= false;
		g_aEnemy[nCntEnemy].state			= ENEMTSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState	= 0;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME000, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME001, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME002, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME003, &g_apTextureEnemy[3]);

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
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;				// ���_�f�[�^�ւ̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0;		// �G�̑������N���A
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
	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	// �G���g�p����Ă��鎞
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMTSTATE_NORMAL:
				break;
			case ENEMTSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMTSTATE_NORMAL;

					// ���_���(���_�J���[)�̐ݒ�
					pVtx[nCntEnemy * 4].col		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					g_pVtxBuffEnemy->Unlock();
				}
				nHitEnemy++;
				break;
			}
			g_aEnemy[nCntEnemy].nCounterAnim++;			// �J�E���^�[���Z

			if (g_nNumEnemy == 12)
			{
				if (rand() % 250 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}

			else if (g_nNumEnemy >= 10 && g_nNumEnemy <= 11)
			{
				if (rand() % 190 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}
			else if (g_nNumEnemy >= 8 && g_nNumEnemy <= 9)
			{
				if (rand() % 120 == 0)
				{
					D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
					Player *pPlayer;
					static float fAngle;

					pPlayer = GetPlayer();

					fAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

					BulletMove.x = sinf(fAngle) * 5.0f;
					BulletMove.y = cosf(fAngle) * 5.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, BulletMove, BULLETTYPE_ENEMY, 0);
				}
			}
			else if (g_nNumEnemy >= 6 && g_nNumEnemy <= 7)
			{
				if (rand() % 70 == 0)
				{
					D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
					Player *pPlayer;
					static float fAngle;

					pPlayer = GetPlayer();

					fAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

					BulletMove.x = sinf(fAngle) * 5.0f;
					BulletMove.y = cosf(fAngle) * 5.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, BulletMove, BULLETTYPE_ENEMY, 0);
				}
			}
			else if (g_nNumEnemy >= 4 && g_nNumEnemy <= 5)
			{
				if (rand() % 50 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);

				}
			}
			else if (g_nNumEnemy >= 2 && g_nNumEnemy <= 3)
			{
				if (rand() % 35 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 3.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}
			else
			{
				if (rand() % 10 == 0)
				{

					D3DXVECTOR3 BulletMove(0.0f, 0.0f, 0.0f);
					Player *pPlayer;
					static float fAngle;

					pPlayer = GetPlayer();

					fAngle = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);

					BulletMove.x = sinf(fAngle) * 5.0f;
					BulletMove.y = cosf(fAngle) * 5.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, BulletMove, BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * 1.0f, cosf(D3DX_PI * 0.1f) * 5.0f, 0.0f), BULLETTYPE_ENEMY, 0);
				}
			}


			// �G�̈ړ����x
			g_aEnemy[nCntEnemy].nSpped = 5.0f;
			g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].nSpped;
			if (g_aEnemy[nCntEnemy].pos.x < 0 && g_aEnemy[nCntEnemy].pos.y > 0)
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnim % 10) == 0)		// �A�j���[�V�����̑�����ς�����
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;

				// ���_�X�V
				pVtx[nCntEnemy * 4].pos		= D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y - 30, 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y - 30, 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y + 30, 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y + 30, 0.0f);

				// �e�N�X�`���X�V
				pVtx[nCntEnemy * 4].tex		= D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim  * 0.5f), 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f), ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, ENEMY_TEXTURE_UV_V);

				// �F�̕ω�
				if (g_aEnemy[nCntEnemy].col.r != 1.0f)
				{
					static int nCntAnim = 0;
					nCntAnim++;

					if ((nCntAnim % 3) == 0)
					{
						g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}
			}
		}
	}
	// ���_�o�b�t�@�̃A�����b�N
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

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			// ���_�ݒ�
			pVtx[nCntEnemy * 4].pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�e�N�X�`���ݒ�
			pVtx[nCntEnemy * 4].tex		= D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
			pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
			pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

			g_aEnemy[nCntEnemy].nType			= nType;
			g_aEnemy[nCntEnemy].nLife			= 15;
			g_aEnemy[nCntEnemy].nSpped			= 0;
			g_aEnemy[nCntEnemy].bUse			= true;
			g_aEnemy[nCntEnemy].state			= ENEMTSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState	= 0;

			g_nNumEnemy++;				// �G�̑��������Z����
			break;
		}
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
//�G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	GAMESTATE GetGameStateNow();

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aEnemy[nCntEnemy].bUse = false;
		nCountEnemy++;
		g_nNumEnemy--;				// �G�̑��������炷
		if (g_nNumEnemy <= 0)		// �G���S�ł�����
		{
			SetGameState(GAMESTATE_CLEAR);
		}
		if (g_aEnemy[nCntEnemy].nType = 0)
		{
			AddScore(200);
		}
		else if (g_aEnemy[nCntEnemy].nType = 1)
		{
			AddScore(400);
		}
		else if (g_aEnemy[nCntEnemy].nType = 2)
		{
			AddScore(800);
		}
		else if (g_aEnemy[nCntEnemy].nType = 3)
		{
			AddScore(1000);
		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMTSTATE_DAMAGE;
		PlaySound(SOUND_LABEL_SE_HIT001);
		g_aEnemy[nCntEnemy].nCounterState = 5;
		VERTEX_2D * pVtx;
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4); // �Y���̈ʒu�܂Ői�߂�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		g_pVtxBuffEnemy->Unlock();
	}
}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}