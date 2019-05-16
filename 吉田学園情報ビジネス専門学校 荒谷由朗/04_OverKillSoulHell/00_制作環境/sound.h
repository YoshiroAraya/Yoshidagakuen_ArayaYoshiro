//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �r�J�R�N
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �N���X
//*************************************
class CSound
{
public:
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,			// �^�C�g��BGM
		SOUND_LABEL_BGM001,				// �`���[�g���A��BGM
		SOUND_LABEL_BGM002,				// �Q�[��BGM
		SOUND_LABEL_BGM003,				// ���U���gBGM
		SOUND_LABEL_SELECT000,			// ���艹(�^�C�g���A���U���g�A�|�[�Y)
		SOUND_LABEL_SELECT001,			// �I����(�`���[�g���A���A�|�[�Y�A���U���g)
		SOUND_LABEL_PAUSE,				// �|�[�Y�\��(�|�[�Y)
		SOUND_LABEL_PLAYER_BULLET,		// PLAYER���ˉ�(�v���C���[)
		SOUND_LABEL_ENEMY_BULLET,		// ENEMEY���ˉ�(�G�l�~�[)��
		SOUND_LABEL_PLAYER_DAMEGE,		// �_���[�W(�v���C���[)��
		SOUND_LABEL_ENEMY_DAMEGE,		// �_���[�W(�G�l�~�[)
		SOUND_LABEL_SKILL,				// �X�L������
		SOUND_LABEL_SKILL_SELECT,		// �X�L���؂�ւ�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void AllStopSound(void);

private:
	typedef struct
	{
		char					*m_pFilename;						// �t�@�C����
		int						m_nCntLoop;							// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	}SOUNDPARAM;

	IXAudio2					*m_pXAudio2;						// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice		*m_pMasteringVoice;					// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice			*m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE						*m_apDataAudio[SOUND_LABEL_MAX];	// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD						m_aSizeAudio[SOUND_LABEL_MAX];		// �I�[�f�B�I�f�[�^�T�C�Y
	SOUNDPARAM					m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/BGM000.wav", -1 },			// �^�C�g��BGM
		{ "data/BGM/BGM001.wav", -1 },			// �`���[�g���A��BGM
		{ "data/BGM/BGM002.wav", -1 },			// �Q�[��BGM
		{ "data/BGM/BGM003.wav", -1 },			// ���U���gBGM
		{ "data/SE/select000.wav", 0 },			// ���艹(�^�C�g���A���U���g�A�|�[�Y)
		{ "data/SE/select001.wav", 0 },			// �I����(�`���[�g���A���A�|�[�Y�A���U���g)
		{ "data/SE/puse000.wav", 0 },			// �|�[�Y�\��(�|�[�Y)
		{ "data/SE/bullet000.wav", 0 },			// PLAYER���ˉ�(�v���C���[)
		{ "data/SE/bullet001.wav", 0 },			// ENEMEY���ˉ�(�G�l�~�[)
		{ "data/SE/DamageSound000.wav", 0 },	// �_���[�W(�v���C���[)
		{ "data/SE/emenyDamege.wav", 0 },		// �_���[�W(�G�l�~�[)
		{ "data/SE/skill_select000.wav", 0 },	// �X�L������
		{ "data/SE/skill_select001.wav", 0 },	// �X�L���؂�ւ�
	};											// �e���f�ނ̃p�����[�^
};
#endif