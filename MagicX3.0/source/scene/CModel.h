/************************************************************************/
/* Ä£ÐÍ                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_MODEL_H_
#define _MX_SCENE_C_MODEL_H_

#include "scene/IModel.h"
#include "scene/IMesh.h"
#include "render/renderobject/IRenderObject.h"

namespace mx
{
	namespace scene
	{
		using namespace resource;		

		class CModel : public IModel
		{
		public:
			CModel();
			virtual ~CModel();
			
			virtual bool Load(const char *filename);
		private:
			IMesh *m_pMesh;
			render::IRenderObject *m_pRenderObject;
		};
	}
}

#endif