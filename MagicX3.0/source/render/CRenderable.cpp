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
		{
			memset(m_pTexture, 0, sizeof(ITexture *)* TU_TEXTURE_NUM);	
			for (int i = 0; i < RA_NUM; ++i)
				m_bRenderAttrs[i] = true;

			m_pShaderProgram = pRenderer->CreateShaderProgram();

			//绘制阴影图时使用的shader
			m_pShadowShaderProgram = pRenderer->CreateShaderProgram();
			m_pShadowShaderProgram->Attach("shader/shadow.vs", ST_VERTEX);
			m_pShadowShaderProgram->Attach("shader/shadow.ps", ST_FRAGMENT);
			m_pShadowShaderProgram->BindAttributeLocation(1, VAL_POSITION);
			m_pShadowShaderProgram->Link();
		}

		CRenderable::~CRenderable()
		{
			m_pRenderer->DestroyBufferObject(m_pVBO);
			m_pRenderer->DestroyBufferObject(m_pIBO);

			m_pRenderer->DestroyShaderProgram(m_pShaderProgram);
			m_pRenderer->DestroyShaderProgram(m_pShadowShaderProgram);
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

		void CRenderable::Bind()
		{
			if (m_pVBO)
				m_pVBO->Bind();
			if (m_pIBO)
				m_pIBO->Bind();

			if (m_pRenderer->IsRenderShadowMap())
			{
				if (m_pShadowShaderProgram)
					m_pShadowShaderProgram->Bind();
			}
			else
			{
				if (m_pShaderProgram)
					m_pShaderProgram->Bind();
			}


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

		void CRenderable::SetTexture(int slot, ITexture *pTexture)
		{
			m_pTexture[slot] = pTexture;
		}


	}
}