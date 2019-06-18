//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "coin.h"
#include "item.h"
#include "flag.h"
#include "game.h"
#include "sound.h"
#include "explosion.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER			(1)								// �v���C���[�̐�
#define PLAYER_TEXTURENAME  "data/TEXTURE/player000.png"	// �e�N�X�`���̃t�@�C����
#define TEX_LEFT			(0.0f)							// �e�N�X�`�����WU��
#define TEX_RIGHT			(0.25f)							// �e�N�X�`�����WU�E
#define TEX_TOP				(0.0f)							// �e�N�X�`�����WV��
#define TEX_BOT				(0.5f)							// �e�N�X�`�����WV��
#define POLYGON_SPEED		(0.65f)							// �|���S���𓮂������x
#define COUNTER_RESET		(5)								// �J�E���^�[���Z�b�g
#define RISING_SPEED		(8.0f)							// �㏸���x
#define GRAVITY_POWER		(0.5f)							// �d��

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureRunPlayer = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRunPlayer = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
Player					g_player;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	VERTEX_2D			*pVtx;					// ���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// �f�o�C�X���擾

	g_player.nCounterAnim	= 0;
	g_player.nPatternAnim	= 0;
	g_player.nCounterJump	= 0;
	g_player.nDirectionMove = 0;
	g_player.state			= PLAYERSTATE_NORMAL;
	g_player.nLife			= 5;
	g_player.fWidth			= 30;
	g_player.fHeight		= 50;
	g_player.bDisp			= true;
	g_player.bUse			= true;
	g_player.bJump			= false;
	g_player.pos			= D3DXVECTOR3(20.0f, 695.0f, 0.0f);
	g_player.move			= D3DXVECTOR3(0, 0, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURENAME,
		&g_pTextureRunPlayer);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRunPlayer,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y + g_player.fHeight, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y + g_player.fHeight, g_player.pos.z);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRunPlayer->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureRunPlayer != NULL)
	{
		g_pTextureRunPlayer->Release();
		g_pTextureRunPlayer = NULL;
	}
	// ���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffRunPlayer != NULL)
	{
		g_pVtxBuffRunPlayer->Release();
		g_pVtxBuffRunPlayer = NULL;
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
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			VERTEX_2D *pVtx;
			g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);
			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_pVtxBuffRunPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState == 0)
		{
			SetFade(MODE_RESULT);
		}
		return;
		break;
	}

	g_player.posOld =	g_player.pos;		// ���W�̍X�V
	g_player.pos	+=	g_player.move;		// �ʒu�̍X�V
	g_player.nCounterAnim++;				// �J�E���^�[���Z

	VERTEX_2D *pVtx;						// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);


	// ���ꂼ��̏����œ���������ς���(����)
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{	// �W�����v
		if (g_player.bJump == false)
		{
			g_player.move.y = cosf(D3DX_PI) * RISING_SPEED;
			g_player.bJump	= false;
			g_player.nCounterJump++;
			PlaySound(SOUND_LABEL_SE_PLEYERJUMP);		// �T�E���h�̍Đ�
		}
	}
	if (GetKeyboardPress(DIK_A) == true)
	{	// ���ړ�
		g_player.move.x -= POLYGON_SPEED;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{	// �E�ړ�
		g_player.move.x += POLYGON_SPEED;
	}

	// �d��
	g_player.move.y += cosf(0) * GRAVITY_POWER;

	// �ʒu�X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;


	// �e�N�X�`���̍X�V
	if (GetKeyboardPress(DIK_A) == true && g_player.bJump == false)
	{// ���ړ�
		if ((g_player.nCounterAnim % 10) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
		g_player.nDirectionMove = 1;
	}
	else if (GetKeyboardPress(DIK_D) == true && g_player.bJump == false)
	{// �E�ړ�
		if ((g_player.nCounterAnim % 10) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
		g_player.nDirectionMove = 0;
	}
	else if (g_player.bJump == true && g_player.nPatternAnim % 2 == 0)
	{// �W�����v
		if ((g_player.nCounterAnim % 10) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
	}
	else if (g_player.bJump == false && g_player.nPatternAnim % 2 == 1)
	{// �n��
		if ((g_player.nCounterAnim % 10) == 0)		// �A�j���[�V�����̑�����ς�����
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}
	}

	// ����
	g_player.move.x += (0.0f - g_player.move.x) * 0.25f;

	// �u���b�N�̓����蔻��
	if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move) == true)
	{
		g_player.bJump = false;
	}
	else
	{
		if (g_player.bJump == false && g_player.nCounterJump >= 2)
		{
			g_player.bJump = true;
		}
	}

	// �t���b�O�̓����蔻��
	CollisionFlag(&g_player.pos, &g_player.posOld, &g_player.move);
	// �R�C���̓����蔻��
	CollisionCoin(&g_player.pos, &g_player.posOld, &g_player.move);
	// �A�C�e���̓����蔻��
	CollisionItem(&g_player.pos, &g_player.posOld, &g_player.move, g_player.fHeight, g_player.fWidth);

	// ���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, g_player.pos.z);

	// �e�N�X�`���X�V
	pVtx[0].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f), 0.5f * g_player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f) + 0.25f, 0.5f * g_player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f), 0.5f * g_player.nDirectionMove + 0.5f);
	pVtx[3].tex = D3DXVECTOR2(((g_player.nPatternAnim % 4) * 0.25f) + 0.25f, 0.5f * g_player.nDirectionMove + 0.5f);

	// �g�O�ɏo���ꍇ
	if (g_player.pos.y <= 0 + g_player.fWidth)
	{// ��
		g_player.pos.y = 0 + g_player.fWidth;
		g_player.move.y += cosf(0) * GRAVITY_POWER;
	}
	if (g_player.pos.x - g_player.fWidth / 2 < 0)
	{// ������o���獶�ɖ߂�
		g_player.pos.x = g_player.fWidth / 2;
		g_player.move.x = 0;
	}
	if (g_player.pos.x + g_player.fWidth / 2 > SCREEN_WIDTH)
	{// �E����o����E�ɖ߂�
		g_player.pos.x = SCREEN_WIDTH - g_player.fWidth / 2;
		g_player.move.x = 0;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRunPlayer->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾����

	if (g_player.bDisp == true)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffRunPlayer, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRunPlayer);

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
	g_player.nLife -= nDamage;		// ���C�t�̌��Z
	if (g_player.nLife <= 0)
	{// ���C�t��0�ȉ��ɂȂ�����
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_player.bDisp	= false;
		g_player.bUse	= false;
		g_player.state	= PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_PLEYERBAD);		// �T�E���h�̍Đ�
		g_player.nCounterState = 60;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		PlaySound(SOUND_LABEL_SE_PLEYERDAMEZ);		// �T�E���h�̍Đ�
		g_player.nCounterState = 5;

		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
		g_pVtxBuffRunPlayer->Lock(0, 0, (void**)&pVtx, 0);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_pVtxBuffRunPlayer->Unlock();
	}
}