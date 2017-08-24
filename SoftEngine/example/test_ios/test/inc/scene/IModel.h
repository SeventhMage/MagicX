#ifndef _SCENE_I_MODEL_H_
#define _SCENE_I_MODEL_H_

#include "base/VertexAttribute.h"

#include <string>

namespace se
{
	namespace scene
	{

		class IModel
		{
		public:
			virtual ~IModel(){}
			virtual std::string GetMaterialName() = 0;
			virtual base::Vertices *GetVertices() = 0;
			virtual base::Indices *GetIndices() = 0;
			virtual int GetTextureID() = 0;
		};
	}
}

#endif