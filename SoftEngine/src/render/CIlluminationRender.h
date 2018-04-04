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
						
			virtual Color CalcIllumination(const Color &srcColor, const math::CVector3 &viewDir, const math::CVector3 &normalDir);

			void SetIlluminationDir(const math::CVector3 &dir){ m_IlluminationDir = dir; }
			void SetIlluminationDis(float dis) { m_IlluminationDis = dis; }


			void SetRenderParam(float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient);
		protected:
			math::CVector3 m_IlluminationDir;
			float m_IlluminationDis;

			float m_ambientCoefficient;
			float m_diffuseCoefficient;
			float m_specularCoefficient;
			int m_specularityCoefficient;
		};
	}
}

#endif