#ifndef _MX_MX_H_
#define _MX_MX_H_

#include "mxDef.h"
#include "mxType.h"
#include "device/IDevice.h"
#include "resource/IMesh.h"
#include "resource/CResourceManager.h"

namespace mx
{
	using namespace mx::device;
	using namespace mx::device;
	using namespace mx::render;
	using namespace mx::core;
	using namespace mx::resource;

	IDevice *CreateDevice(uint uPosX, uint uPosY, uint uWidth, uint uHeight, bool bFullScreen = false);
	void DestroyDevice(IDevice *device);
}

#endif