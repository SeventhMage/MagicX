#include "CMagicX.h"
#include "CMXDriver.h"
#include "device/CEventManager.h"
namespace mx
{
	CMagicX::CMagicX(IDevice *pDevice, IRenderer *pRenderer, IResourceManager *pResourceMgr, ISceneManager *pSceneMgr)
		:m_pDevice(pDevice), m_pRenderer(pRenderer), m_pResourceMgr(pResourceMgr), m_pSceneMgr(pSceneMgr)
	{
		
	}

	CMagicX::~CMagicX()
	{
		
	}

}