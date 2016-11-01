/************************************************************************/
/* Ä£ÐÍ                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_MODEL_H_
#define _MX_SCENE_C_MODEL_H_

#include "scene/IModel.h"

namespace mx
{
	namespace scene
	{
		class CModel : public IModel
		{
		public:
			CModel();
			virtual ~CModel();

			virtual IMesh *GetMesh() { return m_pMesh; }
			virtual ITextureResource *GetTextureResource() { return m_pTextureRes; }
		private:
			IMesh *m_pMesh;
			ITextureResource *m_pTextureRes;

		};
	}
}

#endif