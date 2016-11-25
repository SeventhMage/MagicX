#include "CGameScene.h"

static const int INIT_NPC_NUM = 100;

CGameScene::CGameScene()
{
	
}

CGameScene::~CGameScene()
{
	SAFE_DEL(m_pHero);
}

void CGameScene::InitScene()
{
	m_pHero = new CHero();
	
}
