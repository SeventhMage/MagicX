#ifndef _SE_I_RENDERER_H_
#define _SE_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IRenderQueue.h"
#include "IMaterial.h"
#include "IRenderCell.h"
#include "IMesh.h"
#include "ITexture.h"
#include "VertexAttribute.h"
#include "IBuffer.h"
#include "SUniform.h"

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
			virtual IRenderCell *CreateRenderCell(uint materialId, IMesh *pMesh, uint textureId) = 0;
			virtual void DestroyRenderCell(IRenderCell *) = 0;		
			virtual uint CreateBuffer() = 0;
			virtual void DestroyBuffer(uint bufferId) = 0;
			virtual void BufferData(uint bufferId,
				ubyte *vertices,						//顶点数据				
				uint vertSize,							//顶点数据尺寸
				int count,								//顶点数量
				VertexFormat format,					//顶点属性格式
				ubyte *indices,							//索引数据
				uint indicesSize						//索引数据尺寸
				) = 0;			
	
			virtual void SubmitRenderCell(IRenderCell *pCell) = 0;

			virtual void Clear() = 0;
			virtual void Render() = 0;
			virtual void Render(IShaderProgram *pShaderProgram, uint materialId, uint bufferId, uint textureId) = 0;						
		};
	}

}

#endif