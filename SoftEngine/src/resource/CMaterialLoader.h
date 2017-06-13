#ifndef _RESOURCE_C_MATERIAL_LOADER_H_
#define _RESOURCE_C_MATERIAL_LOADER_H_

#include "resource/IResourceLoader.h"
#include "math/CVector3.h"
#include <string>

namespace se
{
	namespace resource
	{
		class CMaterialLoader : public IResourceLoader
		{
		public:
			CMaterialLoader(const char *filename);
			virtual ~CMaterialLoader();
			virtual math::CVector3 GetColor(){ return m_color; }
			virtual std::string GetIllumination(){ return m_illumination; }
		private:
			math::CVector3 m_color;
			std::string m_illumination;
		};
	}
}

#endif