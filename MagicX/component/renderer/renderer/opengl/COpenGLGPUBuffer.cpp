#include "COpenGLGPUBuffer.h"
#include "COpenGLRenderableObject.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "OpenGLType.h"
#include "COpenGLShaderProgram.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		COpenGLGPUBuffer::COpenGLGPUBuffer(int stride, bool bNormalize)
			:m_stride(stride)
			,m_bNormalize(bNormalize)
		{
			GLDebug(glGenVertexArrays(1, &m_hVAO));
		}
		
		COpenGLGPUBuffer::~COpenGLGPUBuffer()
		{
			GLDebug(glDeleteVertexArrays(1, &m_hVAO));
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
			GLDebug(glBindVertexArray(m_hVAO));
		}
		void COpenGLGPUBuffer::CreateVertexBuffer(IRenderableObject *object, void * vertexes, int size, int first, int vertexCount, GPUBufferMode mode, GPUBufferUsage usage)
		{
			if (object)
				object->CreateVertexBufferObject(vertexes, size, first, vertexCount, mode, usage);
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
		void COpenGLGPUBuffer::EnableVertexAttrib(VertexAttributeLocation val, int size, RendererVariableType vertType, int offset)
		{
			GLDebug(glEnableVertexAttribArray(val));
			GLDebug(glVertexAttribPointer(val, size, GetGLVariableType(vertType), false, m_stride, (GLvoid *)offset));
		}

		void COpenGLGPUBuffer::CreateIndexBuffer(IRenderableObject *object, void * indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage)
		{
			if (object)
				object->CreateIndexBufferObject(indices, idxCount, idxType, mode, usage);
		}
		void COpenGLGPUBuffer::End()
		{
			GLDebug(glBindVertexArray(0));
		}
		void COpenGLGPUBuffer::Render()
		{
			for (uint i = 0; i < m_vecRenderableObject.size(); ++i)
			{
				if (m_vecRenderableObject[i])
				{
					COpenGLShaderProgram *program = (COpenGLShaderProgram *)m_vecRenderableObject[i]->GetShaderProgram();
					if (program)
					{
						GLDebug(glUseProgram(program->GetHandle()));
						program->BindUniform();
					}

					m_vecRenderableObject[i]->BindTexture();

					
					
					GLDebug(glBindVertexArray(m_hVAO));
					if (m_vecRenderableObject[i]->IsEnabledIndexBuffer())
					{
						COpenGLIndexBufferObject *vio = (COpenGLIndexBufferObject *)m_vecRenderableObject[i]->GetIndexBufferObject();
						if (vio)
						{
							GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio->GetHandle()));
							GLDebug(glDrawElements(GetGLGPUBufferMode(vio->GetGPUBufferMode()), vio->GetVertexNum(), 
								GetGLVariableType(vio->GetIndexType()), vio->GetIndexBufferData()));
						}
					}
					else
					{
						COpenGLVertexBufferObject *vbo = (COpenGLVertexBufferObject *)m_vecRenderableObject[i]->GetVertexBufferObject();
						if (vbo)
						{
							GLDebug(glBindBuffer(GL_ARRAY_BUFFER, vbo->GetHandle()));
							GLDebug(glDrawArrays(GetGLGPUBufferMode(vbo->GetGPUBufferMode()), vbo->GetGLGPUBufferFirst(), vbo->GetVertexNum()));
						}
					}

				}
			}	
		}
	}
}