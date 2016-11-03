#ifndef _MX_RENDER_C_GL_DEBUG_H_
#define _MX_RENDER_C_GL_DEBUG_H_

#include <stdio.h>
#include <assert.h>
#include "GL/glew.h"

namespace mx
{
	namespace render
	{
		inline void DebugGLError(const char *filename, int lineNum)
		{
			GLenum err = glGetError();
			if (err)
			{
				switch (err)
				{
				case GL_INVALID_ENUM: printf("File Line Number[%s:%d] GL_INVALID_ENUM\n", filename, lineNum); break;
				case GL_INVALID_VALUE: printf("File Line Number[%s:%d] GL_INVALID_VALUE\n", filename, lineNum); break;
				case GL_INVALID_OPERATION: printf("File Line Number[%s:%d] GL_INVALID_OPERATION\n", filename, lineNum); break;
				case GL_OUT_OF_MEMORY: printf("File Line Number[%s:%d] GL_OUT_OF_MEMORY\n", filename, lineNum); break;
				case GL_INVALID_FRAMEBUFFER_OPERATION: printf("File Line Number[%s:%d] GL_INVALID_FRAMEBUFFER_OPERATION\n", filename, lineNum); break;
				default: printf("File Line Number[%s:%d] unknown error\n", filename, lineNum); break;
				}
				assert(0);
			}
			
		}
#ifdef _DEBUG
#define GLDebug(Func) Func;DebugGLError(__FILE__, __LINE__);
#else
#define GLDebug(Func) Func;
#endif
	}
}

#endif