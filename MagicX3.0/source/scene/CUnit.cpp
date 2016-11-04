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
			m_pRenderable = RENDERER->CreateRenderable();
		}

		CUnit::~CUnit()
		{
			delete m_pMode;
			RENDERER->DestroyRenderable(m_pRenderable);
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

			float indices[] = {
				0, 1, 2,	 0, 2, 3,
				4, 6, 5,	 4, 7, 6
			};

			if (m_pRenderable)
			{
				IVertexArrayObject *pVAO = RENDERER->CreateVertexArrayObject();
				pVAO->Bind();

				m_pRenderable->CreateVertexBufferObject(vertexes, sizeof(vertexes), 0, sizeof(vertexes) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderable->CreateIndexBufferObject(indices, sizeof(indices) / sizeof(float), RVT_FLOAT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				IShaderProgram *pShaderProgram = pVAO->GetShaderProgram();
				pShaderProgram->Attach("shader/test.vs", render::ST_VERTEX);
				pShaderProgram->Attach("shader/test.fs", render::ST_FRAGMENT);
				pShaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
				pShaderProgram->Link();
				//int iTextureUnit = 0;
				//pShaderProgram->SetUniform("textureUnit0", &iTextureUnit);
				
				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, sizeof(SVertex), 0);
				
				pVAO->UnBind();

			}
		}

		void CUnit::Update(int delta)
		{
			//没有被剔除掉，加入到渲染列表
			if (true)
			{
				m_pRenderable->SumbitToRenderQueue();
			}
		}

	}
}