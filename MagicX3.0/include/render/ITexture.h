/************************************************************************/
/* 纹理接口                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_TEXTURE_H_
#define _MX_RENDER_I_TEXTURE_H_

#include "mxType.h"
#include "resource/IImage.h"

namespace mx
{
	namespace render
	{
		//支持的纹理单元
		enum ETextureUnit
		{
			TU_TEXTURE_0 = 0,
			TU_TEXTURE_1,
			TU_TEXTURE_2,
			TU_TEXTURE_3,
			TU_TEXTURE_4,
			TU_TEXTURE_5,
			TU_TEXTURE_6,
			TU_TEXTURE_7,

			TU_TEXTURE_NUM,
		};

		using namespace resource;
		class ITexture
		{
		public:
			virtual ~ITexture(){}

			//绑定当前纹理到纹理单元
			virtual void Bind(uint slot = 0) = 0;

			//解绑
			virtual void UnBind() = 0;

			//创建2D纹理
			virtual void Create2D(int internalformat, int width, int height, int format, int type, void *data) = 0;

			//创建Cube纹理			
			virtual void CreateCube(IImage *pImgRight, IImage *pImgLeft, IImage *pImgTop, IImage *pImgBottom, IImage *pImgFront, IImage *pImgBack) = 0;

			//创建深度纹理
			virtual void CreateDepth(int width, int height) = 0;

			virtual void Create(uint target, uint handle) = 0;

			//返回纹理句柄
			virtual uint GetHandle() = 0;
		};
	}
}

#endif