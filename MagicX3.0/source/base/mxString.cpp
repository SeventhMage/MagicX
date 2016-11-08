#include "base/mxString.h"

#include <string.h>

namespace mx
{
	namespace base
	{


		std::string ToLower(const char *str)
		{
			std::string ret;
			for (; *str != '\0'; ++str)
			{
				ret.push_back(tolower(*str));
			}
			return ret;
		}

		std::string ToUpper(const char *str)
		{
			std::string ret;
			for (; *str != '\0'; ++str)
			{
				ret.push_back(toupper(*str));
			}
			return ret;
		}

	}
}