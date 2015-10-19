#ifndef _MX_DEF_H_INC_
#define _MX_DEF_H_INC_

#include <string>
#include "../core/matrix44.h"
#include "../core/vector3d.h"

namespace mx
{
	/*
	** #define MX_LEFT_HANDED_COORDINATE_SYSTEM
	*/
#define MX_RIGHT_HANDED_COORDINATE_SYSTEM	//The default usage


#define SAFE_DEL(p) { if (p) { delete (p); (p) = NULL; }}
#define SAFE_DEL_ARRAY(p) { if (p) { delete[] (p); (p) = NULL; }}

	typedef core::CMatrix44<float> CMatrix4;
	typedef core::vector3d<float> CVector3;

	typedef std::string CString;

	typedef unsigned char Byte;
	typedef unsigned int uint;
}

#endif