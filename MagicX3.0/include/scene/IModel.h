/************************************************************************/
/* ģ�ͽӿ�
/* ��������+������Դ���ģ������
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