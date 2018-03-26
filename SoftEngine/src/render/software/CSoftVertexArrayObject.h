#ifndef _SE_RENDER_C_SOFT_VERTEX_ARRAY_OBJECT_H_
#define _SE_RENDER_C_SOFT_VERTEX_ARRAY_OBJECT_H_

#include "../CVertexArrayObject.h"

#include <map>

namespace se
{
	namespace render
	{
		class CSoftVertexArrayObject : public CVertexArrayObject
		{
		public:
			struct VertexAttrFormat 
			{
				VertexAttrFormat(uint index, uint size, EDataType type, uint stride, uint offset)
					:index(index), size(size), type(type), stride(stride), offset(offset)
				{

				}
				uint index;
				uint size;
				EDataType type;
				uint stride;
				uint offset;
			};
			CSoftVertexArrayObject(uint id);
			virtual ~CSoftVertexArrayObject();
			
			virtual void VertexAttrPointer(uint index, uint size, EDataType type, uint stride, uint offset);
		private:
			std::map<uint, VertexAttrFormat> m_mapVertAttrFormat;
		};
	}
}

#endif