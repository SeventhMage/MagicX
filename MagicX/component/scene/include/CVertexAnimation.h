#ifndef _MX_SCENE_C_VERTEX_ANIMATION_H_
#define _MX_SCENE_C_VERTEX_ANIMATION_H_

#include "IAnimation.h"
#include "IMesh.h"

namespace mx
{
	namespace scene
	{
		class CVertexAnimation : public IAnimation
		{
		public:
			CVertexAnimation();
			virtual ~CVertexAnimation();

		private:
			IMesh *m_MeshList;
		};
	}
}

#endif