#ifndef _SE_RENDER_C_SOFT_VERTEX_SHADER_H_
#define _SE_RENDER_C_SOFT_VERTEX_SHADER_H_

#include "render/IShader.h"
#include "render/IIllumination.h"
#include "render/SColor.h"
#include "math/CMatrix4.h"
#include "math/CVector3.h"
#include "math/CVector2.h"

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
			virtual void SetIllumination(IIllumination *illumination) { m_pIllumination = illumination; }
			virtual void PushInAttribute(base::EVertexAttribute vertType, const void *source);
		public:
			virtual math::CVector4 Process(const IShaderAttribute &attrInput, IShaderAttribute &attrOutput);
			virtual math::CVector4 Process(IShaderAttribute &attrOutput);
		private:
			IIllumination *m_pIllumination;			
			math::CMatrix4 m_wordMatrix;
			math::CMatrix4 m_viewMatrix;
			math::CMatrix4 m_projMatrix;	
			Color m_color;

			math::CVector3 m_inPosition;
			math::CVector3 m_inNormal;
			Color m_inColor;
			math::CVector2 m_inTexCoord;
		};
	}
}

#endif