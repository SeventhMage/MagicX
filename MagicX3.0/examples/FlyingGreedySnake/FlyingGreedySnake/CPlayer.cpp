#include "CPlayer.h"

CPlayer::CPlayer()
: m_pHead(nullptr)
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

		CSphereEntity *pBody = new CSphereEntity(m_pColorLightObject, GetBodyRadius(), GetSlice(), GetSlice());
		pBody->Create();
		m_listBody.push_back(pBody);
		m_pTail = new CSphereEntity(m_pColorLightObject, GetBodyRadius(), GetSlice(), GetSlice());
		m_pTail->Create();
		InitPosition();
	}
	else
	{
		CSphereEntity *body = new CSphereEntity(m_pColorLightObject, GetBodyRadius(), GetSlice(), GetSlice());
		body->Create();
		m_listBody.push_back(body);	
		CVector3 vBackBody = m_listBody.back()->GetPosition();
		CVector3 vSrcTail = m_pTail->GetPosition();
		body->SetPosition(vSrcTail);
		m_pTail->SetPosition((vSrcTail - vBackBody) * 2);
	}
}


void CPlayer::UpdatePosition()
{
	CVector3 headPos = m_pHead->GetPosition();
	if (headPos != m_vHeadPosRecord)
	{
		CVector3 vRecord = m_vHeadPosRecord;
		int i = 0;
		for (auto it = m_listBody.begin(); it != m_listBody.end(); ++it)
		{
			CVector3 vTemp = (*it)->GetPosition();
			(*it)->SetPosition(vRecord);
			vRecord = vTemp;			
		}
	}
}


float CPlayer::GetHeadRadius()
{
	return 1;// m_playerData.GetLevel() * 3.f;
}

float CPlayer::GetBodyRadius()
{
	return 1;// m_playerData.GetLevel() * 2.f;
}

int CPlayer::GetSlice()
{
	return m_playerData.GetLevel() * 10;
}

void CPlayer::InitPosition()
{
	m_vHeadPosRecord = CVector3(0, 0, 0);
	m_pHead->SetPosition(m_vHeadPosRecord);
	float dis = m_pHead->GetRadius() * 2;
	int i = 0;
	for (auto it = m_listBody.begin(); it != m_listBody.end(); ++it)
	{
		CVector3 bodyPos(0, 0, (i++) * dis);
		(*it)->SetPosition(bodyPos);
	}

	m_pTail->SetPosition(CVector3(0, 0, i * dis));
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
	for (auto it = m_listBody.begin(); it != m_listBody.end(); ++it)
	{
		pRootNode->AddChild(*it);
	}
	pRootNode->AddChild(m_pTail);
}

void CPlayer::Update(int delta)
{
	UpdatePosition();
}



