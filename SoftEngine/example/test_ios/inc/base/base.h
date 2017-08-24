#ifndef _BASE_BASE_H_
#define _BASE_BASE_H_

#include "CSingleton.h"
#include "Log.h"
#include "seDef.h"
#include "seDef.h"
#include "StringHelper.h"
#include "VertexAttribute.h"

namespace se
{
	namespace base
	{
		template <typename Type>
		inline void swap(Type &a, Type &b)
		{
			Type c = a;
			a = b;
			b = c;
		}
	}
}

#endif