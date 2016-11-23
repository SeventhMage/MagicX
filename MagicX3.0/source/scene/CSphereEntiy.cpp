#include "scene/CSphereEntiy.h"
#include "math/CVector2.h"
#include "math/CVector3.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{
		using namespace math;

		CSphereEntity::CSphereEntity(IRenderObject *pRenderObject, float fRadius, int iSlices, int iStacks)
			:m_pReflectObject(pRenderObject)
		{
			m_pSphere = new CSphere(fRadius, iSlices, iStacks);
		}

		CSphereEntity::~CSphereEntity()
		{
			SAFE_DEL(m_pSphere);			
			SAFE_DEL(m_pRenderable);
		}

		void CSphereEntity::UpdateImp(int delta)
		{
			IScene *pScene = SCENEMGR->GetCurrentScene();
			if (pScene)
			{
				ICamera *pCam = pScene->GetCamera();
				if (pCam)
				{				
					CMatrix4 mvpMat4 = GetAbsluateTransformation() * pCam->GetViewProjectionMatrix();
					CMatrix4 mvMat4 = GetAbsluateTransformation() * pCam->GetViewMatrix();
					CMatrix4 mvRotMat4 = mvMat4;
					mvRotMat4.SetTranslation(CVector3(0, 0, 0));
					CMatrix4 normalMat4;
					CMatrix4 camInvMat4;
					mvRotMat4.GetInverse(camInvMat4);
					camInvMat4.GetTransposed(normalMat4);

					pCam->GetViewMatrix().GetInverse(camInvMat4);
					camInvMat4.SetTranslation(CVector3(0, 0,0));
					ISkyBox *pSkyBox = pScene->GetSkyBox();
					if (pSkyBox)
					{
						CMatrix4 skyBoxMat4 = pSkyBox->GetModelMatrix();
						CMatrix4 skyBoxInvMat4;
						skyBoxMat4.GetInverse(skyBoxInvMat4);

						camInvMat4 = skyBoxInvMat4 * camInvMat4;
					}


					float normalMat3[] = { normalMat4.m[0], normalMat4.m[1], normalMat4.m[2],
						normalMat4.m[4], normalMat4.m[5], normalMat4.m[6],
						normalMat4.m[8], normalMat4.m[9], normalMat4.m[10] };

					if (m_pRenderable)
					{
						m_pRenderable->Bind();
						if (m_pReflectObject)
						{
							UniformMap um;
							um["mvpMatrix"] = mvpMat4.m;
							um["mvMatrix"] = mvMat4.m;
							um["normalMatrix"] = normalMat3;
							um["mInverseMatrix"] = camInvMat4.m;

							CPointLight *pLight = (CPointLight *)pScene->GetLight(0);
							if (pLight)
							{
								CVector3 vLightPos = pLight->GetPosition();
								pCam->GetViewMatrix().TransformVect(vLightPos);
								um["vLightPos"] = vLightPos.v;
							}

							
							CMatrix4 lightViewMat;
							CVector3 pos = ((CPointLight *)pLight)->GetPosition();
							lightViewMat.BuildCameraLookAtMatrix(pos, -pos, CVector3(0, 1, 0));
							CMatrix4 lightProMat;
							lightProMat.BuildProjectionMatrixPerspectiveFovRH(PI / 2.f, 1.f * 800 / 600, 1.f, 1000.f);
							CMatrix4 smvpMat4 = GetAbsluateTransformation() * lightViewMat * lightProMat;

							UniformMap sum;

							sum["mvpMatrix"] = smvpMat4.m;
							m_pReflectObject->Update(m_pRenderable, um, &sum);
						}
						m_pRenderable->SumbitToRenderList();

						m_pRenderable->UnBind();
					}
				
				}									
			}			
		}

		void CSphereEntity::Create()
		{
			if (!m_pSphere) return;
			
			IVertexArrayObject *pVAO = m_pReflectObject->GetVAO();
			if (pVAO)
			{
				pVAO->Bind();
				m_pRenderable = RENDERER->CreateRenderable(pVAO->GetRenderList());

				m_pReflectObject->Create(m_pRenderable);

				IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(NULL, m_pSphere->GetVertexSize() * 2, 0, m_pSphere->GetVertexCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				if (bufferObject)
				{
					bufferObject->BufferSubData(m_pSphere->GetVertices(), m_pSphere->GetVertexSize(), 0);
					bufferObject->BufferSubData(m_pSphere->GetNormals(), m_pSphere->GetVertexSize(), m_pSphere->GetVertexSize());
				}				
				
				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
				pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 0, m_pSphere->GetVertexSize());
				
				bufferObject->UnBind();
				pVAO->UnBind();

				m_pReflectObject->SetTexture(m_pRenderable);
			}
		}

	}
}