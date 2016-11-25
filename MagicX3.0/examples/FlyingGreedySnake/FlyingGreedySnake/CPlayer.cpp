#include "CPlayer.h"

#include "time.h"

CPlayer::CPlayer()
: m_pHead(nullptr)
, m_pBody(nullptr)
, m_pTail(nullptr)
{
	m_pReflectObject = new CReflectObject();

	float color[4] = { 0 };
	srand(time(0));
	for (int i = 0; i < 4; ++i)
	{
		color[i] = (rand() % 255) / 255.0f;
	}
	m_pColorLightObject = new CColorPointLightObject(color);

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
		m_pHead = new CSphereEntity(m_pReflectObject, GetRadius(), GetSlice(), GetSlice());
		m_pBody = new CSphereEntity(m_pColorLightObject, GetRadius(), GetSlice(), GetSlice());
		m_pHead->AddChild(m_pBody);		
		m_pTail = new CSphereEntity(m_pColorLightObject, GetRadius(), GetSlice(), GetSlice());
		m_pBody->AddChild(m_pTail);
	}
	else
	{
		CSphereEntity *body = new CSphereEntity(m_pColorLightObject, GetRadius(), GetSlice(), GetSlice());
		m_pTail->AddChild(body);
		m_pTail = body;
	}
}

float CPlayer::GetRadius()
{
	return m_playerData.GetLevel() * 2.f;
}

float CPlayer::GetSlice()
{
	return m_playerData.GetLevel() * 5;
}

void CPlayer::InitPosition(CSphereEntity *entity)
{
	if (entity)
	{
		SceneNodeList list = entity->GetChildNodeList();
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			(*it)->SetPosition(entity->GetPosition() + CVector3(0, 0, entity->GetRadius() * 2.f));
			InitPosition((CSphereEntity *)*it);
			break;
		}
	}
}



