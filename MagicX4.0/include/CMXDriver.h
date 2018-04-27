#ifndef _MX_C_MXDRIVER_H_
#define _MX_C_MXDRIVER_H_

#include "CMagicX.h"

namespace mx
{
	class CMXDriver
	{
	public:
		friend class CMagicX;
		CMXDriver();
		~CMXDriver();
	private:
		IDevice *m_pDevice;
		IRenderer *m_pRenderer;
		IResourceManager *m_pResourceMgr;
		ISceneManager *m_pSceneMgr;
	};

	extern CMagicX *magic;
}

#endif