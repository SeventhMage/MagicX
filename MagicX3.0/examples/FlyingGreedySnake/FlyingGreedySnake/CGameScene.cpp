#include "CGameScene.h"
#include "mx.h"

static const int INIT_NPC_NUM = 100;
static const int MAX_NPC_RADIUS = 24;
static const int SCENE_RADIUS = 512;
static const int GROUND_RADIUS = 256;


CGameScene::CGameScene()
:m_pHero(nullptr)
, m_pScene(nullptr)
{
	
}

CGameScene::~CGameScene()
{
	SAFE_DEL(m_pHero);
}

void CGameScene::InitScene()
{
	m_pScene = SCENEMGR->GetCurrentScene();
	m_pHero = new CHero();

	CVector3 vDir(0, -1, -1);
	CVector3 vUp(0, 1, 0);
	m_pScene->SetupCamera(100.f, m_pHero->GetHead(), vDir, vUp, PI / 3, 1.0f * DEVICEMGR->GetDevice()->GetWindowWidth() / DEVICEMGR->GetDevice()->GetWindowHeight(), 1.0f, 5000.0f);
	m_pScene->SetupSkyBox("texture/FullMoonLeft.tga", "texture/FullMoonRight.tga", "texture/FullMoonUp.tga", "texture/FullMoonDown.tga", "texture/FullMoonFront.tga", "texture/FullMoonBack.tga", 1.f * SCENE_RADIUS);
	m_pHero->Create();
 	float yellow[] = { 8.f, .8f, .1f, 1.f };
	CPointLight *pLight = (CPointLight *)m_pScene->SetupLight(0, LT_POINT, yellow);
	pLight->SetPosition(CVector3(100, 100, 100));
	m_pScene->SetupLightCamera(0, pLight->GetPosition(), -pLight->GetPosition(), CVector3(0, 1, 0), PI * 0.5f, 1.f, 1.f, 1000.f);

	for (int i = 0; i < INIT_NPC_NUM; ++i)
	{
		float color[4] = { 0 };		
		for (int i = 0; i < 4; ++i)
		{
			color[i] = (rand() % 255 + 1) / 255.0f;
		}
		float radius = 1;// rand() % MAX_NPC_RADIUS + 1.f;
		CNPC *pNPC = new CNPC(color, radius);

		float x = rand() % (GROUND_RADIUS * 2) - GROUND_RADIUS * 1.f;
		float y = radius;// rand() % (SCENE_RADIUS * 2) - SCENE_RADIUS * 1.f;
		float z = rand() % (GROUND_RADIUS * 2) - GROUND_RADIUS * 1.f;

		pNPC->SetPosition(CVector3(x, y, z));
		m_listNPC.push_back(pNPC);
		
	}


	m_pGround = new CGround();
	m_pGround->Create();
	
	m_pHero->BeginMove();
}

void CGameScene::Update(int delta)
{	
	for (auto it = m_listNPC.begin(); it != m_listNPC.end(); ++it)
	{		
		if ((m_pHero->GetPosition() - (*it)->GetPosition()).getLengthSQ() <= 4.0f)
		{
			m_pHero->Increase();

			float x = rand() % (SCENE_RADIUS * 2) - SCENE_RADIUS * 1.f;
			float y = 1;
			float z = rand() % (SCENE_RADIUS * 2) - SCENE_RADIUS * 1.f;
			(*it)->SetPosition(CVector3(x, y, z));
		}

		(*it)->Update(delta);
	}
	if (m_pHero)
		m_pHero->Update(delta);
}
