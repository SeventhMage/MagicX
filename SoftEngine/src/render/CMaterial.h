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
			CMaterial(uint id, const char *name);
			virtual ~CMaterial();

			virtual uint GetID(){ return m_Id; }
			virtual std::string GetName(){ return m_strName; }
			virtual Color GetColor() { return m_color; };
			virtual void SetColor(const Color &color);
			virtual std::string GetIllumination() { return m_strIllumination; }
			virtual void SetIllumination(const std::string &illumination);
			virtual IShaderProgram *GetShaderProgram() const;
			virtual uint GetShaderProgramID() const { return m_shaderProgramId; }
		private:
			uint m_Id;
			std::string m_strName;
			Color m_color;
			std::string m_strIllumination;
			uint m_shaderProgramId;
		};
	}
}

#endif