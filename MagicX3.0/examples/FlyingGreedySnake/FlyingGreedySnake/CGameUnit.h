/************************************************************************/
/* ”Œœ∑µ•Œª                                                             */
/************************************************************************/
#ifndef _C_GAME_UNIT_H_
#define _C_GAME_UNIT_H_

#include "mx.h"

using namespace mx;

class CGameUnit : public CEntity
{
public:
	CGameUnit();
	virtual ~CGameUnit();

	virtual void UpdateImp(int delta);

	void SetAlive(bool bAlive) { m_bAlive = bAlive; }
	bool IsAlive() { return m_bAlive; }
private:
	IRenderObject *m_pRenderObject;
	IRenderable *m_pRenderable;
	bool m_bAlive;
};

#endif