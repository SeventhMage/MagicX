#include "scene/CUnit.h"
#include "CModel.h"
#include "mx.h"
#include "render/SVertexAttribute.h"

namespace mx
{
	namespace scene
	{

		CUnit::CUnit()			
			:m_pTexture(nullptr)
		{
			m_pMode = new CModel();

			AddRenderPhase(1, 1);
			AddRenderPhase(2, 2);
			AddRenderPhase(3, 3);

		}

		CUnit::CUnit(IVertex *pVertex, const char *texfile)			
			: m_pMode(NULL)
			,m_pTexture(nullptr)
		{
			AddRenderPhase(1, 1);
			AddRenderPhase(2, 2);
			AddRenderPhase(3, 3);
			CreateRenderable(pVertex, texfile);
		}

		CUnit::~CUnit()
		{
			if (m_pMode)
				delete m_pMode;
			if (m_pTexture)
				delete m_pTexture;
		}

		void CUnit::LoadModel(const char *filename)
		{
			if (m_pMode)
			{
				m_pMode->Load(filename);
			}

			//创建渲染体数据

			float vertexes[] = {
				-1, -1, 1, 0, 0, -1, -1, 1,
				1, -1, 1, 1, 0, 1, -1, 1,
				1, 1, 1, 1, 1, 1, 1, 1,
				-1, 1, 1, 0, 1, -1, 1, 1,

				-1, -1, -1, 0, 0, -1, -1, -1,
				1, -1, -1, 1, 0, 1, -1, -1,
				1, 1, -1, 1, 1, 1, -1, -1,
				-1, 1, -1, 0, 1, -1, 1, -1,
			};


			uint indices[] = {
				0, 1, 2,	 0, 2, 3,
				4, 6, 5,	 4, 7, 6
			};
			for (auto renderable : m_vecRenderables)
			{
				if (renderable)
				{
					IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
					pVAO->Bind();
					ITexture *pTexture = RENDERER->CreateTexture("texture/crate.tga");
					renderable->SetTexture(0, pTexture);

					IShaderProgram *pShaderProgram = renderable->GetShaderProgram();

			
					float vColor[] = { 1, 1, 1, 1 };
					pShaderProgram->SetUniform("vColor", vColor);


					CMatrix4 mat4;
			
					renderable->CreateVertexBufferObject(vertexes, sizeof(vertexes), 0, sizeof(vertexes) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
					renderable->CreateIndexBufferObject(indices, sizeof(indices) / sizeof(uint), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

					int iTextureUnit = 0;
					pShaderProgram->SetUniform("textureColor", &iTextureUnit);

					pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 8 * sizeof(float), 0);
					pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
					pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 8 * sizeof(float), 5 * sizeof(float));

					pVAO->UnBind();
				}
			}

		}

		void CUnit::UpdateImp(int delta)
		{
			//没有被剔除掉，加入到渲染列表
			if (true)
			{
				CEntity::UpdateImp(delta);
			}
		}

		void CUnit::CreateRenderable(IVertex *pVertex, const char *texfile)
		{
			uint vertAttr = pVertex->GetVertexAttribute();
			for (auto renderable : m_vecRenderables)
			{
				if (renderable)
				{
					IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
					pVAO->Bind();

					if (renderable)
					{
						m_pTexture = RENDERER->CreateTexture(texfile);
						renderable->SetTexture(0, m_pTexture);

						uint pUnit = 0;
						renderable->SetUniform("textureColor", &pUnit);

						float vColor[] = { 1, 1, 1, 1 };
						renderable->SetUniform("color", vColor);


						renderable->CreateVertexBufferObject(pVertex->GetVertexData(), pVertex->GetVerticeSize(), 0, pVertex->GetVerticeCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
						renderable->CreateIndexBufferObject(pVertex->GetIndicesData(), pVertex->GetIndicesCount(), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

						uint stride = GetVertexStride(EVertexAttribute(vertAttr));
						uint offset = 0;
						if (vertAttr & VF_POSITION)
						{
							pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, stride, offset);
							offset += 3 * sizeof(float);
						}
						if (vertAttr & VF_COLOR)
						{
							pVAO->EnableVertexAttrib(render::VAL_COLOR, 4, render::RVT_FLOAT, stride, offset);
							offset += 4 * sizeof(float);
						}
						if (vertAttr & VF_TEXCOORD)
						{
							pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, stride, offset);
							offset += 2 * sizeof(float);
						}
						if (vertAttr & VF_NORMAL)
						{
							pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, stride, offset);
							offset += 3 * sizeof(float);
						}

						pVAO->UnBind();
					}
				}
			}

		}

		mx::uint CUnit::GetVertexStride(EVertexAttribute attr)
		{
			uint stride = 0;

			if (attr & VF_POSITION)
			{
				stride += 3 * sizeof(float);
			}
			if (attr & VF_COLOR)
			{
				stride += 4 * sizeof(float);
			}
			if (attr & VF_TEXCOORD)
			{
				stride += 2 * sizeof(float);
			}
			if (attr & VF_NORMAL)
			{
				stride += 3 * sizeof(float);
			}

			return stride;
		}

	}
}