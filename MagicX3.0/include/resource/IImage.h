/************************************************************************/
/* ͼ����Դ�ӿ�                                                         */
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
			CF_BGR,
			CF_BGRA,
			CF_LUMINANCE,
		};

		class IImage : public IResource
		{
		public:
			virtual ~IImage(){}

			//���ļ�����ͼƬ
			virtual ubyte *Load(const char *filename) = 0;
			//�������ݵ��ļ�
			virtual void Save(const char *filename, char *data, int widht, int height) = 0;			
			//ȡ����������
			virtual ubyte *GetData() = 0;
			//ͼƬ��ʽ
			virtual EColorFormat GetFormat() const = 0;
			virtual ulong GetImageSize() const = 0;
			virtual EColorFormat GetComponents() const = 0;
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;

		};
	}
}

#endif