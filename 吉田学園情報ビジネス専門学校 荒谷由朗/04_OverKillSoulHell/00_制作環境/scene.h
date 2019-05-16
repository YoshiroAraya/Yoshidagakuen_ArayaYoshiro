//=============================================================================
//
// ÉVÅ[Éìèàóù [scene.h]
// Author :		çríJóRòN
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX_SCENE		(1000)
#define NUM_PRIORITY	(8)

//=============================================================================
// ÉNÉâÉXÇÃíËã`
//=============================================================================
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_ENEMY,
		OBJTYPE_SCORE,
		OBJTYPE_EFFECT,
		OBJTYPE_GAUGE0,
		OBJTYPE_GAUGE1,
		OBJTYPE_CIRCLE,
		OBJTYPE_BULLETICON,
		OBJTYPE_MPICON,
		OBJTYPE_ITEM,
		OBJTYPE_BARRIER,
		OBJTYPE_SOUL,
		OBJTYPE_PAIR,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 0);
	virtual ~CScene();
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void				SetObjType(OBJTYPE objtype);
	OBJTYPE				GetObjType(void);
	static	CScene		*GetScene(int PRI_Idx,int SCENE_Idx);
	virtual D3DXVECTOR3	GetPosition(void);

	virtual HRESULT	Init(void) = 0;
	virtual void	Uninit(void) {};
	virtual void	Update(void) {};
	virtual void	Draw(void) {};
	virtual void	SetPosition(D3DXVECTOR3 pos, float width, float height) {};

protected:
	void Release(void);

private:
	static CScene	*m_apScene[NUM_PRIORITY][MAX_SCENE];
	static int		m_nNumAll;			// ëçêî
	int				m_nID;
	int				m_nPriID;			// óDêÊèáà ÇÃî‘çÜ
	OBJTYPE			m_objtype;
};
#endif