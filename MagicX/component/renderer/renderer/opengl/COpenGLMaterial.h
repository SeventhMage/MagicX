#ifndef _C_OPENGL_MATERIAL_H_
#define _C_OPENGL_MATERIAL_H_

#include "COpenGLShaderProgram.h"
#include "COpenGLTexture.h"

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
			CString m_sFileName;
			IShaderProgram *m_pShaderProgram;
			COpenGLTexture *m_pTexture;
		};
	}
}

#endif