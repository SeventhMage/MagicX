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
					COpenGLShaderProgram *program = (COpenGLShaderProgram *)m_vecRenderableObject[i]->GetShaderProgram();
					if (program)
					{
						GLDebug(glUseProgram(program->GetHandle()));

						const CShaderProgram::UniformArray &uniforms = program->GetUniforms();
						CShaderProgram::UniformArray::const_iterator cit = uniforms.begin();
						for (; cit != uniforms.end(); ++cit)
						{
							switch (cit->second.m_format)
							{
							case UF_FLOAT:
								glUniform1f(cit->second.m_location, *((float *)cit->second.m_value));
								break;
							case UF_INT:
								GLDebug(glUniform1i(cit->second.m_location, 0));
								break;
							case UF_VEC2:
								break;
							case UF_VEC3:
								break;
							case UF_VEC4:
								break;
							case UF_MAT4:
								GLDebug(glUniformMatrix4fv(cit->second.m_location, 1, GL_FALSE, (const float *)cit->second.m_value));
								break;
							case UF_TEXTURE:
								break;
							default:
								break;
							}
						}
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