//=============================================================================
//
// ���C�t���� [Life.cpp]
// Author : Kishida Rei
//
//=============================================================================
#include "life.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "game.h"
#include "died.h"
#include "char_select.h"
#include "particle.h"
//****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIFE_VERTEX ((g_Life_h + 1) * (g_Life_v + 1))
#define LIFE_INDEX ( (g_Life_h * g_Life_v )* 2 + (4 * (g_Life_v - 1)) + 2 )
#define LIFE_POLYGON ( (g_Life_h * g_Life_v) * 2 + (4 * (g_Life_v - 1)) )

#define LIFE_RADIUS (38.0f)
#define LIFE_RADIUS2 (6.0f)

#define SOLDIER_LIFE (1000)
#define WARRIOR_LIFE (700)
#define SORCERER_LIFE (650)

#define LIFE_HEIGHT (5.0f)

#define LIFE_H (100) //���b�V���̕�����(H)
#define LIFE_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffLife = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_posLife;		//�ʒu(���S���W)
D3DXVECTOR3 g_rotLife;		//����
D3DXMATRIX g_mtxWorldLife;	//���[���h�}�g���b�N�X
D3DXCOLOR g_colLife;
LIFE g_Life;
int g_nLife;		//�������̃��C�t
int g_nMax_Life;		//�������̃��C�t�ő�l
int g_nLifeNum;		//�������l�̃��C�t
int g_nMaxLifeNum;		//�������l���C�t�̍ő�l
int g_Life_h, g_Life_v;

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	CHARACTER_TYPE pCharaType = GetCharaType();		// �I���L�����N�^�[���̎擾

	switch (pCharaType)
	{
	case CHARACTER_TYPE_SOLDIER:
			g_Life_h = SOLDIER_LIFE;
			g_Life_v = 1;
			g_nLifeNum = SOLDIER_LIFE;
			g_nMaxLifeNum = 1000;
			break;

	case CHARACTER_TYPE_WARRIOR:
		g_Life_h = WARRIOR_LIFE;
		g_Life_v = 1;
		g_nLifeNum = WARRIOR_LIFE;
		g_nMaxLifeNum = 700;


		break;
	case CHARACTER_TYPE_SORCERER:
		g_Life_h = SORCERER_LIFE;
		g_Life_v = 1;
		g_nLifeNum = SORCERER_LIFE;
		g_nMaxLifeNum = 650;
		break;
	}
	
	int Polygon = (g_Life_h * g_Life_v) * 2 + (4 * (g_Life_v - 1));
	g_nMax_Life = 0;
	g_nLife = 0;
	MakeVertexLife(pDevice);
	MakeIndexLife(pDevice);

	PLAYER pPlayer;
	pPlayer = *GetPlayer();

	g_posLife = pPlayer.pos;
	g_rotLife = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffLife != NULL)
	{
		g_pIdxBuffLife->Release();
		g_pIdxBuffLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{
	PLAYER pPlayer = *GetPlayer();

	CAMERA pCamera = *GetCamera();

	g_posLife = D3DXVECTOR3(pPlayer.pos.x, pPlayer.pos.y + 30.0f, pPlayer.pos.z);
	g_rotLife = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f + pPlayer.rot.y, 0.0f);

	float fCol = 0.0f;

	fCol += 0.01f;

	float fCol2 = 1.0f;

	fCol2 -= 0.01f;

	//if (GetKeyboardTrigger(DIK_I) == true )
	//{	
	//	HitDamage(-100);
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldLife);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxrot,
		g_rotLife.y, g_rotLife.x, g_rotLife.z);

	D3DXMatrixMultiply(&g_mtxWorldLife, &g_mtxWorldLife, &mtxrot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxtrans,
		g_posLife.x, g_posLife.y, g_posLife.z);

	D3DXMatrixMultiply(&g_mtxWorldLife, &g_mtxWorldLife, &mtxtrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldLife);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffLife);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, 0);

	// ���b�V���V�����_�[�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, LIFE_VERTEX, 0, LIFE_POLYGON + g_nLife);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
//���C�t����
//=============================================================================
void HitDamage(int nDamage)
{
	PLAYER *pPlayer = GetPlayer();
	DIED *pDied = GetDied();
	CHARACTER_TYPE pCharaType = GetCharaType();		// �I���L�����N�^�[���̎擾


		

		if (g_nLifeNum >= g_nMaxLifeNum)
		{
			g_nLifeNum = g_nMaxLifeNum;
		}

		if (g_nLife >= g_nMax_Life)
		{
			g_nLife = g_nMax_Life;
		}


	if (pPlayer->status == PLAYERSTATUS_NORMAL)
	{
		g_nLife += nDamage * 2;
		g_nLifeNum += nDamage;
		pPlayer->nCntCoolDown = 2;
		pPlayer->status = PLAYERSTATUS_DAMAGE;

		if (nDamage <= 0)
		{
			for (int nCnt = 0; nCnt < 3; nCnt++)
			{
				SetParticle(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, pPlayer->pos.z), 60, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), PARTICLETYPE_EXPLOSION);
			}
		}
		if (nDamage >= 0)
		{
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				SetParticle(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, pPlayer->pos.z), 60, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), PARTICLETYPE_EXPLOSION);
			}
		}
	}
	if (g_nLifeNum <= 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++, pDied++)
		{
			pDied->bUse = true;
		}
		pPlayer->status = PLAYERSTATUS_DEAD;
		SetPlayerState(PLAYERSTATE_DEATH);
		g_nLifeNum = 0;
		SetGameState(GAMESTATE_GAMEOVER);
	}

}
//=============================================================================
// �ő�Hp����
//=============================================================================
void DecreaseMaxLife(int nLife)
{
	g_nMaxLifeNum += nLife;
	g_nMax_Life   += (nLife * 2);

	if (g_nLifeNum >= g_nMaxLifeNum)
	{
		g_nLifeNum = g_nMaxLifeNum;
	}

	if (g_nLife >= g_nMax_Life)
	{
		g_nLife = g_nMax_Life;
	}
}



//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * LIFE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI / g_Life_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_Life_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_Life_h + 1; nCntLife_H++)
		{
			if (nCntLife_V == 0)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * LIFE_RADIUS;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.y = 1.0f;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * LIFE_RADIUS;
				//�@���̐ݒ�
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_Life_h / 2)), nCntLife_V * -1.0f);

				fDestAngle += fAngle;
			}
			if (nCntLife_V == 1)
			{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * (LIFE_RADIUS - LIFE_RADIUS2);
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.y = 1.0f;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * (LIFE_RADIUS - LIFE_RADIUS2);
				//�@���̐ݒ�
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);

				//�e�N�X�`�����W
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_Life_h / 2)), nCntLife_V * -1.0f);

				fDestAngle += fAngle;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// �C���f�b�N�X���̍쐬
//=============================================================================
void MakeIndexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * LIFE_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffLife,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffLife->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIndex_V = 0; nCntIndex_V < g_Life_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_Life_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_Life_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_Life_h && nCntIndex_V <= g_Life_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_Life_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffLife->Unlock();
}