#include "CSoftVertexArrayObject.h"

namespace se
{
	namespace render
	{


		CSoftVertexArrayObject::CSoftVertexArrayObject(uint id)
			:CVertexArrayObject(id)
		{

		}

		CSoftVertexArrayObject::~CSoftVertexArrayObject()
		{

		}

		void CSoftVertexArrayObject::VertexAttrPointer(uint index, uint size, EDataType type, uint stride, uint offset)
		{
			VertexAttrFormat format(index, size, type, stride, offset);
			m_mapVertAttrFormat[index] = format;
		}

	}
}