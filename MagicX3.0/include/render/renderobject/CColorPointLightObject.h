/************************************************************************/
/* 点光源渲染颜色对象                                                   */
/************************************************************************/

#ifndef _MX_RENDER_C_COLOR_POINT_LIGHT_OBJECT_H_
#define _MX_RENDER_C_COLOR_POINT_LIGHT_OBJECT_H_

#include "CRenderObject.h"

namespace mx
{
	namespace render
	{
		class CColorPointLightObject : public CRenderObject
		{
		public:
			CColorPointLightObject(float fColor[4]);
			virtual ~CColorPointLightObject();

			virtual void Create(IRenderable *pRenderable);			
		private:
			float m_fColor[4];
		};
	}
}

#endif