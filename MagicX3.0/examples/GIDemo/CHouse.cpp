#include "CHouse.h"
#include "mx.h"

namespace mx
{
	namespace ex
	{

		CHouse::CHouse(float w, float h, float d)
		{
			AddRenderPhase(1, 1);
			AddRenderPhase(2, 2);
			AddRenderPhase(3, 3);

			float halfW = w * 0.5f;
			float halfH = h * 0.5f;
			float halfD = d * 0.5f;

			float vertices[] = {
				-halfW, -halfH, halfD,
				halfW, -halfH, halfD, 
				halfW, halfH, halfD,
				-halfW, halfH, halfD,

				-halfW, -halfH, -halfD,
				halfW, -halfH, -halfD, 
				halfW, halfH, -halfD,
				-halfW, halfH, -halfD

				////back
				//halfW, -halfH, -halfD, 
				//-halfW, -halfH, -halfD,
				//-halfW, halfH, -halfD,
				//halfW, halfH, -halfD,
			};
			float normals[] = {
				1.0, 1.0, .0,
				-1.0, 1.0, .0,
				-1.0, -1.0, .0,
				1.0, -1.0, .0,

				1.0, 1.0, 1.0,
				-1.0, 1.0, 1.0,
				-1.0, -1.0, 1.0,
				1.0, -1.0, 1.0,

				//1.0, -1.0, -1.0,
				//-1.0, -1.0, -1.0,
				//-1.0, 1.0, -1.0,
				//1.0, 1.0, -1.0
			};

			uint indices[] = {

				//back
				4, 5, 6,
				4, 6, 7, 


				//left
				0, 4, 7,
				0, 7, 3,
				
				//right
				5, 1, 2, 
				5, 2, 6,

				//top
				7, 6, 2,
				7, 2, 3,

				//bottom
				0, 1, 5,
				0, 5, 4,
			};


			for (auto renderable : m_vecRenderables)
			{
				IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
				pVAO->Bind();
				IBufferObject *pBufferObject = renderable->CreateVertexBufferObject(nullptr, sizeof(vertices) + sizeof(normals), 0, sizeof(vertices) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				if (pBufferObject)
				{
					pBufferObject->BufferSubData(vertices, sizeof(vertices), 0);
					pBufferObject->BufferSubData(normals, sizeof(normals), sizeof(vertices));
				}
				renderable->CreateIndexBufferObject(indices, sizeof(indices) / sizeof(uint), RVT_UINT, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				renderable->Disable(RA_CULL_FACE);
				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
				pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 0, sizeof(vertices));
				pVAO->UnBind();
			}

		}

		CHouse::~CHouse()
		{
		}

		void CHouse::UpdateImp(int delta)
		{
			static float color[] = {0.9, 0.9, 0.9};
			for (auto renderable : m_vecRenderables)
			{
				renderable->SetUniform("color", color);
				//CMatrix4 rot;
				//rot.SetRotationRadians(30 * PI / 180.f, CVector3(0, 1, 0));
				//renderable->SetUniform("modelMatrix", (rot * GetAbsluateTransformation()).m);
			}
			CEntity::UpdateImp(delta);
		}

	}
}