//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// �v���C���[�̃A�j���[�V�����̏��
typedef enum
{
	PLAYER_STATE_NEUTRAL = 0,
	PLAYER_STATE_DEATH,
	PLAYER_STATE_DAMAGE,
	PLAYER_STATE_MAX
}PLAYER_STATE;

typedef enum
{
	PLAYER_MOSIONSTATE_NEUTRAL = 0,
	PLAYER_MOSIONSTATE_MOVE,
	PLAYER_MOSIONSTATE_UP,
	PLAYER_MOSIONSTATE_DOWN,
	PLAYER_MOSIONSTATE_TURNING_R,
	PLAYER_MOSIONSTATE_TURNING_L,
	PLAYER_MOSIONSTATE_AVOID_R,
	PLAYER_MOSIONSTATE_AVOID_L,
	PLAYER_MOSIONSTATE_MAX
}PLAYER_MOSIONSTATE;

// ���f���̍\����
typedef struct
{
	LPD3DXMESH pMash = NULL;
	LPD3DXBUFFER pBuffMat = NULL;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float nIdxModelParent = -1;	// �e���f���̃C���f�b�N�X
	char FileName[256];
}Model;

// �v���C���[�̍\����
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;					// ���݂̈ʒu
	D3DXVECTOR3 posOld;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXCOLOR	col;					// �F
	float rotDest;						// �ڕW�̌���
	float fAngle;						// ����
	D3DXVECTOR3 move;					// �ړ�
	D3DXVECTOR3 vtxMin;					// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;					// ���f���̍ő�l
	int nLife;							// ���C�t
	int nCunterState;
	int nCntFleam;
	int PlayerAnim;
	int	nNumParts = 0;
	int MAX_PARTS;						// �p�[�c�̍ő吔
	int nCntPlayermotion;				// ���[�V�����̔ԍ� 
	bool bUse;						//�g�p���Ă��邩�ǂ���
	Model aModel[256];					// �p�[�c
	PLAYER_STATE PlayerState;
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void SetPLAYER_STATE(PLAYER_STATE state);
void SetPLAYER_MOSIONSTATE(PLAYER_MOSIONSTATE state);
PLAYER_MOSIONSTATE GetPLAYER_MOSIONSTATENow(void);
Player *GetPlayer(void);

#endif
