#ifndef _RENDER_C_MATERIAL_MANAGER_H_
#define _RENDER_C_MATERIAL_MANAGER_H_

#include "base/CSingleton.h"
#include "render/IMaterialManager.h"

#include <map>

namespace se
{
	namespace render
	{
		class CMaterialManager : public IMaterialManager, public base::CSingleton<CMaterialManager>
		{
		public:
			CMaterialManager();
			virtual ~CMaterialManager();
			virtual int CreateMaterial(const char *filename);
			virtual void DestroyMaterial(int materialId);
			virtual IMaterial *GetMaterial(int materialId);			
		private:
			std::map<int, IMaterial *> m_mapMaterial;
		};
	}
}

#endif