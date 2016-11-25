#include "CPlayer.h"

CPlayer::CPlayer()
: m_pHead(nullptr)
, m_pBody(nullptr)
, m_pTail(nullptr)
{
	m_pReflectObject = new CReflectObject();

	float color[4] = { 0 };	
	for (int i = 0; i < 4; ++i)
	{
		color[i] = (rand() % 255) / 255.0f;
	}
	m_pColorLightObject = new CColorPointLightObject(color);

	Increase();
	Increase();
	Increase();

	InitPosition(m_pHead);
}

CPlayer::~CPlayer()
{
	SAFE_DEL(m_pHead);
	SAFE_DEL(m_pColorLightObject);
	SAFE_DEL(m_pReflectObject);
;}

void CPlayer::Increase()
{
	if (!m_pHead)
	{			
		m_pHead = new CSphereEntity(m_pReflectObject, GetHeadRadius(), GetSlice(), GetSlice());

		m_pBody = new CSphereEntity(m_pColorLightObject, GetBodyRadius(), GetSlice(), GetSlice());
		m_pBody->Create();
		m_pHead->AddChild(m_pBody);		
		m_pTail = new CSphereEntity(m_pColorLightObject, GetBodyRadius(), GetSlice(), GetSlice());
		m_pTail->Create();
		m_pBody->AddChild(m_pTail);
	}
	else
	{
		CSphereEntity *body = new CSphereEntity(m_pColorLightObject, GetBodyRadius(), GetSlice(), GetSlice());
		body->Create();
		m_pTail->AddChild(body);
		m_pTail = body;
	}
}

float CPlayer::GetHeadRadius()
{
	return m_playerData.GetLevel() * 3.f;
}

float CPlayer::GetBodyRadius()
{
	return m_playerData.GetLevel() * 2.f;
}

int CPlayer::GetSlice()
{
	return m_playerData.GetLevel() * 10;
}

void CPlayer::InitPosition(CSphereEntity *entity)
{
	if (entity)
	{
		const ISceneNode::SceneNodeList &list = entity->GetChildNodeList();
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			(*it)->SetPosition(CVector3(0, 0, entity->GetRadius() * 1.5f));
			InitPosition((CSphereEntity *)*it);
			break;
		}
	}
}

void CPlayer::SetPosition(const CVector3 &pos)
{
	if (m_pHead)
		m_pHead->SetPosition(pos);
}

const CVector3 &CPlayer::GetPosition()
{
	return m_pHead->GetPosition();
}

void CPlayer::Create()
{
	m_pHead->Create();
	ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
	pRootNode->AddChild(m_pHead);
}



