﻿/************************************************************************/
/* 每一组渲染队列包含了使用当前材质的渲染列表                           */
/************************************************************************/
#ifndef _RENDER_I_RENDER_QUEUE_H_
#define _RENDER_I_RENDER_QUEUE_H_

#include <map>

#include "math/CMatrix4.h"
#include "IRenderCell.h"
#include "IMaterial.h"
#include "scene/ICamera.h"


namespace se
{
	namespace render
	{
		class IRenderQueue
		{
		public:
			virtual ~IRenderQueue(){}
			virtual void AddRenderCell(IRenderCell *pCell) = 0;
			virtual void Clear() = 0;
			virtual IMaterial *GetMaterial() const = 0;
			virtual void Render(scene::ICamera *pCamera) = 0;
		};

		typedef std::map<int, IRenderQueue *> RenderQueueGroup;
	}
}

#endif