#include "scene/CMeshNode.h"
#include "scene/ICamera.h"
#include "scene/IScene.h"
#include "render/SColor.h"
#include "resource/IMesh.h"

namespace mx
{
	namespace scene
	{

		CMeshNode::CMeshNode(resource::IMesh *pMesh, render::IGPUBuffer *pBuffer)			
			:m_pMesh(pMesh)
			, m_pGPUBuffer(pBuffer)
		{
			SetPosition(pMesh->GetWorldPosition());
			for (uint i = 0; i < m_pMesh->GetTrianglesNum(); ++i)
			{
				CreatePLXRenderable(i);
			}
		}

		CMeshNode::~CMeshNode()
		{

		}

		void CMeshNode::UpdateImp(int elapsedTime)
		{
			if (m_pSceneParent)
			{
				ICamera *pCamera = m_pSceneParent->GetCamera();
				if (pCamera)
				{
					if (m_pMesh)
					{
						const CFrustum &frustum = pCamera->GetFrustum();
						CVector3 camPos;
						pCamera->GetViewMatrix().TransformVect(camPos, GetPosition());
						if (!frustum.CullSphere(camPos, m_pMesh->GetMaxRadius()))
						{
							SetActive(true);
							for (uint i = 0; i < m_pMesh->GetTrianglesNum(); ++i)
							{
								if (m_pRenderableObject[i])
								{
									render::IShaderProgram *shaderProgram = m_pRenderableObject[i]->GetShaderProgram();
									if (shaderProgram)
									{
										CMatrix4 modelMat4;
										modelMat4.SetTranslation(GetPosition());
										CMatrix4 mat4 = modelMat4 * pCamera->GetViewProjectionMatrix();
										shaderProgram->SetUniform("mvpMatrix", &mat4.m);
									}


								}
							}
						}
						else
						{
							SetActive(false);
						}
					}
				}

			}
		}

		void CMeshNode::RenderImp()
		{
			for (uint i = 0; i < m_pMesh->GetTrianglesNum(); ++i)
			{
				if (IsActive())
				{
					if (m_pRenderableObject[i])
					{						
						IBufferObject *bufferObject = m_pRenderableObject[i]->GetVertexBufferObject();
						if (bufferObject)
						{
							bufferObject->BufferData(m_pMesh->GetVertices(), sizeof(CVector3)* m_pMesh->GetVerticesNum());
						}
					}
				}
				m_pRenderableObject[i]->SetActive(IsActive());
			}			
		}

		void CMeshNode::CreatePLXRenderable(uint idx)
		{
			m_pRenderableObject.insert(m_pRenderableObject.end(), m_pGPUBuffer->CreateRenderableObject());
			resource::Triangle *triList = m_pMesh->GetTrianglesList();
			if (m_pRenderableObject[idx])
			{
				render::IShaderProgram *shaderProgram = m_pRenderableObject[idx]->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->CreateStandShader(ESS_SHADER_FLAT);					
					if (triList)
					{
						SColor color(triList[idx].color);
						float fColor[] = { color.GetRed() / 255.0f, color.GetGreen() / 255.0f, color.GetBlue() / 255.0f, color.GetAlpha() / 255.0f };
						shaderProgram->SetUniform("vColor", fColor);
					}
				}

				m_pGPUBuffer->Begin();
				m_pRenderableObject[idx]->CreateVertexBufferObject(m_pMesh->GetVertices(), sizeof(CVector3)* m_pMesh->GetVerticesNum(), 0, m_pMesh->GetVerticesNum(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				if (triList)
					m_pRenderableObject[idx]->CreateIndexBufferObject(triList[idx].indices, 3, RVT_UINT, m_pMesh->GetVerticesNum(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pGPUBuffer->EnableVertexAttrib(VAL_POSITION, 3, RVT_FLOAT, sizeof(CVector3), 0);
				m_pGPUBuffer->End();
			}
		}

	}
}