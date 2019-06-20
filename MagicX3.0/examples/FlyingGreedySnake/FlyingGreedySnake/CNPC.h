/************************************************************************/
/* ”Œœ∑NPC                                                              */
/************************************************************************/

#ifndef _C_NPC_H_
#define _C_NPC_H_

#include "CGameUnit.h"

class CNPC : public CGameUnit
{
public:
	CNPC(const CVector3 &color, float radius);
	virtual ~CNPC();	
	virtual void SetPosition(const CVector3 &pos);	
	virtual void Update(int delta);
	const CVector3 &GetColor() { return m_vColor; }
private:
	CSphereEntity *m_pBody;
	CVector3 m_vColor;
};

#endif