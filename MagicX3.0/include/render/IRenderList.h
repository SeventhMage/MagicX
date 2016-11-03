/************************************************************************/
/* ��Ⱦ�б��ӿ�                                                         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_

#include "IRenderable.h"

#include <list>

namespace mx
{
	namespace render
	{
		typedef std::list<IRenderable *> RENDER_LIST;

		class IRenderList
		{
		public:			
			virtual ~IRenderList(){}
			
			//������Ⱦʵ�嵽��Ⱦ�б�
			virtual void AddRenderable(IRenderable *pRenderable) = 0;
			
			//�����Ⱦ�б��ȳ�ʼ����			
			virtual void BeginRender() = 0;
			//ִ����Ⱦ
			virtual void Render() = 0;
			virtual int GetRenderableCount() = 0;
			virtual RENDER_LIST &GetRenderList() = 0;
		};
	}
}

#endif