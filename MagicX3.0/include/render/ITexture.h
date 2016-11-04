/************************************************************************/
/* ����ӿ�                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_TEXTURE_H_
#define _MX_RENDER_I_TEXTURE_H_

#include "mxType.h"

namespace mx
{
	namespace render
	{
		//֧�ֵ�����Ԫ
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
		class ITexture
		{
		public:
			virtual ~ITexture(){}

			//�󶨵�ǰ��������Ԫ
			virtual void Bind(uint slot = 0) = 0;

			//���
			virtual void UnBind() = 0;

			//����2D����
			virtual void Create2D(int internalformat, int width, int height, int format, int type, void *data) = 0;

			//����Cube����
			virtual void CreateCube(int internalformat[6], int width[6], int height[6], int format[6], int type[6], void *data[6]) = 0;

			//����������
			virtual uint GetHandle() = 0;
		};
	}
}

#endif