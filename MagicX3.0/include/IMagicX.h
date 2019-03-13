/************************************************************************/
/* 引擎入口                                                             */
/************************************************************************/
#ifndef _MX_I_MAGIC_X_H_
#define _MX_I_MAGIC_X_H_

#include "mxDef.h"
#include "mxType.h"

//base
#include "base/CSingleton.h"
#include "base/mxString.h"
#include "base/CVirtualTraceBall.h"

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
#include "device/CEventManager.h"

//resource
#include "resource/IResourceManager.h"
#include "resource/IImageManager.h"
#include "resource/IResource.h"
#include "resource/IImage.h"

//scene
#include "scene/light/ILight.h"
#include "scene/light/CDirectionalLight.h"
#include "scene/light/CPointLight.h"
#include "scene/light/CSpotLight.h"
#include "scene/light/CAmbientLight.h"
#include "scene/CUnit.h"
#include "scene/CSphereEntiy.h"
#include "scene/CSphere.h"
#include "scene/CEntity.h"
#include "scene/CUnit.h"
#include "scene/IModel.h"
#include "scene/ISceneManager.h"
#include "scene/IScene.h"
#include "scene/ISceneNode.h"
#include "scene/IVertex.h"

//physics

//render
#include "render/renderobject/IRenderObject.h"
#include "render/renderobject/CReflectObject.h"
#include "render/renderobject/CRenderObject.h"
#include "render/renderobject/CColorFlatObject.h"
#include "render/renderobject/CColorPointLightObject.h"
#include "render/renderobject/CShadowMapObject.h"
#include "render/IRenderer.h"
#include "render/renderphase/IRenderPhaseManager.h"
#include "render/renderphase/IRenderPhase.h"
#include "render/IMaterialManager.h"

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
		
		virtual void Initialize() = 0;

		//获取当前设备
		virtual IDevice *GetDevice() = 0;

		//获取设备管理器
		virtual IDeviceManager *GetDeviceManager() = 0;

		//获取场景管理器
		virtual ISceneManager *GetSceneManager() = 0;
		
		//获取资源管理器
		virtual IResourceManager *GetResourceManager(EResourceType type) = 0;

		virtual IRenderPhaseManager *GetRenderPhaseManager() = 0;

		//获取渲染器
		virtual IRenderer *GetRenderer() = 0;

		//运行
		virtual void Run(int) = 0;
	};
}

#endif