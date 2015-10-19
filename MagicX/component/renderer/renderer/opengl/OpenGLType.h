#ifndef _MX_RENDER_OPENGL_TYPE_H_
#define _MX_RENDER_OPENGL_TYPE_H_

#include "glew/GL/glew.h"

namespace mx
{
	namespace render
	{
		static GLenum GetGLVariableType(RendererVariableType vat)
		{
			switch (vat)
			{
			case RVT_BYTE:
				return GL_BYTE;
			case RVT_UBYTE:
					return GL_UNSIGNED_BYTE;
			case RVT_SHORT:
					return GL_SHORT;
			case RVT_USHORT:
				return GL_UNSIGNED_SHORT;
			case RVT_INT:
				return GL_INT;
			case RVT_UINT:
				return GL_UNSIGNED_INT;
			case RVT_FIXED:
				return GL_FIXED;
			case RVT_FLOAT:
				return GL_FLOAT;
			case RVT_HALF_FLOAT:
				return GL_HALF_FLOAT;
			case RVT_DOUBLE:
				return GL_DOUBLE;
			case RVT_INT_2_10_10_10_REV:
				return GL_INT_2_10_10_10_REV;
			case RVT_UINT_2_10_10_10_REV:
				return GL_UNSIGNED_INT_2_10_10_10_REV;
			default:
				break;
			}
			return GL_FLOAT;
		}

		static int GetGLGPUBufferMode(GPUBufferMode mode)
		{
			switch (mode)
			{
			case GBM_LINES:
				return GL_LINE;
			case GBM_POINTS:
				return GL_POINT;
			case  GBM_TRIANGLES:
				return GL_TRIANGLES;
			case GBM_TRIANGLE_STKIP:
				return GL_TRIANGLE_STRIP;
			case GBM_TRIANGLE_FAN:
				return GL_TRIANGLE_FAN;
			default:
				;
			}
			return GL_TRIANGLES;
		}

		static int GetGLGPUBufferUsage(GPUBufferUsage usage)
		{
			switch (usage)
			{
			case GBU_STREAM_DRAW:
				return GL_STREAM_DRAW;
			case GBU_STREAM_READ:
				return GL_STREAM_READ;
			case GBU_STREAM_COPY:
				return GL_STREAM_COPY;
			case GBU_STATIC_DRAW:
				return GL_STATIC_DRAW;
			case GBU_STATIC_READ:
				return GL_STATIC_READ;
			case GBU_STATIC_COPY:
				return GL_STATIC_COPY;
			case GBU_DYNAMIC_DRAW:
				return GL_DYNAMIC_DRAW;
			case GBU_DYNAMIC_READ:
				return GL_DYNAMIC_READ;
			case GBU_DYNAMIC_COPY:
				return GL_DYNAMIC_COPY;
			default:
				;
			}
			return GL_DYNAMIC_DRAW;
		}
		
		static int GetGLShaderType(ShaderType type)
		{
			switch (type)
			{
			case ST_VERTEX:
				return GL_VERTEX_SHADER;
			case ST_FRAGMENT:
				return GL_FRAGMENT_SHADER;
			}
			return 0;
		}
	}
}

#endif
