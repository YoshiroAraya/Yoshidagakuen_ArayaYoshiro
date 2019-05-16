//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "light.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LIGHT	(3)		// �ݒu���郉�C�g�̐�

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
D3DLIGHT9 g_alight[MAX_LIGHT];	// ���C�g�̏��

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT] =
	{
		{ D3DXVECTOR3(0.22f, -0.87f, 0.44f) },
		{ D3DXVECTOR3(-0.18f, 0.88f, -0.44f) },
		{ D3DXVECTOR3(0.89f, -0.11f, 0.44f) },
	};	// �ݒ�p�����x�N�g��

	//===========================================================
	// ���C�g���N���A����
	ZeroMemory(&g_alight, sizeof(D3DLIGHT9));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g�̎�ނ�ݒ�
		g_alight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		//g_alight[0].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f);
		//g_alight[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 0.0f);
		//g_alight[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 0.0f);

		g_alight[0].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.0f);
		g_alight[1].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.0f);
		g_alight[2].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 0.0f);

		// ���C�g�̕����̐ݒ�
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);		// ���K������
		g_alight[nCntLight].Direction = vecDir[nCntLight];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_alight[nCntLight]);

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

