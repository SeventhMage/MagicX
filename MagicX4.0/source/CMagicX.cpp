#include "CMagicX.h"
#include "CMXDriver.h"
namespace mx
{
	MagicX::MagicX(IDevice *pDevice, IRenderer *pRenderer, IResourceManager *pResourceMgr, ISceneManager *pSceneMgr)
		:m_pDevice(pDevice), m_pRenderer(pRenderer), m_pResourceMgr(pResourceMgr), m_pSceneMgr(pSceneMgr)
	{
	}
}