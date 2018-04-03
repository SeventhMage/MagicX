#ifndef _SE_RENDER_C_SOFT_FRAGMENT_SHADER_H_
#define _SE_RENDER_C_SOFT_FRAGMENT_SHADER_H_

#include "../CIllumination.h"
#include "render/IShader.h"
#include "CSoftShaderAttribute.h"
#include "CSoftTexture.h"
#include "CSampler.h"

namespace se
{
	namespace render
	{
		class CSoftFragmentShader : public IShader
		{
		public:
			CSoftFragmentShader();
			virtual ~CSoftFragmentShader();

			virtual EShaderType GetType() const { return ST_FRAGMENT; }
			
			virtual void SetUniform(EUniformName uniformName, ubyte *data);
			virtual void SetIllumination(CIllumination *illumination) {}
			virtual void PushInAttribute(base::EVertexAttribute vertType, const void *source);			
		public:						
			const Color &Process();
			const Color &Process(const Color &inColor, uint tx, uint ty);
			void SetTextureData(ubyte *texData, uint texWidth);
		private:						
			ubyte *m_texData;
			uint m_texWidth;
			CSampler *m_pSampler;	//very slow to use it.

			Color m_inColor;
			math::CVector2 m_inTexCoord;
						
		};
	}
}

#endif