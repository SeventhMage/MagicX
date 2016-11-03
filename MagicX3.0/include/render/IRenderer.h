/************************************************************************/
/* ��Ⱦ���ӿ�                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERER_H_
#define _MX_RENDER_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IBufferData.h"
#include "IRenderable.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};

			//��ȡ��Ⱦ����������
			virtual IRenderDriver *GetRenderDriver() = 0;

			//��Ⱦ
			virtual void Render() = 0;
		};
	}
}

#endif