/************************************************************************/
/* Ä£ÐÍ                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_MODEL_H_
#define _MX_SCENE_C_MODEL_H_

#include "scene/IModel.h"
#include "scene/ISceneNode.h"
#include "resource/IMesh.h"
#include "render/IMaterial.h"
#include "render/IRenderable.h"

namespace mx
{
	namespace scene
	{
		using namespace resource;
		using namespace render;

		class CModel : public IModel
		{
		public:
			CModel();
			virtual ~CModel();
			
			virtual bool Load(const char *filename);
		private:
			IMesh *m_pMesh;
			IMaterial *m_pMaterial;
		};
	}
}

#endif