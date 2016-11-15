#include "scene/CReflectObject.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{

		CReflectObject::CReflectObject()
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());
		}

		CReflectObject::~CReflectObject()
		{
			RENDERER->DestroyRenderable(m_pRenderable);
			RENDERER->DestroyVertexArrayObject(m_pVAO);
		}

		void CReflectObject::Create(void *pVertexes, void *pNormals, int vertSize, int verticeCount, ITexture *pTexture)
		{
			if (!m_pVAO) return;

			m_pVAO->Bind();
			IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
			if (pShaderProgram)
			{
				pShaderProgram->Attach("shader/reflection.vs", ST_VERTEX);
				pShaderProgram->Attach("shader/reflection.ps", ST_FRAGMENT);
				pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				pShaderProgram->Link();

				int cubeUnit = 0;
				pShaderProgram->SetUniform("cubeMap", &cubeUnit);
			}

			IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(NULL, vertSize + vertSize, 0, verticeCount, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			if (bufferObject)
			{
				bufferObject->BufferSubData(pVertexes, vertSize, 0);
				bufferObject->BufferSubData(pNormals, vertSize, vertSize);
			}

			m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
			m_pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 0, vertSize);
		
			bufferObject->UnBind();
			m_pRenderable->SetTexture(0, pTexture);							

			m_pVAO->UnBind();

		}

		void CReflectObject::Update(const float mvpMat4[16], const float mvMat4[16], const float camInvMat4[16], const float normalMat3[9])
		{
			IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
			if (pShaderProgram)
			{
				pShaderProgram->SetUniform("mvpMatrix", (float *)mvpMat4);
				pShaderProgram->SetUniform("mvMatrix", (float *)mvMat4);
				pShaderProgram->SetUniform("mInverseMatrix", (float *)camInvMat4);
				pShaderProgram->SetUniform("normalMatrix", (float *)normalMat3);
			}
			if (m_pRenderable)
				m_pRenderable->SumbitToRenderList();
		}

		void CReflectObject::Render()
		{
			if (m_pVAO)
				m_pVAO->Render();
		}

	}
}