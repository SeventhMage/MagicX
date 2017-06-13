#ifndef _RENDER_C_MATERIAL_MANAGER_H_
#define _RENDER_C_MATERIAL_MANAGER_H_

#include "base/CSingleton.h"
#include "render/IMaterialManager.h"

namespace se
{
	namespace render
	{
		class CMaterialManager : public IMaterialManager, public base::CSingleton<CMaterialManager>
		{
		public:
			CMaterialManager();
			virtual ~CMaterialManager();
		};
	}
}

#endif