#ifndef _BASE_LOG_H_
#define _BASE_LOG_H_

#include <stdio.h>

namespace se
{
	namespace base
	{
#define LogPrint(formats, ...) printf(formats, ##__VA_ARGS__)
	}
}

#endif