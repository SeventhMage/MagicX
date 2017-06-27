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
			virtual int CreateMaterial(const char *filename) = 0;
			virtual void DestroyMaterial(int materialId) = 0;
			virtual IMaterial *GetMaterial(int materialId) = 0;

		};
	}
}

#endif