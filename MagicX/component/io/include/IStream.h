#ifndef _I_STREAM_H_INC_
#define _I_STREAM_H_INC_

#include "common/CSingleton.h"
#include "common/mxDef.h"
#include "../include/IBuffer.h"

namespace mx
{
	namespace io
	{
		class IStream
		{
		public:
			IStream(){};
			virtual ~IStream(){};

			IBuffer *GetBuffer() { };
			
			/*
			IStream &operator>>(char);
			IStream &operator>>(int);
			IStream &operator>>(unsigned int);
			IStream &operator>>(float);
			IStream &operator>>(double);
			IStream &operator>>(short);
			IStream &operator>>(unsigned short);
			IStream &operator>>(const resource::IResource &);

			IStream &operator<<(char);
			IStream &operator<<(int);
			IStream &operator<<(unsigned int);
			IStream &operator<<(float);
			IStream &operator<<(double);
			IStream &operator<<(short);
			IStream &operator<<(unsigned short);
			IStream &operator<<(const resource::IResource &);
			*/
		};
	}
}

#endif // !_I_STREAM_H_INC_
