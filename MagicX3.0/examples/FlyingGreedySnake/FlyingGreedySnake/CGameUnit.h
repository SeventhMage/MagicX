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
	enum ERotateState
	{
		ERS_NONE,
		ERS_LEFT,
		ERS_RIGHT,
	};

	CGameUnit();
	virtual ~CGameUnit();

	virtual void InitConfigTable() {};
	virtual void Update(int delta);
	virtual void SetPosition(const CVector3 &pos) { m_vPosition = pos; }
	virtual const CVector3 &GetPosition() { return m_vPosition; }
	virtual void SetDirection(const CVector3 &dir) { m_vDirection = dir; }
	virtual const CVector3 &GetDirection() { return m_vDirection; }
	virtual void SetLevel(int level);
	virtual void Release() {}
	void SetAlive(bool bAlive) { m_bAlive = bAlive; }
	bool IsAlive() { return m_bAlive; }
	void SetSpeed(float fSpeed) { m_fCurSpeed = fSpeed; }
	float GetSpeed() { return m_fCurSpeed; }
	void SetMaxSpeed(float fSpeed) { m_fMaxSpeed = fSpeed; }
	float GetMaxSpeed() { return m_fMaxSpeed; }
	void SetAcceleratedSpeed(float fSpeed) { m_fAcceleratedSpeed = fSpeed; }
	float GetAcceleratedSpeed() { return m_fAcceleratedSpeed; }
	void SetRotateSpeed(float fSpeed) { m_fRotateSpeed = fSpeed; }
	float GetRotateSpeed() { return m_fRotateSpeed; }
	void SetMoved(bool bMoved) { m_bMoved = bMoved; }
	void SetRotate(ERotateState state);
	int GetLevel() { return m_level; }
protected:
	float m_fCurSpeed;
	float m_fAcceleratedSpeed;
	float m_fMaxSpeed;
	int m_level;
	CVector3 m_vPosition;
	CVector3 m_vDirection;
	int m_rotateState;
	bool m_bAlive;
	bool m_bMoved;

	float m_fRotateSpeed;
};

#endif