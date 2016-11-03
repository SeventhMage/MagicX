/************************************************************************/
/* 模型管理器                                                           */
/************************************************************************/

#ifndef _MX_SCENE_I_MODEL_MANAGER_H_
#define _MX_SCENE_I_MODEL_MANAGER_H_

#include "IModel.h"

namespace mx
{
	namespace scene
	{
		class IModelManager
		{
		public:
			virtual ~IModelManager(){}

			virtual bool CreateModel(const char *filename) = 0;
			virtual void DestroyMode(IModel *pModel) = 0;
			virtual void Clear() = 0;
		};
	}
}

#endif