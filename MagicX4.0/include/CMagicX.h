//引擎主程序，主板程序
#ifndef _C_MAGIC_X_H_
#define _C_MAGIC_X_H_

#include "device/IDevice.h"
#include "render/IRenderer.h"
#include "resource/IResourceManager.h"
#include "scene/ISceneManager.h"

namespace mx
{
	class CMagicX
	{
	public:
		//通过驱动程序选择组件并初始化
		CMagicX(IDevice *pDevice, IRenderer *pRenderer, IResourceManager *pResourceMgr, ISceneManager *pSceneMgr);
		~CMagicX();
		
		//用户接口
		ISceneManager *GetSceneManager() { return m_pSceneMgr; }
		IRenderer *GetRenderer() { return m_pRenderer; }
		IDevice *GetDevice() { return m_pDevice; }
		
	private:
			//提供动态更换组件接口
		void SetDevice(IDevice *pDevice) { m_pDevice = pDevice; }
		void SetRenderer(IRenderer *pRenderer) { m_pRenderer = pRenderer; }
		void SetResourceManager(IResourceManager *pMgr) { m_pResourceMgr = pMgr; }
		void SetSceneManager(ISceneManager *pMgr) { m_pSceneMgr = pMgr; }
	private:
		IDevice *m_pDevice;
		IRenderer *m_pRenderer;
		IResourceManager *m_pResourceMgr;
		ISceneManager *m_pSceneMgr;		
	};
}

#endif