/************************************************************************/
/* 图像资源接口                                                         */
/************************************************************************/

#ifndef _MX_RESOURCE_I_IMAGE_RESOURCE_H_
#define _MX_RESOURCE_I_IMAGE_RESOURCE_H_

#include "IResource.h"
#include "mxType.h"

namespace mx
{
	namespace resource
	{
	
		enum EColorFormat
		{
			CF_ALPHA,
			CF_RGB,
			CF_RGBA,
			CF_RGB16F,
			CF_BGR,
			CF_BGRA,
			CF_LUMINANCE,
		};

		enum EPixelType
		{
			PT_UNSIGNED_BYTE,
			PT_UNSIGNED_SHORT_5_6_5,
			PT_UNSIGNED_SHORT_4_4_4_4, 
			PT_UNSIGNED_SHORT_5_5_5_1,
		};

		class IImage : public IResource
		{
		public:
			virtual ~IImage(){}

			//从文件载入图片
			virtual ubyte *Load(const char *filename) = 0;
			//保存数据到文件
			virtual void Save(const char *filename, char *data, int widht, int height) = 0;			
			//取得纹理数据
			virtual ubyte *GetData() = 0;
			//图片格式
			virtual EColorFormat GetFormat() const = 0;
			virtual ulong GetImageSize() const = 0;
			virtual EColorFormat GetComponents() const = 0;
			virtual EPixelType GetPixelType() const = 0;
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;

		};
	}
}

#endif