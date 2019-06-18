//=============================================================================
//
// �u���b�N���� [block.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	BlockType_NORMAL = 0,
	BlockType_DELETE,
	BlockType_MAX
}BlockType;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float		fWidth;		// ��
	float		fHeight;	// ����
	bool		bUse;		// �g�p���Ă��邩�ǂ���
	BlockType	type;		// �u���b�N�̏��
}Block;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBlock				(void);
void UninitBlock			(void);
void UpdateBlock			(void);
void DrawBlock				(void);
void SetBlock				(D3DXVECTOR3 pos, float fWidth, float fHeight, BlockType type);
bool CollisionBlock			(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool CollisionBlock_Bullet	(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
#endif
