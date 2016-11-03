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

			virtual bool Load(const char *filename) = 0;
		};
	}
}