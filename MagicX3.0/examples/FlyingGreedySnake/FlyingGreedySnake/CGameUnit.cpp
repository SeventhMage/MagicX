#include "CGameUnit.h"

CGameUnit::CGameUnit()
: m_bAlive(true)
, m_fMaxSpeed(100.f)
, m_fCurSpeed(10.f)
, m_vDirection(CVector3(0.f, 0.f, -1.f))
, m_level(1)
{

}

CGameUnit::~CGameUnit()
{

}

void CGameUnit::Update(int delta)
{
	if (m_fCurSpeed > 0)
	{
		float distance = m_fCurSpeed * (float)delta / 1000.f;
		const CVector3 &curPos = GetPosition();
		const CVector3 &dir = GetDirection();
		SetPosition(curPos + dir * distance);
	}
}

