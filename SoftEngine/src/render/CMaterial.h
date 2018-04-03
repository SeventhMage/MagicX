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
			virtual void SetAmbientCoefficient(float coe) { m_ambientCoefficient = coe; }
			virtual void SetDiffuseCoefficient(float coe) { m_diffuseCoefficient = coe; }
			virtual void SetSpecularCoefficient(float coe) { m_specularCoefficient = coe; }
			virtual void SetSpecularityCoefficient(int coe) { m_specularityCoefficient = coe; }
			virtual float GetAmbientCoefficient() { return m_ambientCoefficient; }
			virtual float GetDiffuseCoefficient() { return m_diffuseCoefficient; }
			virtual float GetSpecularCoefficient() { return m_specularCoefficient; }
			virtual int GetSpecularityCoefficient() { return m_specularityCoefficient; }
			virtual IShaderProgram *GetShaderProgram() const;
			virtual uint GetShaderProgramID() const { return m_shaderProgramId; }
		private:
			uint m_Id;
			std::string m_strName;
			Color m_color;
			std::string m_strIllumination;
			uint m_shaderProgramId;

			float m_ambientCoefficient;
			float m_diffuseCoefficient;
			float m_specularCoefficient;
			int m_specularityCoefficient;
		};
	}
}

#endif