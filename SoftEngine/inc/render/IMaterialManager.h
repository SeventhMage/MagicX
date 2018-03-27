#ifndef _RENDER_I_MATERIAL_MANAGER_H_
#define _RENDER_I_MATERIAL_MANAGER_H_

#include "IMaterial.h"
#include "base/seType.h"

namespace se
{
	namespace render
	{
		class IMaterialManager
		{
		public:
			virtual ~IMaterialManager(){}
			virtual IMaterial *CreateMaterial(const char *filename) = 0;
			virtual void DestroyMaterial(IMaterial *) = 0;
			virtual int GetMaterialID(const char *filename) = 0;			
		};
	}
}

#endif