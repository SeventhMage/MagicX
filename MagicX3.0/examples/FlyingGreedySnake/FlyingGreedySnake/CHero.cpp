#include "CHero.h"

CHero::CHero()
:m_bBeginMove(false)
, m_vMoveDir(0, 0, -1)
{

}

CHero::~CHero()
{

}


void CHero::Update(int delta)
{	
	if (m_bBeginMove)
	{
		SetPosition(GetPosition() + m_vMoveDir * 1.5f);
	}
	CPlayer::Update(delta);
}


void CHero::BeginMove()
{
	m_bBeginMove = true;
}

void CHero::SetMoveDir(const CVector3 &vDir)
{	
	m_vMoveDir = vDir;
	m_vMoveDir.normalize();
}

void CHero::LeftMove()
{
	if (m_bBeginMove)
		m_vMoveDir.rotateXZBy(0.2f);
}

void CHero::RightMove()
{
	if (m_bBeginMove)
		m_vMoveDir.rotateXZBy(-0.2f);
}

