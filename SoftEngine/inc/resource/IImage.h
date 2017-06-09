#ifndef _I_RESOURCE_IMAGE_H_
#define _I_RESOURCE_IMAGE_H_

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

		class IImage
		{

		};
	}
}

#endif