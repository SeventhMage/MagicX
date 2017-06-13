#ifndef _RENDER_I_MATERIAL_MANAGER_H_
#define _RENDER_I_MATERIAL_MANAGER_H_

#include "IMaterial.h"

namespace se
{
	namespace render
	{
		class IMaterialManager
		{
		public:
			virtual ~IMaterialManager(){}
			virtual IMaterial *CreateMaterial(const char *filename) = 0;
			virtual void DestroyMaterial(int id) = 0;
			virtual IMaterial *GetMaterial(int id) = 0;
		};
	}
}

#endif