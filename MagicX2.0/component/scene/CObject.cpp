#include "CObject.h"
#include "core/CMatrix4.h"
#include <assert.h>

namespace mx
{
	namespace scene
	{		

		CObject::CObject()
			:m_pMesh(0)
		{

		}

		CObject::~CObject()
		{

		}

		void CObject::CreateRenderableObject(IRenderer *renderer)
		{
			assert(renderer);
			uint stride = m_pMesh->GetVertexStride();
			IGPUBuffer *buffer = renderer->CreateGPUBuffer(stride);
			if (buffer)
			{
				IRenderableObject *renderableObject = buffer->CreateRenderableObject();
				if (renderableObject)
				{
					IShaderProgram *shaderProgram = renderableObject->GetShaderProgram();
					if (shaderProgram)
					{
						shaderProgram->CreateStandShader(ESS_SHADER_SHADED);
						core::CMatrix4 mat4;
						shaderProgram->SetUniform("mvpMatrix", &mat4.m);
					}

					buffer->Begin();
					buffer->CreateVertexBuffer(renderableObject, m_pMesh->GetVerticesData(), m_pMesh->GetVerticesSize(), 0, m_pMesh->GetVerticesCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
					buffer->CreateIndexBuffer(renderableObject, m_pMesh->GetIndicesData(), m_pMesh->GetIndicesCount(), RVT_UINT, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
					buffer->EnableVertexAttrib(VAL_POSITION, 4, RVT_FLOAT, 0);
					buffer->EnableVertexAttrib(VAL_COLOR, 4, RVT_FLOAT, sizeof(float) * 4);

					buffer->End();
				}

			}
		}

	}
}