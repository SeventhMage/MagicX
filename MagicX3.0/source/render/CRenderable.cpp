#include "CRenderable.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CRenderable::CRenderable(IRenderList *pRenderList, IRenderer *pRenderer)
			:m_pRenderList(pRenderList)
			, m_pVBO(nullptr)
			, m_pIBO(nullptr)
			,m_pRenderer(pRenderer)
			,m_pShaderProgram(nullptr)
		{
			memset(m_pTexture, 0, sizeof(ITexture *)* TU_TEXTURE_NUM);	
			for (int i = 0; i < RA_NUM; ++i)
				m_bRenderAttrs[i] = true;
		}

		CRenderable::CRenderable(IRenderQueue *pQueue, IRenderer *pRenderer)		
			:m_pRenderQueue(pQueue)
			, m_pVBO(nullptr)
			, m_pIBO(nullptr)
			, m_pRenderer(pRenderer)
			, m_pShaderProgram(nullptr)
		{
			memset(m_pTexture, 0, sizeof(ITexture *)* TU_TEXTURE_NUM);	
			for (int i = 0; i < RA_NUM; ++i)
				m_bRenderAttrs[i] = true;
			m_pVAO = pRenderer->CreateVertexArrayObject();
		}

		CRenderable::~CRenderable()
		{
			m_pRenderer->DestroyBufferObject(m_pVBO);
			m_pRenderer->DestroyBufferObject(m_pIBO);
			m_pRenderer->DestroyVertexArrayObject(m_pVAO);
		}

		void CRenderable::SumbitToRenderList()
		{
			if (m_pRenderList)
				m_pRenderList->AddRenderable(this);
		}

		void CRenderable::RemoveFromRenderList()
		{
			m_pRenderList->RemoveRenderable(this);
		}

		void CRenderable::SumbitToRenderQueue()
		{
			m_pRenderQueue->AddRenderable(this);
		}

		void CRenderable::Bind()
		{
			if (m_pVAO)
				m_pVAO->Bind();
			if (m_pVBO)
				m_pVBO->Bind();
			if (m_pIBO)
				m_pIBO->Bind();

			for (auto &uniform : m_uniforms)
			{
				m_pShaderProgram->SetUniform(uniform.first, uniform.second.m_value);
			}

			if (m_pShaderProgram)
				m_pShaderProgram->Bind();


			for (int i = 0; i < TU_TEXTURE_NUM; ++i)
			{
				if (m_pTexture[i])
					m_pTexture[i]->Bind(i);
			}
		}

		void CRenderable::UnBind()
		{
			if (m_pVBO)
				m_pVBO->UnBind();
			if (m_pIBO)
				m_pIBO->UnBind();
	
			for (int i = 0; i < TU_TEXTURE_NUM; ++i)
			{
				if (m_pTexture[i])
					m_pTexture[i]->UnBind();
			}
			if (m_pVAO)
				m_pVAO->UnBind();
		}

		IBufferObject * CRenderable::CreateVertexBufferObject(void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage)
		{
			m_pVBO = m_pRenderer->CreateVertexBufferObject(vertexes, size, first, count, mode, usage);
			return m_pVBO;
		}

		IBufferObject * CRenderable::CreateIndexBufferObject(void *indices, uint idsCount, RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage)
		{
			m_pIBO = m_pRenderer->CreateIndexBufferObject(indices, idsCount, idsType, mode, usage);
			return m_pIBO;
		}

		void CRenderable::SetShaderProgram(IShaderProgram *program)
		{
			m_pShaderProgram = program;
		}

		void CRenderable::SetUniform(const char *name, const void *value)
		{
			if (m_pShaderProgram)
			{
				int location = m_pShaderProgram->GetUniformLocation(name);
				if (location >= 0)
				{
					int size = m_pShaderProgram->GetUniformTypeSizeByLocation(location);
					strncpy(m_uniforms[location].m_name, name, sizeof(m_uniforms[location].m_name));
					m_uniforms[location].SetValue(value, size);
				}
			}
		}

		void CRenderable::SetUniform(int location, const void *value, uint size)
		{
			//if (m_uniforms.find(location) != m_uniforms.end())
			m_uniforms[location].SetValue(value, size);
		}

		void CRenderable::SetTexture(int slot, ITexture *pTexture)
		{
			m_pTexture[slot] = pTexture;
		}


	}
}