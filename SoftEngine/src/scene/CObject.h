#ifndef _SCENE_C_OBJECT_H_
#define _SCENE_C_OBJECT_H_

#include "scene/IObject.h"
#include "math/CRay.h"
#include "render/SColor.h"

namespace se
{
	namespace scene
	{
		class CObject : public IObject
		{
		public:
			CObject(uint id);
			~CObject();
			virtual uint GetID() const { return m_Id; }
		private:
			uint m_Id;
		};
	}
}

#endif