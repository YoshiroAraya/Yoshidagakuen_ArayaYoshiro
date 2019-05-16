//=============================================================================
//
// �G���� [enemy.h]
// Author :�r�J�R�N
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(256)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//�G�̏�Ԃ̎�ށi�񋓌^�j
//typedef enum
//{
//	ENEMTSTATE_NORMAL = 0,		//�G�̒ʏ���
//	ENEMTSTATE_DAMAGE,			//�G�̃_���[�W���
//	ENMEYSTATE_MAX				//�G�̏�Ԏ�ނ̑���
//}ENEMYSTATE;

//�G�̍\����
typedef enum
{
	EnemyType_NORMAL1 = 0,
	EnemyType_NORMAL2,
	EnemyType_MAX
}EnemyType;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�e�̈ړ���
	D3DXCOLOR col;			//�F
	float move_bullet;
	float fWidth;			//��
	float fHeight;			//����
	EnemyType type;			//���
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	int nCounterState;		//��ԊǗ��̃J�E���^�[
	float nSpped;			//�G�̈ړ����x
	bool bUse;				//�g�p����Ă��邩�ǂ���
}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight, EnemyType type, float move_bullet);
//Enemy *GetEnemy(void);
#endif