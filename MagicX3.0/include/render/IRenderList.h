/************************************************************************/
/* ��Ⱦ�б�ӿ�                                                         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_

#include "IRenderable.h"

namespace mx
{
	namespace render
	{

		class IRenderList
		{
		public:			
			virtual ~IRenderList(){}
			
			//�����Ⱦʵ�嵽��Ⱦ�б�
			virtual void AddRenderable(IRenderable *pRenderable) = 0;
			//�Ƴ���Ⱦʵ��
			virtual void RemoveRenderable(IRenderable *pRenderable) = 0;
			
			virtual void Clear() = 0;

			//ִ����Ⱦ
			virtual void Render() = 0;

		};
	}
}

#endif