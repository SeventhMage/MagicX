#include "scene/CSphereEntiy.h"
#include "math/CVector2.h"
#include "math/CVector3.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{
		using namespace math;

		CSphereEntity::CSphereEntity(float fRadius, int iSlices, int iStacks, const CVector3 &color /* = CVector3(1.0f, 1.0f, 1.0f) */)
			:m_vColor(color)
			,m_fRadius(fRadius)
		{
			m_pSphere = new scene::CSphere(fRadius, iSlices, iStacks);


			AddRenderPhase(1, 10);
			AddRenderPhase(2, 2);
			AddRenderPhase(3, 9);
		}

		CSphereEntity::~CSphereEntity()
		{
			SAFE_DEL(m_pSphere);
		}

		void CSphereEntity::UpdateImp(int delta)
		{
			CEntity::UpdateImp(delta);
			for (auto renderable : m_vecRenderables)
			{
				renderable->SetUniform("color", m_vColor.v);
			}
		}

		void CSphereEntity::Create()
		{
			for (auto renderable : m_vecRenderables)
			{
				IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
				pVAO->Bind();
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