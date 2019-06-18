//=============================================================================
//
// �Z���T�[���� [Sencer.cpp]
//�@Coment: �v���C���[�A�G�l�~�[�ɂ������Ă��铖���蔻��
// Author : KishidaRei 
//
//=============================================================================
#include "SencerCol.h"
#include "input.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "enemy0.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "enemy5.h"
#include "enemy6.h"
#include "enemy7.h"
#include "enemy8.h"

#include "enemy_arrow.h"
#include "player.h"
#include "life.h"
#include "boss.h"
#include "sound.h"
#include "enemy_axe.h"
#include "enemy_axe2.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SENCERCOLLSION (50)
#define MAX_TEXTURE (2)

#define SENCERCOLLISION_VERTEX (  (g_SencerCollision_h + 1) * (g_SencerCollision_v + 1)   )	//���_��
#define SENCERCOLLISION_INDEX (   (g_SencerCollision_h * g_SencerCollision_v )* 2 + (4 * (g_SencerCollision_v - 1)) + 2   ) //�C���f�b�N�X��
#define SENCERCOLLISION_POLYGON ( (g_SencerCollision_h * g_SencerCollision_v) * 2 + (4 * (g_SencerCollision_v - 1)) )	//�|���S����

#define SENCERCOL_RADIUS (35.0f)
#define SENCERCOL_HEIGHT (80.0f)

#define MESH_H (20) //���b�V���̕�����(H)
#define MESH_V (1) //���b�V���̕�����(V)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSencerCollision(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSencerCollision(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSencerCollision = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSencerCollision = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSencerCollision = NULL; //�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

SENCERCOLLISION g_aSencerCollision[MAX_SENCERCOLLSION];

int g_SencerCollision_h, g_SencerCollision_v;
//=============================================================================
// ����������
//=============================================================================
void InitSencerCollision(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_SencerCollision_h = MESH_H;
	g_SencerCollision_v = MESH_V;


	MakeVertexSencerCollision(pDevice);
	MakeIndexSencerCollision(pDevice);

	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{
		g_aSencerCollision[nCntSencer].fRadius = SENCERCOL_RADIUS;
		g_aSencerCollision[nCntSencer].bUse = false;
	}




}

//=============================================================================
// �I������
//=============================================================================
void UninitSencerCollision(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureSencerCollision != NULL)
	{
		g_pTextureSencerCollision->Release();
		g_pTextureSencerCollision = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSencerCollision != NULL)
	{
		g_pVtxBuffSencerCollision->Release();
		g_pVtxBuffSencerCollision = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffSencerCollision != NULL)
	{
		g_pIdxBuffSencerCollision->Release();
		g_pIdxBuffSencerCollision = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSencerCollision(void)
{
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSencerCollision(void)
{
#if 1
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxrot, mtxtrans;


	
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O

	

	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{
		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSencerCollision[nCntSencer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				g_aSencerCollision[nCntSencer].rot.y, g_aSencerCollision[nCntSencer].rot.x, g_aSencerCollision[nCntSencer].rot.z);

			D3DXMatrixMultiply(&g_aSencerCollision[nCntSencer].mtxWorld, &g_aSencerCollision[nCntSencer].mtxWorld, &mtxrot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxtrans,
				g_aSencerCollision[nCntSencer].pos.x, g_aSencerCollision[nCntSencer].pos.y, g_aSencerCollision[nCntSencer].pos.z);

			D3DXMatrixMultiply(&g_aSencerCollision[nCntSencer].mtxWorld, &g_aSencerCollision[nCntSencer].mtxWorld, &mtxtrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSencerCollision[nCntSencer].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSencerCollision, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSencerCollision);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			//pDevice->SetFVF(D3DXGetFVFVertexSize);
			pDevice->SetTexture(0, 0);


			// ���b�V���V�����_�[�̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SENCERCOLLISION_VERTEX, 0, SENCERCOLLISION_POLYGON);

		}
	}


#endif
}

void SetPositionSencerCollision(int nIdxSencer, D3DXVECTOR3 pos)
{	
		g_aSencerCollision[nIdxSencer].pos = pos;
}

void DeleteSencerCol(int nIdxSencerCol)
{
	g_aSencerCollision[nIdxSencerCol].bUse = false;
}
//
////=============================================================================
//// ���_���̍쐬
////=============================================================================
void MakeVertexSencerCollision(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gg.jpg", &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SENCERCOLLISION_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSencerCollision,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSencerCollision->Lock(0, 0, (void**)&pVtx, 0);
	float fAngle = D3DX_PI * 2 / g_SencerCollision_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_SencerCollision_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_SencerCollision_h + 1; nCntLife_H++)
		{

			if (fDestAngle >= D3DX_PI)
			{
				fDestAngle -= D3DX_PI * 2;
			}
			pVtx[nCntLife_V * (g_SencerCollision_h + 1) + nCntLife_H].pos.x = sinf(fDestAngle) * SENCERCOL_RADIUS;
			pVtx[nCntLife_V * (g_SencerCollision_h + 1) + nCntLife_H].pos.y = SENCERCOL_HEIGHT * nCntLife_V;
			pVtx[nCntLife_V * (g_SencerCollision_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * SENCERCOL_RADIUS;
			//�@���̐ݒ�
			pVtx[nCntLife_V * (g_SencerCollision_h + 1) + nCntLife_H].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[nCntLife_V * (g_SencerCollision_h + 1) + nCntLife_H].col = D3DXCOLOR(1.0f, 0.0, 0.0f, 0.3f);

			//�e�N�X�`�����W
			pVtx[nCntLife_V * (g_SencerCollision_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_SencerCollision_h / 2)), nCntLife_V * -1.0f);

			fDestAngle += fAngle;
		}


	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSencerCollision->Unlock();


}

////=============================================================================
//// �C���f�b�N�X���쐬
////=============================================================================
void MakeIndexSencerCollision(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * SENCERCOLLISION_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSencerCollision,
		NULL);

	WORD *pIdx;

	int nCntIndex = 0;	//�C���f�b�N�X�̃J�E���g

						//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffSencerCollision->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIndex_V = 0; nCntIndex_V < g_SencerCollision_v; nCntIndex_V++)
	{
		for (int nCntIndex_H = 0; nCntIndex_H <= g_SencerCollision_h; nCntIndex_H++, nCntIndex++)
		{
			pIdx[0] = (g_SencerCollision_h + 1) + nCntIndex;
			pIdx[1] = nCntIndex;

			pIdx += 2;

			if (nCntIndex == g_SencerCollision_h && nCntIndex_V <= g_SencerCollision_v)
			{
				pIdx[0] = nCntIndex;
				pIdx[1] = (g_SencerCollision_h + 1) + nCntIndex + 1;

				pIdx += 2;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pIdxBuffSencerCollision->Unlock();

}


//=============================================================================
// �V�����_�[�쐬
//=============================================================================
int SetSencerCollision(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SENCERCOLTYPE type)
{
	int nCntSencer;
	// ���_���̐ݒ�

	for ( nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{
		if (g_aSencerCollision[nCntSencer].bUse == false)
		{
			g_aSencerCollision[nCntSencer].pos = pos;
			g_aSencerCollision[nCntSencer].rot = rot;
			g_aSencerCollision[nCntSencer].type = type;
			g_aSencerCollision[nCntSencer].bUse = true;

			break;
		}
	}

	return nCntSencer;
}

//=============================================================================
// �Z���T�[����
//=============================================================================
bool CollisionSencer_Col(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold)
{
	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{
		

		fxpos = (g_aSencerCollision[nCntSencer].pos.x - pos->x) * (g_aSencerCollision[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerCollision[nCntSencer].pos.z - pos->z) * (g_aSencerCollision[nCntSencer].pos.z - pos->z);
		fRadius = SENCERCOL_RADIUS * SENCERCOL_RADIUS;


		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY || g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_ARROW
					|| g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
				{
					bCol = true;
					pos->x = posold->x;
					pos->z = posold->z;

				}
			}

		}
	}
#if  0
#endif
	return bCol;
}

//=============================================================================
// ���@�Ƃ̓����蔻��(�ʏ펞)
//=============================================================================
bool CollisionSencer_Magic(D3DXVECTOR3 * pos, int nCntEnemy)
{
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{


		fxpos = (g_aSencerCollision[nCntSencer].pos.x - pos->x) * (g_aSencerCollision[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerCollision[nCntSencer].pos.z - pos->z) * (g_aSencerCollision[nCntSencer].pos.z - pos->z);
		fRadius = SENCERCOL_RADIUS * SENCERCOL_RADIUS;


		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY)
				{
					bCol = true;
					HitEnemy(-10, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}


				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY0)
				{
					bCol = true;
					HitEnemy_0(-10, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY1)
				{
					bCol = true;
					HitEnemy_1(-10, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY2)
				{
					bCol = true;
					HitEnemy_2(-10, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}


				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
				{
					bCol = true;
					HitEnemyAxe(-12, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE2)
				{
					bCol = true;
					HitEnemyAxe2(-12, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_ARROW)
				{
					bCol = true;
					HitEnemyArrow(-12, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_BOSS)
				{
					bCol = true;
					HitEnemy(-3, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
			}

		}
	}
	return bCol;
}

//=============================================================================
// ���@�Ƃ̓����蔻��(ᏋC)
//=============================================================================
bool CollisionSencer_L_Magic(D3DXVECTOR3 * pos, int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();


	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{


		fxpos = (g_aSencerCollision[nCntSencer].pos.x - pos->x) * (g_aSencerCollision[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerCollision[nCntSencer].pos.z - pos->z) * (g_aSencerCollision[nCntSencer].pos.z - pos->z);
		fRadius = SENCERCOL_RADIUS * SENCERCOL_RADIUS;


		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY)
				{
					bCol = true;
					HitEnemyAxe(-pPlayer->nCntCharge, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}

				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY0)
				{
					bCol = true;
					HitEnemy_0(-pPlayer->nCntCharge, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY1)
				{
					bCol = true;
					HitEnemy_1(-pPlayer->nCntCharge, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY2)
				{
					bCol = true;
					HitEnemy_2(-pPlayer->nCntCharge, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
				{
					bCol = true;
					HitEnemyAxe(-pPlayer->nCntCharge, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE2)
				{
					bCol = true;
					HitEnemyAxe2(-pPlayer->nCntCharge, nCntEnemy);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
			}

		}
	}
	return bCol;
}


//=============================================================================
// ���@�Ƃ̓����蔻��(boss�Ƃ̓����蔻��)(�ʏ펞)
//=============================================================================
bool CollisionSencer_Magic_Boss(D3DXVECTOR3 * pos)
{
	BOSS *pBoss;
	pBoss = GetBoss();

	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{


		fxpos = (g_aSencerCollision[nCntSencer].pos.x - pos->x) * (g_aSencerCollision[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerCollision[nCntSencer].pos.z - pos->z) * (g_aSencerCollision[nCntSencer].pos.z - pos->z);
		fRadius = SENCERCOL_RADIUS * SENCERCOL_RADIUS;


		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_BOSS)
				{
					bCol = true;
					HitBoss(-3);
					

				}
			}

		}
	}
	return bCol;
}

//=============================================================================
// ���@�Ƃ̓����蔻��(boss�Ƃ̓����蔻��)(Ꮜ���)
//=============================================================================
bool CollisionSencer_L_Magic_Boss(D3DXVECTOR3 * pos)
{
	PLAYER *pPlayer = GetPlayer();

	BOSS *pBoss;
	pBoss = GetBoss();

	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{


		fxpos = (g_aSencerCollision[nCntSencer].pos.x - pos->x) * (g_aSencerCollision[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerCollision[nCntSencer].pos.z - pos->z) * (g_aSencerCollision[nCntSencer].pos.z - pos->z);
		fRadius = SENCERCOL_RADIUS * SENCERCOL_RADIUS;


		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{

				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_BOSS)
				{
					bCol = true;
					HitBoss(-pPlayer->nCntCharge);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);

				}
			}

		}
	}
	return bCol;
}


//=============================================================================
// �Z���T�[����(Player->Enemy�ւ̍U������)(�ʏ펞)
//=============================================================================
bool CollisionAttackPlayer(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemy)
{
	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0 ;

	
	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY)
			{
				bCol = true;
				HitEnemy(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY0)
			{
				bCol = true;
				HitEnemy_0(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY1)
			{
				bCol = true;
				HitEnemy_1(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY2)
			{
				bCol = true;
				HitEnemy_2(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY3)
			{
				bCol = true;
				HitEnemy_3(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY4)
			{
				bCol = true;
				HitEnemy_4(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY5)
			{
				bCol = true;
				HitEnemy_5(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY6)
			{
				bCol = true;
				HitEnemy_6(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
			{
				bCol = true;
				HitEnemyAxe(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE2)
			{
				bCol = true;
				HitEnemyAxe2(-1, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT);
			}
		}
	}
	

	return bCol;
}
//=============================================================================
// �Z���T�[����(Player->Enemy�ւ̍U������)(�|)(�ʏ펞)
//=============================================================================
bool CollisionAttackPvA(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyArrow)
{
	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_ARROW)
			{
				bCol = true;
				HitEnemyArrow(-1, nCntEnemyArrow);
				PlaySound(SOUND_LABEL_SE_HIT);

			}


		}
	}


	return bCol;
}
//=============================================================================
// �Z���T�[����(Player->Enemy�ւ̍U������)(��)(�ʏ펞)
//=============================================================================
bool CollisionAttackAxe(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyAxe)
{
	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
			{
				bCol = true;
				HitEnemyArrow(-1, nCntEnemyAxe);
				PlaySound(SOUND_LABEL_SE_HIT);

			}

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE2)
			{
				bCol = true;
				HitEnemyAxe2(-1, nCntEnemyAxe);
				PlaySound(SOUND_LABEL_SE_HIT);

			}
		}
	}


	return bCol;
}


//=============================================================================
// �Z���T�[����(Player->Enemy�ւ̍U������)(Ꮜ�)
//=============================================================================
bool Collision_L_AttackPlayer(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY)
			{
				bCol = true;
				HitEnemy(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);

			}

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY0)
			{
				bCol = true;
				HitEnemy_0(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY1)
			{
				bCol = true;
				HitEnemy_1(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY2)
			{
				bCol = true;
				HitEnemy_2(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY3)
			{
				bCol = true;
				HitEnemy_3(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY4)
			{
				bCol = true;
				HitEnemy_4(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY5)
			{
				bCol = true;
				HitEnemy_5(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY6)
			{
				bCol = true;
				HitEnemy_6(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
			{
				bCol = true;
				HitEnemy(-pPlayer->nCntCharge, nCntEnemy);
				PlaySound(SOUND_LABEL_SE_HIT2);

			}
		}
	}


	return bCol;
}


//=============================================================================
// �Z���T�[����(Player->boss�ւ̍U������)(�ʏ펞)
//=============================================================================
bool CollisionAttackPvB(D3DXVECTOR3 pos, float fRadius, int nCntSencer)
{
	BOSS *pBoss;
	pBoss = GetBoss();


	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_BOSS)
			{
				bCol = true;
				HitBoss(-2);
				PlaySound(SOUND_LABEL_SE_HIT);

			}

		}
	}


	return bCol;
}


//=============================================================================
// �Z���T�[����(Player->boss�ւ̍U������)(Ꮜ���)
//=============================================================================
bool Collision_L_AttackPvB(D3DXVECTOR3 pos, float fRadius, int nCntSencer)
{
	BOSS *pBoss;
	pBoss = GetBoss();

	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_BOSS)
			{
				bCol = true;
				HitBoss(-pPlayer->nCntCharge);
				PlaySound(SOUND_LABEL_SE_HIT2);
			}

		}
	}


	return bCol;
}

bool Collision_L_AttackPvA(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyArrow)
{
	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_ARROW)
			{
				bCol = true;
				HitEnemyArrow(-pPlayer->nCntCharge, nCntEnemyArrow);
				PlaySound(SOUND_LABEL_SE_HIT2);

			}

		}
	}


	return bCol;
}

bool Collision_L_AttackAxe(D3DXVECTOR3 pos, float fRadius, int nCntSencer, int nCntEnemyAxe)
{
	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE)
			{
				bCol = true;
				HitEnemyArrow(-pPlayer->nCntCharge, nCntEnemyAxe);
				PlaySound(SOUND_LABEL_SE_HIT2);

			}
			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_ENEMY_AXE2)
			{
				bCol = true;
				HitEnemyAxe2(-pPlayer->nCntCharge, nCntEnemyAxe);
				PlaySound(SOUND_LABEL_SE_HIT2);

			}
		}
	}


	return bCol;
}


//=============================================================================
// �Z���T�[����(Enemy->Player�ւ̍U������)
//=============================================================================
bool CollisionAttackEnemy(D3DXVECTOR3 pos, float fRadius, int nCntSencer, SENCERCOLTYPE Type)
{
	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y);
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_PLAYER && pPlayer->status == PLAYERSTATUS_NORMAL)
			{
				bCol = true;
				if (Type == SENCERCOLTYPE_ENEMY)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}
				if (Type == SENCERCOLTYPE_ENEMY0)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}
				if (Type == SENCERCOLTYPE_ENEMY1)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}if (Type == SENCERCOLTYPE_ENEMY2)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}if (Type == SENCERCOLTYPE_ENEMY3)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}if (Type == SENCERCOLTYPE_ENEMY4)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}if (Type == SENCERCOLTYPE_ENEMY5)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}
				if (Type == SENCERCOLTYPE_ENEMY6)
				{
					HitDamage(-5);
					PlaySound(SOUND_LABEL_SE_HIT);

				}
				if (Type == SENCERCOLTYPE_ENEMY_AXE)
				{
						HitDamage(-10);
						PlaySound(SOUND_LABEL_SE_HIT2);

				}
				if (Type == SENCERCOLTYPE_ENEMY_AXE2)
				{
					HitDamage(-10);
					PlaySound(SOUND_LABEL_SE_HIT2);

				}
				if (Type == SENCERCOLTYPE_ENEMY_BOSS)
				{
					HitDamage(-15);
					PlaySound(SOUND_LABEL_SE_HIT3);

				}
			}

		}
	}


	return bCol;
}

//=============================================================================
// �Z���T�[����(Enemy->Player�ւ̍U������)  (�|)
//=============================================================================
bool CollisionAttackEnemyArrow(D3DXVECTOR3 *pos)
{
	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;
	float fxpos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fRadius = 0.0f;
	for (int nCntSencer = 0; nCntSencer < MAX_SENCERCOLLSION; nCntSencer++)
	{


		fxpos = (g_aSencerCollision[nCntSencer].pos.x - pos->x) * (g_aSencerCollision[nCntSencer].pos.x - pos->x);
		fzpos = (g_aSencerCollision[nCntSencer].pos.z - pos->z) * (g_aSencerCollision[nCntSencer].pos.z - pos->z);
		fRadius = SENCERCOL_RADIUS * SENCERCOL_RADIUS;


		if (g_aSencerCollision[nCntSencer].bUse == true)
		{
			if (fxpos + fzpos <= fRadius)
			{
				if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_PLAYER&& pPlayer->status == PLAYERSTATUS_NORMAL)
				{
					bCol = true;
					HitDamage(-10);
					PlaySound(SOUND_LABEL_SE_HIT3);


				}
			}

		}
	}
	return bCol;
}

bool CollisionAttackBoss(D3DXVECTOR3 pos, float fRadius, int nCntSencer, SENCERCOLTYPE Type)
{
	PLAYER *pPlayer = GetPlayer();

	bool bCol = false;

	float fxpos = 0.0f;
	float fypos = 0.0f;
	float fzpos = 0.0f;
	float fpos = 0.0f;
	float fLength = 0.0f;
	float fRadius0;


	if (g_aSencerCollision[nCntSencer].bUse == true)
	{

		fxpos = (pos.x - g_aSencerCollision[nCntSencer].pos.x) * (pos.x - g_aSencerCollision[nCntSencer].pos.x);
		fypos = (pos.y - g_aSencerCollision[nCntSencer].pos.y) * (pos.y - g_aSencerCollision[nCntSencer].pos.y)/2;
		fzpos = (pos.z - g_aSencerCollision[nCntSencer].pos.z) * (pos.z - g_aSencerCollision[nCntSencer].pos.z);
		fLength = fxpos + fypos + fzpos;
		fRadius0 = (SENCERCOL_RADIUS + fRadius) * (SENCERCOL_RADIUS + fRadius);

		if (fLength < fRadius0)
		{

			if (g_aSencerCollision[nCntSencer].type == SENCERCOLTYPE_PLAYER && pPlayer->status == PLAYERSTATUS_NORMAL)
			{
				bCol = true;
				
				
					HitDamage(-30);
				
			}

		}
	}


	return bCol;
}

