#ifndef _SE_C_SOFT_ENGINE_H_
#define _SE_C_SOFT_ENGINE_H_

#include "base/CSingleton.h"
#include "device/IDeviceManager.h"
#include "resource/IResourceManager.h"
#include "scene/ISceneManager.h"

namespace se
{
	class CSoftEngine : public base::CSingleton<CSoftEngine>
	{
	public:
		~CSoftEngine();
		void InitEngine(int x, int y, int width, int height, bool fullScreen = false);
		void DestroyEngine();

		static device::IDevice *GetDevice();
		static render::IRenderer *GetRenderer(){ return m_pRenderer; }
		static resource::IResourceManager *GetResourceManager() { return m_pResourceMgr; }
		static scene::ISceneManager *GetSceneManager() { return m_pSceneMgr; }
	private:
		static device::IDeviceManager *m_pDeviceMgr;
		static render::IRenderer *m_pRenderer;
		static resource::IResourceManager *m_pResourceMgr;
		static scene::ISceneManager *m_pSceneMgr;
	};
}

#endif