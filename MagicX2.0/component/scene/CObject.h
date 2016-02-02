#ifndef _MX_SCENE_COBJECT_H_
#define _MX_SCENE_COBJECT_H_

#include "scene/IObject.h"
#include "resource/IMesh.h"

namespace mx
{
	namespace scene
	{
		using namespace resource;
		class CObject : public IObject
		{
		public:
			CObject();
			virtual ~CObject();
			virtual void CreateRenderableObject(IRenderer *renderer);
		private:
			IMesh *m_pMesh;
		};
	}
}

#endif