#include <cstring>
#include "base/StringHelper.h"

namespace mx 
{
	namespace base 
	{

		std::string GetFileExtName(const char *filename)
		{
			const char *pLastPoint = strrchr(filename, '.');
			if (pLastPoint)
			{
				return std::string(pLastPoint + 1);
			}
			return "";
		}

		StringArray Split(const std::string &str, const std::string &delims)
		{
			StringArray strRet;			
			size_t start = 0, pos = 0;
			do 
			{
				pos = str.find_first_of(delims, start);
				if (pos == start)
				{
					start = pos + 1;
				}
				else if (pos == std::string::npos)
				{
					strRet.push_back(str.substr(start));
					break;
				}
				else
				{
					strRet.push_back(str.substr(start, pos - start));
					start = pos + 1;
				}

				start = str.find_first_not_of(delims, start);

			} while (pos != std::string::npos);
			
			return strRet;
		}
		std::string Replace(const std::string & str, const std::string & src, const std::string & dst)
		{
			if (src == dst)
				return str;
			std::string out = str;
			size_t pos = str.find(src, 0);
			while (pos != std::string::npos)
			{
				out.replace(pos, src.size(), dst);
				pos = out.find(src, pos + dst.size());
			}
			return out;
		}
	}
}