#ifndef _MX_SCENE_IOBJECT_H_
#define _MX_SCENE_IOBJECT_H_

#include "IReferenceCount.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace scene
	{
		using namespace render;
		class IObject : public IReferenceCount
		{
		public:
			virtual ~IObject(){}
			virtual void CreateRenderableObject(IRenderer *renderer) = 0;
		};
	}
}

#endif