//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
Camera g_Camera;	// �J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	g_Camera.posV			= D3DXVECTOR3(0.0f, 120, -300);
	g_Camera.posR			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posVDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU			= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot			= D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Camera.rotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.DiffAngle		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fAngle			= 0.0f;
	g_Camera.fLength		= g_Camera.posV.z - g_Camera.posR.z;
	g_Camera.nCounterAngle	= 0.0f;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	// �v���C���[�̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	// ���݂̃��[�h���擾
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:
		// �J�����̒Ǐ]
		g_Camera.posR = pPlayer->pos + D3DXVECTOR3(0.0f,50.0f,0.0f);
		g_Camera.posV = D3DXVECTOR3(sinf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.x, g_Camera.posR.y, cosf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.z);

		// �v���C���[�̌��ɂ���
		g_Camera.rotDest.y		= (pPlayer->rot.y + D3DX_PI);
		g_Camera.DiffAngle.y	= g_Camera.rotDest.y - g_Camera.rot.y;

		// �p�x�̐ݒ�
		if (g_Camera.DiffAngle.y > D3DX_PI)
		{
			g_Camera.DiffAngle.y -= D3DX_PI* 2.0f;
		}
		if (g_Camera.DiffAngle.y < -D3DX_PI)
		{
			g_Camera.DiffAngle.y += D3DX_PI* 2.0f;
		}

		g_Camera.rot.y += g_Camera.DiffAngle.y * 0.03f;

		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI* 2.0f;
		}
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI* 2.0f;
		}
		break;

	case MODE_TITLE:
		// �J�E���^�[�̉��Z
		g_Camera.nCounterAngle++;

		if (g_Camera.nCounterAngle < 300)
		{
			g_Camera.posV = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
			g_Camera.posR = D3DXVECTOR3(500.0f, 0.0f, -600.0f);
		}

		g_Camera.rot.y += 0.003f;
		// 3.14��������
		if (g_Camera.rot.y > D3DX_PI)
		{
			// 3.14�� -3.14�ɂ���
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}
		g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y + D3DX_PI)* g_Camera.fLength;
		g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y + D3DX_PI)* g_Camera.fLength;
		break;
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),								// ��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			// ��ʔ䗦
		10.0f,
		2000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
						&g_Camera.posV,
						&g_Camera.posR,
						&g_Camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera;
}