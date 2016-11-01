/************************************************************************/
/* 模型接口
/* 网格数据+纹理资源组成模型数据
/************************************************************************/

#include "resource/IMesh.h"
#include "resource/ITextureResource.h"

namespace mx
{
	namespace scene
	{
		using namespace resource;
		class IModel
		{
		public:
			virtual ~IModel();

			virtual IMesh *GetMesh() = 0;
			virtual ITextureResource *GetTextureResource() = 0;
		};
	}
}