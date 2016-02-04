#ifndef _MX_MX_H_
#define _MX_MX_H_

#include "mxDef.h"
#include "mxType.h"

#include "core/CBoundingBox.h"
#include "core/CFrustum.h"
#include "core/CMatrix4.h"
#include "core/CPlane3.h"
#include "core/CQuaternion.h"
#include "core/CSingleton.h"
#include "core/CVector2.h"
#include "core/CVector3.h"

#include "device/IDevice.h"
#include "device/EEvent.h"
#include "device/IEvent.h"
#include "device/IKeyEvent.h"
#include "device/CEventManager.h"

#include "resource/IMesh.h"
#include "resource/CResourceManager.h"
#include "resource/CMeshManager.h"

#include "render/IMaterial.h"
#include "render/IBufferObject.h"
#include "render/IGPUBuffer.h"
#include "render/IRenderer.h"
#include "render/IShader.h"
#include "render/IRenderableObject.h"
#include "render/IShaderProgram.h"
#include "render/ITexture.h"
#include "render/SColor.h"
#include "render/SVertexAttribute.h"

#include "scene/CSceneManager.h"
#include "scene/ICamera.h"
#include "scene/ISkyBox.h"
#include "scene/ITerrain.h"
#include "scene/IWater.h"
#include "scene/IScene.h"
#include "scene/ISceneNode.h"

namespace mx
{
	using namespace mx::device;
	using namespace mx::scene;
	using namespace mx::render;
	using namespace mx::core;
	using namespace mx::resource;

	IDevice *CreateDevice(uint uPosX, uint uPosY, uint uWidth, uint uHeight, bool bFullScreen = false);
	void DestroyDevice(IDevice *device);
}

#endif