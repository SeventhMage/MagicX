#ifndef _MX_RENDER_OPENGL_TYPE_H_
#define _MX_RENDER_OPENGL_TYPE_H_

#include "GL/glew.h"
#include "render/ERender.h"
#include "mxType.h"
#include "resource/IImage.h"

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

		static int GetGLVariableSize(int vat)
		{
			switch (vat)
			{
			case GL_BYTE:
				return 1;
			case GL_UNSIGNED_BYTE:
				return 1;
			case GL_SHORT:
				return 2;
			case GL_UNSIGNED_SHORT:
				return 2;
			case GL_INT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_FIXED:
				return 4;
			case GL_FLOAT:
				return 4;
			case GL_HALF_FLOAT:
				return 4;
			case GL_DOUBLE:
				return 8;
			case GL_INT_2_10_10_10_REV:
				return 4;
			case GL_UNSIGNED_INT_2_10_10_10_REV:
				return 4;
			default:
				break;
			}
			return 4;
		}

		static uint GetVariableSize(RendererVariableType vat)
		{
			switch (vat)
			{
			case RVT_BYTE:
				return 1;
			case RVT_UBYTE:
				return 1;
			case RVT_SHORT:
				return 2;
			case RVT_USHORT:
				return 2;
			case RVT_INT:
				return 4;
			case RVT_UINT:
				return 4;
			case RVT_FIXED:
				return 4;
			case RVT_FLOAT:
				return 4;
			case RVT_HALF_FLOAT:
				return 4;
			case RVT_DOUBLE:
				return 8;
			case RVT_INT_2_10_10_10_REV:
				return 4;
			case RVT_UINT_2_10_10_10_REV:
				return 4;
			default:
				break;
			}
			return 4;
		}

		static int GetGLGPUBufferMode(GPUBufferMode mode)
		{
			switch (mode)
			{
			case GBM_LINES:
				return GL_LINES;
			case GBM_POINTS:
				return GL_POINTS;
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

		static GLenum GetGLTextureType(TextureType texType)
		{
			switch (texType)
			{
			case TT_1D:
				return GL_TEXTURE_1D;
			case TT_2D:
				return GL_TEXTURE_2D;
			case TT_3D:
				return GL_TEXTURE_3D;
			case TT_CUBE:
				return GL_TEXTURE_CUBE_MAP;
			}
			return GL_TEXTURE_2D;
		}

		static UniformFormat GetUniformFormat(GLenum type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return UF_FLOAT;
				break;
			case GL_FLOAT_VEC2:
				return UF_VEC2;
				break;
			case GL_FLOAT_VEC3:
				return UF_VEC3;
				break;
			case GL_FLOAT_VEC4:
				return UF_VEC4;
				break;
			case GL_INT:
				return UF_INT;
				break;
			case GL_INT_VEC2:
				break;
			case GL_INT_VEC3:
				break;
			case GL_INT_VEC4:
				break;
			case GL_BOOL:
				break; 
			case GL_BOOL_VEC2:
				break;
			case GL_BOOL_VEC3:
				break;
			case GL_BOOL_VEC4:
				break;
			case GL_FLOAT_MAT2:
				break;
			case GL_FLOAT_MAT3:
				return UF_MAT3;
				break;
			case GL_FLOAT_MAT4:
				return UF_MAT4;
				break;
			case GL_SAMPLER_2D:
				return UF_INT;
				break; 
			case GL_SAMPLER_CUBE:
				return UF_INT;
				break;
			case GL_SAMPLER_2D_SHADOW_ARB:
				return UF_INT;
				break;
			}
			return UF_UNKNOWN;
		}

		static int GetUniformTypeSize(UniformFormat type)
		{
			switch (type)
			{
			case UF_UNKNOWN:
				return 0;
				
			case UF_INT:
				return 4;
				
			case UF_FLOAT:
				return 4;
			case UF_VEC2:
				return 8;
			case UF_VEC3:
				return 12;
			case UF_VEC4:
				return 16;
			case UF_MAT4:
				return 64;				
			case UF_TEXTURE:
				return 4;
			default:
				;
			}
			return 0;
		}

		static GLenum GetGLPolygonMode(PolygonMode pm)
		{
			switch (pm)
			{
			case PM_POINT:
				return GL_POINT;
			case PM_LINE:
				return GL_LINE;
			case PM_FILL:
				return GL_FILL;
			default:
				break;
			}
			return PM_FILL;
		}

		static GLenum GetGLRenderAttr(RenderAttribute attr)
		{
			switch (attr)
			{
			case RA_CULL_FACE:
				return GL_CULL_FACE;
				break;
			case RA_DEPTH_TEST:
				return GL_DEPTH_TEST;
				break;
			default:
				break;
			}
			return GL_INVALID_ENUM;
		}

		static GLenum GetGLColorFormat(int format)
		{
			switch (format)
			{
			case resource::CF_ALPHA:
				return GL_ALPHA;
			case resource::CF_RGB:
				return GL_RGB;
			case resource::CF_RGBA:
				return GL_RGBA;
			case resource::CF_BGR:
				return GL_BGR;
			case resource::CF_BGRA:
				return GL_BGRA;
			case resource::CF_LUMINANCE:
				return GL_LUMINANCE;
			default:
				return GL_RGB;
			}
		}

		static GLenum GetGLPixelType(resource::EPixelType type)
		{
			switch (type)
			{
			case resource::PT_UNSIGNED_BYTE:
				return GL_UNSIGNED_BYTE;
			case resource::PT_UNSIGNED_SHORT_5_6_5:
				return GL_UNSIGNED_SHORT_5_6_5;
			case resource::PT_UNSIGNED_SHORT_4_4_4_4:
				return GL_UNSIGNED_SHORT_4_4_4_4;
			case resource::PT_UNSIGNED_SHORT_5_5_5_1:
				return GL_UNSIGNED_SHORT_5_5_5_1;
			default:
				return GL_UNSIGNED_BYTE;
			}
		}
	}
}

#endif
