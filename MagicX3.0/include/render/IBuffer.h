/************************************************************************/
/* ������                                                               */
/************************************************************************/

#ifndef _MX_RENDER_I_BUFFER_H_
#define _MX_RENDER_I_BUFFER_H_

namespace mx
{
	namespace render
	{
		enum EBufferType
		{
			BT_GPU,			//GPU������
			BT_CPU,			//CPU������
		};
		class IBuffer
		{
		public:
			virtual ~IBuffer(){}
		};
	}
}

#endif