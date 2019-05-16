//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.h]
// Author : komatsu keisuke
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//=============================================================================
// ���b�V���t�B�[���h�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorldMeshField;	//���[���h�}�g���b�N�X
	int nNumIndexMeshField;			//�C���f�b�N�X��
	int nNumPolygonMeshField;		//�|���S����
	float fDepth;					//���s��
	float fWidth;					//��
}MeshField;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
