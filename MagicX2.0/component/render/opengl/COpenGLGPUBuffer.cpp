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
		COpenGLGPUBuffer::COpenGLGPUBuffer(bool bNormalize)		
			:m_bNormalize(bNormalize)
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

		void COpenGLGPUBuffer::AddVertexData(IRenderableObject *object, void * data, int size, int offset)
		{						
			if (object)
			{
				IBufferObject *bufferObj = object->GetVertexBufferObject();
				if (bufferObj)
					bufferObj->BufferSubData(data, size, offset);
			}
		}
		void COpenGLGPUBuffer::EnableVertexAttrib(VertexAttributeLocation val, int size, RendererVariableType vertType, int stride, int offset)
		{
			GLDebug(glEnableVertexAttribArray(val));
			GLDebug(glVertexAttribPointer(val, size, GetGLVariableType(vertType), false, stride, (GLvoid *)offset));
		}

		void COpenGLGPUBuffer::End()
		{
			GLDebug(glBindVertexArray(0));
		}
		void COpenGLGPUBuffer::Render()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
							GLDebug(glDrawElements(GetGLGPUBufferMode(vio->GetGPUBufferMode()), vio->GetIndicesNum(),
								GetGLVariableType(vio->GetIndexType()),0));
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