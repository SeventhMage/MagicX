/************************************************************************/
/* 只有颜色属性的渲染对象                                               */
/************************************************************************/

#ifndef _MX_SCENE_C_COLOR_OBJECT_H_
#define _MX_SCENE_C_COLOR_OBJECT_H_

#include "CRenderObject.h"
#include "render\IShaderProgram.h"

namespace mx
{
	namespace scene
	{
		class CColorFlatObject : public CRenderObject
		{
		public:
			CColorFlatObject(float fColor[4]);
			virtual ~CColorFlatObject();
			
			virtual void Create(IRenderable *pRenderable);			
		private:			
			float m_fColor[4];
		};
	}
}

#endif