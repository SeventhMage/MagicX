/************************************************************************/
/* ģ�ͽӿ�
/* ��������+������Դ���ģ������
/************************************************************************/

#ifndef _MX_SCENE_I_MODEL_H_
#define _MX_SCENE_I_MODEL_H_

#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class IModel
		{
		public:
			virtual ~IModel(){};

			virtual bool Load(const char *filename) = 0;
		};
	}
}

#endif