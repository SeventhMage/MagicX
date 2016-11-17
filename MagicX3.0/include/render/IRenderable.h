/************************************************************************/
/* 每个renderable存储了对渲染器的一次提交                               */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERABLE_H_
#define _MX_RENDER_I_RENDERABLE_H_

#include "IBufferObject.h"
#include "ERender.h"
#include "IShaderProgram.h"
#include "ITexture.h"

namespace mx
{
	namespace render
	{
		class IRenderable
		{
		public:
			virtual ~IRenderable(){}
		
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage) = 0;

			virtual IBufferObject *GetVertexBufferObject() = 0;
			virtual IBufferObject *GetIndexBufferObject() = 0;

			virtual IShaderProgram *GetShaderProgram() = 0;

			//设置纹理
			virtual void SetTexture(int slot, ITexture *pTexture) = 0;

			//提交数据到渲染队列
			virtual void SumbitToRenderList() = 0;
			virtual void RemoveFromRenderList() = 0;
			//绑定当前数据, 使渲染程序知道正在处理的是谁
			virtual void Bind() = 0;
			//解绑
			virtual void UnBind() = 0;

			//渲染属性
			virtual void Enable(RenderAttribute attr) = 0;
			virtual void Disable(RenderAttribute attr) = 0;
			virtual bool IsEnabled(RenderAttribute attr) = 0;
		};
	}
}

#endif