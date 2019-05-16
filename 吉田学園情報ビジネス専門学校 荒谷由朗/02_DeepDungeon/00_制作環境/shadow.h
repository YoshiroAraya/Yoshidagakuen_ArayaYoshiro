//=============================================================================
//
// �e���� [shadow.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// �e�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorldShadow;	// ���[���h�}�g���b�N�X
	float fWidth;				// ��
	float fDepth;				// ���s
	bool bUse;
}SHADOW;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void DeletShadow(int nIdxShadow);

#endif
