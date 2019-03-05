#include "CMagicX.h"
#include "device/CDeviceManager.h"
#include "scene/CSceneManager.h"
#include "resource/CResourceManager.h"
#include "resource/CImageManager.h"
#include "render/opengl//COpenGLRenderer.h"
#include "render/renderphase/CRenderPhaseManager.h"



namespace mx
{

	CMagicX::CMagicX(device::EDeviceType deviceType, render::ERenderDriverType renderDriver, int x, int y, int width, int height, bool bFullScreen /*= false*/)
	{
		m_pDeviceMgr = new CDeviceManager();

		switch (renderDriver)
		{
		case render::RDT_OPENGL:
			m_pRenderer = new COpenGLRenderer();
			break;
		case render::RDT_DIRECTX:
			break;
		case render::RDT_SOFTWARE:
			break;
		default:
			break;
		}		
		
		m_pDeviceMgr->CreateDevice(deviceType, m_pRenderer->GetRenderDriver(), x, y, width, height, bFullScreen);

		m_pSceneMgr = new CSceneManager();
		m_pResourceMgr[RT_IMAGE] = new CImageManager();
		m_pResourceMgr[RT_MESH] = 0;
		m_pResourceMgr[RT_SOUND] = 0;

		m_pRenderPhaseMgr = new CRenderPhaseManager();
		m_pRenderPhaseMgr->Initialize(m_pRenderer, width, height);
		CEventManager::NewInstance();
	}

	CMagicX::~CMagicX()
	{
		
		delete m_pDeviceMgr;
		delete m_pSceneMgr;
		delete m_pRenderer;
		for (int i = 0; i < RT_COUNT; ++i)
		{
			if (m_pResourceMgr[i])
				delete m_pResourceMgr[i];
		}

		CEventManager::DeleteInstance();
	}

	ISceneManager * CMagicX::GetSceneManager()
	{
		return m_pSceneMgr;
	}

	IResourceManager * CMagicX::GetResourceManager(EResourceType type)
	{
		return m_pResourceMgr[type];
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

	void CMagicX::Run(int delta)
	{
		m_pSceneMgr->Update(delta);
		m_pRenderPhaseMgr->ProcessRenderPhase();
		GetDevice()->SwapBuffers();
	}
}