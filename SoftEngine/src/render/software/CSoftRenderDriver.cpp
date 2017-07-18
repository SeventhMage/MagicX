#include "CSoftRenderDriver.h"
#include "base/seDef.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{



		CSoftRenderDriver::CSoftRenderDriver()
			:m_pDrawBuffer(nullptr)
			, m_pDepthBuffer(nullptr)
		{
			
		}

		CSoftRenderDriver::~CSoftRenderDriver()
		{
			SAFE_DEL(m_pDrawBuffer);
			SAFE_DEL(m_pDepthBuffer);
		}
#ifdef WIN32
		void CSoftRenderDriver::InitDriverWin32(HDC hDc, int width, int height)
		{
			if (m_pDrawBuffer)
				return;

			m_uBufferWidth = width;
			m_uBufferHeight = height;
			CreateBuffer();
		}
#endif

		void CSoftRenderDriver::OnSize(int x, int y, int width, int height)
		{
			m_uBufferWidth = width;
			m_uBufferHeight = height;
			CreateBuffer();
		}

		void CSoftRenderDriver::DrawBuffer()
		{
			CSoftEngine::GetDevice()->DrawBuffer((ubyte*)m_pDrawBuffer);
		}

		void CSoftRenderDriver::Clear()
		{			
			memset(m_pDrawBuffer, 0, m_uBufferWidth * m_uBufferHeight * sizeof(uint));
			//memset(m_pDepthBuffer, 0, m_uBufferWidth * m_uBufferHeight * sizeof(uint));
			//uint color = 0xff0000ff;
			//std::fill_n(m_pDrawBuffer, m_uBufferWidth * m_uBufferHeight, color);
			for (uint i = 0; i < m_uBufferHeight * m_uBufferWidth; ++i)
			{
				*(m_pDepthBuffer + i) = 1.f;
			}
		}

		void CSoftRenderDriver::CreateBuffer()
		{
			SAFE_DEL(m_pDrawBuffer);
			m_pDrawBuffer = new uint[m_uBufferWidth * m_uBufferHeight];
			memset(m_pDrawBuffer, 0, m_uBufferWidth * m_uBufferHeight * sizeof(uint));
			SAFE_DEL(m_pDepthBuffer);
			m_pDepthBuffer = new float[m_uBufferWidth * m_uBufferHeight];
			memset(m_pDepthBuffer, 0, m_uBufferWidth * m_uBufferHeight * sizeof(uint));
		}

	}
}