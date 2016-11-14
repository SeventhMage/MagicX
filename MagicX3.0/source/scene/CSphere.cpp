#include "scene/CSphere.h"
#include "math/CVector2.h"
#include "math/CVector3.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{
		using namespace math;
		CSphere::CSphere(IScene *pScene, float fRadius, int iSlices, int iStacks)
			:CEntity(pScene)
			, m_pTexture(nullptr)
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();			
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());

			Create(fRadius, iSlices, iStacks);
	
		}

		CSphere::CSphere(IScene *pScene)
			:CEntity(pScene)
			, m_pTexture(nullptr)
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());
		}

		CSphere::~CSphere()
		{
			RENDERER->DestroyRenderable(m_pRenderable);
			RENDERER->DestroyVertexArrayObject(m_pVAO);			
		}

		void CSphere::UpdateImp(int delta)
		{
			if (m_pSceneParent)
			{
				ICamera *pCam = m_pSceneParent->GetCamera();
				if (pCam)
				{
					IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
					if (pShaderProgram)
					{
						CMatrix4 mvpMat4 = GetAbsluateTransformation() * pCam->GetViewProjectionMatrix();;
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

							camInvMat4 = camInvMat4 * skyBoxInvMat4;
						}


						float normalMat3[] = { normalMat4.m[0], normalMat4.m[1], normalMat4.m[2],
							normalMat4.m[4], normalMat4.m[5], normalMat4.m[6],
							normalMat4.m[8], normalMat4.m[9], normalMat4.m[10] };
						pShaderProgram->SetUniform("mvpMatrix", mvpMat4.m);
						pShaderProgram->SetUniform("mvMatrix", mvMat4.m);
						pShaderProgram->SetUniform("normalMatrix", normalMat3);
						pShaderProgram->SetUniform("mInverseMatrix", camInvMat4.m);



					}
				}
			}


			m_pRenderable->SumbitToRenderList();
		}

		void CSphere::RenderImp()
		{
			if (m_pVAO)
				m_pVAO->Render();
		}


		void CSphere::Create(float fRadius, int iSlices, int iStacks)
		{
			if (!m_pVAO) return;

			m_pVAO->Bind();
			IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
			//pShaderProgram->CreateStandShader(ESS_SHADER_FLAT);
			//float vColor[] = { 1, 0, 1, 1 };
			//pShaderProgram->SetUniform("vColor", vColor);
			if (pShaderProgram)
			{
				pShaderProgram->Attach("shader/Reflection.vs", ST_VERTEX);
				pShaderProgram->Attach("shader/Reflection.ps", ST_FRAGMENT);
				pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				pShaderProgram->Link();

				int cubeUnit = 0;
				pShaderProgram->SetUniform("cubeMap", &cubeUnit);

				ICamera *pCam = m_pSceneParent->GetCamera();
				if (pCam)
				{
					IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
					if (pShaderProgram)
					{
						CMatrix4 mvpMat4 = GetAbsluateTransformation() * pCam->GetViewProjectionMatrix();;
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

							camInvMat4 = camInvMat4 * skyBoxInvMat4;
						}

						float normalMat3[] = { normalMat4.m[0], normalMat4.m[1], normalMat4.m[2],
							normalMat4.m[4], normalMat4.m[5], normalMat4.m[6],
							normalMat4.m[8], normalMat4.m[9], normalMat4.m[10] };
						pShaderProgram->SetUniform("mvpMatrix", mvpMat4.m);
						pShaderProgram->SetUniform("mvMatrix", mvMat4.m);
						pShaderProgram->SetUniform("normalMatrix", normalMat3);
						pShaderProgram->SetUniform("mInverseMatrix", camInvMat4.m);



					}
				}
			
			}
			
			float drho = (float)(3.141592653589) / (float)iStacks;
			float dtheta = 2.0f * (float)(3.141592653589) / (float)iSlices;
			float ds = 1.0f / (float)iSlices;
			float dt = 1.0f / (float)iStacks;
			float t = 1.0f;
			float s = 0.0f;
			int i, j;     // Looping variables

			CVector3 *maxVertexes = new CVector3[iSlices * iStacks * 6];
			CVector3 *maxNormals = new CVector3[iSlices * iStacks * 6];
			CVector2 *maxTexCoords = new CVector2[iSlices * iStacks * 6];
			int curCount = 0;

			for (i = 0; i < iStacks; i++)
			{
				float rho = (float)i * drho;
				float srho = (float)(sin(rho));
				float crho = (float)(cos(rho));
				float srhodrho = (float)(sin(rho + drho));
				float crhodrho = (float)(cos(rho + drho));

				// Many sources of OpenGL sphere drawing code uses a triangle fan
				// for the caps of the sphere. This however introduces texturing 
				// artifacts at the poles on some OpenGL implementations
				s = 0.0f;
				CVector3 vVertex[4];
				CVector3 vNormal[4];
				CVector2 vTexture[4];

				for (j = 0; j < iSlices; j++)
				{
					float theta = (j == iSlices) ? 0.0f : j * dtheta;
					float stheta = (float)(-sin(theta));
					float ctheta = (float)(cos(theta));

					float x = stheta * srho;
					float y = ctheta * srho;
					float z = crho;

					vTexture[0].x = s;
					vTexture[0].y = t;
					vNormal[0].x = x;
					vNormal[0].y = y;
					vNormal[0].z = z;
					vVertex[0].x = x * fRadius;
					vVertex[0].y = y * fRadius;
					vVertex[0].z = z * fRadius;

					x = stheta * srhodrho;
					y = ctheta * srhodrho;
					z = crhodrho;

					vTexture[1].x = s;
					vTexture[1].y = t - dt;
					vNormal[1].x = x;
					vNormal[1].y = y;
					vNormal[1].z = z;
					vVertex[1].x = x * fRadius;
					vVertex[1].y = y * fRadius;
					vVertex[1].z = z * fRadius;


					theta = ((j + 1) == iSlices) ? 0.0f : (j + 1) * dtheta;
					stheta = (float)(-sin(theta));
					ctheta = (float)(cos(theta));

					x = stheta * srho;
					y = ctheta * srho;
					z = crho;

					s += ds;
					vTexture[2].x = s;
					vTexture[2].y = t;
					vNormal[2].x = x;
					vNormal[2].y = y;
					vNormal[2].z = z;
					vVertex[2].x = x * fRadius;
					vVertex[2].y = y * fRadius;
					vVertex[2].z = z * fRadius;

					x = stheta * srhodrho;
					y = ctheta * srhodrho;
					z = crhodrho;

					vTexture[3].x = s;
					vTexture[3].y = t - dt;
					vNormal[3].x = x;
					vNormal[3].y = y;
					vNormal[3].z = z;
					vVertex[3].x = x * fRadius;
					vVertex[3].y = y * fRadius;
					vVertex[3].z = z * fRadius;

					for (int i = 0; i < 3; ++i)
					{
						maxVertexes[curCount] = vVertex[i];
						maxNormals[curCount] = vNormal[i];
						maxTexCoords[curCount] = vTexture[i];
						++curCount;
					}
					
					// Rearrange for next triangle
					memcpy(vVertex[0].v, vVertex[1].v, sizeof(CVector3));
					memcpy(vNormal[0].v, vNormal[1].v, sizeof(CVector3));
					memcpy(vTexture[0].v, vTexture[1].v, sizeof(CVector2));

					memcpy(vVertex[1].v, vVertex[3].v, sizeof(CVector3));
					memcpy(vNormal[1].v, vNormal[3].v, sizeof(CVector3));
					memcpy(vTexture[1].v, vTexture[3].v, sizeof(CVector2));

					for (int i = 0; i < 3; ++i)
					{
						maxVertexes[curCount] = vVertex[i];
						maxNormals[curCount] = vNormal[i];
						maxTexCoords[curCount] = vTexture[i];
						++curCount;
					}
					
				}
				t -= dt;
			}
			int bufferSize = sizeof(CVector3)* iSlices * iStacks * 6 * 2;// +sizeof(CVector2)* iSlices * iStacks * 6;
			IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(NULL, bufferSize, 0, iSlices * iStacks * 6, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			if (bufferObject)
			{
				bufferObject->BufferSubData(maxVertexes, sizeof(CVector3)* iSlices * iStacks * 6, 0);
				bufferObject->BufferSubData(maxNormals, sizeof(CVector3)* iSlices * iStacks * 6, sizeof(CVector3)* iSlices * iStacks * 6);
				//bufferObject->BufferSubData(maxTexCoords, sizeof(CVector2)* iSlices * iStacks * 6, sizeof(CVector3)* iSlices * iStacks * 6 * 2);
			}

			m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
			//m_pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 0, sizeof(CVector3)* iSlices * iStacks * 6);
			//m_pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 0, sizeof(CVector3)* iSlices * iStacks * 6 * 2);

			bufferObject->UnBind();

			if (m_pSceneParent)
			{
				ISkyBox *pSkyBox = m_pSceneParent->GetSkyBox();
				if (pSkyBox)
				{
					ITexture *pTexture = pSkyBox->GetTexture();
					if (pTexture)
						m_pRenderable->SetTexture(0, pTexture);
				}
			}


			m_pVAO->UnBind();

			delete[]maxVertexes;
			delete[]maxNormals;
			delete[]maxTexCoords;
		}

	}
}