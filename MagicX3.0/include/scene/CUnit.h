/************************************************************************/
/* 场景中物体单元                                                       */
/************************************************************************/

#ifndef _MX_SCENE_C_UNIT_H_
#define _MX_SCENE_C_UNIT_H_

#include "IEntity.h"
#include "IModel.h"
#include "render/IVertexArrayObject.h"

namespace mx
{
	namespace scene
	{
		using namespace render;
		class CUnit : public IEntity
		{
		public:
			CUnit();
			CUnit(IVertex *pVertex, const char *texfile = nullptr);

			virtual ~CUnit();

			virtual void UpdateImp(int delta);
			virtual void RenderImp();

			void LoadModel(const char *filename);	
		private:
			void CreateRenderable(IVertex *pVertex, const char *texfile);
		private:
			IModel *m_pMode;
			IVertexArrayObject *m_pVAO;
			IRenderable *m_pRenderable;
		};
	}
}

#endif