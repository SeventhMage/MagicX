#include "CSoftEngine.h"
#include "base/seDef.h"
#include "device/CDeviceManager.h"
#include "render/software/CSoftRenderer.h"
#include "render/CMaterialManager.h"
#include "resource/CResourceManager.h"
#include "scene/CSceneManager.h"


namespace se
{	
	device::IDeviceManager *CSoftEngine::m_pDeviceMgr = nullptr;
	render::IRenderer *CSoftEngine::m_pRenderer = nullptr;
	render::IMaterialManager *CSoftEngine::m_pMaterialManager = nullptr;
	resource::IResourceManager *CSoftEngine::m_pResourceMgr = nullptr;
	scene::ISceneManager *CSoftEngine::m_pSceneMgr = nullptr;

	CSoftEngine::~CSoftEngine()
	{
		DestroyEngine();
	}

	void CSoftEngine::InitEngine(int x, int y, int width, int height, bool fullScreen /*= false*/)
	{
		m_pDeviceMgr = device::CDeviceManager::NewInstance();

		m_pRenderer = render::CSoftRenderer::NewInstance();

		m_pDeviceMgr->CreateDevice(device::DT_WIN32, m_pRenderer->GetRenderDriver(), x, y, width, height, fullScreen);		
		
		m_pSceneMgr = scene::CSceneManager::NewInstance();
		m_pResourceMgr = resource::CResourceManager::NewInstance();

		m_pMaterialManager = render::CMaterialManager::NewInstance();
	}


	void CSoftEngine::DestroyEngine()
	{
		resource::CResourceManager::DeleteInstance();
		scene::CSceneManager::DeleteInstance();
		render::CSoftRenderer::DeleteInstance();
		device::CDeviceManager::DeleteInstance();		
		render::CMaterialManager::DeleteInstance();
	}

	device::IDevice * CSoftEngine::GetDevice()
	{
		return m_pDeviceMgr->GetDevice();
	}

}