#include "CHero.h"

CHero::CHero()
{
	Create();
}

CHero::~CHero()
{

}


void CHero::Update(int delta)
{	
	CPlayer::Update(delta);
}

void CHero::LeftRotate()
{
	m_vDirection.rotateXZBy(0.02f * GetLevel());
}

void CHero::RightRotate()
{
	m_vDirection.rotateXZBy(-0.02f * GetLevel());
}

