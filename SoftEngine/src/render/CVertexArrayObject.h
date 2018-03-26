#ifndef _SE_RENDER_C_VERTEX_ARRAY_OBJECT_H_
#define _SE_RENDER_C_VERTEX_ARRAY_OBJECT_H_

#include "render/IVertexArrayObject.h"

namespace se
{
	namespace render
	{
		class CVertexArrayObject : public IVertexArrayObject
		{
		public:			
			CVertexArrayObject(uint id);
			virtual ~CVertexArrayObject();
			virtual uint GetID() const { return m_id; }
		private:
			uint m_id;			
		};
	}
}

#endif