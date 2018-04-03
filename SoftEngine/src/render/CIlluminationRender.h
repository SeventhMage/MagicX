#ifndef _SE_RENDER_C_ILLUNINATION_RENDER_H_
#define _SE_RENDER_C_ILLUNINATION_RENDER_H_

#include "render/SColor.h"
#include "math/CVector3.h"

namespace se
{
	namespace render
	{
		class CIlluminationRender
		{
		public:
			CIlluminationRender();
			virtual ~CIlluminationRender();
						
			virtual Color CalcIllumination(const Color &srcColor);

			void SetIlluminationDir(const math::CVector3 &dir){ m_IlluminationDir = dir; }
			void SetIlluminationDis(float dis) { m_IlluminationDis = dis; }

			void SetViewDir(const math::CVector3 &viewDir) { m_viewDir = viewDir; }
			void SetNormalDir(const math::CVector3 &normalDir) { m_normalDir = normalDir; }

			void SetRenderParam(float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient);
		protected:
			math::CVector3 m_IlluminationDir;
			float m_IlluminationDis;

			math::CVector3 m_viewDir;
			math::CVector3 m_normalDir;

			float m_ambientCoefficient;
			float m_diffuseCoefficient;
			float m_specularCoefficient;
			int m_specularityCoefficient;
		};
	}
}

#endif