#include "CNPC.h"


CNPC::CNPC(float color[4], float radius)
{
	m_pColorLightObject = new CColorPointLightObject(color);
	m_pBody = new CSphereEntity(m_pColorLightObject, radius, 50, 25);
	m_pBody->Create();

	ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
	pRootNode->AddChild(m_pBody);
}

CNPC::~CNPC()
{
	SAFE_DEL(m_pBody);
	SAFE_DEL(m_pColorLightObject);
}

void CNPC::SetPosition(const CVector3 &pos)
{
	if (m_pBody)
		m_pBody->SetPosition(pos);
}

mx::math::CVector3 CNPC::GetPosition()
{
	return m_pBody ? m_pBody->GetPosition() : CVector3(0, 0, 0);
}
