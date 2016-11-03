/************************************************************************/
/* ģ�ͽӿ�
/* ��������+������Դ���ģ������
/************************************************************************/

#include "resource/IMesh.h"
#include "resource/ITextureResource.h"
#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		using namespace resource;
		class IModel : public ISceneNode
		{
		public:
			virtual ~IModel();

			virtual IMesh *GetMesh() = 0;
			virtual ITextureResource *GetTextureResource() = 0;
		};
	}
}