//=============================================================================
//
// ���C������ [camera.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=====================
//�@   �O���錾
//=====================
class CPlayer;

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// �L�[�̍ő吔
#define	NUM_MOUSE_MAX		(8)					// �}�E�X�̍ő吔

//=====================
//	   ��{�N���X
//=====================
class CCamera
{
public://�N�ł�������
	typedef enum
	{
		CAMERA_TYPE_NONE = 0,		//�����Ȃ����
		CAMERA_TYPE_DEMO,			//�^�C�g���J����
		CAMERA_TYPE_RANKING_DEMO,	//�����L���O�J����
		CAMERA_TYPE_GAME,			//�Q�[���J����
		CAMERA_TYPE_MAX				//�J�����̍ő吔
	}CAMERATYPE;

	CCamera();
	~CCamera();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void SetCamera();
	float GetRot(void) { return m_fAngle; }
	static D3DXVECTOR3 GetPosV(void) { return m_posV; }
	static void Delete(void);
	static CCamera *Create(CAMERATYPE CameraType);

protected://�l�ł̂ݎg��
	static D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_posVDest;			//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;			//�ړI�̒����_
	D3DXVECTOR3 m_rot;				//�J�����̌���������
	float		m_fDistance;		//����
	D3DXVECTOR3 m_vecU;				//������x�N�g��
	D3DXMATRIX	m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			//�r���[�}�g���b�N�X
	float		m_fAngle;			//�p�x
	float		m_fLength;			//����
	int			m_nType;			//���
	int			m_nCount;			//�b���J�E���g
	int			m_CameraCount;		//�J�����̈ړ�����
	float		m_fCameraAngle;		//�p�x
	float		m_fRot;				//��]
	bool		m_bOnOff;
	float		m_fRange;			// Y���̋���
	int			m_nCntTitle;		// �^�C�g�����̃J�E���^�[
	bool		m_bReset;			// �^�C�g���J�����̃��Z�b�g
	static CPlayer *m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif