//=============================================================================
//
// �v���C���[���� [player.h]
// Author : TEAM_Fascinator
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//------------------------------------------------------------------------
// ���f���̍\����														  |
//------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMeshPlayerModel = NULL;
	LPD3DXBUFFER pBuffMatPlayerModel = NULL;
	DWORD nNumMatPlayerModel;
	D3DXMATRIX mtxWorldPlayerModel;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float nIdxModelParent = -1;		// �e���f���̃C���f�b�N�X
	char FileName[256];
}PLAYERMODEL;

//------------------------------------------------------------------------
// �����蔻��̍\����														  |
//------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorldCollision;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fRadius;
	int StartFlame;
	int EndFlame;
	bool bUse;
	int nCntMotion;
	int nIdxMotion;
	int nIdxParent;
}PLAYERCOLLISION;

typedef enum
{
	PLAYERSTATUS_NORMAL = 0,			// �j���[�g����
	PLAYERSTATUS_DAMAGE,					// �ړ�
	PLAYERSTATUS_DEAD,					// �ړ�
	PLAYERSTATUS_MAX
}PLAYERSTATUS;

//=============================================================================
// �v���C���[�̍\����
//=============================================================================
typedef struct
{
	D3DXMATRIX mtxWorldPlayer;
	D3DXVECTOR3 pos;					// ���݂̈ʒu
	D3DXVECTOR3 posOld;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	float rotDest;						// �ڕW�̌���
	float fAngle;						// ����
	float fMoveSpeed;					//�X�s�[�h
	float fSaveSpeed;
	D3DXVECTOR3 move;					// �ړ�
	D3DXVECTOR3 vtxMinModel;			// ���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;			// ���f���̍ő�l
	int PlayerAnim;
	int	nNumParts = 0;
	int MAX_PARTS;						// �p�[�c�̍ő吔
	int nIdxShadow;						// �e�̔ԍ�
	int nIdxSencer;						//�Z���T�[�̔ԍ�(�����蔻��p)
	int nIdxSencerLock;					//�Z���T�[�̔ԍ�(���b�N�p)
	int nCntMotionFlame;				//���[�V�����J�E���g
	int nCntCoolDown;
	int nCntCharge;
	PLAYERCOLLISION Collision;
	PLAYERMODEL aModel[256];			// �p�[�c
	PLAYERSTATUS status;
}PLAYER;

//------------------------------------------------------------------------
// �v���C���[�̏��															  |
//------------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NEUTRAL = 0,		// �j���[�g����
	PLAYERSTATE_MOVE,				// �ړ�
	PLAYERSTATE_ATTACK,				// �U��
	PLAYERSTATE_JAMP,				// �W�����v
	PLAYERSTATE_LANDING,			// ���n
	PLAYERSTATE_DAMAGE,				// �_���[�W
	PLAYERSTATE_DEATH,				// ���S
	PLAYERSTATE_MIASMA,				// ᏋC
	PLAYERSTATE_ORIGINAL,			// �I���W�i��
	PLAYERSTATE_ATTACK2,			//Ꮜ�
	PLAYERSTATE_MAX
}PLAYERSTATE;




//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayerState(PLAYERSTATE state);
PLAYER *GetPlayer(void);
PLAYERSTATE GetPlayerStateNow(void);

#endif
