#include "CMXDriver.h"

namespace mx
{
	CMagicX *mx;
	
	CMXDriver::CMXDriver()
	{
		mx = new CMagicX(nullptr, nullptr, nullptr, nullptr);
	}
	
	CMXDriver::~CMXDriver()
	{
		delete mx;
	}
	
	CMXDriver mxDriver;
}