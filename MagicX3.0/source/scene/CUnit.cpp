#include "scene/CUnit.h"
#include "CModel.h"
#include "mx.h"
#include "render/SVertexAttribute.h"

namespace mx
{
	namespace scene
	{

		CUnit::CUnit()
		{
			m_pMode = new CModel();
			m_pVAO =  RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());
		}

		CUnit::CUnit(IVertex *pVertex, const char *texfile /*= nullptr*/)
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());

			CreateRenderable(pVertex, texfile);
		}

		CUnit::~CUnit()
		{
			delete m_pMode;
			RENDERER->DestroyRenderable(m_pRenderable);
			RENDERER->DestroyVertexArrayObject(m_pVAO);
		}

		void CUnit::LoadModel(const char *filename)
		{
			if (m_pMode)
			{
				m_pMode->Load(filename);
			}

			//创建渲染体数据

			float vertexes[] = {
				-1, -1, 1,
				1, -1, 1,
				1, 1, 1,
				-1, 1, 1,

				-1, -1, -1,
				1, -1, -1,
				1, 1, -1,
				-1, 1, -1
			};

			uint indices[] = {
				0, 1, 2,	 0, 2, 3,
				4, 6, 5,	 4, 7, 6
			};

			if (m_pRenderable)
			{
				m_pVAO->Bind();

				IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();				

				pShaderProgram->CreateStandShader(ESS_SHADER_IDENTITY);

				float vColor[] = { 1, 0, 1, 1 };
				pShaderProgram->SetUniform("vColor", vColor);

				
				for (int i = 0; i < sizeof(vertexes) / sizeof(float); ++i)
				{
					vertexes[i] *= 0.5;
				}

				m_pRenderable->CreateVertexBufferObject(vertexes, sizeof(vertexes), 0, sizeof(vertexes) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderable->CreateIndexBufferObject(indices, sizeof(indices) / sizeof(uint), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
	
				//pShaderProgram->Attach("shader/test.vs", render::ST_VERTEX);
				//pShaderProgram->Attach("shader/test.fs", render::ST_FRAGMENT);
				//pShaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
				//pShaderProgram->Link();
				//int iTextureUnit = 0;
				//pShaderProgram->SetUniform("textureUnit0", &iTextureUnit);
				
				m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
				
				m_pVAO->UnBind();

			}
		}

		void CUnit::UpdateImp(int delta)
		{
			//没有被剔除掉，加入到渲染列表
			if (true)
			{
				m_pRenderable->SumbitToRenderList();
			}
		}

		void CUnit::RenderImp()
		{
			m_pVAO->Render();
		}

		void CUnit::CreateRenderable(IVertex *pVertex, const char *texfile)
		{
			uint vertAttr = pVertex->GetVertexAttribute();

			if (m_pRenderable)
			{
				m_pVAO->Bind();

				IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();

				pShaderProgram->CreateStandShader(ESS_SHADER_IDENTITY);


				m_pRenderable->CreateVertexBufferObject(pVertex->GetVertexData(), pVertex->GetVerticeSize(), 0, pVertex->GetVerticeCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderable->CreateIndexBufferObject(pVertex->GetIndicesData(), pVertex->GetIndicesCount(), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

				//pShaderProgram->Attach("shader/test.vs", render::ST_VERTEX);
				//pShaderProgram->Attach("shader/test.fs", render::ST_FRAGMENT);
				//pShaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
				//pShaderProgram->Link();
				//int iTextureUnit = 0;
				//pShaderProgram->SetUniform("textureUnit0", &iTextureUnit);

				m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);

				m_pVAO->UnBind();

			}
		}

	}
}