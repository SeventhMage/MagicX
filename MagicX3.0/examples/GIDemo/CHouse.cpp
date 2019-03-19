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

			float halfW = w * 0.5f;
			float halfH = h * 0.5f;
			float halfD = d * 0.5f;

			float vertices[] = {
				//front
				-halfW, -halfH, halfD,
				halfW, -halfH, halfD, 
				halfW, halfH, halfD,
				-halfW, halfH, halfD,

				//back
				halfW, -halfH, -halfD, 
				-halfW, -halfH, -halfD,
				-halfW, halfH, -halfD,
				halfW, halfH, -halfD,

				//left
				-halfW, -halfH, -halfD, 
				-halfW, -halfH, halfD,
				-halfW, halfH, halfD, 
				-halfW, halfH, -halfD,

				//right
				halfW, -halfH, halfD,
				halfW, -halfH, -halfD, 
				halfW, halfH, -halfD, 
				halfW, halfH, halfD,

				//top
				-halfW, halfH, halfD, 
				halfW, halfH, halfD,
				halfW, halfH, -halfD,
				-halfW, halfH, -halfD,

				//bottom
				-halfW, -halfH, -halfD,
				halfW, -halfH, -halfD, 
				halfW, -halfH, halfD,
				-halfW, -halfH, halfD,
			};
			float normals[] = {
				-1.0, -1.0, 1.0,
				1.0, -1.0, 1.0,
				1.0, 1.0, 1.0,
				-1.0, 1.0, 1.0,

				
				1.0, -1.0, -1.0,
				-1.0, -1.0, -1.0,
				-1.0, 1.0, -1.0,
				1.0, 1.0, -1.0
			};
			uint indices[] = {
				////front
				//0, 1, 2, 0, 1, 2, 
				//0, 2, 3, 0, 2, 3,

				//back
				4, 5, 6, 4, 5, 6,
				4, 6, 7, 4, 6, 7,

				////left
				//8, 9, 10, 4, 0, 3,
				//8, 10, 11,4, 3, 7,

				////right
				//12, 13, 14, 1, 4, 6,
				//12, 14, 15, 1, 6, 3,

				////top
				//16, 17, 18, 3, 2, 6,
				//16, 18, 19, 3, 6, 7,

				////bottom
				//20, 21, 22, 1, 0, 4,
				//20, 22, 23, 1, 4, 5,
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
				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
				pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 0, sizeof(vertices));
				renderable->Disable(RA_CULL_FACE);
				pVAO->UnBind();
			}

		}

		CHouse::~CHouse()
		{
		}

		void CHouse::UpdateImp(int delta)
		{
			CEntity::UpdateImp(delta);
		}

	}
}