#include "CMXDriver.h"
#include "devicewin/CDeviceWin.h"
#include "glrender/CGLRenderer.h"
#include "resource/CResourceManager.h"
#include "scene/CSceneManager.h"
#include "device/CEventManager.h"

namespace mx
{
	CMagicX *magic = nullptr;
	
	CMXDriver::CMXDriver()
	{			
		CEventManager::NewInstance();
		m_pRenderer = new CGLRenderer();
		m_pDevice = new CDeviceWin(m_pRenderer, 0, 0, 960, 640, false);
		m_pResourceMgr = new CResourceManager();
		m_pSceneMgr = new CSceneManager();
		magic = new CMagicX(m_pDevice, m_pRenderer, m_pResourceMgr, m_pSceneMgr);		
	}
	
	CMXDriver::~CMXDriver()
	{
		delete magic;
		delete m_pDevice;
		delete m_pRenderer;
		delete m_pResourceMgr;
		delete m_pSceneMgr;		
		CEventManager::DeleteInstance();
	}
	
	CMXDriver mxDriver;
}