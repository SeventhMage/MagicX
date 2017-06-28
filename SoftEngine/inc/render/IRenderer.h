#ifndef _SE_I_RENDERER_H_
#define _SE_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IRenderQueue.h"
#include "IMaterial.h"
#include "IRenderCell.h"
#include "IMesh.h"
#include "ITexture.h"
#include "VertexAttribute.h"

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
			virtual IRenderQueue *CreateRenderQueue(const char *material) = 0;
			virtual void DestroyRenderQueue(IRenderQueue *) = 0;
			virtual IRenderCell *CreateRenderCell(IMesh *pMesh, ITexture *pTexture, int materialId) = 0;
			virtual void DestroyRenderCell(IRenderCell *) = 0;		
			virtual void BufferData(ubyte *vertices,	//顶点数据
				uint size,								//顶点数据尺寸
				int count,								//顶点数量
				VertexFormat format						//顶点属性格式
				) = 0;
		};
	}

}

#endif