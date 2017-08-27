#include "CSoftEngine.h"
#include "base/seDef.h"
#include "device/CDeviceManager.h"
#include "device/CEventManager.h"
#include "render/software/CSoftRenderer.h"
#include "render/CMaterialManager.h"
#include "resource/CResourceManager.h"
#include "scene/CSceneManager.h"
#include "render/CTextureManager.h"


namespace se
{	
	device::IDeviceManager *CSoftEngine::m_pDeviceMgr = nullptr;
    device::IEventManager *CSoftEngine::m_pEventMgr = nullptr;
	render::IRenderer *CSoftEngine::m_pRenderer = nullptr;
	render::IMaterialManager *CSoftEngine::m_pMaterialManager = nullptr;
	resource::IResourceManager *CSoftEngine::m_pResourceMgr = nullptr;
	scene::ISceneManager *CSoftEngine::m_pSceneMgr = nullptr;
	render::ITextureManager *CSoftEngine::m_pTextureMgr = nullptr;

	CSoftEngine::~CSoftEngine()
	{
		DestroyEngine();
	}

	void CSoftEngine::InitEngine(render::RenderDriverType driver, int x, int y, int width, int height, bool fullScreen /* = false */)
	{
		m_pDeviceMgr = device::CDeviceManager::NewInstance();
        m_pEventMgr = device::CEventManager::NewInstance();
		m_pSceneMgr = scene::CSceneManager::NewInstance();
		m_pResourceMgr = resource::CResourceManager::NewInstance();

		m_pMaterialManager = render::CMaterialManager::NewInstance();
		m_pTextureMgr = render::CTextureManager::NewInstance();

		switch (driver)
		{
		case se::render::RDT_SOFTWARE:
			m_pRenderer = render::CSoftRenderer::NewInstance();
			break;
		default:
			m_pRenderer = render::CSoftRenderer::NewInstance();
		}

		m_pDeviceMgr->CreateDevice(m_pRenderer->GetRenderDriver(), x, y, width, height, fullScreen);

	}


	void CSoftEngine::DestroyEngine()
	{
		resource::CResourceManager::DeleteInstance();
		scene::CSceneManager::DeleteInstance();
		render::CSoftRenderer::DeleteInstance();
		device::CDeviceManager::DeleteInstance();
        device::CEventManager::DeleteInstance();
		render::CMaterialManager::DeleteInstance();
		render::CTextureManager::DeleteInstance();
	}

	device::IDevice * CSoftEngine::GetDevice()
	{
		return m_pDeviceMgr->GetDevice();
	}

}
