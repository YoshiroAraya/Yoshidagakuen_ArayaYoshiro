//=============================================================================
//
// ���C������ [main.cpp]
// Author :�r�J�R�N
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "Result.h"
#include "title.h"
#include "sound.h"
#include "tutoriaru.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CLASS_NAME	"WindowClass"		// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"�����R��"	// �E�C���h�E�̖��O(�L���v�V������)

//=============================================================================
// Prototype(Main)
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=============================================================================
// Global variables(Main)
//=============================================================================
LPDIRECT3D9	g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;

//===========================================================================//
// The main function
//===========================================================================//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),								// WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,										// �\������E�B���h�E�̃X�^�C����ݒ�
		WindowProc,										// �E�B���h�E�v���V�[�W���̃A�h���X���w��
		0,												// �ʏ�͎w�肵�Ȃ�����"0"���w��
		0,												// �ʏ�͎w�肵�Ȃ�����"0"���w��
		hInstance,										// WinMain�̈����̃C���X�^���X�n���h�����w��
		LoadIcon(NULL, IDI_APPLICATION),				// �^�X�N�o�[�Ɏg�p����A�C�R�����w��
		LoadCursor(NULL, IDC_ARROW),					// �g�p����}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),						// �E�B���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
		NULL,											// Windows�ɂ��郁�j���[��ݒ�
		CLASS_NAME,										// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)					// �t�@�C���A�C�R���Ɏg�p����A�C�R�����w��
	};

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	// �N���C�A���g�̈�̐ݒ�
	HWND hWnd;											// �E�B���h�E�n���h���i���ʎq�j
	MSG msg;											// ���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;								// ���ݎ���
	DWORD dwExecLastTime;								// �Ō�ɏ�����������

														// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̐���
	hWnd = CreateWindowEx
	(
		0,											// �g���E�B���h�E�X�^�C��
		CLASS_NAME,									// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,								// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,						// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,								// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,								// �E�B���h�E�̍���Y���W
		(rect.right - rect.left),					// �E�B���h�E�̕�
		(rect.bottom - rect.top),					// �E�B���h�E�̍���
		NULL,										// �e�E�B���h�E�̃n���h��
		NULL,										// ���j���[�n���h���܂��̓E�B���h�EID
		hInstance,									// �C���X�^���X�n���h��
		NULL										// �E�B���h�E�쐬�f�[�^
	);

	// ����������(�E�B���h�E�𐶐����Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);	// �E�B���h�E�̕\���i�E�B���h�E�̕\����Ԃ�ݒ�j
	UpdateWindow(hWnd);			// �E�B���h�E�̔��f�i�E�B���h�E�̃N���C�A���g�̈�̍X�V�j

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		//���ݎ������擾

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{	// Windows�̏���
			if (msg.message == WM_QUIT)
			{	// "WM_QUIT"���b�Z�[�W�������Ă����烋�[�v�𔲂���
				break;
			}
			else
			{	// ���b�Z�[�W�̖|��
				TranslateMessage(&msg);	// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{	// DirectX�̏���
			dwCurrentTime = timeGetTime();	// ���ݎ������擾

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{	// "60��1�b"�o��
				dwExecLastTime = dwCurrentTime;	// ��������������ێ�

												// �X�V����
				Update();

				// �`�揈��
				Draw();
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//===========================================================================//
// Window procedure
//===========================================================================//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;		// ���b�Z�[�W�I��ID

	switch (uMsg)
	{
	case WM_DESTROY:
		// "WM_QUIT"���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		// �x��
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);	// �I���m�F���b�Z�[�W

		if (nID == IDYES)
		{	// YES���������ꍇ
			// �E�B���h�E��j������iWM_DESTOROY���b�Z�[�W�𑗂�j
			DestroyWindow(hWnd);
		}
		else
		{	// NO���������ꍇ
			// �E�B���h�E��ێ�����
			return 0;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:	// ESC�L�[�������ꂽ
						// �I���m�F���b�Z�[�W
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{	// YES���������ꍇ�̂�
				// �E�B���h�E��j������iWM_DESTOROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ����̏�����Ԃ�
}

//===========================================================================//
// The initialization process(Main)
//===========================================================================//
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��(VSync��҂��ĕ`��)

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,												// �f�o�C�X�^�C�v
		hWnd,														// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,														// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))											// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �L�[�{�[�h����������
	InitKeyboard(hInstance, hWnd);

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//InitTitle();
	//InitTutoriaru();
	//InitGame();
	InitFade(g_mode);
	InitSound(hWnd);

	// Mode
	SetMode(g_mode);

	return S_OK;
}

//===========================================================================//
// End process(Main)
//===========================================================================//
void Uninit(void)
{
	//����
	UninitKeyboard();
	/*UninitTitle();
	UninitTutoriaru();
	UninitGame();*/
	UninitFade();
	UninitSound();
	//StopSound(SOUND_LABEL_BGM000);

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===========================================================================//
// Update process(Main)
//===========================================================================//
void Update(void)
{
	// �L�[�{�[�h�̏���
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TUTORIARU:
		UpdateTutoriaru();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
	UpdateFade();

}

//===========================================================================//
// Draw process(Main)
//===========================================================================//
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_TUTORIARU:
			DrawTutoriaru();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}
		// �`��̏I��
		g_pD3DDevice->EndScene();
	}
	DrawFade();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIARU:
		UninitTutoriaru();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIARU:
		InitTutoriaru();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;
}

MODE GetMode(void)
{
	return g_mode;
}
