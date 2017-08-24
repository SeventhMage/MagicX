#ifndef _BASE_STRING_HELPER_H_
#define _BASE_STRING_HELPER_H_

#include "seType.h"

#include <string>
#include <vector>

namespace se
{
	namespace base
	{
		using namespace std;
		string GetFileExtName(const char *filename);
		
		StringArray Split(const string &str, const string &delims);
	}
}


#endif