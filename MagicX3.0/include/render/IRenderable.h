/************************************************************************/
/* ÿ��renderable�洢�˶���Ⱦ����һ���ύ                               */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERABLE_H_
#define _MX_RENDER_I_RENDERABLE_H_

#include "IBufferObject.h"

namespace mx
{
	namespace render
	{
		class IRenderable
		{
		public:
			virtual ~IRenderable(){}

			//���ɻ���������
			virtual IBufferObject *CreateBufferObject(EBufferObjectType type);
			
			virtual 
		};
	}
}

#endif