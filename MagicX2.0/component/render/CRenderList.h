#ifndef _MX_RENDER_CRENDERLIST_H_
#define _MX_RENDER_CRENDERLIST_H_

namespace mx
{
	namespace render
	{
		class CRenderList
		{
		public:
			CRenderList();
			~CRenderList();

			int state;				//渲染列表的状态
			int attr;				//渲染列表的属性
		};
	}
}

#endif