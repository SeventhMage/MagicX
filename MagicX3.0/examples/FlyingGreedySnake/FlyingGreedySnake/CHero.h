/************************************************************************/
/* Ö÷½Ç                                                                 */
/************************************************************************/

#ifndef _C_HERO_H_
#define _C_HERO_H_

#include "CPlayer.h"

class CHero : public CPlayer
{
public:
	CHero();
	virtual ~CHero();

	virtual void Update(int delta);

	void BeginMove();
	void SetMoveDir(const CVector3 &vDir);
	void LeftMove();
	void RightMove();	
private:
	bool m_bBeginMove;
	CVector3 m_vMoveDir;
	float m_fSpeed;
};

#endif