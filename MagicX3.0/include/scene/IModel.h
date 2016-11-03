/************************************************************************/
/* 模型接口
/* 网格数据+纹理资源组成模型数据
/************************************************************************/

#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class IModel
		{
		public:
			virtual ~IModel();

			virtual bool LoadMesh(const char *filename) = 0;
			virtual bool LoadMaterial(const char *filename) = 0;
		};
	}
}