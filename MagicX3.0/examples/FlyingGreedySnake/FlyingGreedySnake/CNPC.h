/************************************************************************/
/* ”Œœ∑NPC                                                              */
/************************************************************************/

#ifndef _C_NPC_H_
#define _C_NPC_H_

#include "CGameUnit.h"

class CNPC : public CGameUnit
{
public:
	CNPC(float color[4], float radius);
	virtual ~CNPC();	
	virtual void SetPosition(const CVector3 &pos);
private:
	CSphereEntity *m_pBody;
	CColorPointLightObject *m_pColorLightObject;
};

#endif