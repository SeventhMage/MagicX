#ifndef _RENDER_C_MATERIAL_H_
#define _RENDER_C_MATERIAL_H_

#include "render/IMaterial.h"


namespace se
{
	namespace render
	{
		class CMaterial : public IMaterial
		{
		public:
			CMaterial(int id, const char *name);
			virtual ~CMaterial();

			virtual int GetID(){ return m_Id; }
			virtual std::string GetName(){ return m_strName; }
			virtual Color GetColor() { return m_color; };
			virtual void SetColor(const Color &color);
			virtual std::string GetIllumination() { return m_strIllumination; }
			virtual void SetIllumination(const std::string &illumination);
		private:
			int m_Id;
			std::string m_strName;
			Color m_color;
			std::string m_strIllumination;
		};
	}
}

#endif