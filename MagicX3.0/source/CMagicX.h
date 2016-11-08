/************************************************************************/
/* 引擎主入口实现                                                       */
/************************************************************************/
#ifndef _MX_C_MAGIC_X_H_
#define _MX_C_MAGIC_X_H_

#include "IMagicX.h"


namespace mx
{
	class CMagicX : public IMagicX
	{
	public:
		CMagicX(device::EDeviceType deviceType, render::ERenderDriverType  renderDriver, int x, int y, int width, int height, bool bFullScreen = false);
		~CMagicX();

		virtual IDevice *GetDevice();
		virtual IDeviceManager *GetDeviceManager();
		virtual ISceneManager *GetSceneManager();
		virtual IResourceManager *GetResourceManager(EResourceType type);
		virtual IRenderer *GetRenderer();
		virtual IEntityManager *GetEntityManager();
	private:
		IDeviceManager *m_pDeviceMgr;
		ISceneManager *m_pSceneMgr;
		IResourceManager *m_pResourceMgr[RT_COUNT];
		IRenderer *m_pRenderer;
		IEntityManager *m_pEntityMgr;
		
	};
}

#endif

