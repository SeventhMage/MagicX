#include <cstring>
#include "base/StringHelper.h"

namespace se
{
	namespace base
	{

		std::string GetFileExtName(const char *filename)
		{
			const char *pLastPoint = strrchr(filename, '.');
			if (pLastPoint)
			{
				return string(pLastPoint + 1);
			}
			return "";
		}

	}
}