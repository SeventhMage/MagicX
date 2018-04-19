#include "CGLRenderer"

namespace mx
{
	GLRenderer::GLRenderer()
	{
		
	}
	GLRenderer::~GLRenderer()
	{
		
	}
	
	void GLRenderer::InitDriver(IDevice *pDevice)
	{
		if (!pDevice)
			return;
		switch (pDevice->GetType())
		{
		case DT_WIN:
			CGLDriverWin driver(pDevice->GetHandle());
			break;
		case DT_IOS:
			break;
		}
	}
	
	void GLRenderer::OnSize(int x, int y, int width, int height)
	{
		
	}
	
	void GLRenderer::BufferData(const void *data)
	{
		
	}
	
	void GLRenderer::AttributePointer(EVertexAttribute va, int offset, int stride)
	{
		
	}
	
	void GLRenderer::Clear()
	{
		
	}
	
	void GLRenderer::DrawArray(EPrimitiveType type)
	{
		
	}
	
}