//***************************************************************************//
//
// �T�E���h���� [sound.cpp]
// Author : TEAM_Fascinator
//
//***************************************************************************//
#include "sound.h"

//***************************************************************************//
// Structure definition(SoundParam)
//***************************************************************************//
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
} SOUNDPARAM;

//***************************************************************************//
// �v���g�^�C�v�錾(Sound)
//***************************************************************************//
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//***************************************************************************//
// �O���[�o���ϐ�(Sound)
//***************************************************************************//
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aSoundParam[SOUND_LABEL_MAX] =
{
	{ "data/SOUND/BGM/Title.wav", -1 },				// BGM0(Title)	-1�̓��[�v,0�͒P��
	{ "data/SOUND/BGM/C-Select.wav", -1 },			// BGM1(C_Select)
	{ "data/SOUND/BGM/Gallery.wav", -1 },			// BGM2(Gallery)
	{ "data/SOUND/BGM/Prologue.wav", -1 },			// BGM3(Option)
	{ "data/SOUND/BGM/Dungeon.wav", -1 },			// BGM4(Game)
	{ "data/SOUND/BGM/BossBattle-Custom.wav", -1 },	// BGM5(Boss)
	{ "data/SOUND/BGM/Result4.wav", -1 },			// BGM6(Result75)
	{ "data/SOUND/BGM/Result3.wav", -1 },			// BGM7(Result50)
	{ "data/SOUND/BGM/Result2.wav", -1 },			// BGM8(Result25)
	{ "data/SOUND/BGM/TrueClear.wav", -1 },			// BGM9(TrueClear)
	{ "data/SOUND/SE/Title Decision.wav", 0 },		// �^�C�g������
	{ "data/SOUND/SE/Tutorial Decision.wav", 0 },	// �`���[�g���A������
	{ "data/SOUND/SE/cursor.wav", 0 },		// �I��
	{ "data/SOUND/SE/Decision Sound.wav", 0 },		// ����
	{ "data/SOUND/SE/Cancel.wav", 0 },				// �L�����Z��
	{ "data/SOUND/SE/Footstep.wav", 0 },				// ����
	{ "data/SOUND/SE/dead.wav", 0 },				// ���S��
	{ "data/SOUND/SE/salsh.wav", 0 },				// ����
	{ "data/SOUND/SE/fire.wav", 0 },				// ��
	{ "data/SOUND/SE/slash2.wav", 0 },				// ����2
	{ "data/SOUND/SE/hit.wav", 0 },					// ����2
	{ "data/SOUND/SE/hit2.wav", 0 },					// ����2
	{ "data/SOUND/SE/bomb2.wav", 0 },					// ����2
	{ "data/SOUND/SE/hit3.wav", 0 },					// ����2
	{ "data/SOUND/SE/mekuri.wav", 0 },					// ����2
};	

//===========================================================================//
// ����������(Sound)
//===========================================================================//
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u����������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�쐬
	hr = XAudio2Create(&g_pXAudio2, 0);

	// COM���C�u�����̏I������
	if (FAILED(hr)) { MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING); CoUninitialize(); return E_FAIL; } 

    // �}�X�^�[�{�C�X����
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// XAudio2�I�u�W�F�N�g�J��
		if (g_pXAudio2) { g_pXAudio2->Release(); g_pXAudio2 = NULL; } 

		// COM���C�u�����I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^������
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C������
		hFile = CreateFile(g_aSoundParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{	// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr)) { MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr)) { MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		if (dwFiletype != 'EVAW') { MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr)) { MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr)) { MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr)) { MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);

		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr)) { MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING); return S_FALSE; }

		// �\�[�X�{�C�X����
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr)) { MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING); return S_FALSE; }

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = g_aSoundParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

//===========================================================================//
// �I������(Sound)
//===========================================================================//
void UninitSound(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;

	// XAudio2�I�u�W�F�N�g�J��
	if (g_pXAudio2) { g_pXAudio2->Release(); g_pXAudio2 = NULL; }

	// COM���C�u�����I������
	CoUninitialize();
}

//===========================================================================//
// �Z�O�����g�Đ�(��~)
//===========================================================================//
HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = g_aSoundParam[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{	// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}

//===========================================================================//
// �Z�O�����g��~
//===========================================================================//
void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{	// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//===========================================================================//
// �Z�O�����g��~
//===========================================================================//
void StopSound(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);

			// �I�[�f�B�I�o�b�t�@�폜
			g_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//===========================================================================//
// �`�����N�̃`�F�b�N
//===========================================================================//
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	// �t�@�C���|�C���^��擪�Ɉړ�
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) { return HRESULT_FROM_WIN32(GetLastError()); } 

	while (hr == S_OK)
	{
		// �`�����N�ǂݍ���
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0) { hr = HRESULT_FROM_WIN32(GetLastError()); } 

		// �`�����N�f�[�^�ǂݍ���
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0) { hr = HRESULT_FROM_WIN32(GetLastError()); } 

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			// �t�@�C���^�C�v�ǂݍ���
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0) { hr = HRESULT_FROM_WIN32(GetLastError()); } 
			break;

		default:
			// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) { return HRESULT_FROM_WIN32(GetLastError()); } 
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format) { *pChunkSize = dwChunkDataSize; *pChunkDataPosition = dwOffset; return S_OK; }

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize) { return S_FALSE; }
	}

	return S_OK;
}

//===========================================================================//
// �`�����N�f�[�^�ǂݍ���
//===========================================================================//
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	// �t�@�C���|�C���^���w��ʒu�܂ňړ�
	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) { return HRESULT_FROM_WIN32(GetLastError()); } 

	// �f�[�^�ǂݍ���
	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0) { return HRESULT_FROM_WIN32(GetLastError()); } 

	return S_OK;
}