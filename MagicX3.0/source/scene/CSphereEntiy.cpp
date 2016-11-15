#include "scene/CSphereEntiy.h"
#include "math/CVector2.h"
#include "math/CVector3.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{
		using namespace math;
		CSphereEntity::CSphereEntity(IScene *pScene, float fRadius, int iSlices, int iStacks)
			:CEntity(pScene)
			, m_pReflectObject(nullptr)
		{
			m_pSphere = new CSphere(fRadius, iSlices, iStacks);	
		}

		CSphereEntity::~CSphereEntity()
		{
			SAFE_DEL(m_pSphere);
			SAFE_DEL(m_pReflectObject);
		}

		void CSphereEntity::UpdateImp(int delta)
		{
			if (m_pSceneParent)
			{
				ICamera *pCam = m_pSceneParent->GetCamera();
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
					ISkyBox *pSkyBox = m_pSceneParent->GetSkyBox();
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

					if (m_pReflectObject)
						m_pReflectObject->Update(mvpMat4.m, mvMat4.m, camInvMat4.m, normalMat3);
					
				}
			}			
		}

		void CSphereEntity::RenderImp()
		{
			if (m_pReflectObject)
				m_pReflectObject->Render();
		}


		void CSphereEntity::CreateReflect()
		{
			if (m_pSceneParent)
			{
				ISkyBox *pSkyBox = m_pSceneParent->GetSkyBox();
				if (pSkyBox)
				{
					ITexture *pTexture = pSkyBox->GetTexture();
					if (pTexture)
					{
						m_pReflectObject = new CReflectObject();
						m_pReflectObject->Create(m_pSphere->GetVertices(), m_pSphere->GetNormals(), m_pSphere->GetVertexSize(), m_pSphere->GetVertexCount(), pTexture);
					}
				}
			}
		}

	}
}