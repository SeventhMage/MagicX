#ifndef _I_RESOURCE_IMAGE_H_
#define _I_RESOURCE_IMAGE_H_

#include "IResource.h"
#include "base/seType.h"

namespace se
{
	namespace resource
	{

		enum EColorFormat
		{
			CF_ALPHA,
			CF_RGB,
			CF_RGBA,
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

			virtual EColorFormat GetColorFormat() const = 0;
			virtual EPixelType GetPixelType() const = 0;
			virtual ubyte *GetData()const = 0;
			virtual ulong GetImageSize() const = 0;			
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;
		};
	}
}

#endif