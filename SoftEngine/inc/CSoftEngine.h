#ifndef _SE_C_SOFT_ENGINE_H_
#define _SE_C_SOFT_ENGINE_H_

#include "base/CSingleton.h"
#include "base/Log.h"
#include "device/IDeviceManager.h"
#include "device/IEventManager.h"
#include "resource/IResourceManager.h"
#include "scene/ISceneManager.h"
#include "scene/IObjectManager.h"
#include "render/IMaterialManager.h"
#include "render/ITextureManager.h"
#include "render/IRenderer.h"
#include "render/IRenderDriver.h"

namespace se
{
	class CSoftEngine : public base::CSingleton<CSoftEngine>
	{
	public:
		~CSoftEngine();
		void InitEngine(render::RenderDriverType driver, int x, int y, int width, int height, bool fullScreen = false);
		void DestroyEngine();

		static device::IDevice *GetDevice();
        static device::IEventManager *GetEventManager(){return m_pEventMgr; }
		static render::IRenderer *GetRenderer(){ return m_pRenderer; }
		static render::RenderDriverType GetRenderDriverType() { return m_pRenderer->GetRenderDriverType(); }
		static render::IMaterialManager *GetMaterialManager(){ return m_pMaterialManager; }
		static render::ITextureManager *GetTextureManager(){ return m_pTextureMgr; }
		static resource::IResourceManager *GetResourceManager() { return m_pResourceMgr; }
		static scene::ISceneManager *GetSceneManager() { return m_pSceneMgr; }
		static scene::IObjectManager *GetObjectManager() { return m_pObjectMgr; }
	private:
		static device::IDeviceManager *m_pDeviceMgr;
        static device::IEventManager *m_pEventMgr;
		static render::IRenderer *m_pRenderer;
		static render::IMaterialManager *m_pMaterialManager;
		static render::ITextureManager *m_pTextureMgr;
		static resource::IResourceManager *m_pResourceMgr;
		static scene::ISceneManager *m_pSceneMgr;
		static scene::IObjectManager *m_pObjectMgr;
	};
}

#endif
