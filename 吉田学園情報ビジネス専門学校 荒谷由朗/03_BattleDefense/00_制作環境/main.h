//=============================================================================
//
// ���C������ [main.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <Xinput.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"
#include "xaudio2.h"					//�T�E���h�����ŕK�v

//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "xinput.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���

// 2�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / ���_�J���[ / �e�N�X�`�����W )
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 2�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`��
} VERTEX_3D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,
	MODE_TUTORIARU,
	MODE_GAME,
	MODE_RESULT,
	MODE_SCOER,
	MODE_MAX,
}MODE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif