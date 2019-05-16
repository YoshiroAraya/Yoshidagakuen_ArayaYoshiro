//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  ��{�N���X
//=====================
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM_NATURE = 0,		// ���R����BGM
		SOUND_LABEL_BGM_TITLE,			// �^�C�g����BGM
		SOUND_LABEL_BGM_GAME,			// �Q�[����BGM
		SOUND_LABEL_BGM_RESULT,			// ���U���g��BGM
		SOUND_LABEL_SE_DECISION,		// ���艹
		SOUND_LABEL_SE_ITEMGET,			// �A�C�e���擾��
		SOUND_LABEL_SE_JUMP,			// �W�����v��
		SOUND_LABEL_SE_PAUSE_CLOSE,		// �|�[�Y����鉹
		SOUND_LABEL_SE_PAUSE_OPEN,		// �|�[�Y���J����
		SOUND_LABEL_SE_PAUSE_SELECT,	// �|�[�Y���̑I����
		SOUND_LABEL_SE_RUN,				// ���s��
		SOUND_LABEL_SE_WATERIN,			// ��ɓ�������
		SOUND_LABEL_MAX
	}SOUND_LABEL;
	
	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label); //�Q�[���̏������߂��@
	void StopSound(SOUND_LABEL label);	  //�������O�������ăX�g�b�v��������
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	typedef struct
	{
		char *m_pFilename;		// �t�@�C����
		int m_nCntLoop;			// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	IXAudio2				*m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice	*m_pMasteringVoice;						// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice	*m_apSourceVoice[SOUND_LABEL_MAX];			// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX];		// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX];			// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		//-1�̓��[�v�@�@0�͒P��
		//BGM�ꗗ
		{ "data/SOUND/BGM/NatureBGM.wav", -1 },
		{ "data/SOUND/BGM/TitleBGM.wav", -1 },
		{ "data/SOUND/BGM/GameBGM.wav", -1 },
		{ "data/SOUND/BGM/ResultBGM.wav", -1 },
		//SE�ꗗ
		{ "data/SOUND/SE/decision.wav", 0 },
		{ "data/SOUND/SE/item_get.wav", 0 },
		{ "data/SOUND/SE/jump.wav", 0 },
		{ "data/SOUND/SE/pause_close.wav", 0 },
		{ "data/SOUND/SE/pause_open.wav", 0 },
		{ "data/SOUND/SE/pause_select.wav", 0 },
		{ "data/SOUND/SE/run.wav", 0 },
		{ "data/SOUND/SE/water_in.wav", 0 },
	};
};

#endif