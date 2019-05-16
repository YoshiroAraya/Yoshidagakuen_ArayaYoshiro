//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �r�J�R�N
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera;	//�J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//Player *g_aEnemy;
	////�v���C���[�̎擾
	//g_aEnemy = GetPlayer();
	//g_Camera.posV = g_aEnemy->pos + D3DXVECTOR3(0.0f,100.0f,-200.0f);		//���_
	//g_Camera.posR = g_aEnemy->pos;											//�����_
	//g_Camera.vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);									//������x�N�g��
	//g_Camera.CameraMove = 0;														//�ړ���
	//g_Camera.CameraDistance = -g_Camera.posV.z;										//����
	//g_Camera.CameraTimer = 0;
	g_Camera.posV = D3DXVECTOR3(0.0f, 120, -300);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fAngle = 0.0f;
	g_Camera.fLength = g_Camera.posV.z - g_Camera.posR.z;
	g_Camera.nCounterAngle = 0.0f;
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
	////�J�����ړ�(WSAD)
	//if (GetKeyboardPress(DIK_UP))
	//{//��
	//	g_Camera.posV.x += sinf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;
	//	g_Camera.posV.z += cosf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_DOWN))
	//{//��
	//	g_Camera.posV.x -= sinf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;
	//	g_Camera.posV.z -= cosf(D3DX_PI*0.0f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) *g_Camera.CameraDistance;
	//}
	//if (GetKeyboardPress(DIK_RIGHT))
	//{//��
	//	g_Camera.posV.x += sinf(D3DX_PI*0.5f + g_Camera.CameraMove) * 2.0f;
	//	g_Camera.posV.z += cosf(D3DX_PI*0.5f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_LEFT))
	//{//�E
	//	g_Camera.posV.x -= sinf(D3DX_PI*0.5f + g_Camera.CameraMove) * 2.0f;
	//	g_Camera.posV.z -= cosf(D3DX_PI*0.5f + g_Camera.CameraMove)*2.0f;

	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) *g_Camera.CameraDistance;
	//}
	//���_����(YNZC)
	//if (GetKeyboardPress(DIK_Y))
	//{//��
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posV.y = g_Camera.posR.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_N))
	//{//��
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posV.y = g_Camera.posR.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//if (GetKeyboardPress(DIK_Z) == true)
	//{//��
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{//�E
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	////�����_����(TBQE)
	//if (GetKeyboardPress(DIK_T))
	//{//��
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posR.y = g_Camera.posV.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_B))
	//{//��
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posR.y = g_Camera.posV.y + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//if (GetKeyboardPress(DIK_Q))
	//{//��
	//	g_Camera.CameraMove -= 0.1f;
	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}
	//else if (GetKeyboardPress(DIK_E))
	//{//�E
	//	g_Camera.CameraMove += 0.1f;
	//	g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//	g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.CameraMove) * g_Camera.CameraDistance;
	//}

	Player *pPlayer;
	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	////�J�����̒Ǐ]
	//g_Camera.posR = g_aEnemy->pos;
	//g_Camera.posV = D3DXVECTOR3(sinf(g_Camera.CameraMove) * g_Camera.CameraDistance + g_Camera.posR.x, g_Camera.posV.y, cosf(g_Camera.CameraMove) * g_Camera.CameraDistance + g_Camera.posR.z);

	//���݂̃��[�h���擾
	MODE Mode = GetMode();

	switch (Mode)
	{
	case MODE_GAME:
		////���_����L�[�������ꂽ�ꍇ
		//if (GetKeyboardPress(DIK_Z) == true)
		//{	// Z�ō�����
		//	g_Camera.rot.y += 0.02f;
		//	g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
		//	g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
		//	if (g_Camera.rot.y > D3DX_PI)
		//	{
		//		g_Camera.fAngle -= D3DX_PI * 2.0f;
		//	}
		//}
		//if (GetKeyboardPress(DIK_C) == true)
		//{	// C�ŉE����
		//	g_Camera.rot.y -= 0.02f;
		//	g_Camera.posV.x = g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
		//	g_Camera.posV.z = g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
		//	if (g_Camera.rot.y < -D3DX_PI)
		//	{
		//		g_Camera.fAngle += D3DX_PI * 2.0f;
		//	}
		//}

		/*g_Camera.posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.x) * 80, pPlayer->pos.y, pPlayer->pos.z + cosf(pPlayer->rot.z) * 80);
		g_Camera.posVDest = D3DXVECTOR3(pPlayer->pos.x + sinf(g_Camera.fAngle) * g_Camera.fLength, pPlayer->pos.y, pPlayer->pos.z + cosf(g_Camera.fAngle) * g_Camera.fLength);*/

		/*g_Camera.posR += (g_Camera.posRDest - g_Camera.posR) * 0.2f;
		g_Camera.posV += (g_Camera.posVDest - g_Camera.posV) * 0.2f;*/

		/*g_Camera.rotDest = D3DXVECTOR3(g_Camera.rot.x, g_Camera.rot.y + sinf(pPlayer->rot.y + g_Camera.rot.y) * g_Camera.fLength, g_Camera.rot.z);
		g_Camera.rot += (g_Camera.rotDest - g_Camera.rot) * 0.2f;*/

		//�J�����̒Ǐ]
		g_Camera.posR = pPlayer->pos + D3DXVECTOR3(0.0f,50.0f,0.0f);
		g_Camera.posV = D3DXVECTOR3(sinf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.x, g_Camera.posR.y, cosf(g_Camera.rot.y) * g_Camera.fLength + g_Camera.posR.z);

		//�v���C���[�̌��ɂ���
		g_Camera.rotDest.y = (pPlayer->rot.y + D3DX_PI);
		g_Camera.DiffAngle.y = g_Camera.rotDest.y - g_Camera.rot.y;

		//�p�x�̐ݒ�
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
		//�J�E���^�[�̉��Z
		g_Camera.nCounterAngle++;

		if (g_Camera.nCounterAngle < 300)
		{
			g_Camera.posV = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
			g_Camera.posR = D3DXVECTOR3(500.0f, 0.0f, -600.0f);
		}
		/*if (g_Camera.nCounterAngle == 300)
		{
		g_Camera.posV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		}
		if (g_Camera.nCounterAngle == 600)
		{
		g_Camera.posV = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		g_Camera.fLength = 200;
		}
		if (g_Camera.nCounterAngle == 900)
		{
		g_Camera.nCounterAngle = 0;
		}
		if (g_Camera.nCounterAngle < 300)
		{
		g_Camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
		}*/

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
		D3DXToRadian(45.0f),								//��p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//��ʔ䗦
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

Camera *GetCamera(void)
{
	return &g_Camera;
}