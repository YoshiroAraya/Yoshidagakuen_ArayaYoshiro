//=============================================================================
//
// �^�C�}�[���� [time.h]
// Author : keisuke komatsu
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene.h"

class CNumber;
//=============================================================================
//	�}�N����`
//=============================================================================
#define TIME_MAX	(3)		// �^�C�}�[�̌���

//=============================================================================
// �N���X��`
//=============================================================================
class CTime : public CScene
{
public:
	CTime(int nPriority = 6, OBJTYPE objType = OBJTYPE_TIME);
	~CTime();

	static CTime *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetTime(void) { return m_nTime; };
	static void MinusTime(int nTime);

private:
	CNumber *m_apNumber[TIME_MAX];	// �i���o�[�ւ̃|�C���^
	static int m_nTime;				// ����
	int m_nTimeCount;				// ���Ԃ̃J�E���^
	D3DXVECTOR3 m_pos;				// �ʒu	
};

#endif