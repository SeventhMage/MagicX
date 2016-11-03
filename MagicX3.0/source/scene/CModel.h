/************************************************************************/
/* Ä£ÐÍ                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_MODEL_H_
#define _MX_SCENE_C_MODEL_H_

#include "scene/IModel.h"
#include "resource/IMesh.h"
#include "render/IMaterial.h"

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
			
			virtual bool LoadMesh(const char *filename);
			virtual bool LoadMaterial(const char *filename);

		private:
			IMesh *m_pMesh;
			IMaterial *m_pMaterial;

		};
	}
}

#endif