#ifndef _BASE_LOG_H_
#define _BASE_LOG_H_

#include <stdio.h>

namespace se
{
	namespace base
	{
#ifdef _DEBUG
#define LogPrint(formats, ...) printf(formats, ##__VA_ARGS__)
#else
#define LogPrint(formats, ...)
#endif
	}
}

#endif