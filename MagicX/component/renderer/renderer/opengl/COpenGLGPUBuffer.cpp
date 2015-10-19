#include "COpenGLGPUBuffer.h"
#include "COpenGLRenderableObject.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "OpenGLType.h"

namespace mx
{
	namespace render
	{
		COpenGLGPUBuffer::COpenGLGPUBuffer(int stride, bool bNormalize)
			:m_stride(stride)
			,m_bNormalize(bNormalize)
		{
			glGenVertexArrays(1, &m_hVAO);
		}
		
		COpenGLGPUBuffer::~COpenGLGPUBuffer()
		{
			glDeleteVertexArrays(1, &m_hVAO);
			for (uint i = 0; i < m_vecRenderableObject.size(); ++i)
			{
				SAFE_DEL(m_vecRenderableObject[i]);
			}
			
		}
		IRenderableObject * COpenGLGPUBuffer::CreateRenderableObject()
		{
			IRenderableObject *object = new COpenGLRenderableObject();
			m_vecRenderableObject.push_back(object);
			return object;
		}
		void COpenGLGPUBuffer::Begin()
		{
			glBindVertexArray(m_hVAO);
		}
		void COpenGLGPUBuffer::CreateVertexBuffer(IRenderableObject *object, void * vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage)
		{
			if (object)
				object->CreateVertexBufferObject(vertexes, size, first, count, mode, usage);
		}
		void COpenGLGPUBuffer::AddVertexData(IRenderableObject *object, void * data, int size, int offset)
		{						
			if (object)
			{
				IBufferObject *bufferObj = object->GetVertexBufferObject();
				if (bufferObj)
					bufferObj->BufferSubData(data, size, offset);
			}
		}
		void COpenGLGPUBuffer::EnableVertexAttrib(VertexAttributeIndex vai, int size, RendererVariableType vertType, int offset)
		{
			glEnableVertexAttribArray(vai);
			glVertexAttribPointer(vai, size, GetGLVariableType(vertType), false, m_stride, (GLvoid *)offset);
			GLenum err = glGetError();
			//////////////////////////////////////////////////////////////////////////
		}

		void COpenGLGPUBuffer::CreateIndexBuffer(IRenderableObject *object, void * indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage)
		{
			if (object)
				object->CreateIndexBufferObject(indices, idxCount, idxType, mode, usage);
		}
		void COpenGLGPUBuffer::End()
		{
			glBindVertexArray(0);
		}
		void COpenGLGPUBuffer::Render()
		{
			for (uint i = 0; i < m_vecRenderableObject.size(); ++i)
			{
				if (m_vecRenderableObject[i])
				{
					IShaderProgram *program = m_vecRenderableObject[i]->GetShaderProgram();
					if (program)
						glUseProgram(program->GetHandle());
					glBindVertexArray(m_hVAO);
					if (m_vecRenderableObject[i]->IsEnabledIndexBuffer())
					{
						COpenGLIndexBufferObject *vio = (COpenGLIndexBufferObject *)m_vecRenderableObject[i]->GetIndexBufferObject();
						if (vio)
						{
							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio->GetHandle());
							glDrawElements(GetGLGPUBufferMode(vio->GetGPUBufferMode()), vio->GetVertexNum(), GetGLVariableType(vio->GetIndexType()), vio->GetIndexBufferData());
						}
					}
					else
					{
						COpenGLVertexBufferObject *vbo = (COpenGLVertexBufferObject *)m_vecRenderableObject[i]->GetVertexBufferObject();
						if (vbo)
						{
							glBindBuffer(GL_ARRAY_BUFFER, vbo->GetHandle());
							glDrawArrays(GetGLGPUBufferMode(vbo->GetGPUBufferMode()), vbo->GetGLGPUBufferFirst(), vbo->GetVertexNum());							
						}
					}
				}
			}			
		}
	}
}