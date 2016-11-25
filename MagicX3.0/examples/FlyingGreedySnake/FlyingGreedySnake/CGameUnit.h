/************************************************************************/
/* ”Œœ∑µ•Œª                                                             */
/************************************************************************/
#ifndef _C_GAME_UNIT_H_
#define _C_GAME_UNIT_H_

#include "mx.h"

using namespace mx;

class CGameUnit
{
public:
	CGameUnit();
	virtual ~CGameUnit();

	virtual void SetPosition(const CVector3 &pos){}

	void SetAlive(bool bAlive) { m_bAlive = bAlive; }
	bool IsAlive() { return m_bAlive; }
private:
	IRenderObject *m_pRenderObject;
	IRenderable *m_pRenderable;
	bool m_bAlive;
};

#endif