//=============================================================================
//
// �Q�[������ [game.h]
// Author :	�r�J�R�N
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "block.h"
#include "enemy.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,			//�������Ă��Ȃ����
	GAMESTATE_NORMAL,			//�ʏ���
	GAMESTATE_CLEAR,
	GAMESTATE_OVER,
	GAMESTATE_MAX
}GAMESTATE;
//=============================================================================
// �G���̍\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	float fWidth;					//��
	float fHeight;					//����
	EnemyType type;
	float move_bullet;
}EnemyInfo;

//=============================================================================
// �u���b�N���̍\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	float fWidth;					//��
	float fHeight;					//����
	BlockType type;
}BlockInfo;
//=============================================================================
// �R�C�����̍\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	float fWidth;					//��
	float fHeight;					//����
}CoinInfo;
//=============================================================================
// �A�C�e�����̍\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 move;
	float fWidth;					//��
	float fHeight;					//����
	float fHorLimit;
}ItemInfo;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameStateNow(void);
void SetPauseState(bool bPause);

#endif // _GAME_H_
