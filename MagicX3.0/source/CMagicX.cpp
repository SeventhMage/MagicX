#include "CMagicX.h"
#include "device/CDeviceManager.h"
#include "scene/CSceneManager.h"
#include "resource/CResourceManager.h"
#include "render/CRenderer.h"


namespace mx
{

	CMagicX::CMagicX(device::EDeviceType deviceType, render::ERenderDriverType renderDriver, int x, int y, int width, int height, bool bFullScreen /*= false*/)
	{
		m_pDeviceMgr = new CDeviceManager();

		m_pRenderer = new CRenderer(renderDriver);
		
		m_pDeviceMgr->CreateDevice(deviceType, m_pRenderer->GetRenderDriver(), x, y, width, height, bFullScreen);

		m_pSceneMgr = new CSceneManager();
		m_pResourceMgr = new CResourceManager();
	}

	CMagicX::~CMagicX()
	{
		delete m_pRenderer;
		delete m_pDeviceMgr;
		delete m_pSceneMgr;
		delete m_pResourceMgr;
	}

	ISceneManager * CMagicX::GetSceneManager()
	{
		return m_pSceneMgr;
	}

	IResourceManager * CMagicX::GetResourceManager()
	{
		return m_pResourceMgr;
	}

	IDevice * CMagicX::GetDevice()
	{
		return m_pDeviceMgr->GetDevice();
	}

	IDeviceManager * CMagicX::GetDeviceManager()
	{
		return m_pDeviceMgr;
	}

	IRenderer * CMagicX::GetRenderer()
	{
		return m_pRenderer;
	}

}