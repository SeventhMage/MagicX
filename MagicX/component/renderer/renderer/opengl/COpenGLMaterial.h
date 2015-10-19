#ifndef _C_OPENGL_MATERIAL_H_
#define _C_OPENGL_MATERIAL_H_

#include "../../include/IShaderProgram.h"

namespace mx
{
	namespace render
	{
		class COpenGLMaterial
		{
		public:
			COpenGLMaterial();
			~COpenGLMaterial();
			
			void CreateShaderProgram();
		protected:
			IShaderProgram *m_shaderProgram;
		};
	}
}

#endif