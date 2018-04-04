#ifndef _RESOURCE_C_MATERIAL_RESOURCE_H_
#define _RESOURCE_C_MATERIAL_RESOURCE_H_

#include "resource/IMaterialResource.h"
#include "math/CVector3.h"

#include <map>
#include <vector>

namespace se
{
	namespace resource
	{

		typedef struct SMaterialResourceAttribute
		{
			int attrId;
			char *attrName;
		}MRAttribute;

		static MRAttribute GetMSAttribute[MRA_COUNT] = {
			MRA_COLOR, "Color",
			MRA_ILLUMINATION, "Illumination",
			MRA_AMBIENT_COE, "AmbientCoe",
			MRA_DIFFUSE_COE, "DiffuseCoe",
			MRA_SPECULAR_COE, "SpecularCoe",
			MRA_SPECULARITY_COE, "SpecularityCoe"
		};		

		class CMaterialResource : public IMaterialResource
		{
		public:

			typedef struct AttrValue
			{
				EMaterialResAttr attr;
				std::string value;
			};

			CMaterialResource(const char *filename);
			virtual ~CMaterialResource();
			virtual int GetAttrCount(){ return m_attrValue.size(); }			
			virtual std::string GetValueByIdx(uint index);
			virtual std::string GetValue(EMaterialResAttr attr);
		private:
			EMaterialResAttr GetAttrID(const std::string &strAttr);
			bool ReadLine(std::ifstream &in, char *out, int size);
		private:			
			std::vector<AttrValue> m_attrValue;
		};
	}
}

#endif