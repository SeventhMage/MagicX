/************************************************************************/
/* »º³åÇø                                                               */
/************************************************************************/

#ifndef _MX_RENDER_I_BUFFER_H_
#define _MX_RENDER_I_BUFFER_H_

namespace mx
{
	namespace render
	{
		enum EBufferType
		{
			BT_GPU,			//GPU»º³åÇø
			BT_CPU,			//CPU»º³åÇø
		};
		class IBuffer
		{
		public:
			virtual ~IBuffer(){}
		};
	}
}

#endif