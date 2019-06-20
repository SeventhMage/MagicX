#include "CNPC.h"


CNPC::CNPC(const CVector3 &color, float radius)
	:m_vColor(color)
{
	m_pBody = new CSphereEntity(radius, 50, 25, color);
	m_pBody->Create();

	ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
	pRootNode->AddChild(m_pBody);
}

CNPC::~CNPC()
{
	SAFE_DEL(m_pBody);
}

void CNPC::SetPosition(const CVector3 &pos)
{
	CGameUnit::SetPosition(pos);
	if (m_pBody)
		m_pBody->SetPosition(pos);
}


void CNPC::Update(int delta)
{
	CGameUnit::Update(delta);
}
