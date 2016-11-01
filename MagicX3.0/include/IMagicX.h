/************************************************************************/
/* 引擎入口                                                             */
/************************************************************************/
#ifndef _MX_I_MAGIC_X_H_
#define _MX_I_MAGIC_X_H_

#include "mxDef.h"
#include "mxType.h"

//base
#include "base/CSingleton.h"

//math
#include "math/CBoundingBox.h"
#include "math/CFrustum.h"
#include "math/CMatrix4.h"
#include "math/CPlane3.h"
#include "math/CQuaternion.h"
#include "math/CVector2.h"
#include "math/CVector3.h"

//net

//device
#include "device/EEvent.h"
#include "device/IDevice.h"
#include "device/IDeviceManager.h"
#include "device/IEvent.h"
#include "device/IKeyEvent.h"

//resource
#include "resource/IResourceManager.h"

//scene
#include "scene/ISceneManager.h"
#include "scene/IScene.h"
#include "scene/ISceneNode.h"

//physics

//render
#include "render/IRenderer.h"

namespace mx
{
	using namespace base;
	//using namespace math;
	//using namespace net;
	using namespace device;
	using namespace resource;
	using namespace scene;
	//using namespace physics;
	using namespace render;

	class IMagicX
	{
	public:
		virtual ~IMagicX(){};

		//获取当前设备
		virtual IDevice *GetDevice() = 0;

		//获取设备管理器
		virtual IDeviceManager *GetDeviceManager() = 0;

		//获取场景管理器
		virtual ISceneManager *GetSceneManager() = 0;
		
		//获取资源管理器
		virtual IResourceManager *GetResourceManager() = 0;

		//获取渲染器
		virtual IRenderer *GetRenderer() = 0;
	};
}

#endif