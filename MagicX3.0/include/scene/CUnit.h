/************************************************************************/
/* 场景中物体单元                                                       */
/************************************************************************/

#ifndef _MX_SCENE_C_UNIT_H_
#define _MX_SCENE_C_UNIT_H_

#include "CEntity.h"
#include "IModel.h"
#include "render/IVertexArrayObject.h"
#include "render/ITexture.h"
#include "render/IRenderable.h"
#include "IVertex.h"


namespace mx
{
	namespace scene
	{
		using namespace render;
		class CUnit : public CEntity
		{
		public:
			CUnit();
			CUnit(IVertex *pVertex, const char *texfile = "");

			virtual ~CUnit();

			virtual void UpdateImp(int delta);			

			void LoadModel(const char *filename);	

			//根据顶点属性返回stride
			uint GetVertexStride(EVertexAttribute attr);
		private:
			void CreateRenderable(IVertex *pVertex, const char *texfile);
		private:
			IModel *m_pMode;
			IVertexArrayObject *m_pVAO;
			ITexture *m_pTexture;
			IRenderable *m_pRenderable;
		};
	}
}

#endif