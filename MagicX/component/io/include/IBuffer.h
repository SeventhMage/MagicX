#ifndef _I_BUFFER_H_INC_
#define _I_BUFFER_H_INC_

#include "common/mxDef.h"

namespace mx
{
	namespace io
	{
		class IBuffer
		{
		public:
			IBuffer();
			virtual ~IBuffer();
			virtual Byte *GetData() = 0;
		};
	}
}

#endif // !_I_BUFFER_H_INC_
