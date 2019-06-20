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

	virtual void Update(int delta);
	virtual void SetPosition(const CVector3 &pos) { m_vPosition = pos; }
	virtual const CVector3 &GetPosition() { return m_vPosition; }
	virtual void SetDirection(const CVector3 &dir) { m_vDirection = dir; }
	virtual const CVector3 &GetDirection() { return m_vDirection; }
	virtual void SetLevel(int level) { m_level = level; }

	void SetAlive(bool bAlive) { m_bAlive = bAlive; }
	bool IsAlive() { return m_bAlive; }
	void SetSpeed(float fSpeed) { m_fCurSpeed = fSpeed; }
	float GetSpeed() { return m_fCurSpeed; }
	void SetMaxSpeed(float fSpeed) { m_fMaxSpeed = fSpeed; }
	float GetMaxSpeed() { return m_fMaxSpeed; }
	int GetLevel() { return m_level; }
protected:
	bool m_bAlive;
	float m_fCurSpeed;
	float m_fMaxSpeed;
	int m_level;
	CVector3 m_vPosition;
	CVector3 m_vDirection;
};

#endif