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
			MRA_ILLUMINATION, "Illumination"
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
			virtual std::string GetValueByIdx(int index);
			virtual std::string GetValue(EMaterialResAttr attr);
			virtual math::CVector3 GetColor(){ return m_color; }
			virtual std::string GetIllumination(){ return m_illumination; }
		private:			
			std::vector<AttrValue> m_attrValue;
			math::CVector3 m_color;
			std::string m_illumination;
		};
	}
}

#endif