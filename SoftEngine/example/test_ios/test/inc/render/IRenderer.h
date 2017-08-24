#ifndef _SE_I_RENDERER_H_
#define _SE_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IRenderQueue.h"
#include "IMaterial.h"
#include "IRenderCell.h"
#include "IMesh.h"
#include "ITexture.h"
#include "IBuffer.h"
#include "base/base.h"


namespace se
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){}
			virtual IRenderDriver *GetRenderDriver() = 0;
			virtual RenderDriverType GetRenderDriverType() = 0;
			virtual IRenderCell *CreateRenderCell(uint bufferId, uint materialId, uint textureId) = 0;
			virtual void DestroyRenderCell(IRenderCell *) = 0;		
			virtual uint CreateBuffer() = 0;
			virtual void DestroyBuffer(uint bufferId) = 0;		
			virtual void BufferData(uint bufferId, base::Vertices *pVertices, base::Indices *pIndeces = nullptr) = 0;
			virtual void SubmitRenderCell(IRenderCell *pCell) = 0;
			virtual IShaderProgram *CreateShaderProgram() = 0;
			virtual void DestroyShaderProgram(IShaderProgram *) = 0;

			virtual void Clear() = 0;
			virtual void Render() = 0;
			virtual void Render(IShaderProgram *pShaderProgram, uint materialId, uint bufferId, uint textureId) = 0;						
		};
	}

}

#endif