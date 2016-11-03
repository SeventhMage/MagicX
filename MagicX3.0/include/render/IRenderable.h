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
		
			//�ύ���ݵ���Ⱦ����
			virtual void SumbitToRenderQueue() = 0;
			
			//�󶨵�ǰ����, ʹ��Ⱦ����֪�����ڴ������˭
			virtual void Bind() = 0;

			virtual IBufferObject *GetVertexBufferObject() = 0;
			virtual IBufferObject *GetIndexBufferObject() = 0;

		};
	}
}

#endif