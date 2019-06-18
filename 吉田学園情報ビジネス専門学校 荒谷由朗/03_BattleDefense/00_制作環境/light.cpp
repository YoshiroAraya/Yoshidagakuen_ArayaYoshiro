//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �r�J �R�N
//
//=============================================================================
#include "light.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LIGHT		(6)			// ���C�g�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
D3DLIGHT9 g_light[MAX_LIGHT];		// ���C�g�̏��

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3			vecDir0;
	D3DXVECTOR3			vecDir1;
	D3DXVECTOR3			vecDir2;
	D3DXVECTOR3			vecDir3;
	D3DXVECTOR3			vecDir4;
	D3DXVECTOR3			vecDir5;

	// ���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;
	g_light[3].Type = D3DLIGHT_DIRECTIONAL;
	g_light[4].Type = D3DLIGHT_DIRECTIONAL;
	g_light[5].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[3].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[4].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_light[5].Diffuse = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir0 = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	vecDir1 = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vecDir2 = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vecDir3 = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	vecDir4 = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	vecDir5 = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	D3DXVec3Normalize(&vecDir0, &vecDir0);		// ���K���ɂ���
	D3DXVec3Normalize(&vecDir1, &vecDir1);		// ���K���ɂ���
	D3DXVec3Normalize(&vecDir2, &vecDir2);		// ���K���ɂ���
	D3DXVec3Normalize(&vecDir3, &vecDir3);		// ���K���ɂ���
	D3DXVec3Normalize(&vecDir4, &vecDir4);		// ���K���ɂ���
	D3DXVec3Normalize(&vecDir5, &vecDir5);		// ���K���ɂ���

	g_light[0].Direction = vecDir0;
	g_light[1].Direction = vecDir1;
	g_light[2].Direction = vecDir2;
	g_light[3].Direction = vecDir3;
	g_light[4].Direction = vecDir4;
	g_light[5].Direction = vecDir5;

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}