#ifndef _RESOURCE_C_MATERIAL_RESOURCE_H_
#define _RESOURCE_C_MATERIAL_RESOURCE_H_

#include "resource/IMaterialResource.h"
#include "math/CVector3.h"

#include <map>

namespace se
{
	namespace resource
	{
		class CMaterialResource : public IMaterialResource
		{
		public:
			CMaterialResource(const char *filename);
			virtual ~CMaterialResource();
			virtual int GetAttrCount();
			virtual std::string GetAttrByIdx(int index);
			virtual std::string GetValueByIdx(int index);
			virtual std::string GetValue(const std::string &attr);
			virtual math::CVector3 GetColor(){ return m_color; }
			virtual std::string GetIllumination(){ return m_illumination; }
		private:
			std::map<std::string, std::string>m_mapAttrValue;
			math::CVector3 m_color;
			std::string m_illumination;
		};
	}
}

#endif