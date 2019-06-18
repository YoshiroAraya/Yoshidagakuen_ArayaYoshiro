//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �r�J �R�N
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// �v���C���[�̃A�j���[�V�����̏��
//=============================================================================
typedef enum
{
	PLAYER_STATE_NEUTRAL = 0,		// �ʏ�
	PLAYER_STATE_DAMAGE,			// �_���[�W
	PLAYER_STATE_DEATH,				// ���S
	PLAYER_STATE_MAX
}PLAYER_STATE;

//=============================================================================
//
//=============================================================================
typedef enum
{
	PLAYER_MOSIONSTATE_NEUTRAL = 0,		// �j���[�g����
	PLAYER_MOSIONSTATE_MOVE,			// �ړ�
	PLAYER_MOSIONSTATE_UP,				// �㏸
	PLAYER_MOSIONSTATE_DOWN,			// ���~
	PLAYER_MOSIONSTATE_TURNING_R,		// �E����
	PLAYER_MOSIONSTATE_TURNING_L,		// ������
	PLAYER_MOSIONSTATE_MAX
}PLAYER_MOSIONSTATE;

//=============================================================================
// ���f���̍\����
//=============================================================================
typedef struct
{
	LPD3DXMESH				pMash = NULL;			// ���b�V��
	LPD3DXBUFFER			pBuffMat = NULL;		// �o�b�t�@
	DWORD					nNumMat;				// �}�e���A���f�[�^
	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9		*pTexture;				// �e�N�X�`���f�[�^�ւ̃|�C���^
	D3DXMATERIAL			*pmat;					// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3				pos;					// ���W
	D3DXVECTOR3				rot;					// ����
	float					nIdxModelParent = -1;	// �e���f���̃C���f�b�N�X
	char					FileName[256];			// �e�L�X�g�t�@�C���̃A�h���X
}Model;

//=============================================================================
// �v���C���[�̍\����
//=============================================================================
typedef struct
{
	D3DXMATRIX		mtxWorld;
	D3DXVECTOR3		pos;					// ���݂̈ʒu
	D3DXVECTOR3		posOld;					// �ʒu
	D3DXVECTOR3		rot;					// ����
	D3DXVECTOR3		move;					// �ړ�
	D3DXVECTOR3		vtxMin;					// ���f���̍ŏ��l
	D3DXVECTOR3		vtxMax;					// ���f���̍ő�l
	D3DXCOLOR		col;					// �F
	int				nLife;					// ���C�t
	int				nCunterState;			// �J�E���^�[�X�e�[�^�X
	int				nCntFleam;				// �t���[���̃J�E���^�[
	int				PlayerAnim;				// ���[�V�����J�E���^�[
	int				nNumParts = 0;			// �p�[�c�̔ԍ�
	int				MAX_PARTS;				// �p�[�c�̍ő吔
	int				nCntPlayermotion;		// ���[�V�����̔ԍ�
	float			rotDest;				// �ڕW�̌���
	float			fAngle;					// ����
	bool			bUse;					// �g�p���Ă��邩�ǂ���
	Model			aModel[3];				// �p�[�c
	PLAYER_STATE	PlayerState;			// �v���C���[�̏��
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void				InitPlayer					(void);
void				UninitPlayer				(void);
void				UpdatePlayer				(void);
void				DrawPlayer					(void);
void				HitPlayer					(int nDamage);
void				SetPLAYER_STATE				(PLAYER_STATE state);
void				SetPLAYER_MOSIONSTATE		(PLAYER_MOSIONSTATE state);
PLAYER_MOSIONSTATE	GetPLAYER_MOSIONSTATENow	(void);
Player				*GetPlayer					(void);
#endif