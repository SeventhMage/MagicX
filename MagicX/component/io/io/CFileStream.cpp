#include "../include/CFileStream.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>

namespace mx
{
	namespace io
	{
		CFileStream::CFileStream()
		{

		}

		CFileStream::~CFileStream()
		{

		}

		bool CFileStream::Open(const char *filename)
		{
			struct stat tagStat;
			int ret = stat(filename, &tagStat);
			if (ret == 0)
			{
				std::ifstream stream;
				stream.open(filename, std::ios::in | std::ios::binary);
				if (!stream.fail())
				{
					m_uSize = tagStat.st_size + 1;
					m_pData = new Byte[m_uSize];
					
					stream.read((char *)m_pData, m_uSize);
					m_pData[m_uSize - 1] = 0;
					m_fileName = filename;
					return true;
				}

			}
			std::cout << "Open file:" << filename << "failed." << std::endl;
			return false;
		}

	}
}