#ifndef _MX_RENDER_I_MATERIAL_MANAGER_H_
#define _MX_RENDER_I_MATERIAL_MANAGER_H_

#include "IMaterial.h"

namespace mx
{
	namespace render
	{
		class IMaterialManager
		{
		public:
			virtual void LoadMaterial(const char *root) = 0;
			virtual IMaterial *GetMaterial(const char *name) = 0;
			virtual IMaterial *GetMaterial(int id) = 0;
		};
	}
}

#endif