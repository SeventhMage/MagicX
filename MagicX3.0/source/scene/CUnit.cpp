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
			:m_pTexture(nullptr)
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

			////创建渲染体数据

			//float vertexes[] = {
			//	-1, -1, 1,
			//	1, -1, 1,
			//	1, 1, 1,
			//	-1, 1, 1,

			//	-1, -1, -1,
			//	1, -1, -1,
			//	1, 1, -1,
			//	-1, 1, -1
			//};

			//uint indices[] = {
			//	0, 1, 2,	 0, 2, 3,
			//	4, 6, 5,	 4, 7, 6
			//};

			//if (m_pRenderable)
			//{
			//	m_pVAO->Bind();

			//	IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();				

			//	pShaderProgram->CreateStandShader(ESS_SHADER_IDENTITY);

			//	float vColor[] = { 1, 0, 1, 1 };
			//	pShaderProgram->SetUniform("vColor", vColor);

			//	
			//	for (int i = 0; i < sizeof(vertexes) / sizeof(float); ++i)
			//	{
			//		vertexes[i] *= 0.5;
			//	}

			//	m_pRenderable->CreateVertexBufferObject(vertexes, sizeof(vertexes), 0, sizeof(vertexes) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			//	m_pRenderable->CreateIndexBufferObject(indices, sizeof(indices) / sizeof(uint), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
	
			//	//pShaderProgram->Attach("shader/test.vs", render::ST_VERTEX);
			//	//pShaderProgram->Attach("shader/test.fs", render::ST_FRAGMENT);
			//	//pShaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
			//	//pShaderProgram->Link();
			//	//int iTextureUnit = 0;
			//	//pShaderProgram->SetUniform("textureUnit0", &iTextureUnit);
			//	
			//	m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
			//	
			//	m_pVAO->UnBind();

			typedef struct
			{
				float x, y, z;
				float u, v;
			}Vertex;

			Vertex pyramid[9] = {
				{ -5.0f, -5.0f, 5.0f, 0, 1.0f },
				{ 5.0f, -5.0f, 5.0f, 1.0f, 1.0f },
				{ 0, 5.0f, 0, 0.5f, 0 },

				{ 5.0f, -5.0f, 5.0f, 0.0f, 1.0f },
				{ 0, -5.0f, -5.0f, 1.0f, 1.0f },
				{ 0, 5.0f, 0, 0.5f, 0 },

				{ 0, -5.0f, -5.0f, 0.0f, 1.0f },
				{ -5.0f, -5.0f, 5.0f, 1.0f, 1.0f },
				{ 0, 5.0f, 0, 0.5f, 0 },
			};

			uint indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
			m_pVAO->Bind();

			m_pTexture = RENDERER->CreateTexture("texture/crate.tga");

			IShaderProgram *shaderProgram = m_pVAO->GetShaderProgram();
			shaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_MODULATE);

			int iTextureUnit = 0;
			shaderProgram->SetUniform("textureUnit0", &iTextureUnit);

			float vColor[] = { 1, 1, 1, 1 };
			shaderProgram->SetUniform("vColor", vColor);
			CMatrix4 mat4;
			//mat4.buildProjectionMatrixOrthoRH(20, 20, 10, -10);

			CMatrix4 projectMat4;
			projectMat4.BuildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 1.0f * 600 / 800, 1, 100.0f);
			CMatrix4 viewMat4;
			viewMat4.BuildCameraLookAtMatrix(CVector3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 1, 0));
			CMatrix4 modelMat4;
			modelMat4.SetTranslation(CVector3(0, 0, -20.0f));

			CMatrix4 mvpMat4 = projectMat4 * viewMat4 * modelMat4;

			shaderProgram->SetUniform("mvpMatrix", mvpMat4.m);
			m_pRenderable->SetTexture(0, m_pTexture);
			m_pRenderable->CreateVertexBufferObject(pyramid, sizeof(pyramid), 0, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			m_pRenderable->CreateIndexBufferObject(indices, 9, RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			//buffer->AddVertexData(renderableObject, triangle1, sizeof(triangle1), 0);
			//buffer->AddVertexData(renderableObject, color, sizeof(color), sizeof(triangle));
			//buffer->AddVertexData(renderableObject, texture, sizeof(texture), sizeof(triangle1));
			m_pVAO->EnableVertexAttrib(VAL_POSITION, 4, RVT_FLOAT, sizeof(Vertex), 0);
			//buffer->EnableVertexAttrib(VAI_COLOR, 4, RVT_FLOAT, sizeof(triangle));
			m_pVAO->EnableVertexAttrib(VAL_TEXTURE0, 2, RVT_FLOAT, sizeof(Vertex), sizeof(float)* 3);
			
		}

		void CUnit::UpdateImp(int delta)
		{
			//没有被剔除掉，加入到渲染列表
			if (true)
			{
				IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
				if (pShaderProgram)
				{
					//pShaderProgram->SetUniform("mvpMatrix", color);

				}

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
				m_pTexture = RENDERER->CreateTexture(texfile);
				m_pVAO->Bind();

				IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();	
				

				pShaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_MODULATE);

				m_pRenderable->CreateVertexBufferObject(pVertex->GetVertexData(), pVertex->GetVerticeSize(), 0, pVertex->GetVerticeCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderable->CreateIndexBufferObject(pVertex->GetIndicesData(), pVertex->GetIndicesCount(), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

				m_pRenderable->SetTexture(0, m_pTexture);

				uint pUnit = 0;
				pShaderProgram->SetUniform("textureUnit0", &pUnit);

				float vColor[] = { 1, 1, 1, 1 };
				pShaderProgram->SetUniform("vColor", vColor);

				CMatrix4 mat4;
				//mat4.buildProjectionMatrixOrthoRH(20, 20, 10, -10);

				CMatrix4 projectMat4;
				projectMat4.BuildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 1.0f * 600 / 800, 1, 1000.0f);
				CMatrix4 viewMat4;
				viewMat4.BuildCameraLookAtMatrix(CVector3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 1, 0));
				CMatrix4 modelMat4;
				modelMat4.SetTranslation(CVector3(0, 0, -20.0f));

				CMatrix4 mvpMat4 = projectMat4 * viewMat4 * modelMat4;

				pShaderProgram->SetUniform("mvpMatrix", mvpMat4.m);

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