/************************************************************************/
/* 场景中物体单元                                                       */
/************************************************************************/

#ifndef _MX_SCENE_C_UNIT_H_
#define _MX_SCENE_C_UNIT_H_

#include "IEntity.h"
#include "IModel.h"

namespace mx
{
	namespace scene
	{
		class CUnit : public IEntity
		{
		public:
			CUnit();
			virtual ~CUnit();

			virtual void Update(int delta);

			void LoadModel(const char *filename);			
		private:
			IModel *m_pMode;
			IRenderable *m_pRenderable;
		};
	}
}

#endif