#ifndef _MXTYPE_H_
#define _MXTYPE_H_

#include <string>
#include <vector>

namespace se
{
	typedef unsigned int uint;
	typedef unsigned short ushort;
	typedef unsigned char ubyte;
	typedef char byte;
	typedef unsigned long ulong;	
	typedef std::vector<std::string> StringArray;

	enum EDataType
	{
		SE_BYTE,
		SE_SHORT,
		SE_USHORT,
		SE_INT,
		SE_UINT,		
		SE_FLOAT,
		SE_DOUBLE,
	};

}

#endif