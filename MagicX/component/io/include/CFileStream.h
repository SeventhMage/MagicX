#ifndef _MX_IO_I_FILE_STREAM_H_INC_
#define _MX_IO_I_FILE_STREAM_H_INC_

#include "IStream.h"

namespace mx
{
	namespace io
	{
		class CFileStream : public IStream
		{
		public:
			CFileStream();
			virtual ~CFileStream();

			bool Open(const char *filename);
			uint GetSize() { return m_uSize; };
			Byte *GetData() { return m_pData; };
		private:
			CString m_fileName;
			Byte *m_pData;
			uint m_uSize;
		};
	}
}

#endif // !_MX_IO_I_FILE_STREAM_H_INC_
