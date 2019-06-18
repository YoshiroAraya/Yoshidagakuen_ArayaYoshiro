//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "sound.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POYGON_TEXTURENAME		"data/TEXTURE/player000.png"			// �ǂݍ��ރe�N�X�`��
#define POYGON_POS_X			(300)									// ���_���W�iX���W�j(�ʒu)
#define POYGON_POS_Y			(200)									// ���_���W�iY���W�j(�ʒu)
#define POYGON_POS_WIDTH		(500)									// �摜�̑傫���iX���W)
#define POYGON_POS_HEIGHT		(500)									// �摜�̑傫��(Y���W)
#define POYGON_ANIM_PATTERN		(10)									// �A�j���[�V�����̃p�^�[��
#define POYGON_ANIM_WIDTH		(1.0f)									// �A�j���[�V�����̕�
#define POLYGON_ANIM_HEIGHT		(1.0f)									// �A�j���[�V�����̍���
#define POLYGON_SPEED			(3.0f)									// �|���S���𓮂������x
#define BULLET_SPEED			(-5.0f)									// �e�̃X�s�[�h

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;	// �e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Player					g_player;


//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	g_player.bDisp	= true;
	g_player.nLife	= 10;
	g_player.state	= PLAYERSTATE_NORMAL;
	g_player.pos	= D3DXVECTOR3(SCREEN_WIDTH / 2 , SCREEN_HEIGHT - 50, 0.0f);			// �|���S���̒��S�_
	g_player.move	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// �|���S���̈ړ����x

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POYGON_TEXTURENAME, &g_pTexturePlayer);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(POYGON_POS_WIDTH, POYGON_POS_Y, 0.0f);			// ���_���W(X���W,Y���W)
	pVtx[1].pos = D3DXVECTOR3(POYGON_POS_WIDTH, POYGON_POS_HEIGHT, 0.0f);		// ���_���W(X���W,Y���W)
	pVtx[2].pos = D3DXVECTOR3(POYGON_POS_X, POYGON_POS_Y, 0.0f);				// ���_���W(X���W,Y���W)
	pVtx[3].pos = D3DXVECTOR3(POYGON_POS_X, POYGON_POS_HEIGHT, 0.0f);			// ���_���W(X���W,Y���W)

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T�j
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);  // �F�̎w��i�O�`�Q�T�T�j&�����x�i�O�`�Q�T�T)

	 // �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, 0.0f);						// U�����AV�������@(0.0f�`1.0f�j
	pVtx[1].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, POLYGON_ANIM_HEIGHT);		// U�����AV�������@(0.0f�`1.0f�j
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);									// U�����AV�������@(0.0f�`1.0f�j
	pVtx[3].tex = D3DXVECTOR2(0.0f, POLYGON_ANIM_HEIGHT);					// U�����AV�������@(0.0f�`1.0f�j

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// �e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCunterState--;
		if (g_player.nCunterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			VERTEX_2D * pVtx;
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_pVtxBuffPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCunterState--;
		if (g_player.nCunterState == 0)
		{
			SetFade(MODE_RESULT);
		}
		return;
		break;
	}
	VERTEX_2D*pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���ꂼ��̏����œ���������ς���(����)
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{	// ����ړ�
				g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED + 1.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * POLYGON_SPEED + 1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{	// �����ړ�
				g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED + 1.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * POLYGON_SPEED - 1.0f;
			}
			else
			{	// ���ړ�
				g_player.move.x += sinf(-D3DX_PI * 0.5) * POLYGON_SPEED + 1.0f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{	// �E��ړ�
				g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED - 1.0f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * POLYGON_SPEED + 1.0f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{	// �E���ړ�
				g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED - 1.0f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * POLYGON_SPEED - 1.0f;
			}
			else
			{	// �E�ړ�
				g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED - 1.0f;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{	// S�����������Ɖ��Ɉړ�
			g_player.move.y += cosf(0) * POLYGON_SPEED - 1.0f;
		}
		else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{	// W�����������Ə�Ɉړ�
			g_player.move.y += cosf(D3DX_PI) * POLYGON_SPEED + 1.0f;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
	{
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{	// ����ړ�
			g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * POLYGON_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{	// �����ړ�
			g_player.move.x += sinf(-D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * POLYGON_SPEED;
		}
		else
		{	// ���ړ�
			g_player.move.x += sinf(-D3DX_PI * 0.5) * POLYGON_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{
		if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{	// �E��ړ�
			g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * POLYGON_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{	// �E���ړ�
			g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * POLYGON_SPEED;
		}
		else
		{	// �E�ړ�
			g_player.move.x += sinf(D3DX_PI * 0.5f) * POLYGON_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
	{	// S�����������Ɖ��Ɉړ�
		g_player.move.y += cosf(0) * POLYGON_SPEED;
	}
	else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
	{	// W�����������Ə�Ɉړ�
		g_player.move.y += cosf(D3DX_PI) * POLYGON_SPEED;
	}

	// �e�̐ݒ�
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{	// X�L�[�Œe���o��(�E���΂�)
		SetBullet(g_player.pos, D3DXVECTOR3(0.0f, -5.0f, 0.0f), BULLETTYPE_PLAYER, 0);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * -1.0f, cosf(D3DX_PI * 0.1f) * -5.0f, 0.0f), BULLETTYPE_PLAYER1, 0);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * -1.0f, cosf(D3DX_PI * 0.1f) * -5.0f, 0.0f), BULLETTYPE_PLAYER2, 0);
		PlaySound(SOUND_LABEL_SE_SHOT);
	}
	g_player.nCunterAnim++;

	// �ʒu�X�V(�ړ�)
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	// ����
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.5f;

	// �g�O�ɏo���ꍇ
	if (g_player.pos.x < 40)
	{	// �E����o���獶����߂�
		g_player.pos.x = 40;
	}
	if (g_player.pos.x > SCREEN_WIDTH - 40)
	{	// ������o����E����߂�
		g_player.pos.x = SCREEN_WIDTH - 40;
	}
	if (g_player.pos.y < 50)
	{	// �ォ��o���牺����߂�
		g_player.pos.y = 50;
	}
	if (g_player.pos.y > SCREEN_HEIGHT - 50)
	{	// ������o����ォ��߂�
		g_player.pos.y = SCREEN_HEIGHT - 50;
	}

	// ���_���̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x -30, g_player.pos.y- 30, 0.0f);		// ���_���W(X���W,Y���W)
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 30, g_player.pos.y- 30, 0.0f);		// ���_���W(X���W,Y���W)
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 30, g_player.pos.y + 30, 0.0f);		// ���_���W(X���W,Y���W)
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 30, g_player.pos.y + 30, 0.0f);		// ���_���W(X���W,Y���W)

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);											// U�����AV�������@(0.0f�`1.0f�j
	pVtx[1].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, 0.0f);								// U�����AV�������@(0.0f�`1.0f�j
	pVtx[2].tex = D3DXVECTOR2(0.0f, POLYGON_ANIM_HEIGHT);							// U�����AV�������@(0.0f�`1.0f�j
	pVtx[3].tex = D3DXVECTOR2(POYGON_ANIM_WIDTH, POLYGON_ANIM_HEIGHT);				// U�����AV�������@(0.0f�`1.0f�j

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�̃|�C���^

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos,D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f));
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		SetGameState(GAMESTATE_OVER);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_player.nCunterState = 60;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		PlaySound(SOUND_LABEL_SE_HIT000);
		g_player.nCunterState = 5;

		VERTEX_2D * pVtx;
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_pVtxBuffPlayer->Unlock();
	}
}