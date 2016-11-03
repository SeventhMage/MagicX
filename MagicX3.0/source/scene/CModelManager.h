/************************************************************************/
/* 模型管理器                                                           */
/************************************************************************/

#ifndef _MX_SCENE_C_MODEL_MANAGER_H_
#define _MX_SCENE_C_MODEL_MANAGER_H_

#include "scene/IModelManager.h"

#include <list>

namespace mx
{
	namespace scene
	{
		class CModelManager : public IModelManager
		{
		public:
			CModelManager();
			virtual ~CModelManager();

			virtual bool CreateModel(const char *filename);
			virtual void DestroyMode(IModel *pModel);
			virtual void Clear();
		private:
			std::list<IModel *>m_listModel;
		};
	}
}

#endif