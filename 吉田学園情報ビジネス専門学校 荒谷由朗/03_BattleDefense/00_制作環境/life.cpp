//=============================================================================
//
// ���C�t�Q�[�W���� [life.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "life.h"
#include "input.h"
#include "camera.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LIFE_VERTEX				((g_Life_h + 1) * (g_Life_v + 1))
#define LIFE_INDEX				( (g_Life_h * g_Life_v )* 2 + (4 * (g_Life_v - 1)) + 2 )
#define LIFE_POLYGON			( (g_Life_h * g_Life_v) * 2 + (4 * (g_Life_v - 1)) )
#define LIFE_RADIUS				(1000.0f)													// �~(�O��)�̔��a
#define LIFE_RADIUS2			(100.0f)													// �~(����)�̔��a
#define LIFE_HEIGHT				(600.0f)
#define LIFE_H					(100)														// ���b�V���̕�����(H)
#define LIFE_V					(1)															// ���b�V���̕�����(V)
#define MESHCYLINDER_TEXTURE	"data/TEXTURE/WallClinder.png"								// �ǂݍ��ރe�N�X�`��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexLife	(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexLife	(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffLife = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXMATRIX				g_mtxWorldLife;				// ���[���h�}�g���b�N�X
LIFE g_Life;
int g_nLife;
int g_Life_h, g_Life_v;

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_Life_h = LIFE_H;
	g_Life_v = LIFE_V;

	int Polygon = (g_Life_h * g_Life_v) * 2 + (4 * (g_Life_v - 1));
	g_nLife		= 0;

	MakeVertexLife	(pDevice);
	MakeIndexLife	(pDevice);

	// �v���C���[�̎擾
	Player pPlayer;
	pPlayer = *GetPlayer();

	g_Life.pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Life.rot		= D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
	g_Life.RADIUS	= LIFE_RADIUS;
	g_Life.bUse		= false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	// �e�N�X�`���̔j��
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
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX			mtxrot, mtxtrans;


	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldLife);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxrot,
		g_Life.rot.y, g_Life.rot.x, g_Life.rot.z);

	D3DXMatrixMultiply(&g_mtxWorldLife, &g_mtxWorldLife, &mtxrot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxtrans,
		g_Life.pos.x, g_Life.pos.y, g_Life.pos.z);

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
	pDevice->SetTexture(0, g_pTextureLife);

	// ���b�V���V�����_�[�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, LIFE_VERTEX, 0, LIFE_POLYGON + g_nLife);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
LIFE *GetLife(void)
{
	return &g_Life;
}

//=============================================================================
// ���C�t����
//=============================================================================
void HitDamage(int nDamage)
{
	g_nLife += nDamage;
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEXTURE, &g_pTextureLife);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * LIFE_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = D3DX_PI * 2 / g_Life_h;
	float fDestAngle;
	for (int nCntLife_V = 0; nCntLife_V < g_Life_v + 1; nCntLife_V++)
	{
		fDestAngle = 0.0f;
		for (int nCntLife_H = 0; nCntLife_H < g_Life_h + 1; nCntLife_H++)
		{
				if (fDestAngle >= D3DX_PI)
				{
					fDestAngle -= D3DX_PI * 2;
				}
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.x = -sinf(fDestAngle) * LIFE_RADIUS;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.y = nCntLife_V * LIFE_HEIGHT;
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].pos.z = cosf(fDestAngle) * LIFE_RADIUS;

				// �@���̐ݒ�
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].nor = D3DXVECTOR3(sinf(fDestAngle), 0.0f, cosf(fDestAngle));

				// ���_�J���[
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W
				pVtx[nCntLife_V * (g_Life_h + 1) + nCntLife_H].tex = D3DXVECTOR2(nCntLife_H * (1.0f / (g_Life_h / 2)), nCntLife_V * -1.0f);

				fDestAngle += fAngle;
				g_Life.nHeight = nCntLife_V * LIFE_HEIGHT;
		}
	}
	// ���_�o�b�t�@���A�����b�N
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

	int nCntIndex = 0;	// �C���f�b�N�X�̃J�E���g

	// �C���f�b�N�X�o�b�t�@�����b�N
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
	// ���_�o�b�t�@���A�����b�N
	g_pIdxBuffLife->Unlock();
}

bool CollisionClinder(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMin, D3DXVECTOR3 *pVtxMax)
{
	bool bCollision = false;

	Player *g_aPlayer;
	//�v���C���[�̎擾
	g_aPlayer = GetPlayer();

	g_Life.fAngle = g_aPlayer->pos - g_Life.pos;
	g_Life.nAngle = (g_Life.fAngle.x * g_Life.fAngle.x) + (g_Life.fAngle.z * g_Life.fAngle.z);

	if (g_Life.nAngle > (LIFE_RADIUS * LIFE_RADIUS))
	{
		float fAngle;

		fAngle= atan2f(g_aPlayer->pos.x, g_aPlayer->pos.z);

		g_aPlayer->pos = D3DXVECTOR3(sinf(fAngle) * LIFE_RADIUS, g_aPlayer->pos.y,cosf(fAngle) * LIFE_RADIUS);
	}

	return bCollision;
}

double Norm(double *vec, int nCntDimensions)
{
	double sVecNorm = 0.0;

	for (int i = 0; i < nCntDimensions; i++)
	{
		sVecNorm += vec[i] * vec[i];
	}

	return sqrt(sVecNorm);
}