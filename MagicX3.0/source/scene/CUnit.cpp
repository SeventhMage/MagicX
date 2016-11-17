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
			m_pVAO =  RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());
		}

		CUnit::CUnit(IVertex *pVertex, const char *texfile /*= nullptr*/)			
			: m_pMode(NULL)
			,m_pTexture(nullptr)
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());

			CreateRenderable(pVertex, texfile);
		}

		CUnit::~CUnit()
		{
			if (m_pMode)
				delete m_pMode;
			if (m_pTexture)
				delete m_pTexture;
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
				-1, -1, 1, 0, 0,
				1, -1, 1, 1, 0,
				1, 1, 1, 1, 1,
				-1, 1, 1, 0, 1,

				-1, -1, -1, 0, 0,
				1, -1, -1, 1, 0,
				1, 1, -1, 1, 1,
				-1, 1, -1, 0, 1
			};

			uint indices[] = {
				0, 1, 2,	 0, 2, 3,
				4, 6, 5,	 4, 7, 6
			};

			if (m_pRenderable)
			{
				m_pVAO->Bind();
				ITexture *pTexture = RENDERER->CreateTexture("texture/crate.tga");
				m_pRenderable->SetTexture(0, pTexture);

				IShaderProgram *pShaderProgram = m_pRenderable->GetShaderProgram();				

				pShaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_REPLACE);

				float vColor[] = { 1, 0, 0, 1 };
				pShaderProgram->SetUniform("vColor", vColor);


				CMatrix4 mat4;
				//mat4.buildProjectionMatrixOrthoRH(20, 20, 10, -10);

				CMatrix4 projectMat4;
				projectMat4.BuildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 1.0f * 600 / 800, 1, 1000.0f);
				CMatrix4 viewMat4;
				viewMat4.BuildCameraLookAtMatrix(CVector3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 1, 0));
				CMatrix4 modelMat4;
				modelMat4.SetTranslation(CVector3(0, 0, -20.0f));
				CMatrix4 mvpMat4 = modelMat4 * viewMat4 * projectMat4;
				pShaderProgram->SetUniform("mvpMatrix", mvpMat4.m);

				//for (int i = 0; i < sizeof(vertexes) / sizeof(float); ++i)
				//{
				//	vertexes[i] *= 50;
				//}

				m_pRenderable->CreateVertexBufferObject(vertexes, sizeof(vertexes), 0, sizeof(vertexes) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderable->CreateIndexBufferObject(indices, sizeof(indices) / sizeof(uint), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

				//pShaderProgram->Attach("shader/test.vs", render::ST_VERTEX);
				//pShaderProgram->Attach("shader/test.fs", render::ST_FRAGMENT);
				//pShaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
				//pShaderProgram->Link();
				int iTextureUnit = 0;
				pShaderProgram->SetUniform("textureUnit0", &iTextureUnit);

				m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 5 * sizeof(float), 0);
				m_pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

				m_pVAO->UnBind();
			}
		}

		void CUnit::UpdateImp(int delta)
		{
			//没有被剔除掉，加入到渲染列表
			if (true)
			{
				IShaderProgram *pShaderProgram = m_pRenderable->GetShaderProgram();
				if (pShaderProgram)
				{
					CMatrix4 vpMat4;
					if (SCENEMGR->GetCurrentScene())
					{
						ICamera *pCam = SCENEMGR->GetCurrentScene()->GetCamera();
						if (pCam)
						{
							vpMat4 = pCam->GetViewProjectionMatrix();
						}
					}
					CMatrix4 mvpMat4 = GetAbsluateTransformation() * vpMat4;
					pShaderProgram->SetUniform("mvpMatrix", mvpMat4.m);
				}
			
				m_pRenderable->SumbitToRenderList();
			}
		}

		void CUnit::CreateRenderable(IVertex *pVertex, const char *texfile)
		{
			uint vertAttr = pVertex->GetVertexAttribute();

			if (m_pRenderable)
			{				
				m_pVAO->Bind();

				IShaderProgram *pShaderProgram = m_pRenderable->GetShaderProgram();
				if (pShaderProgram)
				{
					if (vertAttr == VF_POSITION)
						pShaderProgram->CreateStandShader(ESS_SHADER_IDENTITY);
					else if (vertAttr == (VF_POSITION | VF_COLOR))
						pShaderProgram->CreateStandShader(ESS_SHADER_FLAT);
					else if (vertAttr == (VF_POSITION | VF_TEXCOORD))
						pShaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_REPLACE);
					else if (vertAttr == (VF_POSITION | VF_COLOR))
						pShaderProgram->CreateStandShader(ESS_SHADER_SHADED);
					else if (vertAttr == (VF_POSITION | VF_COLOR | VF_TEXCOORD))
						pShaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_MODULATE);
					else if (vertAttr == (VF_POSITION | VF_TEXCOORD | VF_NORMAL))
						pShaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_REPLACE);
					else if (vertAttr == (VF_POSITION | VF_COLOR | VF_NORMAL | VF_TEXCOORD))
						pShaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_REPLACE);


					m_pTexture = RENDERER->CreateTexture(texfile);
					m_pRenderable->SetTexture(0, m_pTexture);

					uint pUnit = 0;
					pShaderProgram->SetUniform("textureUnit0", &pUnit);

					float vColor[] = { 1, 1, 1, 1 };
					pShaderProgram->SetUniform("vColor", vColor);

	
					m_pRenderable->CreateVertexBufferObject(pVertex->GetVertexData(), pVertex->GetVerticeSize(), 0, pVertex->GetVerticeCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
					m_pRenderable->CreateIndexBufferObject(pVertex->GetIndicesData(), pVertex->GetIndicesCount(), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

					uint stride = GetVertexStride(EVertexAttribute(vertAttr));
					uint offset = 0;
					if (vertAttr & VF_POSITION)
					{
						m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, stride, offset);
						offset += 3 * sizeof(float);
					}
					if (vertAttr & VF_COLOR)
					{
						m_pVAO->EnableVertexAttrib(render::VAL_COLOR, 4, render::RVT_FLOAT, stride, offset);
						offset += 4 * sizeof(float);
					}
					if (vertAttr & VF_TEXCOORD)
					{
						m_pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, stride, offset);
						offset += 2 * sizeof(float);
					}
					if (vertAttr & VF_NORMAL)
					{
						m_pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, stride, offset);
						offset += 3 * sizeof(float);
					}

					m_pVAO->UnBind();
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