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

			virtual bool Load(const char *filename) = 0;
		};
	}
}