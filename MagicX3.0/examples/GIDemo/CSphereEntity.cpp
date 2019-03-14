#include "CSphereEntity.h"
#include "mx.h"

namespace mx
{
	namespace ex
	{
		CSphereEntity::CSphereEntity(float fRadius, int iSlices, int iStacks)
		{
			m_pSphere = new scene::CSphere(fRadius, iSlices, iStacks);
			AddRenderPhase(1, 1);
			AddRenderPhase(2, 2);
			AddRenderPhase(3, 3);
			AddRenderPhase(4, 4);
			AddRenderPhase(5, 5);
		}

		CSphereEntity::~CSphereEntity()
		{
			SAFE_DEL(m_pSphere);
		}

		void CSphereEntity::UpdateImp(int delta)
		{
			for (auto renderable : m_vecRenderables)
			{
				
				if (renderable)
					renderable->SumbitToRenderQueue();
			}

		}

		void CSphereEntity::Create()
		{

			for (auto renderable : m_vecRenderables)
			{
				IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
				
				IBufferObject *bufferObject = renderable->CreateVertexBufferObject(NULL, m_pSphere->GetVertexSize() * 2, 0, m_pSphere->GetVertexCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				if (bufferObject)
				{
					bufferObject->BufferSubData(m_pSphere->GetVertices(), m_pSphere->GetVertexSize(), 0);
					bufferObject->BufferSubData(m_pSphere->GetNormals(), m_pSphere->GetVertexSize(), m_pSphere->GetVertexSize());
				}

				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
				pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 0, m_pSphere->GetVertexSize());

				bufferObject->UnBind();
				pVAO->UnBind();
			}

		}
	}


}