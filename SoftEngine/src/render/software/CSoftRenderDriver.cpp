#include "CSoftRenderDriver.h"
#include "base/seDef.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{



		CSoftRenderDriver::CSoftRenderDriver()
			:m_pDrawBuffer(nullptr)
		{
			
		}

		CSoftRenderDriver::~CSoftRenderDriver()
		{
			SAFE_DEL(m_pDrawBuffer)
		}
#ifdef WIN32
		void CSoftRenderDriver::InitDriverWin32(HDC hDc, int width, int height)
		{
			if (m_pDrawBuffer)
				return;

			m_uBufferWidth = width;
			m_uBufferHeight = height;
			m_pDrawBuffer = new ubyte[m_uBufferWidth * m_uBufferHeight];
		}
#endif

		void CSoftRenderDriver::OnSize(int x, int y, int width, int height)
		{
			m_uBufferWidth = width;
			m_uBufferHeight = height;
		}

		void CSoftRenderDriver::DrawBuffer()
		{
			CSoftEngine::GetDevice()->DrawBuffer(m_pDrawBuffer);
		}

	}
}