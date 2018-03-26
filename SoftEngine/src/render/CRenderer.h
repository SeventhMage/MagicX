#ifndef _SE_RENDER_C_RENDERER_H_
#define _SE_RENDER_C_RENDERER_H_

#include "render/IRenderer.h"

namespace se
{
	namespace render
	{
		class CRenderer : public IRenderer
		{
		public:
			CRenderer();
			virtual void UseShaderProgram(uint shaderProgramId);
			virtual void EnableVertexArrayObject(uint vaoId);
			virtual void BindBuffer(uint bufferId);
			virtual void BindTexture(uint textureId);
			
		private:
			//最终渲染时需要的对象
			uint m_shaderProgramId;
			uint m_vaoId;
			uint m_bufferId;
			uint m_textureId;
		};
	}
}

#endif