#include "CGLRenderer.h"
#include "CGLDriverWin.h"
#include "GLDebug.h"
#include "glew/GL/glew.h"

namespace mx
{
	CGLRenderer::CGLRenderer()
	{		
	}
	CGLRenderer::~CGLRenderer()
	{
		
	}
#ifdef WIN32
	void CGLRenderer::InitDriver(HDC hDC)
	{
		CGLDriverWin driver(hDC);
		GLDebug(glClearColor(0.f, 0.f, 0.f, 1.f));
	}
#endif
	
	void CGLRenderer::OnSize(int x, int y, int width, int height)
	{
		GLDebug(glViewport(x, y, width, height));
	}
	
	void CGLRenderer::BufferData(const void *data)
	{
		
	}
	
	void CGLRenderer::AttributePointer(EVertexAttribute va, int offset, int stride)
	{
		
	}
	
	void CGLRenderer::Clear()
	{
		GLDebug(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	
	void CGLRenderer::DrawArray(EPrimitiveType type)
	{
		
	}
	
}