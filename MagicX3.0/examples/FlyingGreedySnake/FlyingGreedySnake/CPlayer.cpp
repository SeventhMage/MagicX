#include "CPlayer.h"
#include "resource/ITableConfigManager.h"
#include "resource/ITableConfig.h"

CPlayer::CPlayer()
	: m_pHead(nullptr)
	, m_pTail(nullptr)
	, m_fVolume(1.f)
{
	Create();
}

CPlayer::~CPlayer()
{
	SAFE_DEL(m_pHead);
}

void CPlayer::InitConfigTable()
{
	resource::ITableConfigManager *pTableCfgMgr = RESOURCEMGR(ITableConfigManager, RT_TABLE_CONFIG);
	ITableConfig *pTableCfg = dynamic_cast<ITableConfig *>(pTableCfgMgr->LoadResource("config/snake.xml"));
	if (pTableCfg)
	{
		std::string strSpeed = pTableCfg->GetRecord(GetLevel(), "maxmovespeed");
		if (!strSpeed.empty())
		{
			SetMaxSpeed(atof(strSpeed.c_str()));
		}
		std::string strAcceSpeed = pTableCfg->GetRecord(GetLevel(), "acceleratedspeed");
		if (!strAcceSpeed.empty())
		{
			SetAcceleratedSpeed(atof(strAcceSpeed.c_str()));
		}
		std::string strScale = pTableCfg->GetRecord(GetLevel(), "scale");
		if (!strScale.empty())
		{
			float scale = atof(strScale.c_str());
			m_pHead->SetScale(CVector3(scale, scale, scale));
			for (auto body : m_listBody)
			{
				body->SetScale(CVector3(scale, scale, scale));
			}
			m_pTail->SetScale(CVector3(scale, scale, scale));
			m_fVolume = scale;
		}

		std::string strRotateSpeed = pTableCfg->GetRecord(GetLevel(), "rotatespeed");
		if (!strRotateSpeed.empty())
		{
			m_fRotateSpeed = DEG_TO_RAD(atof(strRotateSpeed.c_str()));
		}
	}

}

void CPlayer::Increase(const CVector3 &color)
{
	CSphereEntity *body = new CSphereEntity(GetBodyRadius(), GetSlice(), GetSlice(), color);
	body->SetScale(CVector3(m_fVolume, m_fVolume, m_fVolume));
	body->Create();
	CVector3 vBackBody = m_listBody.back()->GetPosition();
	CVector3 vSrcTail = m_pTail->GetPosition();
	body->SetPosition(vSrcTail);
	m_listBody.push_back(body);
	CVector3 dir = vSrcTail - vBackBody;
	dir.normalize();
	m_pTail->SetPosition(vSrcTail + 1.5f * GetBodyRadius() * dir);

	ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
	pRootNode->AddChild(body);
}


void CPlayer::UpdatePosition()
{
	CVector3 headPos = m_pHead->GetPosition();
	if (headPos != m_vHeadPosRecord)
	{
		CVector3 vRecord = m_vHeadPosRecord;
		CVector3 vFront = headPos;
		int i = 0;
		for (auto it = m_listBody.begin(); it != m_listBody.end(); ++it)
		{
			CVector3 vTemp = (*it)->GetPosition();
			CVector3 dir = (vTemp - vFront).normalize();
			vFront = vFront + dir * 1.5f * GetBodyRadius();
			(*it)->SetPosition(vFront);
			vRecord = vTemp;
		}
		CVector3 vTemp = m_pTail->GetPosition();
		CVector3 dir = (vTemp - vFront).normalize();
		vFront = vFront + dir * 1.5f * GetBodyRadius();
		m_pTail->SetPosition(vFront);
		m_vHeadPosRecord = headPos;
	}
}


void CPlayer::Release()
{
	SAFE_DEL(m_pHead);
	SAFE_DEL(m_pTail);
	for (auto body : m_listBody)
	{
		SAFE_DEL(body);
	}
	m_listBody.clear();
}

float CPlayer::GetHeadRadius()
{
	return 1.1f;
}

float CPlayer::GetBodyRadius()
{
	return 1.f;
}

int CPlayer::GetSlice()
{
	return m_playerData.GetLevel() * 10;
}

void CPlayer::InitPosition()
{
	m_vHeadPosRecord = CVector3(0, GetHeadRadius(), 0);
	m_pHead->SetPosition(m_vHeadPosRecord);
	float dis = 1.5f * GetBodyRadius();
	int i = 0;
	for (auto it = m_listBody.begin(); it != m_listBody.end(); ++it)
	{
		CVector3 bodyPos(0, GetBodyRadius(), (++i) * dis);
		(*it)->SetPosition(bodyPos);
	}

	m_pTail->SetPosition(CVector3(0, GetBodyRadius(), (++i) * dis));
}

void CPlayer::SetPosition(const CVector3 &pos)
{
	CGameUnit::SetPosition(pos);
	if (m_pHead)
		m_pHead->SetPosition(CVector3(pos.x, GetHeadRadius(), pos.z));
}


void CPlayer::Create()
{
	m_pHead = new CSphereEntity(GetHeadRadius(), GetSlice(), GetSlice(), CVector3(Random(0.f, 1.f), Random(0.f, 1.f), Random(0.f, 1.f)));
	m_pHead->Create();
	CSphereEntity *pBody = new CSphereEntity(GetBodyRadius(), GetSlice(), GetSlice(), CVector3(Random(0.f, 1.f), Random(0.f, 1.f), Random(0.f, 1.f)));
	pBody->Create();
	m_listBody.push_back(pBody);
	m_pTail = new CSphereEntity(GetBodyRadius(), GetSlice(), GetSlice(), CVector3(Random(0.f, 1.f), Random(0.f, 1.f), Random(0.f, 1.f)));
	m_pTail->Create();

	ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
	pRootNode->AddChild(m_pHead);
	pRootNode->AddChild(pBody);
	pRootNode->AddChild(m_pTail);
	InitPosition();

}

void CPlayer::Update(int delta)
{
	CGameUnit::Update(delta);
	UpdatePosition();

}

void CPlayer::SetLevel(int level)
{
	CGameUnit::SetLevel(level);
}

