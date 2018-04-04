#ifndef _SE_RENDER_C_SOFT_VERTEX_SHADER_H_
#define _SE_RENDER_C_SOFT_VERTEX_SHADER_H_

#include "render/IShader.h"
#include "render/SColor.h"
#include "math/CMatrix4.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include "../CIllumination.h"

namespace se
{
	namespace render
	{			
		class CSoftVertexShader : public IShader
		{
		public:			
			CSoftVertexShader();
			virtual ~CSoftVertexShader();
			virtual EShaderType GetType() const { return ST_VERTEX; }

			virtual void SetUniform(EUniformName uniformName, ubyte *data);
			virtual void SetIllumination(CIllumination *illumination) { m_pIllumination = illumination; }
			virtual void PushInAttribute(base::EVertexAttribute vertType, const void *source);
			virtual void PopOutAttribute(base::EVertexAttribute vertType, void *&source);
		public:			
			virtual math::CVector4 &Process();
		private:
			CIllumination *m_pIllumination;
			math::CMatrix4 m_wordMatrix;
			math::CMatrix4 m_viewMatrix;
			math::CMatrix4 m_projMatrix;
			math::CMatrix4 m_normalMatrix;
			Color m_color;

			float m_ambientCoefficient;
			float m_diffuseCoefficient;
			float m_specularCoefficient;
			int m_specularityCoefficient;

			const math::CVector3 *m_inPosition;
			const math::CVector3 *m_inNormal;			
			const Color *m_inColor;
			const math::CVector2 *m_inTexCoord;

			math::CVector3 m_outPosition;
			math::CVector3 m_outNormal;
			Color m_outColor;
			math::CVector2 m_outTexCoord;
		};
	}
}

#endif