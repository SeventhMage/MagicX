#ifndef _SE_RENDER_C_ILLUMINATION_H_
#define _SE_RENDER_C_ILLUMINATION_H_

#include "CIlluminationRender.h"
#include "render/SColor.h"
#include "math/CVector3.h"
#include "math/CMatrix4.h"

namespace se
{
	namespace render
	{
		class CIllumination
		{
		public:
			CIllumination(CIlluminationRender *pIlluminationRender = nullptr);
			~CIllumination();
			
			void SelectIlluminationRender(CIlluminationRender *pIlluminationRender){ m_pIlluminationRender = pIlluminationRender; }			
			void SetRenderParam(float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient);
			void SetPosition(const math::CVector3 &position) { m_position = position; }
			void TransformPosition(const math::CMatrix4 &viewMat);
			Color Shine(const Color &srcColor, const math::CVector3 &targetPoint, const math::CVector3 &viewDir, const math::CVector3 &normalDir);

		private:
			CIlluminationRender *m_pIlluminationRender;
			math::CVector3 m_position;
			math::CVector3 m_transPositoin;
		};
	}
}

#endif