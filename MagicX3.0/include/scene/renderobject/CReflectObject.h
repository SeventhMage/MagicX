/************************************************************************/
/* ����������������ݽ�Ϲ��ɿ���Ⱦ����                               */
/************************************************************************/
#ifndef _MX_C_REFLECT_OBJECT_H_
#define _MX_C_REFLECT_OBJECT_H_

#include "CRenderObject.h"

namespace mx
{
	namespace scene
	{		
		class CReflectObject : public CRenderObject
		{
		public:
			CReflectObject();
			~CReflectObject();						
			
			virtual void SetTexture(IRenderable *pRenderable);						
			virtual void Create(IRenderable *pRenderable);
		private:
			
		};
	}
}

#endif