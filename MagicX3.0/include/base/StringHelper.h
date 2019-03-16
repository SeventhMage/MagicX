#ifndef _MX_BASE_STRING_HELPER_H_
#define _MX_BASE_STRING_HELPER_H_

#include "mxType.h"

namespace mx
{
	namespace base
	{
		std::string GetFileExtName(const char *filename);
		
		StringArray Split(const std::string &str, const std::string &delims);
	}
}


#endif