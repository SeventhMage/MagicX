#include "CGLRenderer.h"
#include "CGLDriverWin.h"
#include "glew\GL\glew.h"

namespace mx
{
	CGLRenderer::CGLRenderer()
	{
		glClearColor(0, 0, 0, 1);
	}
	CGLRenderer::~CGLRenderer()
	{
		
	}
	
	void CGLRenderer::InitDriver(IDevice *pDevice)
	{
		if (!pDevice)
			return;
		switch (pDevice->GetType())
		{
		case DT_WIN:
		{
			CGLDriverWin driver(pDevice->GetHandle());
		}
			break;
		case DT_IOS:
			break;
		}
	}
	
	void CGLRenderer::OnSize(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}
	
	void CGLRenderer::BufferData(const void *data)
	{
		
	}
	
	void CGLRenderer::AttributePointer(EVertexAttribute va, int offset, int stride)
	{
		
	}
	
	void CGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void CGLRenderer::DrawArray(EPrimitiveType type)
	{
		
	}
	
}