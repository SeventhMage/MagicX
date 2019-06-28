#include "CGameScene.h"
#include "mx.h"

static const int INIT_NPC_NUM = 100;
static const int SCENE_RADIUS = 512;
static const int GROUND_RADIUS = 768;


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
	m_pHero->SetLevel(1);
	m_pHero->SetMaxSpeed(10.f);
	CVector3 vDir(0, -1, -1);
	CVector3 vUp(0, 1, 0);
	m_pScene->SetupCamera(100.f, m_pHero->GetHead(), vDir, vUp, PI / 3, 1.0f * DEVICEMGR->GetDevice()->GetWindowWidth() / DEVICEMGR->GetDevice()->GetWindowHeight(), 1.0f, 5000.0f);
	m_pScene->SetupSkyBox("texture/neg_x.tga", "texture/pos_x.tga", "texture/pos_y.tga", "texture/neg_y.tga", "texture/pos_z.tga", "texture/neg_z.tga", 1.f * SCENE_RADIUS);
	CVector3 lightPos;
	CVector3 lightDir(0, -1, -1);
	CVector3 lightUp(0, 0, -1);
	CVector3 lightColor;
	lightPos.set(0, 100, 0);

 	float yellow[] = { .8f, .8f, .7f, 1.f };
	CDirectionalLight*pLight = (CDirectionalLight *)m_pScene->SetupLight(0, LT_DIRECTIONAL, yellow);
	m_pScene->SetupLight(1, LT_AMBIENT, CVector3(0.4, 0.4, 0.4).v);
	pLight->SetDirection(vDir);
	m_pScene->SetupLightCamera(0, lightPos, lightDir, lightUp, GROUND_RADIUS * DEVICEMGR->GetDevice()->GetWindowWidth() / DEVICEMGR->GetDevice()->GetWindowHeight(), GROUND_RADIUS, 1.f, GROUND_RADIUS);

	for (int i = 0; i < INIT_NPC_NUM; ++i)
	{
		float radius = 1;// rand() % MAX_NPC_RADIUS + 1.f;
		CNPC *pNPC = new CNPC(CVector3(Random(0.f, 1.f), Random(0.f, 1.f), Random(0.f, 1.f)), radius);

		float x = rand() % (GROUND_RADIUS * 2) - GROUND_RADIUS * 1.f;
		float y = radius;// rand() % (SCENE_RADIUS * 2) - SCENE_RADIUS * 1.f;
		float z = rand() % (GROUND_RADIUS * 2) - GROUND_RADIUS * 1.f;

		pNPC->SetPosition(CVector3(x, y, z));
		pNPC->SetLevel(rand() % 9 + 1);
		m_listNPC.push_back(pNPC);
		
	}


	m_pGround = new CGround();
	m_pGround->Create(GROUND_RADIUS);
	
}

void CGameScene::Update(int delta)
{	
	for (auto it = m_listNPC.begin(); it != m_listNPC.end(); ++it)
	{		
		if ((m_pHero->GetPosition() - (*it)->GetPosition()).getLengthSQ() <= 4.0f)
		{
			m_pHero->Increase((*it)->GetColor());

			float x = rand() % (SCENE_RADIUS * 2) - SCENE_RADIUS * 1.f;
			float y = 1;
			float z = rand() % (SCENE_RADIUS * 2) - SCENE_RADIUS * 1.f;
			(*it)->SetPosition(CVector3(x, y, z));
		}
		(*it)->SetSpeed((*it)->GetLevel());
		CVector3 randDir(Random(0.f, 1.f), 0, Random(0.f, 1.f));
		randDir.normalize();
		(*it)->SetDirection(randDir);
		(*it)->Update(delta);
	}
	if (m_pHero)
		m_pHero->Update(delta);
}
