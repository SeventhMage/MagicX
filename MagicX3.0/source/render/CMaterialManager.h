#ifndef _MX_RENDER_C_MATERIAL_MANAGER_H_
#define _MX_RENDER_C_MATERIAL_MANAGER_H_

#include "render/IMaterialManager.h"
#include <map>

namespace mx
{
	namespace render
	{
		class CMaterialManager : public IMaterialManager
		{
		public:
			CMaterialManager();
			~CMaterialManager();

			virtual void LoadMaterial(const char *root);
			virtual IMaterial *GetMaterial(const char *name);
			virtual IMaterial *GetMaterial(int id);

		protected:
			IMaterial *CreateMaterial(int id, const char *name);
		private:
			std::map<int, IMaterial *> m_mapMaterials;
		};
	}
}

#endif