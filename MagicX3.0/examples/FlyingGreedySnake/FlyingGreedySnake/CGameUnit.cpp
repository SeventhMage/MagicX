#include "CGameUnit.h"

CGameUnit::CGameUnit()
: m_bAlive(true)
, m_fMaxSpeed(100.f)
, m_fCurSpeed(0.f)
, m_fAcceleratedSpeed(1.f)
, m_vDirection(CVector3(0.f, 0.f, -1.f))
, m_level(1)
, m_bMoved(false)
, m_rotateState(ERS_NONE)
, m_fRotateSpeed(1.f)
{
}

CGameUnit::~CGameUnit()
{
	Release();
}

void CGameUnit::Update(int delta)
{
	if (m_bMoved)
	{
		if (m_fCurSpeed < m_fMaxSpeed)
		{
			m_fCurSpeed += m_fAcceleratedSpeed * delta / 1000.f;
		}
		else
		{
			m_fCurSpeed = m_fMaxSpeed;
		}
	}
	else
	{
		if (m_fCurSpeed > 0.f)
		{
			m_fCurSpeed -= m_fAcceleratedSpeed * delta / 1000.f;
		}
		else
		{
			m_fCurSpeed = 0.f;
		}
	}

	if (m_fCurSpeed > 0)
	{
		float distance = m_fCurSpeed * (float)delta / 1000.f;
		const CVector3 &curPos = GetPosition();
		const CVector3 &dir = GetDirection();
		SetPosition(curPos + dir * distance);
	}

	if (m_rotateState == ERS_LEFT)
	{
		m_vDirection.rotateXZBy(m_fRotateSpeed * delta * 0.001);
	}
	else if (m_rotateState == ERS_RIGHT)
	{
		m_vDirection.rotateXZBy(-m_fRotateSpeed * delta * 0.001);
	}
}

void CGameUnit::SetLevel(int level)
{
	if (m_level != level)
	{
		m_level = level;
		InitConfigTable();
	}
}

void CGameUnit::SetRotate(ERotateState state)
{
	m_rotateState = state;
}

