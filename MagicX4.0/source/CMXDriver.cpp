#include "CMXDriver.h"

namespace mx
{
	CMagicX *mx;
	
	CMXDriver::CMXDriver()
	{	
		m_pDevice = new CDeviceWin();
		m_pRenderer = new CGLRenderer();
		m_pResourceMgr = new CResourceManager();
		m_pSceneMgr = new CSceneManager();
		mx = new CMagicX(m_pDevice, m_pRenderer, m_pResourceMgr, m_pSceneMgr);
	}
	
	CMXDriver::~CMXDriver()
	{
		delete mx;
		delete m_pDevice;
		delete m_pRenderer;
		delete m_pResourceMgr;
		delete m_pSceneMgr;
	}
	
	CMXDriver mxDriver;
}