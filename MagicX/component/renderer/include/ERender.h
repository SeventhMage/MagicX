#ifndef _MX_RENDER_E_RENDER_H_
#define _MX_RENDER_E_RENDER_H_

namespace mx
{
	namespace render
	{
		enum GPUBufferType
		{
			GBT_VERTEX,
			GBT_INDEX,
		};

		enum GPUBufferUsage
		{
			GBU_STREAM_DRAW,
			GBU_STREAM_READ,
			GBU_STREAM_COPY,
			GBU_STATIC_DRAW,
			GBU_STATIC_READ,
			GBU_STATIC_COPY,
			GBU_DYNAMIC_DRAW,
			GBU_DYNAMIC_READ,
			GBU_DYNAMIC_COPY,
		};

		enum GPUBufferMode
		{
			GBM_POINTS,
			GBM_LINES,
			GBM_TRIANGLES,
			GBM_TRIANGLE_FAN,
			GBM_TRIANGLE_STKIP,
		};

		enum ShaderLang
		{
			SL_HLSL,
			SL_GLSL,
			SL_CG,
		};

		enum ShaderType
		{
			ST_VERTEX,
			ST_GEOMETRY,
			ST_FRAGMENT,

			ST_COUNT,
		};

		enum VertexAttributeIndex
		{
			VAI_VERTEX = 0,
			VAI_COLOR,
			VAI_NORMAL,
			VAI_TEXTURE1,
			VAI_TEXTURE2,
			VAI_TEXTURE3,
			VAI_TEXTURE4,
			VAI_TEXTURE5,
			VAI_TEXTURE6,
			VAI_TEXTURE7,
			VAI_TEXTURE8,
			VAI_TEXTURE9,
		};

		enum RendererVariableType
		{
			RVT_BYTE,
			RVT_UBYTE,
			RVT_SHORT,
			RVT_USHORT,
			RVT_INT,
			RVT_UINT,
			RVT_FIXED,
			RVT_FLOAT,
			RVT_HALF_FLOAT,
			RVT_DOUBLE,
			RVT_INT_2_10_10_10_REV,
			RVT_UINT_2_10_10_10_REV,
		};

		enum UniformFormat
		{
			UF_INT,
			UF_FLOAT,
			UF_VEC2,
			UF_VEC3,
			UF_VEC4,
			UF_MAT4,
			UF_TEXTURE,
		};

		enum RendererType
		{
			RT_OPENGL,
			RT_DX9,
			RT_DX11,
		};

		enum TextureType
		{
			TT_1D,
			TT_2D,
			TT_3D,
			TT_CUBE,
		};

	}
}

#endif
