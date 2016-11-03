/************************************************************************/
/* ���������ʵ��                                                       */
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
		virtual IResourceManager *GetResourceManager();
		virtual IRenderer *GetRenderer();
	private:
		IDeviceManager *m_pDeviceMgr;
		ISceneManager *m_pSceneMgr;
		IResourceManager *m_pResourceMgr;
		IRenderer *m_pRenderer;
		
	};
}

#endif
