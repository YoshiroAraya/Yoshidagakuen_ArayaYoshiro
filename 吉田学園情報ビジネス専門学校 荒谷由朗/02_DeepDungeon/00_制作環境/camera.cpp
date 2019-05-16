//=============================================================================
//
// �J�������� [camera.cpp]
// Author : TEAM_Fascinator
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "inputx.h"
#include "player.h"
#include "Wall1.h"
#include "SencerLock.h"
//=============================================================================
// �}�N����`
//============================================================================
#define CAMERA_SPEED	(0.025f)		// �ړ����x

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CAMERA		g_camera;			// �J�����̏��
JoyState	g_JoyStateCamera;	// �W���C�p�b�h�̏��
float fposR;
//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	PLAYER *g_aModel = GetPlayer();

	g_JoyStateCamera.nJoypadState = INPUT_JOYSTATE_NOTPUSH;

	g_camera.posV = D3DXVECTOR3(0.0f, 90.0f, -150.0f);	//���_
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����_
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.fLength = g_camera.posV.z - g_camera.posR.z;
	fposR = 0.0f;
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
	JoyState pJoystate = GetJoystate();
	PLAYER *pPlayer = GetPlayer();

	XINPUT_STATE state;
	XInputGetState(0, &state);

	g_camera.posVOld = g_camera.posV;

	if (GetKeyboardPress(DIK_RIGHT) == true || (state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true))
	{//���_���v����
		g_camera.rot.y += CAMERA_SPEED;
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) *-130.0f;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -130.0f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true || (state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true))
	{//���_�����v���
		g_camera.rot.y -= CAMERA_SPEED;
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -130.0f;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -130.0f;
	}
	/*if (GetKeyboardPress(DIK_UP) == true || (state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true))
	{
		fposR += 0.5f;
	}

	else if (GetKeyboardPress(DIK_DOWN) == true || (state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true))
	{
		fposR -= 0.5f;
	}*/
	if (GetKeyboardPress(DIK_M) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB && pJoystate.bConnectionJoypad == true))
	{//�J�������v���C���[�̉�]�ɍ��킹��
		if (g_JoyStateCamera.nJoypadState == INPUT_JOYSTATE_NOTPUSH)
		{//�A�Ŗh�~
			g_camera.rot.y = pPlayer->rot.y + (-1.0f * D3DX_PI);
		}
		g_JoyStateCamera.nJoypadState = INPUT_JOYSTATE_PUSH;
	}
	//else  if (state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true)
	//{
	//	g_camera.posV.y += 5.0f;
	//}
	//else if (state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pJoystate.bConnectionJoypad == true)
	//{
	//	g_camera.posV.y -= 5.0f;
	//}

	//���_�E�����_�̍X�V
	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * -130.0f;
	g_camera.posVDest.y = g_camera.posV.y ;
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * -130.0f;

	g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 1.0f;
	g_camera.posRDest.y = pPlayer->pos.y - sinf(pPlayer->rot.y) * 1.0f ;
	g_camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 1.0f;

	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.5f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.5f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.5f;

	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.3f;
	g_camera.posR.y = pPlayer->pos.y + 50.0f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.3f;

	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	 
	if (fposR > 1.5f)
	{
		fposR = 1.5f;
	}
	if (fposR < -1.5f)
	{
		fposR = -1.5f;
	}
	//CollisionWall(&g_camera.posV, &g_camera.posVOld, &g_camera.rot, 6.0f);

	//�W���C�p�b�h�̏�ԍX�V
	if (g_JoyStateCamera.nJoypadState == INPUT_JOYSTATE_PUSH)
	{
		g_JoyStateCamera.nJoypadState = INPUT_JOYSTATE_NONE;
	}
	else if (g_JoyStateCamera.nJoypadState == INPUT_JOYSTATE_NONE)
	{
		g_JoyStateCamera.nJoypadState = INPUT_JOYSTATE_NOTPUSH;
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera;
}

