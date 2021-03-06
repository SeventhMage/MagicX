#ifndef _RENDER_C_MATERIAL_MANAGER_H_
#define _RENDER_C_MATERIAL_MANAGER_H_

#include "base/CSingleton.h"
#include "render/IMaterialManager.h"

#include <map>
#include <string>

namespace se
{
	namespace render
	{
		class CMaterialManager : public IMaterialManager, public base::CSingleton<CMaterialManager>
		{
		public:
			CMaterialManager();
			virtual ~CMaterialManager();
			virtual IMaterial *CreateMaterial(const char *filename);			
			virtual void DestroyMaterial(IMaterial *);
			virtual int GetMaterialID(const char *filename);			
		private:
			std::map<uint, IMaterial *> m_mapMaterial;
		};
	}
}

#endif