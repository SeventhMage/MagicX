/************************************************************************/
/* ��Ⱦ����һ��ʵ�����Ⱦ���ԣ�ͬһ����ѡ��ͬ����Ⱦ���������ֵ�Ч */
/* ����ͬ																*/
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_OBJECT_H_
#define _MX_RENDER_I_RENDER_OBJECT_H_

#include "render/IVertexArrayObject.h"
#include "render/IRenderable.h"

#include <map>

namespace mx
{
	namespace render
	{
		typedef std::map<const char *, const void *> UniformMap;
		using namespace render;
		class IRenderObject
		{
		public:
			virtual ~IRenderObject(){}
			virtual void Create(IRenderable *pRenderable) = 0;
			virtual IVertexArrayObject *GetVAO() = 0;
			virtual void SetTexture(IRenderable *pRenderable) = 0;						
			virtual void Update(IRenderable *pRenderable, const UniformMap &normalParam, const UniformMap *shadowParam = nullptr) = 0;
		};
	}
}

#endif